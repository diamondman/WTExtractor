#include <QtWidgets/QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QMessageBox>
#include <QTextStream>

#include "MainWindow.h"

void showerr(QString errmsg){
  QTextStream err(stderr);
  err << errmsg << endl;
  QMessageBox msgBox;
  msgBox.setText(errmsg);
  msgBox.exec();
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QApplication::setApplicationName("PWT/WT Model Viewer");
  //QApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("3d Model view for Wild Tangent Web Driver WT/PWT model format.");
  parser.addHelpOption();
  //parser.addVersionOption();
  parser.addPositionalArgument("modelfile", "The PWT/WT model file to view.");

  parser.process(app);

  const QStringList posargs = parser.positionalArguments();
  if(posargs.isEmpty()){
    showerr("This program must be invoked with a file provided as the first "
            "argument, but none was found.");
    return -1;
  }
  if(posargs.size() > 1){
    showerr("Too many file paths provided; only one is supported.");
    return -2;
  }

  QFileInfo modelfile(posargs.first());
  if(!modelfile.exists()){
    showerr("The specified file \"" + modelfile.absoluteFilePath() + "\" does not exist.");
    return -3;
  }
  if(!modelfile.isFile()){
    showerr("The specified file \"" + modelfile.absoluteFilePath() + "\" exists but is not a file.");
    return -4;
  }
  if(!modelfile.isReadable()){
    showerr("The specified file \"" + modelfile.absoluteFilePath() + "\" can not be read.");
    return -5;
  }
  QString suffix = modelfile.completeSuffix().toLower();
  if(suffix != "wt" && suffix != "pwt"){
    showerr("The specified file \"" + modelfile.absoluteFilePath() + "\" can not be read.");
    return -6;
  }

  MainWindow window(posargs.first());
  window.show();

  return app.exec();
}
