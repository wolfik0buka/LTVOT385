
/**
  ******************************************************************************
  * @file    config.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file contains config Datas of VOTUM
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG2_H
#define __CONFIG2_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f2xx.h>

/* Exported types ------------------------------------------------------------*/
typedef enum { UNREADY= 0, READY = !UNREADY} MessageState;
typedef enum { OFF= 0, ON = !OFF} State, PinState;

/* Exported constants --------------------------------------------------------*/
/*---------------------------------Keys---------------------------------------*/
#define MAXKEYS 40
#define NUMBERKEYS 40
#define NUBERSAFEKEYS 3
#define NUMBERMAXOPEN 5


#define KEY1CONTROLPORT GPIOE
#define KEY1CONTROLPIN  GPIO_Pin_0
#define KEY1FEEDBACKPORT GPIOE
#define KEY1CONTROLPIN  GPIO_Pin_0


/*------------------------------Sensors---------------------------------------*/
#define NUMBERSENSORS 5
#define MAXSENSORS 7

#define SENSORLOWWATER 0
#define SENSORFLOW     1
#define SENSOROPENBALOON 2
#define SENSORLOWPREASSURE 3
#define SENSORPREASSURE 4
#define RESERV1 5
#define RESERV2 6
                                     
                                     
                                     
/*-----------------------Protocol---------------------------------------------*/
#define ADDRESS 0x31

#define WRITEFUNCTION   0x10
#define READFUNCTION	0x04
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  



#endif /* __CONFIG_H */
/******************* AME 2018 *****END OF FILE****/

