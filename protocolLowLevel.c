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


/**
  * @brief  Interupt handler of USART3.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler (void)
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
	}
	TIM_Cmd(TIM3,DISABLE);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
}

/******************* AME 2018*****END OF FILE****/
