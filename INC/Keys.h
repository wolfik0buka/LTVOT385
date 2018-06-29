
/**
  ******************************************************************************
  * @file    main.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file is header for main.h.
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEYS_H
#define __KEYS_H

/* Global types --------------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/


#include "config.h"
#include "KeysLowLevel.h"
/* Exported types ------------------------------------------------------------*/
typedef struct{
	Pin pinControl;
	Pin pinFeedback;
	PinState feedback;
    PinState programmState;
}Key;

typedef struct{
	
	Key keys[NUMBERKEYS];
    uint32_t KeysState[2];
	uint8_t nOpenKeys;
	uint8_t numbersOpenKeys[NUMBERMAXOPEN];
}KeyApp;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void initializeKeys(KeyApp *keyApp);
void ProcessKeys(KeyApp *keyApp, uint32_t *state);
void readKeys(KeyApp *keys);

#endif /* __KEYS_H */


/******************* AME 2018 *****END OF FILE****/

