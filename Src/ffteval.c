/* ffteval.c
	
	Encapsulated function for fft evaluation
*/

#include "ffteval.h"
#include "FFT_test1.inc"

const uint32_t FFT_SIZE = 256;
unsigned char *fft_input = FFT_test1_raw;
arm_rfft_instance_q15 fft_instance;
q15_t *fft_output;
arm_status fft_status;

void FFT_Test(void)
{
	
	
	fft_status = arm_rfft_init_q15(&fft_instance, FFT_SIZE, 0, 1);
	arm_rfft_q15(&fft_instance, (q15_t*)fft_input, fft_output);
	arm_abs_q15(fft_output, fft_output, FFT_SIZE);
}
