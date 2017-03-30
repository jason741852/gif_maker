#include "gif_maker.h"


struct gif_file{
    FILE* file;
};
typedef struct gif_file gif_file;


bool writeGifHeader(gif_file* gif_maker){
    QTextStream(stdout) << "crash!" << endl;

    gif_maker->file = fopen("test.gif","wb");
    QTextStream(stdout) << "crash?" << endl;

    // signature
    fputs("GIF89a", gif_maker->file);

    fclose(gif_maker->file);

    return true;
}
