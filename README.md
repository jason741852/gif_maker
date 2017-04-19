# MPEG-1 to GIF Converter
## Author
Jason Chan

## Program Description
This repository contains 2 programs.
"gif_maker" in Debug_Dir decodes MPEG-1 video and store image frames in /frames directory


"ppm_to_gif" in main directory encodes the frames into an animated gif. The output test.gif is location in the Debug_Dir

## Compile Instructions
gif_maker's Makefile is located in the Debug_Dir directory
simply cd into Debug_Dir and type make

To compile ppm_to_gif, in the main directory, user must enter the command
```
g++ `Magick++-config --cxxflags --cppflags` -o ppm_to_gif ppm_to_gif.cpp `Magick++-config --ldflags --libs`
```

Note that ppm_to_gif is not a part of gif_maker's Makefile
They are 2 independent programs
