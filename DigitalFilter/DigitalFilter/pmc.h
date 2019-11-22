/*
 * pmc.h
 *
 * Created: 18/11/2019 13:49:42
 *  Author: luuk_
 */ 


#ifndef PMC_H_
#define PMC_H_


#define F_CPU 300000000UL
#define F_PER (F_CPU / 2)
#define F_XOSC 12000000UL

#define EFC_WAIT_STATE 6
#define XOSC12M_STARTUP_TIME 62				// Start up time for the external oscillator (ms): <0-256>
#define PLL_STARTUP_TIME  0x3fU				// Startup time PLL

uint32_t mainclk_init();
uint32_t pll_init();
uint32_t sysclk_init();


#endif /* PMC_H_ */