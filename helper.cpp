#include "helper.h"

#define INBUF_SIZE 4096


struct gif{
    FILE* f;
    uint8_t* frame;
};
typedef struct gif gif;

bool gifHeaderDescriptor(gif *Gif, uint32_t frame_width, uint32_t frame_height){
    const char* filename = "test.gif";
    Gif->f = fopen(filename,"wb");

    // signature
    fputs("GIF89a", Gif->f);

    // screen descriptor
    fputc(frame_width & 0xff, Gif->f);
    fputc((frame_width >> 8) & 0xff, Gif->f);
    fputc(frame_height & 0xff, Gif->f);
    fputc((frame_height >> 8) & 0xff, Gif->f);

    fputc(0xf0, Gif->f);  // there is an unsorted global color table of 2 entries
    fputc(5, Gif->f);     // background color
    fputc(0, Gif->f);     // pixels are square (we need to specify this because it's 1989)

    // now the "global" palette (really just a dummy palette)
    // color 0: black
    fputc(255, Gif->f);
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    // color 1: also black
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    fputc(255, Gif->f);

    // animation header
    fputc(0x21, Gif->f); // extension introducer
    fputc(0xf9, Gif->f); // graphic control label
    fputc(11, Gif->f); // length 11
    fputs("NETSCAPE2.0", Gif->f); // yes, really
    fputc(3, Gif->f); // 3 bytes of NETSCAPE2.0 data

    fputc(1, Gif->f); // JUST BECAUSE
    fputc(0, Gif->f); // loop infinitely (byte 0)
    fputc(0, Gif->f); // loop infinitely (byte 1)

    fputc(0, Gif->f); // block terminator



    fclose(Gif->f);

    return true;
}



// Routine to add frame to the gif file
bool addFrame(gif *Gif, uint32_t frame_width, uint32_t frame_height){
    // Use ASCII / Hex code
    // Hex code is shown in text editor
    // image descriptor
    const char* filename = "test.gif";
    Gif->f = fopen(filename,"a+"); // append

    fputc(0x2c, Gif->f);
    // Image Left
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    fputc(0, Gif->f);

    // Image Top
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    fputc(0, Gif->f);
    fputc(0, Gif->f);

    // Image width
    fputc(frame_width & 0xff, Gif->f);
    fputc((frame_width >> 8) & 0xff, Gif->f);

    // Image height
    fputc(frame_height & 0xff, Gif->f);
    fputc((frame_height >> 8) & 0xff, Gif->f);

    // Packet field with LCT flag, Interlace flag, Sort flag, Reserve, Size of LCT (total 8 bits
    fputc(0, Gif->f);
    fputc(0, Gif->f);

    // LCT?


    // LZW compression for image data



    fclose(Gif->f);

    return true;

}



// Routine to close gif file
bool closeGif(gif *gif_maker){

}




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
    AVFormatContext *pFormatCtx = NULL;

    const char* Path = filePath.c_str();
    if(avformat_open_input(&pFormatCtx, Path, NULL, NULL) != 0){
        QTextStream (stdout) << "Cannot open file" << endl;
    }
    else{
        QTextStream (stdout) << "File open successful" << endl;
    }

    if(avformat_find_stream_info(pFormatCtx, NULL) < 0){
        QTextStream (stdout) << "Cannot find video info" << endl;
    }
    else{
        // Print video info on screen
        av_dump_format(pFormatCtx, 0, Path, 0);
    }

    unsigned int i;
    AVCodecContext *pCodecCtxOrig = NULL;
    AVCodecContext *pCodecCtx = NULL;
    QTextStream(stdout) << "Codec Name is " << pFormatCtx->streams[0]->codecpar->height << endl;


    unsigned int videoStream = -1;

    for(i=0; i<pFormatCtx->nb_streams; i++){
        if(pFormatCtx->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO){
            videoStream = i;

            QTextStream(stdout) << "i= " << i << endl;
            break;
        }

    }
    if(videoStream == -1){
        QTextStream(stdout) << "Cannot find video stream" << endl;
        exit(0);
    }
    else{
        QTextStream(stdout) << "Video stream found at i= " <<videoStream << endl;

    }

    pCodecCtxOrig=pFormatCtx->streams[videoStream]->codec;

    QTextStream(stdout) << "Frame size check: " << pCodecCtxOrig->width << " "<< pCodecCtxOrig->height << endl;
    AVCodec *pCodec = NULL;

    // Find decoder
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec == NULL){
        QTextStream(stdout) << "Cannot find codec for this video type" << endl;
        exit(0);
    }
    else{
        QTextStream(stdout) << "Codec found " << pCodec<< endl;

    }

    // Memory allocations
    pCodecCtx = avcodec_alloc_context3(pCodec);

    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig)!=0){
        QTextStream(stdout) << "Cannot copy codec" << endl;
        exit(0);
    }

    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, NULL)<0){
        exit(0);
    }

    // Storing data
    AVFrame *pFrame = NULL;
    pFrame = av_frame_alloc();

    AVFrame *pFrameRGB;
    pFrameRGB = av_frame_alloc();

    uint8_t* buffer = NULL;
    int numBytes;
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    buffer=(uint8_t*)av_malloc(numBytes*sizeof(uint8_t));


    avpicture_fill((AVPicture*)pFrameRGB, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

    // Storing data //
    struct SwsContext *sws_ctx = NULL;
    int frameFinished;
    AVPacket packet;

    QTextStream(stdout) << "Frame size check: " << pCodecCtx->width << " "<< pCodecCtx->height << endl; // working

    sws_ctx = sws_getContext(    pCodecCtx->width,
                                 pCodecCtx->height,
                                 pCodecCtx->pix_fmt,
                                 pCodecCtx->width,
                                 pCodecCtx->height,
                                 AV_PIX_FMT_RGB24,
                                 SWS_BILINEAR,
                                 NULL,
                                 NULL,
                                 NULL
                                 );

    i = 0;
    QTextStream(stdout)<< "number of channels: " << pCodecCtx->channels << endl;
    QTextStream(stdout)<< "uint32 width test: " << (uint32_t) pCodecCtx->width <<endl;

    // TODO: convert to gif frame by frame here
    // Init gif Structure and header
    gif* g = new gif;
    gifHeaderDescriptor(g, (uint32_t) pCodecCtx->width, (uint32_t) pCodecCtx->height);






    AVCodec* outCodec;
    AVCodecContext* outC = NULL;
    AVFrame* outFrame;
    AVPacket outPacket;

    outCodec = avcodec_find_encoder(AV_CODEC_ID_GIF);
    if (!outCodec) {
            QTextStream(stdout) << "Codec not found" << endl;
            exit(1);
    }

    outC = avcodec_alloc_context3(outCodec);
    if(!outC){
        QTextStream(stdout) << "Codec alloc error" << endl;
        exit(1);
    }

//    outC->bit_rate = pCodecCtx->bit_rate;
//    outC->width = pCodecCtx->width;
//    outC->height = pCodecCtx->height;
//    outC->pix_fmt = AV_PIX_FMT_YUV420P;

////    gif_encode_init();

//    GifFileType* gifFile = DGifOpenFileName("test.gif",NULL);
//////////////////
//    const char* outputFile = "testing.gif";
//    AVOutputFormat* avoutputFormat;
//    AVFormatContext* avformatContext;
//    AVStream* avstream;
//    AVFrame* outFrame;
//    AVCodec* outCodec;
//    AVCodecContext* outC;
//    AVPacket outPkt;
//    int x, y;
//    int ret;
//    int output;
//    int write_ret;
//    //////////////////////////

//    avoutputFormat = av_guess_format(NULL, outputFile, NULL);
//    if(!avoutputFormat){
//        QTextStream(stdout) << "Cannot guess format error" << endl;
//        exit(1);
//    };

//    QTextStream(stdout) << "Format name: " << avoutputFormat->name << endl;
//    QTextStream(stdout) << "Format codec: " << avoutputFormat->video_codec << endl; // GIF = 98

//    avformatContext = avformat_alloc_context();

//    avformatContext->oformat = avoutputFormat;

//    snprintf(avformatContext->filename, sizeof(avformatContext->filename), "%s", outputFile);

//    outCodec = avcodec_find_encoder(avoutputFormat->video_codec);

//    avstream = avformat_new_stream(avformatContext, outCodec);
//    if (!avstream) {
//        QTextStream(stdout) << "stream error" << endl;
//        exit(1);
//    }
//    if(avstream->codec==NULL){
//        QTextStream(stdout) << "stream NULL" << endl;
//        exit(1);
//    }

//    outC = avstream->codec;

//    outC->bit_rate = 40000;
//    outC->width = pCodecCtx->width;
//    outC->height = pCodecCtx->height;
//    outC->pix_fmt = AV_PIX_FMT_RGB8;


    ///////////////////////////////////////////////

//    outFrame = av_frame_alloc();
//    outFrame->width = outC->width;
//    outFrame->height = outC->height;
//    outFrame->format =  outC->pix_fmt;

//    ret = av_image_alloc(outFrame->data, outFrame->linesize, outC->width, outC->height, outC->pix_fmt, 4);

//    if(ret<0){
//        QTextStream(stdout) << "Cannot allocate image buffer" << endl;
//        exit(1);
//    }

//    if(avformatContext->oformat->flags & AVFMT_GLOBALHEADER){
//        outC->flags |= CODEC_FLAG_GLOBAL_HEADER;
//    }

    //avformat_write_header(avformatContext, NULL);

//    for(int i=0; i<25;i++){
//        av_init_packet(&outPkt);
//        outPkt.data=NULL;
//        outPkt.size=0;
//        for(y=0;y<outC->height;y++) {
//            for(x=0;x<outC->width;x++) {
//                outFrame->data[0][y * outFrame->linesize[0] + x] = x + y + i * 3;
//               // outFrame->data[1][y * outFrame->linesize[0] + x] = x + y + i * 3;
//               // outFrame->data[2][y * outFrame->linesize[0] + x] = x + y + i * 3;

//            }
//        }
//    }
//    outFrame->pts = i;
//    ret = avcodec_encode_video2(outC, &outPkt, outFrame, &output);
//    if(ret<0){
//        QTextStream(stdout) << "Cannot encode video" << endl;
//        exit(1);
//    }

//    if(output){
//        if (outC->coded_frame->pts != AV_NOPTS_VALUE) {
//                       outPkt.pts = av_rescale_q(outC->coded_frame->pts, outC->time_base, avstream->time_base);
//        }
//    }

//    outPkt.pts = i;












    i = 1;
    while(av_read_frame(pFormatCtx, &packet) >= 0){
        if(packet.stream_index==videoStream) {
          // Decode video frame
          avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
         // QTextStream(stdout) << "bad" <<endl;

          if(frameFinished) {
          // Convert the image from its native format to YUV
              sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data,
                pFrame->linesize, 0, pCodecCtx->height,
                pFrameRGB->data, pFrameRGB->linesize);
              //QTextStream(stdout) << "good" <<endl;

              // Save the frame to disk
              //if(++i<=10){
                  FILE *pFile;
                  char szFilename[32];
                  int  y;

                  // Open file
                  sprintf(szFilename, "frames/frame%d.ppm", i);
                  pFile=fopen(szFilename, "wb");
                  if(pFile==NULL)
                    break;

                  // Write header
                  fprintf(pFile, "P6\n%d %d\n255\n", pCodecCtx->width, pCodecCtx->height);
                 // QTextStream(stdout)<< "number of channels: " << pCodecCtx->channels << endl;


                  // Write pixel data
                  for(y=0; y<pCodecCtx->height; y++){
                      fwrite(pFrameRGB->data[0]+y*pFrameRGB->linesize[0], 1, (pCodecCtx->width)*3, pFile);
                      //QTextStream(stdout) << "frame data: " << (uint64_t*) pFrameRGB->data[0]+y*pFrameRGB->linesize[0] << endl;
                  }

                  // Close file
                  fclose(pFile);
             // }

          }
        }
        i++;
        av_free_packet(&packet);
    }

    av_free(buffer);
    av_free(pFrameRGB);

    // Free the YUV frame
    av_free(pFrame);

    // Close the codecs
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);

    // Close the video file
    avformat_close_input(&pFormatCtx);


    //gif_image
}
