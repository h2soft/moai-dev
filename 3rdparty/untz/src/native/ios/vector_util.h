/*
 *  vector_util.h
 *  dopplerpad
 *
 *  Created by dan walton on 5/3/09.
 *  Copyright 2009 Retronyms. All rights reserved.
 *
 */

void vector_fmul_vfp(float *dst, const float *src, int len);
void vector_fmul1_vfp(float *dst, const float *src, float *mult, int len);
void vector_fmac1_vfp(float *dst, const float *src, float *mult, int len);
void float_to_int16_vfp(short *dst,  float *src, int len);
void limit_float(float *srcdest,int numSamples);