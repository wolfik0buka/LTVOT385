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
#include "KeysLowLevel.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 GPIO_TypeDef* KEYCONTROLPORT[MAXKEYS] = {GPIOE,
                                    GPIOE, GPIOE, GPIOE, GPIOE, //5
                                    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, //10
                                    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, //15 
                                    GPIOE, GPIOF, GPIOF, GPIOF, GPIOF, //20
                                    GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, //25
                                    GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, //30
                                    GPIOF, GPIOF, GPIOG, GPIOG, GPIOG, //35
                                    GPIOG, GPIOG, GPIOG, GPIOG, GPIOG};//40

 GPIO_TypeDef* KEYFEEDBACKPORT[MAXKEYS] = {GPIOC,
                                     GPIOC, GPIOC, GPIOC, GPIOC,//5
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
                                     GPIO_Pin_15};  
/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
void setPin (Pin* pin)
{
    GPIO_SetBits(pin->port, pin->pinNumber);
}


void clearPin (Pin* pin)
{
    GPIO_ResetBits(pin->port, pin->pinNumber);
}

PinState readPin (Pin* pin)
{
    return (PinState) GPIO_ReadInputDataBit(pin->port, pin->pinNumber);
}


void initPin(Direction direction, uint16_t pin,GPIO_TypeDef* port )
{
    GPIO_InitTypeDef pinInitStruct;
    
    pinInitStruct.GPIO_OType = GPIO_OType_PP;
    pinInitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    pinInitStruct.GPIO_Speed =GPIO_Speed_2MHz;
    if (direction == INPUT)
    {
        pinInitStruct.GPIO_Mode = GPIO_Mode_IN;
    }
    else 
    {
        pinInitStruct.GPIO_Mode = GPIO_Mode_OUT;
    }
    pinInitStruct.GPIO_Pin = pin;
    GPIO_Init(port, &pinInitStruct);
    
    if (direction == OUTPUT)
    {
        GPIO_ResetBits(port, pin);;
    }
}

void initPinControl(uint8_t number, Pin *pin)
{

   pin->pinNumber = KEYCONTROLPIN[number];
   pin->port =  KEYCONTROLPORT[number];
   initPin(OUTPUT, pin->pinNumber,pin->port );
}

void initPinFeedback (uint8_t number, Pin *pin)
{
    pin->pinNumber = KEYFEEDBACK[number];
    pin->port = KEYFEEDBACKPORT[number];
    initPin(INPUT, pin->pinNumber,pin->port );
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */




/******************* AME 2018*****END OF FILE****/
