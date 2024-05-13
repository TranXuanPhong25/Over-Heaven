#ifndef VIDEOSTREAMER_H_
#define VIDEOSTREAMER_H_
#include "../../core/Constants.hpp"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#include <deque>
class VideoStreamer
{
public:
	VideoStreamer();
	~VideoStreamer();
	void init(SDL_Renderer* ren, const char* url);
	bool readFrames();
	bool readFrame();
	void render(SDL_Renderer*ren);
	void renderFrame(SDL_Renderer*ren,AVFrame * frame);
	void reset();
	void free();
	void play(SDL_Renderer* ren);
private:
	bool is_end_of_stream_;
	AVFormatContext* format_context_;
	AVCodecContext* codec_context_;
	// std::deque<AVFrame*> frames_;
	AVFrame* frame_;
	AVPacket packet_;
	SDL_Texture* frame_texture_;
	int video_stream_index_;
	bool isFrameReady;
};

#endif // VIDEOSTREAMER_H_