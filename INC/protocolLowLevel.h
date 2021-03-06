
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
#ifndef __PTOTOCOLLOWLEVEL_H
#define __PTOTOCOLLOWLEVEL_H



/* Includes ------------------------------------------------------------------*/
#include <stm32f2xx.h>

#include "config.h"
//#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void sendRS485(uint8_t *data, uint8_t len);


#endif /* __PTOTOCOLLOWLEVEL_H */


/******************* AME 2018 *****END OF FILE****/

