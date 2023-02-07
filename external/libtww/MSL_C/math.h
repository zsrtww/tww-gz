#ifndef LIB_TWW_MATH
#define LIB_TWW_MATH

#define M_PI ((double)3.141592653589793238462643383279502884e+00)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include "../addrs.h"

typedef double (*tww_atan_t)(double x);
typedef double (*tww_copysign_t)(double x, double y);
typedef double (*tww_cos_t)(double x);
typedef double (*tww_floor_t)(double x);
typedef double (*tww_frexp_t)(double x, int* exponent);
typedef double (*tww_ldexp_t)(double x, int exponent);
typedef double (*tww_sin_t)(double x);
typedef double (*tww_tan_t)(double x);
typedef double (*tww_acos_t)(double x);
typedef double (*tww_asin_t)(double x);
typedef double (*tww_atan2_t)(double x, double y);
typedef double (*tww_fmod_t)(double x, double y);

#define tww_atan ((tww_atan_t)tww_atan_addr)
#define tww_copysign ((tww_copysign_t)tww_copysign_addr)
#define tww_cos ((tww_cos_t)tww_cos_addr)
#define tww_floor ((tww_floor_t)tww_floor_addr)
#define tww_frexp ((tww_frexp_t)tww_frexp_addr)
#define tww_ldexp ((tww_ldexp_t)tww_ldexp_addr)
#define tww_sin ((tww_sin_t)tww_sin_addr)
#define tww_tan ((tww_tan_t)tww_tan_addr)
#define tww_acos ((tww_acos_t)tww_acos_addr)
#define tww_asin ((tww_asin_t)tww_asin_addr)
#define tww_atan2 ((tww_atan2_t)tww_atan2_addr)
#define tww_fmod ((tww_fmod_t)tww_fmod_addr)

#endif  // !LIB_TWW_MATH