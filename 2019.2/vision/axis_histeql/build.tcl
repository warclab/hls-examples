source ../../.settings.tcl

set PROJ "axis_histeql.prj"
set SOLN "sol1"

if {![info exists CLKP]} {
  set CLKP 10
}

if {![info exists SAMPLE_DATA]} {
  set SAMPLE_DATA "1920x1080.png"
}


open_project -reset $PROJ

add_files "./src/axis_histeql.cpp" -cflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
add_files -tb "./test/axis_histeql_tb.cpp" -cflags "-I${OPENCV_INCLUDE} -I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
set_top sobel_accel

open_solution -reset $SOLN

set_part $XPART
create_clock -period $CLKP

if {$CSIM == 1} {
  csim_design -argv "../../../../../data/${SAMPLE_DATA}"
}

if {$CSYNTH == 1} {
  csynth_design
}

if {$COSIM == 1} {
  cosim_design -argv "../../../../../data/${SAMPLE_DATA}"
}

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

exit
