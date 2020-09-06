#include "bsp_bluetooth.h"

<<<<<<< HEAD
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void Debug_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK,ENABLE);
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ; 
	
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
=======

void Debug_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* ��һ������ʼ��GPIO */
	 RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK,ENABLE);
	
	  /* GPIO��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	  /* ����Rx����Ϊ���ù��� */
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
<<<<<<< HEAD
  GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
  GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
	
	
	
	
	
	RCC_APB1PeriphClockCmd(DEBUG_USART_CLK, ENABLE);
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(DEBUG_USART, &USART_InitStructure);
	
  USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
	
  USART_Cmd(DEBUG_USART, ENABLE);
	//NVIC_Configuration();
=======
	/* GPIO���帴�ó�ʲô */
	 /* ���� PXx �� USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
  /*  ���� PXx �� USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
	
	/* �ڶ��������ô��ڳ�ʼ���ṹ�� */
	  /* ʹ�� USART ʱ�� */
  RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);
	  /* ���ô�DEBUG_USART ģʽ */
  /* ���������ã�DEBUG_USART_BAUDRATE */
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  /* �ֳ�(����λ+У��λ)��8 */
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* ֹͣλ��1��ֹͣλ */
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* У��λѡ�񣺲�ʹ��У�� */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  /* Ӳ�������ƣ���ʹ��Ӳ���� */
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  /* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* ���USART��ʼ������ */
  USART_Init(DEBUG_USART, &USART_InitStructure);
	
	
	/* ʹ�ܴ��� */
  USART_Cmd(DEBUG_USART, ENABLE);
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2
}



<<<<<<< HEAD


//����һ���ַ�����
void USART_SendByte (USART_TypeDef * pUSARTx ,char ch)
{
   USART_SendData( pUSARTx, ch);
	 while(USART_GetFlagStatus( pUSARTx ,USART_FLAG_TXE)==RESET); 

}

//�����ַ���
void USART_SendString(USART_TypeDef * pUSARTx, char *str)
{unsigned int k=0;
	
	do{
		 USART_SendByte(pUSARTx, *(str+k));
	   k++;
	  }while(*(str+k)!='\0');
		
	 while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC)==RESET)
   {}
   }


//ʹ��Printf�����񴮿ڷ�����Ϣ
	 int fputc(int ch, FILE *f)
	 {
		USART_SendData(USART2, (uint8_t) ch );
		while(USART_GetFlagStatus( USART2 ,USART_FLAG_TXE)==RESET); 
		return ch;
	 }
//ʹ��getchar �� scanf �������մ�����Ϣ��
	 int fgetc(FILE *f)
	 {
		 while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE )==RESET);
		 return (int)USART_ReceiveData(USART2);
		 
	 }
	 
=======
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		

	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}



void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  

  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


int fgetc(FILE *f)
{
		
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}
>>>>>>> dd2629fede7cb2404575abbd2be5e1ad1e7f73d2
