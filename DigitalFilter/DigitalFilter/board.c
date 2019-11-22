/*
 * board.c
 *
 * Created: 18/11/2019 13:53:56
 *  Author: Luuk Bleijendaal
 */ 

#include <sam.h>
#include "board.h"

static inline void tcm_disable(void)
{

	__DSB();
	__ISB();
	SCB->ITCMCR &= ~(uint32_t)(1UL);
	SCB->DTCMCR &= ~(uint32_t)SCB_DTCMCR_EN_Msk;
	__DSB();
	__ISB();
}


void ioport_init()
{
	/* Initialize IOPORTs */
	PMC->PMC_PCR = PMC_PCR_PID(ID_PIOA);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	PMC->PMC_PCR = PMC_PCR_PID(ID_PIOB);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	PMC->PMC_PCR = PMC_PCR_PID(ID_PIOC);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	PMC->PMC_PCR = PMC_PCR_PID(ID_PIOD);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	PMC->PMC_PCR = PMC_PCR_PID(ID_PIOE);
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;
	
	/* Configure the pins connected to LED as output and set their
	 * default initial state to high (LED off).
	 */
	PIOC->PIO_OER |= PIO_PC8;
	PIOC->PIO_OWER |= PIO_PC8;
	PIOC->PIO_CODR |= PIO_PC8;
	
	
	//PIOB->PIO_PDR |= PIO_PB13;
	//PIOB->PIO_OWER |= PIO_PB13;

	

	
	/* Configure Push Button pins */
	PIOA->PIO_ODR |= PIO_PA11;
	PIOA->PIO_OWER |= PIO_PA11;
	PIOA->PIO_PUER |= PIO_PA11;
	PIOA->PIO_PPDDR |= PIO_PA11;
	PIOA->PIO_MDDR |= PIO_PA11;
	PIOA->PIO_IFER |= PIO_PA11;
	PIOA->PIO_IFSCER |= PIO_PA11;
	PIOA->PIO_ABCDSR[0] &= ~(PIO_PA11);
	PIOA->PIO_ABCDSR[1] &= ~(PIO_PA11);
	PIOA->PIO_ESR |= PIO_PA11;
	PIOA->PIO_REHLSR |= PIO_PA11;
	PIOA->PIO_AIMER |= PIO_PA11;
}

void board_init()
{
	/* Disable Watchdog */
	WDT->WDT_MR |= WDT_MR_WDDIS;
	
	/* Enabling the Cache */
	SCB_EnableICache();
	SCB_EnableDCache();
	
	/* TCM Configuration */
	EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_CGPB
	| EEFC_FCR_FARG(8));
	EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_CGPB
	| EEFC_FCR_FARG(7));
	
	tcm_disable();
	
	ioport_init();
}

