/*
 * dac.c
 *
 * Created: 21/11/2019 14:56:57
 *  Author: Luuk Bleijendaal
 */

#include <stdio.h>

#include "sam.h"
/*
void dac(void) 
{
	DACC -> DACC_WPMR	&=	(0x1u << 0);		//disable write protection
	DACC -> DACC_WPMR	|=	(0x444143 << 8);	//write WPKEY
	
	DACC -> DACC_CR |= (0x1u << 0); //reset dac
	DACC -> DACC_MR = 0;
	
	DACC -> DACC_CHER |= (0x1u << 0); //enable DAC0
	DACC -> DACC_ACR = 3; //adapts the slew rate of the analog output
	
	while(((DACC -> DACC_CHSR) & (0x1u << 8)) != 256);
	
	DACC -> DACC_CDR[0] = 0x0000;
}
*/
void dac0ch0init(void) 
{
	/* Enable DACC peripheral's clock. */
	PMC->PMC_PCR = PMC_PCR_PID(ID_DACC);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	/* Reset and configure the DACC module */
	DACC->DACC_CR = DACC_CR_SWRST;
	
	DACC->DACC_WPMR |= DACC_WPMR_WPKEY_PASSWD;
	DACC->DACC_WPMR |= (0x00 << 0);
	
	DACC->DACC_MR |= DACC_MR_PRESCALER(0xF)
	| DACC_MR_DIFF_DISABLED_Val
	| (0x0 << 5)
	| DACC_MR_WORD_DISABLED
	| DACC_MR_MAXS0_TRIG_EVENT ;
	
	//DACC->DACC_TRIGR |= DACC_TRIGR_OSR0(0x0);
	//DACC->DACC_TRIGR |= DACC_TRIGR_OSR1(0x0);
	
	//DACC->DACC_TRIGR |= DACC_TRIGR_TRGSEL0_TRGSEL0;
	//DACC->DACC_TRIGR |= DACC_TRIGR_TRGSEL1_TRGSEL0;
	
	DACC->DACC_TRIGR |= DACC_TRIGR_TRGEN0_DIS;
	//DACC->DACC_TRIGR |= DACC_TRIGR_TRGEN1_DIS;
	DACC->DACC_ACR |= DACC_ACR_IBCTLCH0(3);
	

	
//	NVIC_ClearPendingIRQ(DACC_IRQn);
//	NVIC_SetPriority(DACC_IRQn, 1);
//	NVIC_EnableIRQ(DACC_IRQn);
	
	
	
	uint32_t daccStatus = DACC->DACC_CHSR;
	
	DACC->DACC_CHER = DACC_CHER_CH0_Msk;
	
	while((daccStatus & DACC_CHSR_DACRDY0_Msk) == 0) daccStatus = DACC->DACC_CHSR;
	
	DACC->DACC_CDR[0] = (0x0000 << 0x00);        
	
//	DACC->DACC_IER = DACC_IER_EOC0_Msk; 	
	
	
}