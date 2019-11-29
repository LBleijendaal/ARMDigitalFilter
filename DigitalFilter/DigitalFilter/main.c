/*
 * DigitalFilter.c
 *
 * Created: 21/11/2019 11:36:23
 * Author : Luuk Bleijendaal
 */ 

#include <stdio.h>
#include <inttypes.h>
#include <float.h>

#include "sam.h"
#include "board.h"
#include "pmc.h"
#include "afec.h"
#include "dac.h"
#include "fpu.h"
#include "fir.h"

float tmp;

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
	fpu_enable();
	
    /* Replace with your application code */
    while (1) 
    {
		asm volatile ("nop");
	}	
}
void AFEC0_Handler(void)
{
	uint32_t status = AFEC0->AFEC_ISR;
	
	if((status & AFEC_IMR_EOC0) == 1) {
	
		tmp = AFEC0->AFEC_CDR;
		
		//tmp = firFilter((float)AFEC0->AFEC_CDR);
	
		if( ((((DACC->DACC_ISR) & DACC_ISR_TXRDY0_Msk)) == 1) && ((DACC -> DACC_CHSR) & (0x1u << 8)) == 256 ) 
		{
			DACC->DACC_CDR[0] = DACC_CDR_DATA0((uint32_t)tmp);
			
		}
		
		if(((DACC->DACC_ISR) & (0x01)) == 0) 
		{
			
		}
		
	}
	AFEC0->AFEC_CR = AFEC_CR_START;
}

void DACC_Handler(void) {

}

