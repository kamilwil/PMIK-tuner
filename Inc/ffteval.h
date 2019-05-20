/*
	ffteval.h
	
	Header file for FFT evaluation
*/

#ifndef FFTEVAL_H_
#define FFTEVAL_H_

#include "stm32f3xx_hal.h"
#include "arm_math.h"

extern const uint32_t FFT_SIZE;
extern unsigned char *fft_input;
extern arm_rfft_instance_q15 fft_instance;
extern q15_t *fft_output;
extern arm_status fft_status;

void FFT_Test(void);


#endif // FFTEVAL_H_
