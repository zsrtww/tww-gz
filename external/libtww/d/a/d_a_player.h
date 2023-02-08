#ifndef D_A_PLAYER
#define D_A_PLAYER

#include "../../f_op/f_op_actor.h"
#include "../../addrs.h"

class daPy_lk_c : public fopAc_ac_c {
public:
};

#define l_debug_keep_pos (*(cXyz*)(l_debug_keep_pos_addr))
#define l_debug_current_angle (*(csXyz*)(l_debug_current_angle_addr))
#define l_debug_shape_angle (*(csXyz*)(l_debug_shape_angle_addr))

#endif /* D_A_PLAYER */