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
void processReadFunction(Message *readMessage);
void processWriteFunction(Message *writeMessage);
void sendError(uint8_t functionCode,uint8_t ErrorType);


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
			inputMessage->startAdress = inputBuff[2] << 8 | inputBuff[3];
			inputMessage->numberOfRegisters = inputBuff[4] << 8 | inputBuff[5];
			if (inputMessage->functionCode == WRITEFUNCTION)
			{
				inputMessage->numberOfData = inputBuff[6];
				for(int i=6; i < byteCounter - 2; i++ )
				{
					inputMessage->data[i - 6] = inputBuff[i];
				}
				processWriteFunction(inputMessage);
			}
			else
			{
				processReadFunction(inputMessage);
			}
		}
		else
		{
			sendError(inputMessage->functionCode,ILLEGALFUNCTION);
		}
	}	
	byteCounter = 0;
}

void processReadFunction(Message *readMessage)
{
	if(readMessage->startAdress <= 2)
	{
		if (readMessage->startAdress +
			readMessage->numberOfRegisters - 1 <= 2)
		{
			if (readMessage->numberOfRegisters > 0)
			{
				sendRS485((uint8_t *)"Sucsess read", sizeof("Sucsess read"));
			}
			else 
			{
				sendError(readMessage->functionCode,ILLEFALDATAVALUE);
			}
			
		}
		else
		{
			sendError(readMessage->functionCode,ILLEGALDATAADDRESS);
		}
		
	}
	else 
	{
		sendError(readMessage->functionCode,ILLEGALDATAADDRESS);
	}
}

void processWriteFunction(Message *writeMessage)
{
		if(writeMessage->startAdress <= 1)
	{
		if (writeMessage->startAdress +
			writeMessage->numberOfRegisters - 1 <= 1)
		{
			if (writeMessage->numberOfRegisters > 0 &&
				writeMessage->numberOfData == writeMessage->numberOfRegisters*2)
			{
				sendRS485((uint8_t *)"Sucsess write", sizeof("Sucsess write"));
			}
			else 
			{
				sendError(writeMessage->functionCode,ILLEFALDATAVALUE);
			}
			
		}
		else
		{
			sendError(writeMessage->functionCode,ILLEGALDATAADDRESS);
		}
		
	}
	else 
	{
		sendError(writeMessage->functionCode,ILLEGALDATAADDRESS);
	}
}

/**
  * @brief Sending ErrorMessage
  * @param  functionCode: income FunctionCode
  * @param  ErrorType: Type of Error 
  * @retval None
  */
void sendError(uint8_t functionCode,uint8_t ErrorType)
{
	outputBuffer[0] = ADDRESS;
	outputBuffer[1] = functionCode | 0x80;
	outputBuffer[2] = ErrorType;
	//CRC 
	sendRS485 ((uint8_t *) outputBuffer, 3);
}

/******************* AME 2018*****END OF FILE****/
