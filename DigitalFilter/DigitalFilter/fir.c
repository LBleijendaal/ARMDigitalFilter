/*
 * fir.c
 *
 * Created: 28/11/2019 16:41:02
 *  Author: Luuk Bleijendaal
 */ 

#include <stdio.h>

#include "fir.h"

#include "tmwtypes.h"

//F pass: 200 Hz
//F stop: 4150 Hz
//Fs    : 100 kHz

const uint32_t N_coefficients = 51;
const float coefficients[51] = {
	0.0001654817769905, 0.002890976162645,  0.00226828575227, 0.003228241791065,
	0.004271360224449, 0.005493165213566, 0.006891012204096, 0.008460924402888,
	0.01019666751253,  0.01208459879706,  0.01410861605553,  0.01624527864674,
	0.01846733119722,  0.02074452371352,  0.02304200827184,  0.02532158499598,
	0.02754330591101,  0.02966782978311,  0.03165734475424,   0.0334704229473,
	0.0350732342115,  0.03643170898347,   0.0375204190111,  0.03831308001911,
	0.03879493311723,  0.03895897364476,  0.03879493311723,  0.03831308001911,
	0.0375204190111,  0.03643170898347,   0.0350732342115,   0.0334704229473,
	0.03165734475424,  0.02966782978311,  0.02754330591101,  0.02532158499598,
	0.02304200827184,  0.02074452371352,  0.01846733119722,  0.01624527864674,
	0.01410861605553,  0.01208459879706,  0.01019666751253, 0.008460924402888,
	0.006891012204096, 0.005493165213566, 0.004271360224449, 0.003228241791065,
	0.00226828575227, 0.002890976162645,0.0001654817769905
};

static float buffer[51];
static uint32_t offset;


float firFilter(float input)
{
	float output;
	
	for(int i = (N_coefficients - 1); i > 0; i--) {
		buffer[i] = buffer[i-1];
	}
	
	buffer[0] = input;
	
	for(int i = 0; i < N_coefficients; i++) {
		output += buffer[i] * coefficients[i];
	}
	
	return output;
}


/*
float firFilter(float input) 
{
	float *coeff = coefficients;
	float *coeff_end = coefficients + N_coefficients;
	
	float *buf_val = buffer + offset;
	
	*buf_val = input;
	
	float output = 0;
	
	while(buf_val >= buffer) 
	{
		output += *buf_val-- * *coeff++;
	}
	
	buf_val = buffer + N_coefficients - 1;
	
	while(coeff < coeff_end)
	{
		output += (*buf_val-- * *coeff++);
	}
	
	if(++offset >= N_coefficients)
	{
		offset = 0;
	}
	
	return output;
	
}
*/