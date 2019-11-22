/*
 * DigitalFilter.c
 *
 * Created: 21/11/2019 11:36:23
 * Author : Luuk Bleijendaal
 */ 

#include <stdio.h>
#include <inttypes.h>

#include "sam.h"
#include "board.h"
#include "pmc.h"
#include "afec.h"
#include "dac.h"

uint32_t tmp;
uint32_t boolean = 0;

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	sysclk_init();
	board_init();
	//afec0ch0_init(0xFF);
	dac0ch0init();
	
	//dac();
	
    /* Replace with your application code */
    while (1) 
    {
			
    }
}

void AFEC0_Handler(void)
{
	PIOC->PIO_SODR |= PIO_PC8;
	uint32_t status = AFEC0->AFEC_ISR;
	if((status & AFEC_IMR_EOC0) == 1) {
		PIOC->PIO_CODR |= PIO_PC8;
		tmp = AFEC0->AFEC_CDR;
		boolean = 1;
	}
	AFEC0->AFEC_CR = AFEC_CR_START;
}

void DACC_Handler(void) {
	
	
	uint32_t status = DACC->DACC_ISR;
	if((status & DACC_ISR_EOC0_Msk) == 1) {
		
	}     	
}

