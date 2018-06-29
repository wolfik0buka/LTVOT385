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

#include "Keys.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void initKey(uint8_t number, Key *key);
void openKey(KeyApp *keyApp, uint8_t number);
void closeKey(KeyApp *keyApp, uint8_t number);
/* Functions -----------------------------------------------------------------*/
void initializeKeys(KeyApp *keyApp)
{   
    keyApp->nOpenKeys = 0;
    for (int i = 0; i<NUMBERMAXOPEN;i++)
    {
        keyApp->numbersOpenKeys[i] = 0;
    }
    for (int i = 0; i< NUMBERKEYS; i++)
    {
        initKey(i, &keyApp->keys[i]);
    }
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void initKey(uint8_t number, Key *key)
{
    initPinControl(number, &key->pinControl);
    initPinFeedback(number, &key->pinControl);
    key->feedback = OFF;
    key->programmState = OFF;
}

void ProcessKeys(KeyApp *keyApp, uint32_t *state)
{
    
    //uint32_t state[2];
    for (uint8_t i=0; i < NUMBERKEYS;i++)
    {
       if ((state [i/32] & (1<<i%32)) == 0)
       {
           closeKey(keyApp, i);
       }
    }
    for (uint8_t i=0; i < NUMBERKEYS;i++)
    {
       if ((state [i/32] & (1<<(i%32))) != 0)
       {
           openKey(keyApp, i);
       }
    }
}
void openKey(KeyApp *keyApp, uint8_t number)
{
    if (keyApp->keys[number].programmState == OFF)
    {
        keyApp->keys[number].programmState = ON;
        if (keyApp->nOpenKeys < NUMBERMAXOPEN) 
        {
            keyApp->nOpenKeys++;
            
            if (keyApp->nOpenKeys >NUBERSAFEKEYS)
            {
                //settimer();
            }
            setPin (&keyApp->keys[number].pinControl);
        }                
    }
    clearPin (&keyApp->keys[number].pinControl);
}

void closeKey(KeyApp *keyApp, uint8_t number)
{
    if (keyApp->keys[number].programmState == ON)
    {
        keyApp->keys[number].programmState = OFF;
        if (keyApp->nOpenKeys > 0) keyApp->nOpenKeys--;
    }
    clearPin (&keyApp->keys[number].pinControl);
}

void readKeys(KeyApp *keys)
{
    keys->KeysState[0] = 0;
    keys->KeysState[1] = 0;
    
    for (uint8_t i = 0; i < NUMBERKEYS; i++)
    {
        keys->keys[i].feedback = readPin (&keys->keys[i].pinFeedback);
        if (keys->keys[i].feedback == ON)
        {
            keys->KeysState[i/32] |= 1<<(i % 32);
        }
    }
}



/******************* AME 2018*****END OF FILE****/
