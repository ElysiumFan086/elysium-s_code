#ifndef FFMPEG_INCLUDE_H
#define FFMPEG_INCLUDE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/dict.h>
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavutil/pixfmt.h>
#include <libavutil/imgutils.h>
};

#pragma comment (lib, "avformat.lib")
#pragma comment (lib, "avutil.lib")
#pragma comment (lib, "swscale.lib")
#pragma comment (lib, "avcodec.lib")
#pragma comment (lib, "avdevice.lib")
#pragma comment (lib, "avfilter.lib")

#endif