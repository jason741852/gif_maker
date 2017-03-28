#include "helper.h"

void video_playback_test (cv::VideoCapture& cap){
    if (!cap.isOpened())
    {
        QTextStream(stdout) << "Failed to open file" << endl;
    }

    cv::Mat frame;
    for(;;){
        // Runs until out of frame
        if (!cap.read(frame))
            break;

        cv::imshow("window", frame);

        char key = cvWaitKey(10);
        if (key == 27) // ESC
            break;
    }
}


void video_bitstream_read (cv::VideoCapture& cap){
    if (!cap.isOpened())
    {
        QTextStream(stdout) << "Failed to open file" << endl;
    }

    cv::Mat frame;

    cap.read(frame);
    int ex = cap.get(CV_CAP_PROP_FOURCC);
    char EXT[] = {(char)(ex & 0XFF),(char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24),0};
    QTextStream(stdout)<<EXT<<endl;




    cv::imshow("window", frame);
    QTextStream(stdout) << "frame size: " << frame.rows << " x " << frame.cols << endl;
//    for(int i=0; i< frame.rows; i++){
//        for(int j=0; j< frame.cols; j++){
//            QTextStream(stdout) << frame.at<uchar>(i,j)<<" ";
//        }
//        QTextStream(stdout) << ""<< endl;
//    }

    //double frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
    //QTextStream(stdout) << "frame count: " << frameCount << endl;



}
