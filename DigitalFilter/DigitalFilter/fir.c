/*
 * fir.c
 *
 * Created: 28/11/2019 16:41:02
 *  Author: Luuk Bleijendaal
 */ 

#include <stdio.h>

#include "fir.h"

#include "tmwtypes.h"

const uint32_t N_coefficients = 51;
const float coefficients[51] = {
	-0.0009190982084802,-0.002717696026614,-0.002486952759855, 0.003661438383488,
	0.01365092523065,   0.0173511659011, 0.007665306190435,-0.006554718869626,
	-0.00769678403705, 0.006105459421406,  0.01387391574864,0.0003508617282953,
	-0.01690892543669,-0.008905642749153,  0.01744112950086,  0.02074504452761,
	-0.01229649425194, -0.03424086590958,-0.001034529605573,   0.0477903055208,
	0.02736303791485, -0.05937951883105, -0.08230702592923,  0.06718690943287,
	0.3100151770902,   0.4300478803435,   0.3100151770902,  0.06718690943287,
	-0.08230702592923, -0.05937951883105,  0.02736303791485,   0.0477903055208,
	-0.001034529605573, -0.03424086590958, -0.01229649425194,  0.02074504452761,
	0.01744112950086,-0.008905642749153, -0.01690892543669,0.0003508617282953,
	0.01387391574864, 0.006105459421406, -0.00769678403705,-0.006554718869626,
	0.007665306190435,   0.0173511659011,  0.01365092523065, 0.003661438383488,
	-0.002486952759855,-0.002717696026614,-0.0009190982084802
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