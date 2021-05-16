#ifndef _XF_AXICONV_CONFIG_H_
#define _XF_AXICONV_CONFIG_H_

#include "hls_stream.h"
#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "common/xf_infra.hpp"

#define MAX_WIDTH  1280
#define MAX_HEIGHT 720

#define XF_HEIGHT 720
#define XF_WIDTH 1280

#define RO 0 // Resource Optimized (8-pixel implementation)
#define NO 1 // Normal Operation (1-pixel implementation)

/*  Set Filter size  */

#define FILTER_SIZE_3 1
#define FILTER_SIZE_5 0
#define FILTER_SIZE_7 0

#define T_8U 1
#define T_16S 0

#define GRAY 1
#define RGBA 0
#define XF_USE_URAM false

#if FILTER_SIZE_3
#define FILTER_WIDTH 3
#elif FILTER_SIZE_5
#define FILTER_WIDTH 5
#elif FILTER_SIZE_7
#define FILTER_WIDTH 7
#endif
#if GRAY
#if (FILTER_WIDTH == 3 | FILTER_WIDTH == 5)
#if RO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC8
#endif
#if NO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC1
#endif
#endif

#if (FILTER_WIDTH == 7)
#if NO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC1
#endif
#endif

#else

#if (FILTER_WIDTH == 3 | FILTER_WIDTH == 5)
#if RO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC8
#endif
#if NO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC1
#endif
#endif

#if (FILTER_WIDTH == 7)
#if NO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC1
#endif
#endif
#endif

typedef hls::stream<xf::cv::ap_axiu<24,1,1,1> >           AXI_STREAM;
typedef xf::cv::Mat<512, MAX_HEIGHT,   MAX_WIDTH,   XF_8UC3> RGB_IMAGE;
typedef xf::cv::Mat<512, MAX_HEIGHT,   MAX_WIDTH,   XF_8UC1> GRAY_IMAGE;


void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM);//int rows, int cols);

#endif // _XF_AXICONV_CONFIG_H_
