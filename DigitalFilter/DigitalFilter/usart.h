/*
 * usart.h
 */ 


#ifndef USART_H_
#define USART_H_

void USARTinit(void);
void UART_Puts(const char *str);

uint8_t CanRead_Ctrl(void);
uint8_t ReadByte_Ctrl(void);
uint8_t CanWrite_Ctrl(void);
void WriteByte_Ctrl(uint8_t data);


#endif /* USART_H_ */
