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
void processReadFunction(Protocol *protocol);
void processWriteFunction(Protocol *protocol);
void sendError(uint8_t functionCode,uint8_t ErrorType);
void SendAnswerWrite (Message *outputMessage, uint16_t start, uint16_t number);
void buildMessage(Protocol *protocol);
void SendMessage (Message *sendingMessage);


/**
  * @brief Main process of income message
  * @param  app: pointer to the struct of inputMessage 
  * @retval None
  */
void decodeMessage(Protocol *protocol)
{
	extern uint8_t volatile inputBuff[];
	extern uint16_t volatile byteCounter;
	/*Check CRC*/
	// if (crcRight(inputBuff,  byteCounter))
	//first decode and check Message

	protocol->incomeMessage.adress =  inputBuff[0];
	if (protocol->incomeMessage.adress == ADDRESS)
	{
		protocol->incomeMessage.functionCode = inputBuff[1];
		if (protocol->incomeMessage.functionCode == WRITEFUNCTION ||
			protocol->incomeMessage.functionCode == READFUNCTION)
		{
			protocol->incomeMessage.startAdress = inputBuff[2] << 8 | inputBuff[3];
			protocol->incomeMessage.numberOfRegisters = inputBuff[4] << 8 | inputBuff[5];
			if (protocol->incomeMessage.functionCode == WRITEFUNCTION)
			{
				protocol->incomeMessage.numberOfData = inputBuff[6];
				for(int i=7; i < byteCounter - 2; i++ )
				{
					protocol->incomeMessage.data[i - 6] = inputBuff[i];
				}
				processWriteFunction(protocol);
			}
			else
			{
				processReadFunction(protocol);
			}
		}
		else
		{
			sendError(protocol->incomeMessage.functionCode,ILLEGALFUNCTION);
		}
	}	
	byteCounter = 0;
}
/*----------------------------------------------------------------------------*/
void processReadFunction(Protocol *protocol)
{
	if(protocol->incomeMessage.startAdress <= 2)
	{
		if (protocol->incomeMessage.startAdress +
			protocol->incomeMessage.numberOfRegisters - 1 <= 2)
		{
			if (protocol->incomeMessage.numberOfRegisters > 0)
			{
                buildMessage(protocol);
                SendMessage (&protocol->outputMessage);
				
			}
			else 
			{
				sendError(protocol->incomeMessage.functionCode,ILLEFALDATAVALUE);
			}
			
		}
		else
		{
			sendError(protocol->incomeMessage.functionCode,ILLEGALDATAADDRESS);
		}
		
	}
	else 
	{
		sendError(protocol->incomeMessage.functionCode,ILLEGALDATAADDRESS);
	}
}
/*----------------------------------------------------------------------------*/
void processWriteFunction(Protocol *protocol)
{
	if(protocol->incomeMessage.startAdress <= 1)
	{
		if (protocol->incomeMessage.startAdress +
			protocol->incomeMessage.numberOfRegisters - 1 <= 1)
		{
			if (protocol->incomeMessage.numberOfRegisters > 0 &&
				protocol->incomeMessage.numberOfData == protocol->incomeMessage.numberOfRegisters*2)
			{
                uint8_t start = protocol->incomeMessage.startAdress;
                for (int i = 0;i < protocol->incomeMessage.numberOfRegisters;i++)
                {
                    protocol->writeRegisters[start + i] =//
                    protocol->incomeMessage.data[i];
                }
            //    sendRS485((uint8_t *)"Sucsess write", sizeof("Sucsess write"));
                SendAnswerWrite (&protocol->outputMessage,
                                 protocol->incomeMessage.startAdress,
                                 protocol->incomeMessage.numberOfRegisters);
			}
			else 
			{
				sendError(protocol->incomeMessage.functionCode,ILLEFALDATAVALUE);
			}
			
		}
		else
		{
			sendError(protocol->incomeMessage.functionCode,ILLEGALDATAADDRESS);
		}
		
	}
	else 
	{
		sendError(protocol->incomeMessage.functionCode,ILLEGALDATAADDRESS);
	}
}





/*----------------------------------------------------------------------------*/
void SendMessage (Message *sendingMessage)
{
    uint8_t length = 0;
    uint16_t crcsumm;
    outputBuffer[0] = sendingMessage->adress;
	outputBuffer[1] = sendingMessage->functionCode;
    if (sendingMessage->functionCode == WRITEFUNCTION)
    {
        outputBuffer[2] = sendingMessage->startAdress >> 8;
        outputBuffer[3] = sendingMessage->startAdress & 0xFF;
        outputBuffer[4] = sendingMessage->numberOfRegisters >>8;
        outputBuffer[5] = sendingMessage->numberOfRegisters & 0xFF;
        length = 6;
    }
    else
    {
        outputBuffer[2] = sendingMessage->numberOfData;
        length = 3;
        for (int i=0; i <  sendingMessage->numberOfData; i++)
        {
            outputBuffer[3+i] = sendingMessage->data[i];
            length++;
        }
    }
    crcsumm = 0x1234;
    outputBuffer[length] = crcsumm >> 8;
    outputBuffer[length+1] = crcsumm & 0xff;
    length +=2;
    sendRS485 ((uint8_t *) outputBuffer, length);
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/


void SendAnswerWrite (Message *outputMessage, uint16_t start, uint16_t number)
{
    outputMessage->adress = ADDRESS;
    outputMessage->functionCode = WRITEFUNCTION;
    outputMessage->startAdress = start;
    outputMessage->numberOfRegisters = number;
    
    SendMessage (outputMessage);
}
/*----------------------------------------------------------------------------*/

void buildMessage(Protocol *protocol)
{
    uint8_t start;
    protocol->outputMessage.adress = ADDRESS;
    protocol->outputMessage.functionCode = READFUNCTION;
    protocol->outputMessage.numberOfData = protocol->incomeMessage.numberOfRegisters * 2;
    start = protocol->incomeMessage.startAdress;
    for (int i = 0; i < protocol->incomeMessage.numberOfRegisters; i++)
    {
        protocol->outputMessage.data[2*i] = protocol->readRegistrers[start + i] & 0xFF;
        protocol->outputMessage.data[2*i+1] = (protocol->readRegistrers[start + i] >> 8) & 0xFF;
        
    }
}
/*----------------------------------------------------------------------------*/

void fillReadRegistrs(uint16_t *registrs, 
    State lowPressure,
    uint32_t keys,
    uint8_t trafagValue,
    State systemState,
    State cutWire,
    State lowWater)
{

    
    registrs[0] = 0;
    registrs[1] = 0;
    registrs[2] = 0;
    
    if (lowPressure == ON)
    {
        registrs[0] |= 0x01;
    }
    registrs[0] |= (keys << 1) & 0xffff;
    
    registrs[1] |=  (keys >> 15) & 0xffff;
    
    registrs[2] |= trafagValue;
    
    if (systemState == ON) registrs[2] |= (1 << 8);
    registrs[2] |= (1 << 9);
    if (cutWire == ON) registrs[2] |= (1 << 10);
    if (lowWater == ON) registrs[2] |= (1 << 11);
}



/******************* AME 2018*****END OF FILE****/
