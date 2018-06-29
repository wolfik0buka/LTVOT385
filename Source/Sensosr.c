/**
  ******************************************************************************
  * @file    main.c
  * @author  wolfik
  * @version V0.0.1
  * @date    19-06-2018
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "Sensors.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void initSensor(uint8_t number, Sensor *sensor);
//void openKey(KeyApp *keyApp, uint8_t number);
//void closeKey(KeyApp *keyApp, uint8_t number);
/* Functions -----------------------------------------------------------------*/
void initializeSensor(SensorApp *sensors)
{   

    for (int i = 0; i< NUMBERSENSORS; i++)
    {
        initSensor(i, &sensors->sensor[i]);
    }
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void initSensor(uint8_t number, Sensor *sensor)
{
    initPinSensor(number, &sensor->sensorPin);
    
    sensor->state = OFF;

}




void readSensors(SensorApp *sensors)
{
    
    for (uint8_t i = 0; i < NUMBERSENSORS; i++)
    {
        sensors->sensor[i].state = readPin (&sensors->sensor[i].sensorPin);
        
    }
}



/******************* AME 2018*****END OF FILE****/
