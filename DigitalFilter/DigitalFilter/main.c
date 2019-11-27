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

static volatile uint32_t data = 1024;
static volatile uint32_t updated;

void fillFIFO(void);

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
		if(((DACC->DACC_ISR) & DACC_ISR_TXRDY0_Msk) == 1) {
			fillFIFO();
		}	
	}

		
		
			
    
}

void fillFIFO(void) 
{
	for(int i = 0; i < 5; i++) {
		DACC->DACC_CDR[0] = DACC_CDR_DATA0(data);
	}
	
	if(1) {
		data = 1000;
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
	
	
	//uint32_t status = ;
	//uint32_t status2 = DACC->DACC_CHSR;
	if( ((((DACC->DACC_ISR) & DACC_ISR_TXRDY0_Msk)) == 1) && ((DACC -> DACC_CHSR) & (0x1u << 8)) == 256 ) {
		//fillFIFO();
	}     	
}

