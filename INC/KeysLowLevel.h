
/******************************************************************************
  * @file    KeysLowLevel.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file is header for KeysLowLevel.h.
  ****************************************************************************/

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __KEYSLOWLEVEL_H
#define __KEYSLOWLEVEL_H

/* Global types -------------------------------------------------------------*/

/* Includes -----------------------------------------------------------------*/
#include <stm32f2xx.h>
#include "config.h"

/* Exported types -----------------------------------------------------------*/
typedef enum {OFF = 0, ON = !OFF} PinState;
typedef enum {INPUT = 0, OUTPUT = !INPUT} Direction;

typedef struct{
	GPIO_TypeDef* port;
	uint16_t pinNumber;
}Pin;
/* Exported constants -------------------------------------------------------*/

/* Exported macro -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------ */
void setPin (Pin* pin);
void clearPin (Pin* pin);
PinState readPin (Pin* pin);

void initPinControl(uint8_t number, Pin *pin);
void initPinFeedback (uint8_t number, Pin *pin);
#endif /* __KEYSLOWLEVEL_H */


/******************* AME 2018 *****END OF FILE****/

