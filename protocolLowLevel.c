/**
  ******************************************************************************
  * @file    protocolLowLevel.c
  * @author  wolfik
  * @version V0.0.1
  * @date    20-06-2078
  * @brief   Protocol Low Level functions
  ******************************************************************************
  * @attention
  * This file consists functions for proccess protokols Tasks.
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "protocolLowLevel.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BYTESTIME 10
#define MAX_BUFFER_SIZE 256
#define MIN_RES_BYTES 6
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t volatile inputBuff[MAX_BUFFER_SIZE];
uint16_t volatile byteCounter = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void sendRS485 (uint8_t *data, uint8_t length)
{
	DMA_InitTypeDef dmaStructCongig;
		
	DMA_StructInit(&dmaStructCongig);
	
	dmaStructCongig.DMA_Channel = DMA_Channel_4 ;
	dmaStructCongig.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	dmaStructCongig.DMA_Memory0BaseAddr = (uint32_t) data;
	dmaStructCongig.DMA_BufferSize = length;
	dmaStructCongig.DMA_PeripheralBaseAddr = (uint32_t) &(USART3->DR);
	dmaStructCongig.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_Init(DMA1_Stream3, &dmaStructCongig);
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
//	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Stream3, ENABLE);
}
/**
  * @brief  Interupt handler of USART3.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler (void)
{
	if (USART_GetFlagStatus(USART3, USART_FLAG_TC) == SET)
	{
		USART_ClearFlag(USART3, USART_FLAG_TC);
		DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3 | DMA_FLAG_HTIF3);
		DMA_Cmd(DMA1_Stream3, DISABLE);
	}
	else
	{
		TIM_SetCounter(TIM3, 0);
		TIM_SetAutoreload(TIM3, 2*BYTESTIME);
		TIM_Cmd(TIM3, ENABLE);
		if (byteCounter < MAX_BUFFER_SIZE)
		{
			inputBuff[byteCounter] = USART_ReceiveData(USART3);
			
		}
		byteCounter++;
	}
}

/**
  * @brief  Interupt handler of timer3 used as protocol timer.
  * @param  None
  * @retval None
  */	
void TIM3_IRQHandler (void)
{

	
		extern volatile MessageState incomeMessageState;
		if (byteCounter < MAX_BUFFER_SIZE)
		{
			incomeMessageState = READY;
		} else 
		{
			byteCounter = 0;
		}
		TIM_Cmd(TIM3,DISABLE);
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	
}

/******************* AME 2018*****END OF FILE****/
