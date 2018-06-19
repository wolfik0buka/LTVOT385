#include <stm32f2xx.h>
#include "main.h"

void setMCO1 (void)
{
	GPIO_InitTypeDef MCO_PIN;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	MCO_PIN.GPIO_Mode		= GPIO_Mode_AF;
	MCO_PIN.GPIO_OType 	= GPIO_OType_PP;
	MCO_PIN.GPIO_Pin 		= GPIO_Pin_8;
	MCO_PIN.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	MCO_PIN.GPIO_Speed 	= GPIO_Speed_100MHz;
	
	
	GPIO_Init(GPIOA, &MCO_PIN);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
	
	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);
	
}

int main (void)
{
	setMCO1();
	while(1)
	{
		
	}
}
