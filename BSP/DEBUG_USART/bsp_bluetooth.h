<<<<<<< HEAD

=======
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2
#ifndef __BSP_USART_H
#define	__BSP_USART_H

#include "stm32f4xx.h"
#include "stdio.h"

<<<<<<< HEAD

//���Ŷ���
/*******************************************************/
#define DEBUG_USART                             USART2



#define DEBUG_USART_CLK                         RCC_APB1Periph_USART2
#define DEBUG_USART_BAUDRATE                    115200//���ڲ�����

#define DEBUG_USART_RX_GPIO_PORT                GPIOD
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_RX_PIN                      GPIO_Pin_6
#define DEBUG_USART_RX_AF                       GPIO_AF_USART2
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource6

#define DEBUG_USART_TX_GPIO_PORT                GPIOD
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_TX_PIN                      GPIO_Pin_5
#define DEBUG_USART_TX_AF                       GPIO_AF_USART2
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource5

#define DEBUG_USART_IRQHandler                  USART2_IRQHandler
#define DEBUG_USART_IRQ                 				USART2_IRQn

  
void Debug_USART_Config(void);
void USART_SendByte (USART_TypeDef * pUSARTx ,char ch );
void USART_SendString(USART_TypeDef * pUSARTx, char *str);

void DEBUG_USART_IRQHandler(void) ;

#endif /* __BSP_USART_H */
=======
#define DEBUG_USART                             USART1


#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE                    9600 //���ڲ�����

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                 				USART1_IRQn


void Debug_USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
#endif 
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2

