#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup *fileTypeGroup;
    int outputFileType;
    QString fileType;
    void initStyle();

private slots:
    void save();
    void setOutputFileType();
    void selectFiles();
};

#endif // MAINWINDOW_H
