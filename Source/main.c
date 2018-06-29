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

#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile MessageState incomeMessageState = UNREADY;
/* Private function prototypes -----------------------------------------------*/
void diagnostics(Application *app);
/* Functions -----------------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main (void)
{
	//uint8_t test[] = "Test interface";
	initialization();
	Application app;
    initializeKeys(&app.keys);
    initializeSensor(&app.sensors);
    app.systemState = OFF;
    app.cutWire = OFF;
	while(1)
	{
        diagnostics(&app);
		if ( incomeMessageState == READY)
		{
			decodeMessage(&app.protocol);
        //  check Message()
            switch (app.protocol.incomeMessage.functionCode)
            {
                case WRITEFUNCTION:
                {
                    uint32_t newKeyState[2];
                    newKeyState[1] = 0;
                    newKeyState[0] = app.protocol.writeRegisters[0] |
                                     app.protocol.writeRegisters[1] <<16;   
                    ProcessKeys(&app.keys,newKeyState );
                    break;
                }
                case READFUNCTION:
                {
                    //readAnswer();
                    break;
                }
            }
                
		//	sendRS485(test, sizeof(test));
			incomeMessageState = UNREADY;
		}
		
	}
}


void diagnostics(Application *app)
{
    readKeys(&app->keys);
    readSensors(&app->sensors);
    
    if (app->keys.KeysState[0] | app->keys.KeysState[1]) 
    {
        if (app->sensors.sensor[SENSORFLOW].state == ON)
        {
            app->systemState = ON;
            app->cutWire = OFF;
        } 
        else
        {
            app->systemState = OFF;
            app->cutWire = ON;
        }
    }
    app->TrafagValue = 0x25;
    fillReadRegistrs(app->protocol.readRegistrers, 
    app->sensors.sensor[SENSORLOWPREASSURE].state,
    app->keys.KeysState[0],
    app->TrafagValue,
    app->systemState,
    app->cutWire,
    app->sensors.sensor[SENSORLOWPREASSURE].state);
    
}
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */



/******************* AME 2018*****END OF FILE****/
