

/**
  ******************************************************************************
  * @file    harware.c
  * @author  wolfik
  * @version V0.0.1
  * @date    19-06-2078
  * @brief   Hardware Acces Level
  ******************************************************************************
  * @attention
  * This file consists functions for working with different periphiral of MK.
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hardware.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Protocol defines*/
#define MAINCHANEL		USART1
#define RESERVCHANEL	USART3

#define MAINPORT		GPIOA
#define MAINTX			GPIO_Pin_9
#define MAINRX			GPIO_Pin_10

#ifdef EVAL_BOARD
#define RESERVPORT		GPIOC
#else 
#define RESERVPORT		GPIOB
#endif
#define RESERVTX		GPIO_Pin_10
#define RESERVRX		GPIO_Pin_11


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void initializeMCO1(void);
void initializeRS485 (void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize all nessesery periphery.
  * @param  None
  * @retval None
  */
void initialization (void)
{
	/*Initialize system frequancy is already done in system_stm32f2xx.c*/
	
	/*1) initialize clock signals for used GPIO*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | 
						   RCC_AHB1Periph_GPIOB | 
						   RCC_AHB1Periph_GPIOC | 
						   RCC_AHB1Periph_GPIOD | 
						   RCC_AHB1Periph_GPIOE | 
						   RCC_AHB1Periph_GPIOF | 
						   RCC_AHB1Periph_GPIOG | 
						   RCC_AHB1Periph_GPIOH , ENABLE);
	
	/*2) Initialize DEBUG signal of PLL/2*/
	#ifdef DEBUG
	initializeMCO1();
	#endif
	
	/*3) initialize RS485*/
	initializeRS485();
}


/**
  * @brief  Initialize MCO1 for output PLL/2.
  * @param  None
  * @retval None
  */
void initializeMCO1(void)
{
	GPIO_InitTypeDef mcoPin;
		
	mcoPin.GPIO_Mode	=	GPIO_Mode_AF;
	mcoPin.GPIO_OType	=	GPIO_OType_PP;
	mcoPin.GPIO_Pin		=	GPIO_Pin_8;
	mcoPin.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	mcoPin.GPIO_Speed	=	GPIO_Speed_100MHz;
	
	
	GPIO_Init(GPIOA, &mcoPin);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
	
	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);
}

/**
  * @brief  Initialize RS485.
  * @param  None
  * @retval None
  */
void initializeRS485 (void)
{
	/* Initialize Main channel*/
	
	/* Eneable Clocks for USART*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	/*Connect pins to UART TX and RX*/
	GPIO_PinAFConfig(MAINPORT, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(MAINPORT, GPIO_PinSource10, GPIO_AF_USART1);
	
	 /* Configure USART Tx as alternate function  */
	GPIO_InitTypeDef pinConfigStruct;
	
	pinConfigStruct.GPIO_OType = GPIO_OType_PP;
	pinConfigStruct.GPIO_PuPd = GPIO_PuPd_UP;
	pinConfigStruct.GPIO_Mode = GPIO_Mode_AF;

	pinConfigStruct.GPIO_Pin = MAINTX;
	pinConfigStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &pinConfigStruct);
	
	/* Configure USART Rx as alternate function  */
	pinConfigStruct.GPIO_Pin = MAINRX;
	GPIO_Init(MAINPORT, &pinConfigStruct);
	
	/*Configure RS485 Control Pin*/
	pinConfigStruct.GPIO_Mode = GPIO_Mode_OUT;
	pinConfigStruct.GPIO_Pin = GPIO_Pin_11;
	pinConfigStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA, &pinConfigStruct);
	
	USART_InitTypeDef uartConfigStruct;
	
	uartConfigStruct.USART_BaudRate = 9600;
	uartConfigStruct.USART_WordLength = USART_WordLength_8b;
	uartConfigStruct.USART_StopBits = USART_StopBits_1;
	uartConfigStruct.USART_Parity = USART_Parity_No; 
	uartConfigStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartConfigStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(MAINCHANEL, &uartConfigStruct);
	USART_Cmd(MAINCHANEL, ENABLE);
	
	
	/* Initialize Reserv channel*/
	
	/* Eneable Clocks for USART*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	/*Connect pins to UART TX and RX*/
	GPIO_PinAFConfig(RESERVPORT, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(RESERVPORT, GPIO_PinSource11, GPIO_AF_USART3);
	
	 /* Configure USART Tx as alternate function  */
	//GPIO_InitTypeDef pinConfigStruct;
	
	pinConfigStruct.GPIO_OType = GPIO_OType_PP;
	pinConfigStruct.GPIO_PuPd = GPIO_PuPd_UP;
	pinConfigStruct.GPIO_Mode = GPIO_Mode_AF;

	pinConfigStruct.GPIO_Pin = RESERVTX;
	pinConfigStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RESERVPORT, &pinConfigStruct);
	
	/* Configure USART Rx as alternate function  */
	pinConfigStruct.GPIO_Pin = RESERVRX;
	GPIO_Init(RESERVPORT, &pinConfigStruct);
	
	/*Configure RS485 Control Pin*/
	pinConfigStruct.GPIO_Mode = GPIO_Mode_OUT;
	pinConfigStruct.GPIO_Pin = GPIO_Pin_14;
	pinConfigStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOB, &pinConfigStruct);
	/*
	USART_InitTypeDef uartConfigStruct;
	
	uartConfigStruct.USART_BaudRate = 9600;
	uartConfigStruct.USART_WordLength = USART_WordLength_8b;
	uartConfigStruct.USART_StopBits = USART_StopBits_1;
	uartConfigStruct.USART_Parity = USART_Parity_No; 
	uartConfigStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartConfigStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	*/
	USART_Init(RESERVCHANEL, &uartConfigStruct);
	USART_Cmd(RESERVCHANEL, ENABLE);
}


/******************* AME 2018*****END OF FILE****/
