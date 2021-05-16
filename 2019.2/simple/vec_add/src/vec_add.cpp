#include <iostream>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

using namespace std;

typedef ap_axis <32,1,1,1> AXI_T;
typedef hls::stream<AXI_T> STREAM_T;

void vec_add(STREAM_T &A, STREAM_T &C){
#pragma HLS INTERFACE axis port=A
#pragma HLS INTERFACE axis port=C
// #pragma HLS INTERFACE s_axilite port=return  bundle=control

    int LEN = 10;
    AXI_T tmpA, tmpC;

    for(int i=0; i<LEN; i++){

        A >> tmpA;
        tmpC.data = tmpA.data + 10;

        if(i == LEN-1){
            tmpC.last = 1;  
        }else{
            tmpC.last = 0;
        }
        tmpC.strb = 0xf;    
        tmpC.keep = 0xf;    
        C << tmpC;
    }
    return;
}