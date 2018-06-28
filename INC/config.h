
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




/*
const GPIO_TypeDef* KEYCONTROLPORT[MAXKEYS] = {GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, //5
                                    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, //10
                                    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, //15 
                                    GPIOE, GPIOF, GPIOF, GPIOF, GPIOF, //20
                                    GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, //25
                                    GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, //30
                                    GPIOF, GPIOF, GPIOG, GPIOG, GPIOG, //35
                                    GPIOG, GPIOG, GPIOG, GPIOG, GPIOG};//40

const GPIO_TypeDef* KEYFEEDBACKPORT[MAXKEYS] = {GPIOC, GPIOC, GPIOC, GPIOC, GPIOC,//5
                                     GPIOC, GPIOC, GPIOC, GPIOC, GPIOC,   //10
                                     GPIOC, GPIOC, GPIOC, GPIOC, GPIOC,   //15
                                     GPIOC, GPIOD, GPIOD, GPIOD, GPIOD,   //20
                                     GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,   //25
                                     GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,   //30
                                     GPIOD, GPIOD, GPIOG, GPIOG, GPIOG,   //35
                                     GPIOG, GPIOG, GPIOG, GPIOG, GPIOG};  //40

const uint16_t KEYCONTROLPIN[MAXKEYS] = { GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2,//3
                                     GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5,   //6
                                     GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_8,   //9
                                     GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, //12
                                     GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14,//15
                                     GPIO_Pin_15, GPIO_Pin_0, GPIO_Pin_1,  //18
                                     GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4,   //21
                                     GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,   //24
                                     GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10,  //27
                                     GPIO_Pin_11, GPIO_Pin_12, GPIO_Pin_13,//30
                                     GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_0, //33
                                     GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,   //36
                                     GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6,   //39   
                                     GPIO_Pin_7};                          //40 
                                        
 const uint16_t KEYFEEDBACK[MAXKEYS] =  { GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2,//3
                                     GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5,   //6
                                     GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_8,   //9
                                     GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, //12
                                     GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14,//15
                                     GPIO_Pin_15, GPIO_Pin_0, GPIO_Pin_1,  //18
                                     GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4,   //21
                                     GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,   //24
                                     GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10,  //27
                                     GPIO_Pin_11, GPIO_Pin_12, GPIO_Pin_13,//30
                                     GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_8, //33
                                     GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, //36
                                     GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14,//39   
                                     GPIO_Pin_15};  */

                                     
                                     
                                     
/*-----------------------Protocol---------------------------------------------*/
#define ADDRESS 0x31

#define WRITEFUNCTION   0x10
#define READFUNCTION	0x04
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  



#endif /* __CONFIG_H */
/******************* AME 2018 *****END OF FILE****/

