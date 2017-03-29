#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Link all opencv files
#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <helper.h>



// Because these are written in C, not C++
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/common.h>
    #include <libswresample/swresample.h>
    #include <libavutil/avutil.h>
    #include <libswscale/swscale.h>
}

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
