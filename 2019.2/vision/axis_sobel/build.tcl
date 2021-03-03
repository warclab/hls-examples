source ../../.settings.tcl

set PROJ "axis_sobel.prj"
set SOLN "sol1"

if {![info exists CLKP]} {
  set CLKP 3.3
}

open_project -reset $PROJ

add_files "./src/axis_sobel.cpp" -cflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
add_files -tb "./test/axis_sobel_tb.cpp" -cflags "-I${OPENCV_INCLUDE} -I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
set_top sobel_accel

open_solution -reset $SOLN

set_part $XPART
create_clock -period $CLKP

if {$CSIM == 1} {
  csim_design -argv "../../../../data/128x128.png"
}

if {$CSYNTH == 1} {
  csynth_design
}

if {$COSIM == 1} {
  cosim_design -argv "../../../../data/128x128.png"
}

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

exit
