#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Batch avs and vs script creation tool");

    fileType = ".avs";

    fileTypeGroup = new QButtonGroup();
    fileTypeGroup->addButton(ui->avs, 0);
    fileTypeGroup->addButton(ui->vs, 1);
    ui->avs->setChecked(true);
    ui->scriptContent->setPlainText(
                           "SetWorkingDir(\"C:\\Program Files (x86)\\AviSynth 2.5\\plugins\\\")\r\n"
                           "LoadPlugin(\"ffms2.dll\")\r\n"
                           "FFVideoSource(\"%1\", fpsnum=24000, fpsden=1001, threads=1)\r\n"
                       );

    connect(ui->selectFile, SIGNAL(clicked()), this, SLOT(selectFiles()));
    connect(ui->avs, SIGNAL(clicked()), this, SLOT(setOutputFileType()));
    connect(ui->vs, SIGNAL(clicked()), this, SLOT(setOutputFileType()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(save()));

    initStyle();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initStyle() {
    QString styleData = "QRadioButton {"
                        "   text-align: center;"
                        "}";
    this->setStyleSheet(styleData);
}

void MainWindow::save() {
    QString script_content = ui->scriptContent->toPlainText();
    if(ui->fileList->text().size() < 1) {
        QMessageBox::warning(NULL, "Warning", "No File Selected");
        return;
    }
    if(script_content.indexOf("%1") < 0) {
        QMessageBox::warning(NULL, "Forget setting the video file location", "Please put %1 in the location where is the input");
        return;
    }
    QStringList files = ui->fileList->text().split(";");
    for(QString scriptFile : files) {
        QFile script(scriptFile + fileType);
        if(script.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&script);
            stream.setCodec("utf-8");
            stream.setGenerateByteOrderMark(true);
            stream << script_content.arg(scriptFile).replace("/", "\\") << endl;
        }
        script.close();
    }
    QMessageBox::information(NULL, "Infomation", "Scripts created");
}

void MainWindow::setOutputFileType() {
    outputFileType = fileTypeGroup->checkedId();
    switch(outputFileType) {
        case 0:
            fileType = ".avs";
            break;
        case 1:
            fileType = ".vpy";
            break;
        default:
            break;
    }
}

void MainWindow::selectFiles() {
    QStringList videoFiles = QFileDialog::getOpenFileNames(this,tr("Video files"),
                                                           QDir::currentPath(),
                                                           tr("Video files(*.mp4 *.mkv *.m2ts *.ts);;All files (*.*)"));
    if(videoFiles.isEmpty()) return;
    QString files = "";
    for(QString filename : videoFiles)
        files += filename + ";";
    files = files.mid(0, files.size() - 1);
    ui->fileList->setText(files);

}
