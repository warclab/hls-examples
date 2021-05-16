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

#include "axis_sobel_config.h"

void axis2xfMat(axis_t *src,
                xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> &img)
{
    int rows = img.rows;
    int cols = img.cols;
    int idx = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
// clang-format off
    		#pragma HLS loop_flatten off
    		#pragma HLS pipeline II=1
            // clang-format on
            img.write(idx++, src->data);
            src++;
        }
    }
}

void xfMat2axis(xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> &img,
                axis_t *dst)
{
    int rows = img.rows;
    int cols = img.cols;
    int idx = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
// clang-format off
    		#pragma HLS loop_flatten off
    		#pragma HLS pipeline II=1
            // clang-format on
            ap_uint<1> tmp = 0;
            if ((i == rows - 1) && (j == cols - 1))
            {
                tmp = 1;
            }
            dst->last = tmp;
            dst->data = img.read(idx++);
            dst++;
        }
    }
}

void sobel_accel(axis_t *input,
                   axis_t *output,
                   int rows,
                   int cols)
{
    // clang-format off
    #pragma HLS INTERFACE axis port=input
    #pragma HLS INTERFACE axis port=output
    #pragma HLS INTERFACE s_axilite port=rows               bundle=control
    #pragma HLS INTERFACE s_axilite port=cols               bundle=control
    #pragma HLS INTERFACE s_axilite port=return             bundle=control
    // clang-format on

    xf::cv::Mat<IN_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> src_mat(rows, cols);
    xf::cv::Mat<OUT_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> _dstgx(rows, cols);
    xf::cv::Mat<OUT_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> _dstgy(rows, cols);
    // xf::cv::Mat<OUT_TYPE, XF_HEIGHT, XF_WIDTH, NPC1> dst_mat(rows, cols);
    // clang-format off
    #pragma HLS stream variable=src_mat.data dim=1 depth=2
    #pragma HLS stream variable=_dstgx.data dim=1 depth=2
    #pragma HLS stream variable=_dstgy.data dim=1 depth=2
    // #pragma HLS stream variable=dst_mat.data dim=1 depth=2
    #pragma HLS dataflow
    // clang-format on

    axis2xfMat(input, src_mat);
    xf::cv::Sobel<XF_BORDER_CONSTANT, FILTER_WIDTH, IN_TYPE, OUT_TYPE, XF_HEIGHT, XF_WIDTH, NPC1, XF_USE_URAM>(
        src_mat,
        _dstgx,
        _dstgy);
    // xf::cv::addWeighted<IN_TYPE, OUT_TYPE, XF_HEIGHT, XF_WIDTH, NPC1>(
    //     _dstgx,
    //     0.5,
    //     _dstgy,
    //     0.5,
    //     0,
    //     dst_mat);
    xfMat2axis(_dstgx, output);

    return;
}
