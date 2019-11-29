/*
 * adc.h
 *
 * Created: 18/11/2019 16:08:36
 *  Author: Luuk Bleijendaal
 */ 


#ifndef AFEC_H_
#define AFEC_H_


#define	  AFEC0_CH0				0x00u
void afec0ch0_init(uint32_t prescaler);

uint32_t configure_tc_trigger_afec0(uint32_t freq, uint32_t pres);

#endif /* AFEC_H_ */