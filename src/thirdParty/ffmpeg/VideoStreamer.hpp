#ifndef VIDEOSTREAMER_H_
#define VIDEOSTREAMER_H_
#include "../../core/Constants.hpp"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
/**
 * @class VideoStreamer
 * @brief Class for streaming and rendering video frames using FFmpeg and SDL.
 */
class VideoStreamer
{
public:
	/**
	 * @brief Default constructor for the VideoStreamer class.
	 */
	VideoStreamer();

	/**
	 * @brief Destructor for the VideoStreamer class.
	 */
	~VideoStreamer();

	/**
	 * @brief Initializes the VideoStreamer with the given SDL renderer and video URL.
	 * @param ren The SDL renderer to use for rendering frames.
	 * @param url The URL of the video file to stream.
	 */
	void init(SDL_Renderer* ren, const char* url);

	/**
	 * @brief Reads the next video frame from the stream.
	 * @return True if a frame was successfully read, false otherwise.
	 */
	bool readFrame();

	/**
	 * @brief Renders the current video frame using the given SDL renderer.
	 * @param ren The SDL renderer to use for rendering the frame.
	 */
	void render(SDL_Renderer* ren);

	/**
	 * @brief Resets the VideoStreamer to its initial state.
	 */
	void reset();

	/**
	 * @brief Frees any resources used by the VideoStreamer.
	 */
	void free();

private:
	AVFormatContext* format_context_;   ///< The FFmpeg format context.
	AVCodecContext* codec_context_;     ///< The FFmpeg codec context.
	AVFrame* frame_;                    ///< The FFmpeg frame.
	AVPacket packet_;                    ///< The FFmpeg packet.
	SDL_Texture* frame_texture_;        ///< The SDL texture for rendering frames.
	int video_stream_index_;            ///< The index of the video stream in the format context.
	bool isFrameReady;                  ///< Flag indicating if a frame is ready for rendering.
};
#endif // VIDEOSTREAMER_H_