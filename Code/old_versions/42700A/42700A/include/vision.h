/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature SIG_1 = vex::vision::signature (1, 8703, 9591, 9146, -2707, -2209, -2458, 3, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, -6627, -4929, -5778, -3497, -2217, -2858, 3, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 1285, 1967, 1626, 5011, 8685, 6848, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT10, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/