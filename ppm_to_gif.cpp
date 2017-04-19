#include <Magick++.h>
#include <iostream>
#include <list>
using namespace std;
using namespace Magick;

int main(int argc,char **argv){
  InitializeMagick(*argv);
  list<Image> frames;
  char szFilename[32];

  // Image img1( "100x100", "white" );
  // img1.pixelColor( 49, 49, "red" );
  // frames.push_back(img1);
  //
  // Image img2( "100x100", "red" );
  // img2.pixelColor( 49, 49, "white" );
  // frames.push_back(img2);
  //
  // img1.animationDelay(2000);
  // img2.animationDelay(2000);
  Image img;
  for(int i=2;i<=419;i++){
    sprintf(szFilename, "Debug_Dir/frames/frame%d.ppm", i);
    img.read(szFilename);
    frames.push_back(img);
    img.animationDelay(2000);
  }

  Magick::writeImages(frames.begin(), frames.end(), "test.gif");


}
