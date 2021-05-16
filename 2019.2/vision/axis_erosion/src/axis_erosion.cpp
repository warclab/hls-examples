#include "axis_erosion.hpp"

#define height 1080
#define width 1920

void erosion_accel(stream_t &stream_in, stream_t &stream_out) {
#pragma HLS INTERFACE axis register_mode=both register depth=2 port=stream_in
#pragma HLS INTERFACE axis register_mode=both register depth=2 port=stream_out

#pragma HLS INTERFACE ap_ctrl_none port=return  // no handshakes


	xf::cv::Mat<SINGLE_COLOR_TYPE, HEIGHT_MAX, WIDTH_MAX, NPC1> imgInput(height, width);
	#pragma HLS STREAM variable=imgInput.data depth=2
	xf::cv::Mat<SINGLE_COLOR_TYPE, HEIGHT_MAX, WIDTH_MAX, NPC1> imgOutput(height, width);
	#pragma HLS STREAM variable=imgOutput.data depth=2

#pragma HLS dataflow

	xf::cv::AXIvideo2xfMat(stream_in, imgInput);
    unsigned char _kernel[FILTER_SIZE * FILTER_SIZE] = {0,1,0,1,1,1,0,1,0};
	xf::cv::erode<XF_BORDER_CONSTANT, SINGLE_COLOR_TYPE, HEIGHT_MAX, WIDTH_MAX, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, NPC1>(
			imgInput,imgOutput , _kernel);
	xf::cv::xfMat2AXIvideo<PIXEL_WIDTH,SINGLE_COLOR_TYPE,HEIGHT_MAX,WIDTH_MAX,NPC1>(imgOutput, stream_out);


}



