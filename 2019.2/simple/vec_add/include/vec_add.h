#ifndef _AXIS_PASSTHROUGH_H_
#define _AXIS_PASSTHROUGH_H_

#include <hls_stream.h>
#include <ap_axi_sdata.h>


typedef ap_axis <32,1,1,1> AXI_T;
typedef hls::stream<AXI_T> AXI_STREAM;

void axis_passthrough(AXI_STREAM& input, 
                AXI_STREAM& output); 

#endif //  _AXIS_PASSTHROUGH_H_
