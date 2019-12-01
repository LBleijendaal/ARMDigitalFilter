/*
 * afec.c
 *
 * Created: 21/11/2019 12:37:49
 *  Author: Luuk Bleijendaal
 */ 

#include <stdio.h>

#include "sam.h"

#include "afec.h"
#include <stdlib.h>


void afec0ch0_init(uint32_t prescaler)
{
	/* Enable AFEC0 peripheral's clock. */
	PMC->PMC_PCR = PMC_PCR_PID(ID_AFEC0);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	/* Reset and configure the AFEC module */
	AFEC0->AFEC_CR = AFEC_CR_SWRST;
	
	AFEC0->AFEC_MR = AFEC_MR_PRESCAL(prescaler) 
	| AFEC_MR_ONE 
	| AFEC_MR_TRANSFER(0x02) 											// Set to 2 to optimize transfer time.
	| AFEC_MR_STARTUP_SUT64												// Start Up Time is 64 periods AFEC clock.
	| AFEC_MR_TRACKTIM(0xF);											// Inherent tracking time is always 15 AFE clock cycles. Do not modify this field.
	
	AFEC0->AFEC_EMR = AFEC_EMR_RES_NO_AVERAGE									// 12-bit resolution, AFE sample rate is maximum (no averaging).	
	| AFEC_EMR_STM														// Only a single trigger is required to get an averaged value.
	| AFEC_EMR_SIGNMODE_SE_UNSG_DF_SIGN;								// Single-Ended channels: unsigned conversions. Differential channels: signed conversions.
	
	AFEC0->AFEC_ACR = AFEC_ACR_IBCTL(0x03) | AFEC_ACR_PGA0EN | AFEC_ACR_PGA1EN;
	
	//AFEC0->AFEC_MR |= AFEC_MR_FREERUN_OFF;								
	
	
	//AFEC0->AFEC_MR |= AFEC_MR_TRGSEL_AFEC_TRIG1;						// Trigger TIOA Output of the Timer Counter Channel 0 for AFEC0
	//AFEC0->AFEC_MR |= AFEC_MR_TRGEN;									// Enable Hardware Trigger
	/*
	 * The field AOFF must be configured to 512 (mid scale of the DAC) when there is no offset error to
	 * compensate.
	 */
	AFEC0->AFEC_CSELR = AFEC_CSELR_CSEL(AFEC0_CH0);
	AFEC0->AFEC_COCR = AFEC_COCR_AOFF(0x200);

	/* Enable end of conversion interrupt for channel 0 */
	
	NVIC_ClearPendingIRQ(AFEC0_IRQn);
	NVIC_SetPriority(AFEC0_IRQn, 1);
	NVIC_EnableIRQ(AFEC0_IRQn);
	AFEC0->AFEC_IER = AFEC_IER_EOC0;
	
	
	/* Enable Channel 0 for AFEC0 */
	AFEC0->AFEC_CHER = AFEC_CHER_CH0;
	
	AFEC0->AFEC_CR = AFEC_CR_START;
}



