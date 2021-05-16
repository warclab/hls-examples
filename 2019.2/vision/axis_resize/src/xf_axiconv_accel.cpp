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

  
  
  
/* 
Unpack a AXI video stream into a xf::cv::Mat<> object 
 *input: AXI_video_strm 
 *output: img 
 */  
  
template <int TYPE, int ROWS, int COLS, int NPPC>  
int axistream2xfMat(hls::stream<axis_t<8>>& AXI_video_strm, xf::cv::Mat<TYPE, ROWS, COLS, NPPC>& img) {  
    axis_t<8> pixelpacket;  
    int res = 0;  
  
    int rows = img.rows;  
    int cols = img.cols;  
    int idx = 0;  
  
    assert(img.rows <= ROWS);  
    assert(img.cols <= COLS);  
  
    loop_row_axi2mat:   for (int i = 0; i < rows; i++) {  
        loop_col_axi2mat:     for (int j = 0; j < cols; j++) {  
            // clang-format off  
                #pragma HLS loop_flatten off  
                #pragma HLS pipeline II=1  
            // clang-format on  
            AXI_video_strm >> pixelpacket;  
                img.write(idx++, pixelpacket.data);  
        }  
       }  
    return res;  
}  
  
// Pack the data of a xf::cv::Mat<> object into an AXI Video stream  
/* 
 *  input: img 
 *  output: AXI_video_strm 
 */  
template <int TYPE, int ROWS, int COLS, int NPPC>  
int xfMat2axistream(xf::cv::Mat<TYPE, ROWS, COLS, NPPC>& img, hls::stream<axis_t<8>>& AXI_video_strm) {  
  
    axis_t<8> pixelpacket;  
    int res = 0;  
  
    int rows = img.rows;  
    int cols = img.cols;  
    int idx = 0;  
  
    assert(img.rows <= ROWS);  
    assert(img.cols <= COLS);  
  
    bool sof = true; // Indicates start of frame  
  
    loop_row_mat2axi: for (int i = 0; i < rows; i++) {  
        loop_col_mat2axi: for (int j = 0; j < cols; j++) {  
            // clang-format off  
            #pragma HLS loop_flatten off  
            #pragma HLS pipeline II=1  
            // clang-format on  
                  
                ap_uint<1> tmp = 0;  
                if ((i==rows-1) && (j== cols-1)) {  
                    tmp = 1;  
                }  
  
                pixelpacket.last = tmp;  
                pixelpacket.data = img.read(idx++);  
  
                AXI_video_strm << pixelpacket;  
  
            }  
        }  
  
    return res;  
}

void axiconv_accel(stream_t& input,
                   stream_t& output,
                   int rows_in,
                   int cols_in,
                   int rows_out,
                   int cols_out) {
// clang-format off
    #pragma HLS INTERFACE axis port=input
    #pragma HLS INTERFACE axis port=output
    #pragma HLS INTERFACE s_axilite port=rows_in               bundle=control
    #pragma HLS INTERFACE s_axilite port=cols_in               bundle=control
    #pragma HLS INTERFACE s_axilite port=rows_out               bundle=control
    #pragma HLS INTERFACE s_axilite port=cols_out               bundle=control
    #pragma HLS INTERFACE s_axilite port=return             bundle=control
    // clang-format on

    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, XF_NPPC1> src_mat(rows_in, cols_in);
    // xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, XF_NPPC1> _dstgx(rows, cols);
    // xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, XF_NPPC1> _dstgy(rows, cols);
    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, XF_NPPC1> dst_mat(rows_out, cols_out);
// clang-format off
    #pragma HLS stream variable=src_mat.data dim=1 depth=2
    // #pragma HLS stream variable=_dstgx.data dim=1 depth=2
    // #pragma HLS stream variable=_dstgy.data dim=1 depth=2
    #pragma HLS stream variable=dst_mat.data dim=1 depth=2
    #pragma HLS dataflow
    // clang-format on
    axistream2xfMat<IN_TYPE,HEIGHT,WIDTH,NPCC>(input, src_mat);
    xf::cv::resize<INTERPOLATION, IN_TYPE, HEIGHT, WIDTH, HEIGHT_OUT, WIDTH_OUT, NPCC, MAXDOWNSCALE>(src_mat, dst_mat);
    xfMat2axistream<IN_TYPE,HEIGHT_OUT,WIDTH_OUT,NPCC>(dst_mat, output);

    return;
}