/*
 * tim.c
 *
 * Created: 29/11/2019 16:09:56
 *  Author: Luuk Bleijendaal
 */ 

#include <stdio.h>
#include "sam.h"
#include "tim.h"

void initTimer(void)
{
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, 1);
	NVIC_EnableIRQ(TC0_IRQn);
	
	PMC->PMC_PCR |= PMC_PCR_PID(ID_TC0);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	//REG_PMC_PCER0 |= PMC_PCER0_PID23;
	
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2;
	REG_TC0_IER0 |= TC_IER_CPCS_Msk;
	REG_TC0_CMR0 |= TC_CMR_CPCTRG_Msk;
	
	REG_TC0_CCR0 |= TC_CCR_CLKEN;
	
	REG_TC0_RC0 = 187;
	REG_TC0_CCR0 |= TC_CCR_CLKEN;
	REG_TC0_CCR0 |= TC_CCR_SWTRG;
}

/*
void initTimer(void)
{
	
	
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	TC1->TcChannel[0].TC_CCR = 0x000;
	TC1->TcChannel[0].TC_CCR = TC_CCR_CLKEN;// | TC_CCR_SWTRG;
	
	//TC0->TcChannel[0].TC_CCR = TC_CCR_CLKDIS;
	
	//TC0->TcChannel[0].TC_IDR = 0xFFFFFFFF;
	
	TC1->TcChannel[0].TC_CMR |= (TC_CMR_WAVE | TC_CMR_WAVEFORM_WAVSEL_UP_RC);
	TC1->TcChannel[0].TC_CMR |= (TC_CMR_TCCLKS_TIMER_CLOCK4);
	
	//TC0->TcChannel[0].TC_EMR |= TC_EMR_NODIVCLK_Msk;
	
	TC1->TcChannel[0].TC_RC = 0xFFFF;
	
	NVIC_ClearPendingIRQ(TC1_IRQn);
	NVIC_SetPriority(TC1_IRQn, 1);
	NVIC_EnableIRQ(TC1_IRQn);
	
	TC1->TcChannel[0].TC_IER |= TC_IER_CPCS_Msk | TC_IER_COVFS_Msk;
	
	TC1->TcChannel[0].TC_CCR = TC_CCR_CLKEN;
	TC1->TcChannel[0].TC_CCR |= TC_CCR_SWTRG;
	
	
	
	REG_TC0_CMR0
	
	
	
}

*/