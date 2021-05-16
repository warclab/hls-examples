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

#ifndef _XF_AXICONV_CONFIG_H_
#define _XF_AXICONV_CONFIG_H_

#include <iostream>
#include <math.h> 
#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_utility.hpp"
#include "common/xf_common.hpp"
#include "xf_config_params.h"

#include "imgproc/xf_sobel.hpp"
#include "common/xf_infra.hpp"
#include "imgproc/xf_add_weighted.hpp"

// Set the input and output pixel depth:
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1

// Set the optimization type:
#define NPCC XF_NPPC1

/* config width and height */
#define WIDTH 	1920	//1280
#define HEIGHT 	1080	//720

template <int W>  
struct axis_t {  
    ap_uint<W> data;  
    ap_int<1> last;  
};

typedef hls::stream<axis_t<8>> stream_t;

template <int TYPE, int ROWS, int COLS, int NPPC>
int axistream2xfMat(hls::stream<axis_t<8>>& AXI_video_strm, xf::cv::Mat<TYPE, ROWS, COLS, NPPC>& img);

template <int TYPE, int ROWS, int COLS, int NPPC>
int xfMat2axistream(xf::cv::Mat<TYPE, ROWS, COLS, NPPC>& img, hls::stream<axis_t<8>>& AXI_video_strm);

void axiconv_accel(stream_t& input,
                   stream_t& output,
                   int rows,
                   int cols);

#endif // _XF_AXICONV_CONFIG_H_