#ifndef HELPER_H
#define HELPER_H

#include "mainwindow.h"
#include "gif_maker.h"

struct gif;

bool gifHeader(gif* Gif);

void video_playback_test (cv::VideoCapture& cap);

void video_bitstream_read (cv::VideoCapture& cap);

void video_decode(std::string filePath);

#endif // HELPER_H
