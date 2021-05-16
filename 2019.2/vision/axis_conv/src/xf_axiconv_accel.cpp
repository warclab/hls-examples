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

#include "xf_axiconv_config.h"

void axis2xfMat(axis_t* src, 
			   xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, XF_NPPC1>& img) {
	int rows = img.rows;
	int cols = img.cols;
	int idx = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// clang-format off
    		#pragma HLS loop_flatten off
    		#pragma HLS pipeline II=1
			// clang-format on
	        img.write(idx++, src->data);
			src++;
		}
	}
}


void xfMat2axis(xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, XF_NPPC1>& img,
				axis_t* dst) {
	int rows = img.rows;
	int cols = img.cols;
	int idx = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// clang-format off
    		#pragma HLS loop_flatten off
    		#pragma HLS pipeline II=1
			// clang-format on
			ap_uint<1> tmp = 0;
			if ((i==rows-1) && (j== cols-1)) {
				tmp = 1;
			}
			dst->last = tmp;
			dst->data = img.read(idx++);
			dst++;
		}
	}
}

void axiconv_accel(axis_t* input,
                   axis_t* output,
                   int rows,
                   int cols) {
// clang-format off
    #pragma HLS INTERFACE axis port=input
    #pragma HLS INTERFACE axis port=output
    #pragma HLS INTERFACE s_axilite port=rows               bundle=control
    #pragma HLS INTERFACE s_axilite port=cols               bundle=control
    #pragma HLS INTERFACE s_axilite port=return             bundle=control
    // clang-format on

    xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, XF_NPPC1> src_mat(rows, cols);
// clang-format off
    #pragma HLS stream variable=src_mat.data dim=1 depth=2
    #pragma HLS dataflow
    // clang-format on

    axis2xfMat(input, src_mat);
    xfMat2axis(src_mat, output);

    return;
}