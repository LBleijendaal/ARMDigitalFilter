/*
 * pmc.c
 *
 * Created: 18/11/2019 13:47:05
 *  Author: Luuk Bleijendaal
 */ 

#include <sam.h>
#include <stdlib.h>
#include "fpu.h"
#include "pmc.h"

/* Initialize System Clocks
 * 
 * Enable FPU and Set Flash Wait State for 300 MHz
 * 
 * Initialize Main Clk and PLL
 * Select PLL as Master Clock (150 MHz)
 *
 */

/* Enable Main XOSC (12 MHz) and select it as the Main Clock */
uint32_t mainclk_init()
{
	uint16_t tmp = 0;
	
	/* Enable Main XOSC */
	PMC->CKGR_MOR =	(PMC->CKGR_MOR & ~CKGR_MOR_MOSCXTBY)
	| CKGR_MOR_KEY_PASSWD
	| CKGR_MOR_MOSCXTEN
	| CKGR_MOR_MOSCXTST(XOSC12M_STARTUP_TIME);
	
	/* wait for XOSC to stabilize */
	while (!(PMC->PMC_SR & PMC_SR_MOSCXTS));
	
	/* Select XOSC as Main Clock */
	PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD
	| CKGR_MOR_MOSCSEL;
	
	/* wait for Main Clock to be ready */
	while(!(PMC->PMC_SR & PMC_SR_MOSCSELS));

	/* Check if Main Clock frequency is correct */
	while(!(PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY));
	tmp = (PMC->CKGR_MCFR & CKGR_MCFR_MAINF_Msk);
	
	if(tmp == 0) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
	
}


/* Enable the PLL (300 MHz) */
uint32_t pll_init()
{
	/* Stop PLL first */
	PMC->CKGR_PLLAR = CKGR_PLLAR_ONE
	| CKGR_PLLAR_MULA(0);
	
	/* Configure and enable PLL */
	PMC->CKGR_PLLAR = CKGR_PLLAR_ONE
	| CKGR_PLLAR_DIVA_BYPASS
	| CKGR_PLLAR_MULA(((F_CPU / F_XOSC) - 1))
	| CKGR_PLLAR_PLLACOUNT(PLL_STARTUP_TIME);
	
	/* Wait for PLL lock */
	while(!(PMC->PMC_SR & PMC_SR_LOCKA));
	
	return EXIT_SUCCESS;
}

uint32_t sysclk_init()
{
	fpu_enable();
	
	/* Set flash wait state */
	EFC->EEFC_FMR = EEFC_FMR_FWS(EFC_WAIT_STATE) 
	| EEFC_FMR_CLOE;
			

	mainclk_init();
	pll_init();

	
	/* Select Master Clock Div */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~PMC_MCKR_MDIV_Msk)) 
	| PMC_MCKR_MDIV_PCK_DIV2;
	/* Wait until master clock is ready */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
	
	/* Select PLL as Master Clock Source */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~PMC_MCKR_CSS_Msk))
	| PMC_MCKR_CSS_PLLA_CLK;
	/* Wait until master clock is ready */
	while(!(PMC->PMC_SR & PMC_SR_MCKRDY));
	
	return EXIT_SUCCESS;
}