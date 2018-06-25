
/**
  ******************************************************************************
  * @file    protocol.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file contains different data and datastruct and functions 
  *			 prototypes for protocolLowLevel.c. It includes harware access 
  *			 level for LTX20385 on STM32F207IG.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PROTOCOL_H
#define __PROTOCOL_H



/* Includes ------------------------------------------------------------------*/
#include <stm32f2xx.h>
#include "config.h"
#include "protocolLowLevel.h"


//#include "main.h"
/* Exported types ------------------------------------------------------------*/
typedef struct {
	uint8_t		adress;
	uint8_t		functionCode;
	uint16_t	startAdress;
	uint16_t 	numberOfRegisters;
	uint8_t 	numberOfData;
	uint16_t	data[3];
	uint16_t	summCRC;
} Message;

typedef struct {
	Message incomeMessage;
	Message outputMessage;
}Protocol;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void decodeMessage(Message *inputMessage);


#endif /* __PROTOCOL_H */


/******************* AME 2018 *****END OF FILE****/

