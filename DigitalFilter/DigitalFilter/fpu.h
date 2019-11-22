/*
 * fpu.h
 *
 * Created: 18/11/2019 13:48:25
 *  Author: luuk_
 */ 


#ifndef FPU_H_
#define FPU_H_

/**
 * \brief Enable FPU
 */
static inline void fpu_enable(void)
{
	/** Set bits 20-23 to enable CP10 and CP11 coprocessors */
	SCB->CPACR |= (0xFu << 20);
	__DSB();
	__ISB();
}

#endif /* FPU_H_ */