#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Link all opencv files
#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <helper.h>



// Because these are written in C, not C++
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/common.h>
    #include <libswresample/swresample.h>
    #include <libavutil/avutil.h>
    #include <libavutil/imgutils.h>
//    #include <libavcodec/gif.h>
//    #include <libavcodec/gif.c>
    #include <libswscale/swscale.h>
}

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include <Magick++.h>
//#include <ImageMagick-6/Magick++/Blob.h>
//#include <ImageMagick-6/Magick++/ChannelMoments.h>
//#include <ImageMagick-6/Magick++/CoderInfo.h>
//#include <ImageMagick-6/Magick++/Color.h>
//#include <ImageMagick-6/Magick++/Drawable.h>
//#include <ImageMagick-6/Magick++/Exception.h>
//#include <ImageMagick-6/Magick++/Functions.h>
//#include <ImageMagick-6/Magick++/Geometry.h>
//#include <ImageMagick-6/Magick++/Image.h>
//#include <ImageMagick-6/Magick++/Include.h>
//#include <ImageMagick-6/Magick++/Montage.h>
//#include <ImageMagick-6/Magick++/Pixels.h>
//#include <ImageMagick-6/Magick++/TypeMetric.h>
//#include <ImageMagick-6/Magick++/ResourceLimits.h>
//#include <ImageMagick-6/Magick++/STL.h>

//#include "ImageMagick-6/magick/magick-config.h"
//#include <ImageMagick-6/Magick++/Include.h>
//#include <ImageMagick-6/Magick++/Functions.h>
//#include <ImageMagick-6/Magick++/Image.h>
//#include <ImageMagick-6/Magick++/Pixels.h>
//#include <ImageMagick-6/Magick++/ResourceLimits.h>
//#include <ImageMagick-6/Magick++/STL.h>

#include <libaec.h>
#include <gif_lib.h>
#include <list>

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
