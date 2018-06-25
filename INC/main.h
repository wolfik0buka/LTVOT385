
/**
  ******************************************************************************
  * @file    main.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file is header for main.h.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Global types --------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <stm32f2xx.h>

#include "hardware.h"
#include "protocol.h"
/* Exported types ------------------------------------------------------------*/
//typedef enum { UNREADY= 0, READY = !UNREADY} MessageState;
typedef struct{
	Protocol protocol;
}Application;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  


#endif /* __MAIN_H */


/******************* AME 2018 *****END OF FILE****/

