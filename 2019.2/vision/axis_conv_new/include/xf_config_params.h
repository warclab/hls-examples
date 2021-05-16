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

#define RO 0 // Resource Optimized (8-pixel implementation)
#define NO 1 // Normal Operation (1-pixel implementation)

#define GRAY 1
#define RGB 0

#define FILTER_SIZE_3 1
#define FILTER_SIZE_5 0
#define FILTER_SIZE_7 0

#define T_8U 1
#define T_16S 0

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