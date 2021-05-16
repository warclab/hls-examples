#include "edge_detect.hpp"

void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM)//, int rows, int cols)
{

#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>  img_0(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>  img_1(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_2(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_2a(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_2b(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_3(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_4(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_5(MAX_HEIGHT, MAX_WIDTH);
xf::cv::Mat<XF_8UC1, XF_HEIGHT, XF_WIDTH, XF_NPPC1>   img_6(MAX_HEIGHT, MAX_WIDTH);
;

#pragma HLS dataflow
xf::cv::AXIvideo2Mat(INPUT_STREAM, img_0);
xf::cv::bgr2gray(img_0, img_1);
xf::cv::GaussianBlur<3,3>(img_1,img_2);
xf::cv::Duplicate(img_2,img_2a,img_2b);
xf::cv::Sobel<XF_BORDER_CONSTANT, FILTER_WIDTH, IN_TYPE, OUT_TYPE, HEIGHT, WIDTH, NPC1, XF_USE_URAM>(img_2a, img_3);
xf::cv::Sobel<XF_BORDER_CONSTANT, FILTER_WIDTH, IN_TYPE, OUT_TYPE, HEIGHT, WIDTH, NPC1, XF_USE_URAM>(img_2b, img_4);
xf::cv::AddWeighted(img_4,0.5,img_3,0.5,0.0,img_5);
xf::cv::gray2bgr(img_5, img_6);

xf::cv::Mat2AXIvideo(img_6, OUTPUT_STREAM);
}