#pragma once

#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "imgproc/xf_erosion.hpp"
#include "xf_infra.hpp"
#include <ap_axi_sdata.h>



#define NPC1 XF_NPPC1



#define SINGLE_COLOR_TYPE XF_8UC1
const int WIDTH_MAX = 2048;
const int HEIGHT_MAX = 1536;

/* Define the AXI Stream type */
const int PPC = 1;
const int bytes_per_pixel = 1;
const int PIXEL_WIDTH = 8 * bytes_per_pixel * PPC;
typedef ap_axiu<PIXEL_WIDTH,1,1,1> axiu_8;
typedef hls::stream<axiu_8> stream_t;


#define FILTER_SIZE 3

#define KERNEL_SHAPE XF_SHAPE_CROSS

#define ITERATIONS 1


/* Accelerator specific parameters */
const int FILTER_WIDTH_EROSION = 5;
const int EROSION_NITER = 1;

/* Declare the top function - This function needs redundant inputs */
void erosion_accel(stream_t &stream_in, stream_t &stream_out);