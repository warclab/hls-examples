# Getting Started

For Xilinx tools 2019.2, OpenCV is included in the installation but there are some dependencies that might be missing such as `libpng12-0` & `libjpeg62`.
Please see the [install_deps.sh](../scripts/ubuntu/install_deps.sh) for packages that your OS might require.

```tcl
# Example .settings.tcl
set XF_PROJ_ROOT ${PATH_TO_THIS_REPO}/2019.2/.vitis_libs
set OPENCV_INCLUDE /opt/Xilinx/Vivado/2019.2/include

# Example device - Ultra96
set XPART xczu3eg-sbva484-1-e

set CSIM 1
set CSYNTH 1
set COSIM 1 
set VIVADO_SYN 0
set VIVADO_IMPL 0
set QOR_CHECK 0
```