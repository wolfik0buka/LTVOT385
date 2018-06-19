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
/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main (void)
{
	initialization();
	while(1)
	{
		if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE))
		{
			uint8_t temp = USART_ReceiveData(USART3);
			USART_SendData(USART3, temp);
		}
		
	}
}

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */



/******************* AME 2018*****END OF FILE****/
