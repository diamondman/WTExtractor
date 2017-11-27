#include <QtWidgets/QMainWindow>
#include <QStringListModel>
#include "pwt_decode.h"
#include "wld3_extract.h"

namespace Ui {
  class MainWindow;
}

class FrameTreeModel;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(const QString& modelFilePath);
  virtual ~MainWindow();

 public slots:
  void onSelectedFrameChange(const QModelIndex &current, const QModelIndex &previous);

 private:
  void setWTMetaLabel(WLD3* wt);
  void setPWTMetaLabel();

  PWT* pwt;
  Ui::MainWindow *ui;
  FrameTreeModel* treeModel;
  QStringListModel* textureListModel;
  void setFrameDataLabel(const PWT_Frame* frame);
  void setVisualsDataLabel(const PWT_Visuals* visuals);
};
