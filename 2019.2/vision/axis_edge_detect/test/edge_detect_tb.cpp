#include "common/xf_headers.hpp"
#include "common/xf_axi.hpp"
#include "edge_detect.hpp"
#include <iostream>

using namespace std;

#define _W 24


int main (int argc, char** argv) {

    cv::Mat src;
    AXI_STREAM src_axi, dst_axi;
    src = cv::imread(argv[1], 0);
    if (src.data == NULL) {
        fprintf(stderr, "Cannot open image at %s\n", argv[1]);
        return 0;
    }

    int rows = src.rows;
    int cols = src.cols;
    cv::Mat dst(rows, cols, CV_8UC1);


    // convert input to axiStream
    xf::cv::cvMat2AXIvideoxf<XF_NPPC1, _W>(src, src_axi);

    // output axiStream

    image_filter(src_axi, dst_axi);

    xf::cv::AXIvideo2cvMatxf<XF_NPPC1>(dst_axi, dst);


    cv::imwrite("output.bmp", dst);

}