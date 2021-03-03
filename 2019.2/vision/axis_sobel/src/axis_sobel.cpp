/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "axis_sobel.h"

void sobel_accel(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM_X, AXI_STREAM& OUTPUT_STREAM_Y) {
    #pragma HLS INTERFACE axis port=INPUT_STREAM
    #pragma HLS INTERFACE axis port=OUTPUT_STREAM_Y
    #pragma HLS INTERFACE axis port=OUTPUT_STREAM_Y

    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, NPC1> _src;
    xf::cv::Mat<OUT_TYPE, HEIGHT, WIDTH, NPC1> _dstgx;
    xf::cv::Mat<OUT_TYPE, HEIGHT, WIDTH, NPC1> _dstgy;

    xf::cv::AXIvideo2xfMat(INPUT_STREAM, _src);

    xf::cv::Sobel<XF_BORDER_CONSTANT, FILTER_WIDTH, IN_TYPE, OUT_TYPE, HEIGHT, WIDTH, NPC1, XF_USE_URAM>(_src, 
                                                                                                        _dstgx,
                                                                                                        _dstgy);

    xf::cv::xfMat2AXIvideo(_dstgx, OUTPUT_STREAM_X);
    xf::cv::xfMat2AXIvideo(_dstgy, OUTPUT_STREAM_Y);
}
