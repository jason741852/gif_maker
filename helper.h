#ifndef HELPER_H
#define HELPER_H

#include "mainwindow.h"

void video_playback_test (cv::VideoCapture& cap);

void video_bitstream_read (cv::VideoCapture& cap);

void video_decode(std::string filePath);

//void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);

#endif // HELPER_H
