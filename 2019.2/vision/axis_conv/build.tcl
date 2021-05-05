if { [catch {source .settings.tcl} fid] } {
    puts "Copying global settings"
    file copy ../../.settings.tcl .settings.tcl
    source .settings.tcl
}

set PROJ "xf_axisonv.prj"
set SOLN "sol1"

if {![info exists CLKP]} {
  set CLKP 10
}

open_project -reset $PROJ

add_files "./src/xf_axiconv_accel.cpp" -cflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
add_files -tb "./test/xf_axiconv_tb.cpp" -cflags "-I${OPENCV_INCLUDE} -I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x" -csimflags "-I${XF_PROJ_ROOT}/vision/L1/include -I ./include -I ./ -D__SDSVHLS__ -std=c++0x"
set_top axiconv_accel

open_solution -reset $SOLN

set_part $XPART
create_clock -period $CLKP

# if {$CSIM == 1} {
#   csim_design -argv "../../../../../data/1920x1080.png"
# }

if {$CSYNTH == 1} {
  csynth_design
}

# if {$COSIM == 1} {
#   cosim_design -argv "../../../../../data/1920x1080.png"
# }

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

if {$ZYCAP == 1} {
    call_python ${XF_PROJ_ROOT}/../../scripts/export/generate_config.py $PROJ $SOLN
}

if {$COMPRESS == 1} {
    if {![info exists COMPRESS_LNG]} {
        set COMPRESS_LNG "verilog"
    }
    set status [catch {exec sh -c "cd ${PROJ}/${SOLN}/syn/${COMPRESS_LNG} && tar -czvf ${COMPRESS_LNG}.tar.gz * && mv ${COMPRESS_LNG}.tar.gz ../../../../" } output]

    if {$status == 0} {
        puts "Successfully exported ${COMPRESS_LNG}.tar.gz"
    } elseif {$::errorCode eq "NONE"} {
        puts "Success but $output..."
    } elseif {[lindex $::errorCode 0] eq "CHILDSTATUS"} {
        puts "Error [lindex $::errorCode end]."
    }
}

exit
