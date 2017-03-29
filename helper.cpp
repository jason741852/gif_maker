#include "helper.h"

#define INBUF_SIZE 4096


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

    double frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
    QTextStream(stdout) << "frame count: " << frameCount << endl;

}

/* Routine to decode mpeg-1 encoded video */
void video_decode(std::string filePath){
    av_register_all();





    AVCodec* codec;
    AVCodecContext* c = NULL;
    int frame, got_picture, len;
    FILE* f;
    AVFrame *picture;
    uint8_t inbuf[INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];

    char buf[1024];
    AVPacket avpkt;

    av_init_packet(&avpkt);
    memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);

    QTextStream(stdout)<< "Video decoding..."<< endl;

    // Find mpeg-1 docoder
    codec = avcodec_find_decoder(AV_CODEC_ID_MPEG2VIDEO);

    if(!codec){
        QTextStream(stdout)<< "Codec not found"<< endl;
    }

    c = avcodec_alloc_context3(codec);
    picture = avcodec_alloc_frame();

}


