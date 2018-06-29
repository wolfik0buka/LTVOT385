
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
	uint8_t	data[10];
	uint16_t	summCRC;
} Message;

typedef struct {
	Message incomeMessage;
	Message outputMessage;
    uint16_t readRegistrers[3];
    uint16_t writeRegisters[2];
}Protocol;
/* Exported constants --------------------------------------------------------*/
#define ILLEGALFUNCTION		0x01
#define ILLEGALDATAADDRESS	0x02
#define ILLEFALDATAVALUE	0x03
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void decodeMessage(Protocol *protocol);
void fillReadRegistrs(uint16_t *registrs, 
    State lowPressure,
    uint32_t keys,
    uint8_t trafagValue,
    State systemState,
    State cutWire,
    State lowWater);

#endif /* __PROTOCOL_H */


/******************* AME 2018 *****END OF FILE****/

