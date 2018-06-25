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
volatile uint8_t outputBuffer[30];

/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/



/**
  * @brief Main process of income message
  * @param  app: pointer to the struct of inputMessage 
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
		inputMessage->functionCode = inputBuff[1];
		if (inputMessage->functionCode == WRITEFUNCTION ||
			inputMessage->functionCode == READFUNCTION)
		{
		}
		else
		{
			outputBuffer[0] = ADDRESS;
			outputBuffer[1] = inputMessage->functionCode | 0x80;
			outputBuffer[2] = 0x03;
			//CRC 
			sendRS485 ((uint8_t *) outputBuffer, 3);
		}
	}		
	//USART_SendData(USART3, inputMessage->adress);
}

/******************* AME 2018*****END OF FILE****/
