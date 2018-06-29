
/**
  ******************************************************************************
  * @file    main.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   This file is header for main.h.
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSORS_H
#define __SENSORS_H

/* Global types --------------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/


#include "config.h"
#include "KeysLowLevel.h"
/* Exported types ------------------------------------------------------------*/
typedef struct{
	Pin sensorPin;
	PinState state;
}Sensor;

typedef struct{
	
	Sensor sensor[MAXSENSORS];
}SensorApp;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void initializeSensor(SensorApp *sensors);
void readSensors(SensorApp *sensors);

#endif /* __KEYS_H */


/******************* AME 2018 *****END OF FILE****/

