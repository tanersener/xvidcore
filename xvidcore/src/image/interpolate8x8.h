#ifndef _INTERPOLATE8X8_H_
#define _INTERPOLATE8X8_H_

#include "../utils/mem_transfer.h"

typedef void (INTERPOLATE8X8) (uint8_t * const dst,
							   const uint8_t * const src,
							   const uint32_t stride,
							   const uint32_t rounding);
typedef INTERPOLATE8X8 *INTERPOLATE8X8_PTR;

typedef void (INTERPOLATE8X8_AVG2) (uint8_t *dst,
									const uint8_t *src1,
									const uint8_t *src2,
									const uint32_t stride,
									const uint32_t rounding,
									const uint32_t height);
typedef INTERPOLATE8X8_AVG2 *INTERPOLATE8X8_AVG2_PTR;

typedef void (INTERPOLATE8X8_AVG4) (uint8_t *dst,
									const uint8_t *src1,
									const uint8_t *src2,
									const uint8_t *src3,
									const uint8_t *src4,
									const uint32_t stride,
									const uint32_t rounding);
typedef INTERPOLATE8X8_AVG4 *INTERPOLATE8X8_AVG4_PTR;

typedef void (INTERPOLATE_LOWPASS) (uint8_t *dst,
									   uint8_t *src,
									   int32_t stride,
									   int32_t rounding);

typedef INTERPOLATE_LOWPASS *INTERPOLATE_LOWPASS_PTR;

typedef void (INTERPOLATE_LOWPASS_HV) (uint8_t *dst1,
										  uint8_t *dst2,
										  uint8_t *src,
										  int32_t stride,
										  int32_t rounding);

typedef INTERPOLATE_LOWPASS_HV *INTERPOLATE_LOWPASS_HV_PTR;

typedef void (INTERPOLATE8X8_6TAP_LOWPASS) (uint8_t *dst,
									        uint8_t *src,
									        int32_t stride,
									        int32_t rounding);

typedef INTERPOLATE8X8_6TAP_LOWPASS *INTERPOLATE8X8_6TAP_LOWPASS_PTR;

extern INTERPOLATE8X8_PTR interpolate8x8_halfpel_h;
extern INTERPOLATE8X8_PTR interpolate8x8_halfpel_v;
extern INTERPOLATE8X8_PTR interpolate8x8_halfpel_hv;

extern INTERPOLATE8X8_AVG2_PTR interpolate8x8_avg2;
extern INTERPOLATE8X8_AVG4_PTR interpolate8x8_avg4;

extern INTERPOLATE_LOWPASS_PTR interpolate8x8_lowpass_h;
extern INTERPOLATE_LOWPASS_PTR interpolate8x8_lowpass_v;

extern INTERPOLATE_LOWPASS_PTR interpolate16x16_lowpass_h;
extern INTERPOLATE_LOWPASS_PTR interpolate16x16_lowpass_v;

extern INTERPOLATE_LOWPASS_HV_PTR interpolate8x8_lowpass_hv;
extern INTERPOLATE_LOWPASS_HV_PTR interpolate16x16_lowpass_hv;

extern INTERPOLATE8X8_6TAP_LOWPASS_PTR interpolate8x8_6tap_lowpass_h;
extern INTERPOLATE8X8_6TAP_LOWPASS_PTR interpolate8x8_6tap_lowpass_v;

INTERPOLATE8X8 interpolate8x8_halfpel_h_c;
INTERPOLATE8X8 interpolate8x8_halfpel_v_c;
INTERPOLATE8X8 interpolate8x8_halfpel_hv_c;

INTERPOLATE8X8 interpolate8x8_halfpel_h_mmx;
INTERPOLATE8X8 interpolate8x8_halfpel_v_mmx;
INTERPOLATE8X8 interpolate8x8_halfpel_hv_mmx;

INTERPOLATE8X8 interpolate8x8_halfpel_h_xmm;
INTERPOLATE8X8 interpolate8x8_halfpel_v_xmm;
INTERPOLATE8X8 interpolate8x8_halfpel_hv_xmm;

INTERPOLATE8X8 interpolate8x8_halfpel_h_3dn;
INTERPOLATE8X8 interpolate8x8_halfpel_v_3dn;
INTERPOLATE8X8 interpolate8x8_halfpel_hv_3dn;

INTERPOLATE8X8 interpolate8x8_halfpel_h_ia64;
INTERPOLATE8X8 interpolate8x8_halfpel_v_ia64;
INTERPOLATE8X8 interpolate8x8_halfpel_hv_ia64;

INTERPOLATE8X8_AVG2 interpolate8x8_avg2_c;
INTERPOLATE8X8_AVG4 interpolate8x8_avg4_c;

INTERPOLATE8X8_AVG2 interpolate8x8_avg2_mmx;
INTERPOLATE8X8_AVG4 interpolate8x8_avg4_mmx;

INTERPOLATE_LOWPASS interpolate8x8_lowpass_h_c;
INTERPOLATE_LOWPASS interpolate8x8_lowpass_v_c;

INTERPOLATE_LOWPASS interpolate16x16_lowpass_h_c;
INTERPOLATE_LOWPASS interpolate16x16_lowpass_v_c;

INTERPOLATE_LOWPASS_HV interpolate8x8_lowpass_hv_c;
INTERPOLATE_LOWPASS_HV interpolate16x16_lowpass_hv_c;

INTERPOLATE8X8_6TAP_LOWPASS interpolate8x8_6tap_lowpass_h_c;
INTERPOLATE8X8_6TAP_LOWPASS interpolate8x8_6tap_lowpass_v_c;

INTERPOLATE8X8_6TAP_LOWPASS interpolate8x8_6tap_lowpass_h_mmx;
INTERPOLATE8X8_6TAP_LOWPASS interpolate8x8_6tap_lowpass_v_mmx;

static __inline void
interpolate8x8_switch(uint8_t * const cur,
					  const uint8_t * const refn,
					  const uint32_t x,
					  const uint32_t y,
					  const int32_t dx,
					  const int dy,
					  const uint32_t stride,
					  const uint32_t rounding)
{
	int32_t ddx, ddy;

	switch (((dx & 1) << 1) + (dy & 1))	// ((dx%2)?2:0)+((dy%2)?1:0)
	{
	case 0:
		ddx = dx / 2;
		ddy = dy / 2;
		transfer8x8_copy(cur + y * stride + x,
						 refn + (int)((y + ddy) * stride + x + ddx), stride);
		break;

	case 1:
		ddx = dx / 2;
		ddy = (dy - 1) / 2;
		interpolate8x8_halfpel_v(cur + y * stride + x,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								 rounding);
		break;

	case 2:
		ddx = (dx - 1) / 2;
		ddy = dy / 2;
		interpolate8x8_halfpel_h(cur + y * stride + x,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								 rounding);
		break;

	default:
		ddx = (dx - 1) / 2;
		ddy = (dy - 1) / 2;
		interpolate8x8_halfpel_hv(cur + y * stride + x,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								  rounding);
		break;
	}
}

static __inline uint8_t *
interpolate8x8_switch2(uint8_t * const buffer,
					  const uint8_t * const refn,
					  const uint32_t x,
					  const uint32_t y,
					  const int32_t dx,
					  const int dy,
					  const uint32_t stride,
					  const uint32_t rounding)
{
	int32_t ddx, ddy;

	switch (((dx & 1) << 1) + (dy & 1))	// ((dx%2)?2:0)+((dy%2)?1:0)
	{
	case 0:
		return (uint8_t *)refn + (int)((y + dy/2) * stride + x + dx/2);

	case 1:
		ddx = dx / 2;
		ddy = (dy - 1) / 2;
		interpolate8x8_halfpel_v(buffer,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								 rounding);
		break;

	case 2:
		ddx = (dx - 1) / 2;
		ddy = dy / 2;
		interpolate8x8_halfpel_h(buffer,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								 rounding);
		break;

	default:
		ddx = (dx - 1) / 2;
		ddy = (dy - 1) / 2;
		interpolate8x8_halfpel_hv(buffer,
								 refn + (int)((y + ddy) * stride + x + ddx), stride,
								  rounding);
		break;
	}
	return buffer;
}

static __inline void interpolate8x8_quarterpel(uint8_t * const cur,
				     uint8_t * const refn,
					 uint8_t * const refh,
					 uint8_t * const refv,
					 uint8_t * const refhv,
				     const uint32_t x, const uint32_t y,
					 const int32_t dx,  const int dy,
					 const uint32_t stride,
					 const uint32_t rounding)
{
	const int32_t xRef = x*4 + dx;
	const int32_t yRef = y*4 + dy;

	uint8_t *src, *dst;
	uint8_t *halfpel_h, *halfpel_v, *halfpel_hv;
	int32_t x_int, y_int, x_frac, y_frac;

	x_int = xRef/4;
	if (xRef < 0 && xRef % 4) 
		x_int--;

	x_frac = xRef - (4*x_int); 

	y_int  = yRef/4;
	if (yRef < 0 && yRef % 4)
		y_int--;

	y_frac = yRef - (4*y_int);
 
	src = refn + y_int * stride + x_int;
	halfpel_h = refh;
	halfpel_v = refv;
	halfpel_hv = refhv;

	dst = cur + y * stride + x;
	
	switch((y_frac << 2) | (x_frac)) {

	case 0:
		transfer8x8_copy(dst, src, stride);
		break;

	case 1:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, src, halfpel_h, stride, rounding, 8);
  		break;
  
	case 2:
	    interpolate8x8_lowpass_h(dst, src, stride, rounding);
  		break;
  
	case 3:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, src + 1, halfpel_h, stride, rounding, 8);
  		break;
  
	case 4:
		interpolate8x8_lowpass_v(halfpel_v, src, stride, rounding);
		interpolate8x8_avg2(dst, src, halfpel_v, stride, rounding, 8);
 		break;
   
	case 5:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_v, halfpel_hv, stride, rounding, 8);
 		break;
   
	case 6:
		interpolate8x8_lowpass_hv(halfpel_hv, halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_h, halfpel_hv, stride, rounding, 8);
 		break;
   
	case 7:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src + 1, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_v, halfpel_hv, stride, rounding, 8);
 		break;
   
	case 8:
	    interpolate8x8_lowpass_v(dst, src, stride, rounding);
		break;

	case 9:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(dst, halfpel_v, stride, rounding);
  		break;
  
	case 10:
		interpolate8x8_lowpass_hv(dst, halfpel_h, src, stride, rounding);
		break;
  
	case 11:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src + 1, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(dst, halfpel_v, stride, rounding);
   		break;
 
	case 12:
		interpolate8x8_lowpass_v(halfpel_v, src, stride, rounding);
		interpolate8x8_avg2(dst, src+stride, halfpel_v, stride, rounding, 8);
   		break;
 
	case 13:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_v+stride, halfpel_hv, stride, rounding, 8);
 		break;
   
	case 14:
		interpolate8x8_lowpass_hv(halfpel_hv, halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_h+stride, halfpel_hv, stride, rounding, 8);
 		break;
   
	case 15:
		interpolate8x8_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src + 1, halfpel_h, stride, rounding, 9);
		interpolate8x8_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_hv, halfpel_v + stride, stride, rounding, 8);
		break;
	}
}

static __inline void interpolate16x16_quarterpel(uint8_t * const cur,
				     uint8_t * const refn,
					 uint8_t * const refh,
					 uint8_t * const refv,
					 uint8_t * const refhv,
				     const uint32_t x, const uint32_t y,
					 const int32_t dx,  const int dy,
					 const uint32_t stride,
					 const uint32_t rounding)
{
	const int32_t xRef = x*4 + dx;
	const int32_t yRef = y*4 + dy;

	uint8_t *src, *dst;
	uint8_t *halfpel_h, *halfpel_v, *halfpel_hv;
	int32_t x_int, y_int, x_frac, y_frac;

	x_int = xRef/4;
	if (xRef < 0 && xRef % 4) 
		x_int--;

	x_frac = xRef - (4*x_int); 

	y_int  = yRef/4;
	if (yRef < 0 && yRef % 4)
		y_int--;

	y_frac = yRef - (4*y_int);
 
	src = refn + y_int * stride + x_int;
	halfpel_h = refh;
	halfpel_v = refv;
	halfpel_hv = refhv;

	dst = cur + y * stride + x;

	switch((y_frac << 2) | (x_frac)) {

	case 0:
		transfer8x8_copy(dst, src, stride);
		transfer8x8_copy(dst+8, src+8, stride);
		transfer8x8_copy(dst+8*stride, src+8*stride, stride);
		transfer8x8_copy(dst+8*stride+8, src+8*stride+8, stride);
		break;

	case 1:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, src, halfpel_h, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, src+8, halfpel_h+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, src+8*stride, halfpel_h+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, src+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 8);
		break;

	case 2:
	    interpolate16x16_lowpass_h(dst, src, stride, rounding);
  		break;
  
	case 3:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, src + 1, halfpel_h, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, src + 8 + 1, halfpel_h+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, src + 8*stride + 1, halfpel_h+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, src+8*stride+8 + 1, halfpel_h+8*stride+8, stride, rounding, 8);
		break;

	case 4:
		interpolate16x16_lowpass_v(halfpel_v, src, stride, rounding);
		interpolate8x8_avg2(dst, src, halfpel_v, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, src+8, halfpel_v+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, src+8*stride, halfpel_v+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, src+8*stride+8, halfpel_v+8*stride+8, stride, rounding, 8);
		break;
	
	case 5:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);

		interpolate16x16_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_hv, halfpel_v, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_hv+8, halfpel_v+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_hv+8*stride, halfpel_v+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_hv+8*stride+8, halfpel_v+8*stride+8, stride, rounding, 8);
		break;
   
	case 6:
		interpolate16x16_lowpass_hv(halfpel_hv, halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_h, halfpel_hv, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_h+8, halfpel_hv+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_h+8*stride, halfpel_hv+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_h+8*stride+8, halfpel_hv+8*stride+8, stride, rounding, 8);
		break;
   
	case 7:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src+1, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src+1 + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src+1 + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+1+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);

		interpolate16x16_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_hv, halfpel_v, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_hv+8, halfpel_v+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_hv+8*stride, halfpel_v+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_hv+8*stride+8, halfpel_v+8*stride+8, stride, rounding, 8);
		break;
   
	case 8:
	    interpolate16x16_lowpass_v(dst, src, stride, rounding);
		break;

	case 9:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);
		interpolate16x16_lowpass_v(dst, halfpel_v, stride, rounding);
		break;
  
	case 10:
		interpolate16x16_lowpass_hv(dst, halfpel_h, src, stride, rounding);
		break;
  
	case 11:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src+1, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src+1 + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src+1 + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+1+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);
		interpolate16x16_lowpass_v(dst, halfpel_v, stride, rounding);
		break;
 
	case 12:
		interpolate16x16_lowpass_v(halfpel_v, src, stride, rounding);
		interpolate8x8_avg2(dst, src+stride, halfpel_v, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, src+stride+8, halfpel_v+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, src+stride+8*stride, halfpel_v+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, src+stride+8*stride+8, halfpel_v+8*stride+8, stride, rounding, 8);
		break;
 
	case 13:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);

		interpolate16x16_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_hv, halfpel_v+stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_hv+8, halfpel_v+stride+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_hv+8*stride, halfpel_v+stride+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_hv+8*stride+8, halfpel_v+stride+8*stride+8, stride, rounding, 8);
		break;
   
	case 14:
		interpolate16x16_lowpass_hv(halfpel_hv, halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_h+stride, halfpel_hv, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_h+stride+8, halfpel_hv+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_h+stride+8*stride, halfpel_hv+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_h+stride+8*stride+8, halfpel_hv+8*stride+8, stride, rounding, 8);
		break;
   
	case 15:
		interpolate16x16_lowpass_h(halfpel_h, src, stride, rounding);
		interpolate8x8_avg2(halfpel_v, src+1, halfpel_h, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8, src+1 + 8, halfpel_h+8, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride, src+1 + 8*stride, halfpel_h+8*stride, stride, rounding, 9);
		interpolate8x8_avg2(halfpel_v+8*stride+8, src+1+8*stride+8, halfpel_h+8*stride+8, stride, rounding, 9);

		interpolate16x16_lowpass_v(halfpel_hv, halfpel_v, stride, rounding);
		interpolate8x8_avg2(dst, halfpel_hv, halfpel_v+stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8, halfpel_hv+8, halfpel_v+stride+8, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride, halfpel_hv+8*stride, halfpel_v+stride+8*stride, stride, rounding, 8);
		interpolate8x8_avg2(dst+8*stride+8, halfpel_hv+8*stride+8, halfpel_v+stride+8*stride+8, stride, rounding, 8);
		break;
	}
}
#endif
