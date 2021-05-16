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
#include "common/xf_common.hpp"
#include "xf_config_params.h"

/* config width and height */
#define XF_HEIGHT 1080
#define XF_WIDTH 1920

#define IN_TYPE XF_8UC1
// #define OUT_TYPE ap_uint<8>

#define INPUT_PTR_WIDTH 32
#define OUTPUT_PTR_WIDTH 32

struct axis_t {
    ap_uint<8> data;
    ap_int<1> last;
};

void axis2xfMat(axis_t* src, 
			   xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, XF_NPPC1>& img);

void xfMat2axis(xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, XF_NPPC1>& img,
				axis_t* dst);

void axiconv_accel(axis_t* input,
                   axis_t* output,
                   int rows,
                   int cols);

#endif // _XF_AXICONV_CONFIG_H_