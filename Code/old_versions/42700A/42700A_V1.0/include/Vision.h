/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature Orange = vex::vision::signature (1, 6521, 7149, 6836, -2049, -1635, -1842, 3, 0);
vex::vision::signature Green = vex::vision::signature (2, -7919, -6669, -7294, -3449, -2729, -3090, 3, 0);
vex::vision::signature Purple = vex::vision::signature (3, 631, 1891, 1260, 3449, 7857, 5654, 1.6, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT16, 50, Orange, Green, Purple, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/