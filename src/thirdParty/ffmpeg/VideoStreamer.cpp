#include "VideoStreamer.h"


VideoStreamer::VideoStreamer()
{
	format_context_ = NULL;
	codec_context_ = NULL;
	frame_ = NULL;
	frame_texture_ = NULL;
	video_stream_index_ = -1;
	packet_ = { 0 };
}
VideoStreamer::~VideoStreamer()
{
	SDL_DestroyTexture(frame_texture_);
	avformat_close_input(&format_context_);
	avcodec_free_context(&codec_context_);
	av_frame_free(&frame_);
	av_packet_unref(&packet_);
}
void VideoStreamer::init(SDL_Renderer* ren, const char* url)
{
	format_context_ = avformat_alloc_context();

	if (avformat_open_input(&format_context_, url, NULL, NULL) != 0)
	{
		fprintf(stderr, "Error: Couldn't open file.\n");
		return;
	}

	// Find video stream information
	if (avformat_find_stream_info(format_context_, NULL) < 0)
	{
		fprintf(stderr, "Error: Couldn't find stream information.\n");
		return;
	}

	// Find video stream
	for (int i = 0; i < static_cast<int>(format_context_->nb_streams); i++)
	{
		if (format_context_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream_index_ = i;
			break;
		}
	}

	if (video_stream_index_ == -1)
	{
		fprintf(stderr, "Error: Couldn't find video stream.\n");
		return;
	}

	const AVCodec* codec = avcodec_find_decoder(format_context_->streams[video_stream_index_]->codecpar->codec_id);
	if (!codec)
	{
		fprintf(stderr, "Error: Couldn't find decoder.\n");
		return;
	}

	codec_context_ = avcodec_alloc_context3(codec);
	if (!codec_context_)
	{
		fprintf(stderr, "Error: Couldn't allocate codec context.\n");
		return;
	}

	if (avcodec_parameters_to_context(codec_context_, format_context_->streams[video_stream_index_]->codecpar) < 0)
	{
		fprintf(stderr, "Error: Couldn't copy codec parameters to context.\n");
		return;
	}

	if (avcodec_open2(codec_context_, codec, NULL) < 0)
	{
		fprintf(stderr, "Error: Couldn't open codec.\n");
		return;
	}

	frame_ = av_frame_alloc();
	if (!frame_)
	{
		fprintf(stderr, "Error: Couldn't allocate frame_.\n");
		return;
	}
	frame_texture_ = SDL_CreateTexture(
		ren,
		SDL_PIXELFORMAT_YV12,
		SDL_TEXTUREACCESS_STREAMING,
		codec_context_->width,
		codec_context_->height);
	if (!frame_texture_)
	{
		fprintf(stderr, "SDL: could not create texture - exiting\n");
		exit(1);
	}
}



bool VideoStreamer::readFrames()
{
	//how to know that end of video and start reverse and loop

	while (av_read_frame(format_context_, &packet_) >= 0)
	{
		printf("Reading a new frame...\n");
		if (packet_.stream_index == video_stream_index_)
		{
			// Send the packet to the decoder
			if (avcodec_send_packet(codec_context_, &packet_) < 0)
			{
				fprintf(stderr, "Error: Failed to send packet to decoder.\n");
				return false;
			}
			// Receive the decoded frame
			if (avcodec_receive_frame(codec_context_, frame_) < 0)
			{
				fprintf(stderr, "Error: Failed to receive frame from decoder.\n");
				return false;
			}
			AVFrame* clonedFrame = av_frame_clone(frame_);

			frames_.push_front(clonedFrame);
			// Convert the frame to an SDL frame_texture_
			
		}	
	}
	av_packet_unref(&packet_);
}

bool VideoStreamer::readFrame()
{
	//how to know that end of video and start reverse and loop

	if (av_read_frame(format_context_, &packet_) >= 0)
	{
		printf("Reading a new frame...\n");
		if (packet_.stream_index == video_stream_index_)
		{
			// Send the packet to the decoder
			if (avcodec_send_packet(codec_context_, &packet_) < 0)
			{
				fprintf(stderr, "Error: Failed to send packet to decoder.\n");
				return false;
			}
			// Receive the decoded frame
			if (avcodec_receive_frame(codec_context_, frame_) < 0)
			{
				fprintf(stderr, "Error: Failed to receive frame from decoder.\n");
				return false;
			}
			// AVFrame* clonedFrame = av_frame_clone(frame_);
			SDL_UpdateYUVTexture(frame_texture_, NULL, frame_->data[0], frame_->linesize[0], frame_->data[1], frame_->linesize[1], frame_->data[2], frame_->linesize[2]);

			// frames_.push_front(clonedFrame);
			// Convert the frame to an SDL frame_texture_
			
		}	
	}
	av_packet_unref(&packet_);
}



void VideoStreamer::reset()
{
	avformat_seek_file(format_context_, video_stream_index_, 0, 0, 0, AVSEEK_FLAG_FRAME);
	is_end_of_stream_=false;
	av_seek_frame(format_context_, video_stream_index_, 0, AVSEEK_FLAG_BACKWARD);
	avcodec_flush_buffers(codec_context_);
}
void VideoStreamer::render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, frame_texture_, NULL, NULL);
}
void VideoStreamer::renderFrame(SDL_Renderer*ren,AVFrame * frame)
{
	SDL_UpdateYUVTexture(frame_texture_, NULL, frame->data[0], frame->linesize[0], frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);
	
	SDL_RenderCopy(ren, frame_texture_, NULL, NULL);
	

}
void VideoStreamer::play(SDL_Renderer * ren)
{

	for (auto it = frames_.begin(); it != frames_.end(); ++it) {
    	renderFrame(ren, *it);
	}
	//traverse in reverse frames_
	for (auto it = frames_.rbegin(); it != frames_.rend(); ++it) {
    	renderFrame(ren, *it);
	}
}
