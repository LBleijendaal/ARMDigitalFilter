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
	afec0ch0_init(0x3);
	dac0ch0init();
	
	//dac();
	
    /* Replace with your application code */
    while (1) 
    {
		
	}	
}
void AFEC0_Handler(void)
{
	
	uint32_t status = AFEC0->AFEC_ISR;
	
	PIOC->PIO_SODR |= PIO_PC8;
	
	if((status & AFEC_IMR_EOC0) == 1) {
		
		tmp = AFEC0->AFEC_CDR;
		boolean = 1;
		
		if( ((((DACC->DACC_ISR) & DACC_ISR_TXRDY0_Msk)) == 1) && ((DACC -> DACC_CHSR) & (0x1u << 8)) == 256 ) 
		{
			DACC->DACC_CDR[0] = DACC_CDR_DATA0(tmp);
			PIOC->PIO_SODR |= PIO_PC8;
		}
		
		if(((DACC->DACC_ISR) & (0x01)) == 0) 
		{
			PIOC->PIO_CODR |= PIO_PC8;
		}
		
	}
	
	AFEC0->AFEC_CR = AFEC_CR_START;
}

void DACC_Handler(void) {

}

