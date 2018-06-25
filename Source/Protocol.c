/**
  ******************************************************************************
  * @file    Protocol.c
  * @author  wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file of high level protocol functions
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "protocol.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/



/**
  * @brief Main process of income message
  * @param  app: pointer to the whole struct of apps 
  * @retval None
  */
void decodeMessage(Message *inputMessage)
{
	extern uint8_t volatile inputBuff[];
	extern uint16_t volatile byteCounter;
	/*Check CRC*/
	// if (crcRight(inputBuff,  byteCounter))
	//first decode and check Message

	inputMessage->adress =  inputBuff[0];
	if (inputMessage->adress == ADDRESS)
	{
		inputMessage->functionCode = inputBuff[0];
		if (inputMessage->functionCode == WRITEFUNCTION ||
			inputMessage->functionCode == READFUNCTION)
		{
		}
		else
		{
			//sendER
		}			
			
	
	
	USART_SendData(USART3, inputMessage->adress);
}

/******************* AME 2018*****END OF FILE****/
