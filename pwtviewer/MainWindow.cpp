#include <string>
#include <sstream>
#include <iomanip>
#include <QFileInfo>

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "FrameTreeModel.h"

#include "dataaccessors.h"

#include <iostream>

MainWindow::MainWindow(const QString& modelFilePath)
  : QMainWindow(), pwt(0), ui(new Ui::MainWindow), textureListModel(new QStringListModel(this)) {
  ui->setupUi(this);
  ui->splitter->setSizes(QList<int> {200, 500}); //TODO: FIX HACK
  ui->listViewModelTexture->setModel(textureListModel);
  ui->groupBoxFrameMeta->hide();
  ui->groupBoxVisualsMeta->hide();
  ui->groupBoxModelTextures->hide();

  QFileInfo modelFileInfo(modelFilePath);
  std::string pathstr = modelFilePath.toStdString();
  DataAccessor* acc = openFileAccessor(pathstr.c_str());

  WLD3* wt = 0;

  if(modelFileInfo.completeSuffix().toLower() == "wt") {
    wt = wld3_extract(acc);
    freeFileAccessor(acc);
    acc = openBufferAccessor(wt->payload_data, wt->payload_len);

    setWTMetaLabel(wt);
  }

  pwt = pwt_extract(acc);
  setPWTMetaLabel();

  treeModel = new FrameTreeModel(pwt);
  ui->modelFrameTree->setModel(treeModel);
  ui->modelFrameTree->expandAll();
  connect(ui->modelFrameTree, SIGNAL(onSelectedFrameChange(const QModelIndex, const QModelIndex)),
          this, SLOT(onSelectedFrameChange(const QModelIndex, const QModelIndex)) );

  if(wt) {
    freeBufferAccessor(acc);
    wld3_free(wt);
  } else {
    freeFileAccessor(acc);
  }
}

MainWindow::~MainWindow(){
  pwt_free(pwt); //Doesn't rely on acc after pwt_extract finishes
  if(model)
    delete treeModel;
  if(textureListModel)
    delete textureListModel;
  delete ui;
}

void MainWindow::onSelectedFrameChange(const QModelIndex &current, const QModelIndex &previous) {
  const PWT_Frame* frame = treeModel->getFrameFromTreeSelection(current);

  setFrameDataLabel(frame);
  ui->groupBoxFrameMeta->show();

  //Visual Metadata
  QStringList texlist;
  if(frame->has_visuals){
    for(int i = 0; i < frame->visuals->texture_count; i++)
      texlist << frame->visuals->texture_paths[i];
    ui->groupBoxVisualsMeta->show();
    ui->groupBoxModelTextures->show();
    setVisualsDataLabel(frame->visuals);
  } else {
    ui->groupBoxVisualsMeta->hide();
    ui->groupBoxModelTextures->hide();
    ui->labelVisualsData->setText("");
  }
  textureListModel->setStringList(texlist);
}

void MainWindow::setWTMetaLabel(WLD3* wt){
  std::stringstream ss;
  char uuid_str[37];
  struct tm* timeinfo;

  ss << "<table>";
  ss << "<tr><td><b>Copyright:</b></td><td>" << wt->copyright << "</td></tr>";

  timeinfo = localtime(&wt->createddate);
  ss << "<tr><td><b>CREATED:</b></td><td>" << asctime(timeinfo) << "</td></tr>";
  ss << "<tr><td><b>VALIDD:</b></td><td>";
  if(wt->startvaliedate == 0)
    ss << "NONE</td></tr>";
  else {
    timeinfo = localtime(&wt->startvaliedate);
    ss << asctime(timeinfo) << "</td></tr>";
  }
  timeinfo = localtime(&wt->expiredate);
  ss << "<tr><td><b>EXPIRED:</b></td><td>" << asctime(timeinfo) << "</td></tr>";

  uuid_unparse(wt->wtversionUUID, uuid_str);
  ss << "<tr><td><b>WTVerUUID:</b></td><td>" << uuid_str << "</td></tr>";
  uuid_unparse(wt->resourceUUID, uuid_str);
  ss << "<tr><td><b>ResUUID:</b></td><td>" << uuid_str << "</td></tr>";
  ss << "<tr><td><b>LicenseType:</b></td><td>" << wt->licensetype << "</td></tr>";
  ss << "<tr><td><b>Comment:</b></td><td>" << (wt->comment==0? "":wt->comment) << "</td></tr>";
  ss << "<tr><td><b>EncodeVersion:</b></td><td>" << wt->encodeversion << "</td></tr>";
  ss << "<tr><td><b>OutExt:</b></td><td>" << wt->outext << "</td></tr>";
  ss << "<tr><td><b>CabCompressed:</b></td><td>" << (wt->cabcompression? "true":"false") << "</td></tr>";
  ss << "<tr><td><b>PayloadLen:</b></td><td>" << wt->payload_len << "</td></tr>";

  if(wt->urls){
    ss << "<tr><td><b>URLS:</b></td><td>";
    ExtraStringLL* url = wt->urls;
    while(url){
      ss << "<b>Type:</b> 0x" << std::setfill('0') << std::setw(2) << std::hex << url->type << ";";
      ss << "<b>Val:</b> \"" << url->buff << "\";";
      ss << "(" << url->always300_0 << ", " << url->always300_1 << ")<br/>";
      url = url->next;
    }
    ss << "</td></tr>";
  }

  ss << "</table>";

  std::string fmtmsg = ss.str();
  ui->labelWTData->setText(QString::fromStdString(fmtmsg));
}

void MainWindow::setPWTMetaLabel() {
  std::stringstream ss;
  if(pwt){
    ss << "<table>";
    ss << "<tr><td><b>MIN:</b></td><td>{" <<
      pwt->global_min.X << ", " << pwt->global_min.Y << ", " << pwt->global_min.Z << "}</td></tr>";
    ss << "<tr><td><b>MAX:</b></td><td>{" <<
      pwt->global_max.X << ", " << pwt->global_max.Y << ", " << pwt->global_max.Z << "}</td></tr>";

    ss << "<tr><td><b>VeryClose:</b></td><td>" << pwt->veryclose << "</td></tr>";
    ss << "<tr><td><b>PrettyClose:</b></td><td>" << pwt->prettyclose << "</td></tr>";

    ss << "<tr><td><b>IncVertices:</b></td><td>" << pwt->dowrite_vertices << "</td></tr>";
    ss << "<tr><td><b>IncNormals:</b></td><td>" << pwt->dowrite_normals << "</td></tr>";
    ss << "<tr><td><b>VtexAccuracy:</b></td><td>" << pwt->vertex_bit_accuracy << "</td></tr>";
    ss << "<tr><td><b>VtexAccuracy1:</b></td><td>" << pwt->vertex_bit_accuracy_1 << "</td></tr>";
    ss << "<tr><td><b>NormAccuracy:</b></td><td>" << pwt->normal_bit_accuracy << "</td></tr>";
    ss << "<tr><td><b>unk_f44:</b></td><td>" << pwt->unk_f44 << "</td></tr>";
    ss << "<tr><td><b>unk_f48:</b></td><td>" << pwt->unk_f48 << "</td></tr>";
    ss << "<tr><td><b>VertexCount:</b></td><td>" << pwt->vertex_count << "</td></tr>";
    ss << "<tr><td><b>NormalCount:</b></td><td>" << pwt->normal_count << "</td></tr>";
    ss << "<tr><td><b>FaceCount:</b></td><td>" << pwt->face_count << "</td></tr>";
    ss << "<tr><td><b>unk_v40:</b></td><td>" << pwt->unk_f40 << "</td></tr>";
  }else{
    ss << "PWT struct is null.";
  }

  std::string fmtmsg = ss.str();
  ui->labelPWTData->setText(QString::fromStdString(fmtmsg));
}

void MainWindow::setFrameDataLabel(const PWT_Frame* frame) {
  std::stringstream ss;
  ss << "<table>";

  ss << "<tr><td><b>Name:</b></td><td>" << (frame->name?frame->name:"<null>") << "</td></tr>";
  ss << "<tr><td><b>Matrix:</b></td><td>{"
     << frame->transform_matrix[0] << " " << frame->transform_matrix[1] << " "
     << frame->transform_matrix[2] << " " << frame->transform_matrix[3] << "<br>"
     << frame->transform_matrix[4] << " " << frame->transform_matrix[5] << " "
     << frame->transform_matrix[6] << " " << frame->transform_matrix[7] << "<br>"
     << frame->transform_matrix[8] << " " << frame->transform_matrix[9] << " "
     << frame->transform_matrix[10] << " " << frame->transform_matrix[11] << "<br>"
     << frame->transform_matrix[12] << " " << frame->transform_matrix[13] << " "
     << frame->transform_matrix[14] << " " << frame->transform_matrix[15] << "}</td></tr>";
  ss << "<tr><td><b>HasAnimation:</b></td><td>" << frame->has_animation << "</td></tr>";
  ss << "<tr><td><b>HasVisuals:</b></td><td>" << frame->has_visuals << "</td></tr>";

  ss << "<tr><td><b>SubFrameCount</b></td><td>" << frame->subframe_count << "</td></tr>";

  if(frame->has_animation){
    ss << "<tr><td><b>AnimationCount:</b></td><td>" <<
      "0x" << std::setfill('0') << std::setw(8) << std::hex << frame->animation_count << "</td></tr>";
    ss << "<tr><td><b>AnimationD3DOptions:</b></td><td>" << frame->animation_d3d_options << "</td></tr>";
  }

  ss << "</table>";

  std::string fmtmsg = ss.str();
  ui->labelFrameData->setText(QString::fromStdString(fmtmsg));
}

void MainWindow::setVisualsDataLabel(const PWT_Visuals* visuals) {
  std::stringstream ss;
  ss << "<tr><td><b>VisualsVCOUNT:</b></td><td>" << visuals->vcount << "</td></tr>";
  ss << "<tr><td><b>VisualsNCOUNT:</b></td><td>" << visuals->ncount << "</td></tr>";
  ss << "<tr><td><b>VisualsFCOUNT:</b></td><td>" << visuals->fcount << "</td></tr>";

  ss << "<tr><td><b>VertexCount:</b></td><td>" << visuals->vertex_count << "</td></tr>";
  ss << "<tr><td><b>VertexCompCount:</b></td><td>" << visuals->vertexcomp_count << "</td></tr>";

  ss << "<tr><td><b>bboxMIN:</b></td><td>{"
     << visuals->bboxmin.X << ", " << visuals->bboxmin.Y << ", " << visuals->bboxmin.Z
     << "}</td></tr>";

  ss << "<tr><td><b>unusedbits:</b></td><td>{"
     << (unsigned int)visuals->unused_vbits_x << ", "
     << (unsigned int)visuals->unused_vbits_y << ", "
     << (unsigned int)visuals->unused_vbits_z
     << "}</td></tr>";

  ss << "<tr><td><b>NormalCount:</b></td><td>" << visuals->normal_count << "</td></tr>";
  ss << "<tr><td><b>NormalCompCount:</b></td><td>" << visuals->normalcomp_count << "</td></tr>";

  ss << "<tr><td><b>NormbboxMIN:</b></td><td>{"
     << visuals->norm_bboxmin.X << ", " << visuals->norm_bboxmin.Y << ", " << visuals->norm_bboxmin.Z
     << "}</td></tr>";
  ss << "<tr><td><b>NormbboxMAX:</b></td><td>{"
     << visuals->norm_bboxmax.X << ", " << visuals->norm_bboxmax.Y << ", " << visuals->norm_bboxmax.Z
     << "}</td></tr>";

  ss << "<tr><td><b>Normunusedbits:</b></td><td>{"
     << (unsigned int)visuals->unused_nbits_x << ", "
     << (unsigned int)visuals->unused_nbits_y << ", "
     << (unsigned int)visuals->unused_nbits_z
     << "}</td></tr>";

  ui->labelVisualsData->setText(QString::fromStdString(ss.str()));
}
