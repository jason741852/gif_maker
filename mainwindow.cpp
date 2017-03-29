#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "mpg (*.mpg)");

    QMessageBox::information(this,tr("File Name"), filename);

    std::string vPath = filename.toLocal8Bit().constData();

    cv::VideoCapture cap(vPath);

    video_bitstream_read(cap);

    video_playback_test(cap);

    video_decode(vPath);

}
