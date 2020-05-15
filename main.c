#include "stm32l476xx.h"
#include "lcd.h"
#include "LCD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void Joystick_Initialization(void);
void Translate_Morse(void);

void SysTick_Initialize(uint32_t ticks);
void Delay(uint32_t nTime);
void SysTick_Handler(void);

void greenLED_On(void);
void greenLED_Off(void);
void redLED_On(void);
void redLED_Off(void);

void movingString(uint8_t* str, uint8_t len);

uint8_t curr_index;
uint8_t * string;
uint8_t length;
uint16_t morse;

volatile uint32_t time;

int main(void)
{
		Joystick_Initialization();
		LCD_Initialization();
		SysTick_Initialize(4000);
	
		string = malloc (6 * sizeof(uint8_t));		
		
		while (1)
		{							
			  uint16_t joystick_center = (((GPIOA->IDR) & (0x1 << 0)) >> 0);
				uint16_t joystick_left =   (((GPIOA->IDR) & (0x1 << 1)) >> 1);
				uint16_t joystick_right =  (((GPIOA->IDR) & (0x1 << 2)) >> 2) ;
				uint16_t joystick_up =     (((GPIOA->IDR) & (0x1 << 3)) >> 3) ;
				uint16_t joystick_down =   (((GPIOA->IDR) & (0x1 << 5)) >> 5) ;			
			
				if (joystick_center == 1)
				{
						morse = (morse * 10) + 1;
						redLED_On();
						Delay(500);
						redLED_Off();						
				}
				else if (joystick_left == 1)
				{
						morse = morse / 10;
						redLED_On();
						Delay(500);
						redLED_Off();
				}
				else if (joystick_right == 1)
				{
						morse = morse * 10;
						redLED_On();
						Delay(500);
						redLED_Off();					
				}
				else if (joystick_up == 1)
				{
						greenLED_On();
						Delay(500);
						greenLED_Off();
						morse = (morse * 10) + 3;
				}
				else if (joystick_down == 1)
				{
						greenLED_On();
						Delay(500);
						greenLED_Off();	
						LCD_Clear();
						movingString(string, length);	
					
						if (length > 6)
						{
							uint8_t * temp = malloc (6 * sizeof(uint8_t));
							temp [5] = string [length - 1]; 
							temp [4] = string [length - 2]; 
							temp [3] = string [length - 3]; 
							temp [2] = string [length - 4]; 
							temp [1] = string [length - 5]; 
							temp [0] = string [length - 6];
							movingString(temp, 6);	
							//free(temp);
						}
						else
						{
								movingString(string, length);
						}
				}			
				
				
				if (morse >= 10000)
				{
					Translate_Morse();
					if (length > 6)
					{
							uint8_t * temp = malloc (6 * sizeof(uint8_t));
							temp [5] = string [length - 1]; 
							temp [4] = string [length - 2]; 
							temp [3] = string [length - 3]; 
							temp [2] = string [length - 4]; 
							temp [1] = string [length - 5]; 
							temp [0] = string [length - 6];
							movingString(temp, 6);	
							//free(temp);
					}
					else
					{
							movingString(string, length);
					}
				}
		}
}

void Joystick_Initialization(void)
{		
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 

	//Enable joystick middle: PA0
		GPIOA->MODER &= ~(0x03<<(2*0)) ;    
	
	//Enable joystick left: PA1
		GPIOA->MODER &= ~(0x03<<(2*1)) ;  
		GPIOA->PUPDR |= (0x02<<(2*1)) ;    
	
	//Enable joystick right: PA2
		GPIOA->MODER &= ~(0x03<<(2*2)) ; 
		GPIOA->PUPDR |= (0x02<<(2*2)) ;	
	
	//Enable joystick up: PA3
		GPIOA->MODER &= ~(0x03<<(2*3)) ;  
		GPIOA->PUPDR |= (0x02<<(2*3)) ;
		
		//Enable joystick down: PA5
		GPIOA->MODER &= ~(0x03<<(2*5)) ; 
		GPIOA->PUPDR |= (0x02<<(2*5)) ;
}


void Translate_Morse(void)
{
		
		if (morse == 13000)
		{
				string[curr_index] = 'A';
				curr_index ++;
				length ++;
				morse = 0;
		}	

		else if (morse == 31110)
		{
				string[curr_index] = 'B';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31310)
		{
				string[curr_index] = 'C';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31100)
		{
				string[curr_index] = 'D';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 10000)
		{
				string[curr_index] = 'E';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 11310)
		{
				string[curr_index] = 'F';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 33100)
		{
				string[curr_index] = 'G';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 11110)
		{
				string[curr_index] = 'H';
				curr_index ++;
				length ++;
				morse = 0;
		}

		else if (morse == 11000)
		{
				string[curr_index] = 'I';
				curr_index ++;
				length ++;
				morse = 0;
		}	

		else if (morse == 13330)
		{
				string[curr_index] = 'J';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31300)
		{
				string[curr_index] = 'K';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 13110)
		{
				string[curr_index] = 'L';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 33000)
		{
				string[curr_index] = 'M';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31000)
		{
				string[curr_index] = 'N';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 33300)
		{
				string[curr_index] = 'O';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 13310)
		{
				string[curr_index] = 'P';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 33130)
		{
				string[curr_index] = 'Q';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 13100)
		{
				string[curr_index] = 'R';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 11100)
		{
				string[curr_index] = 'S';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 30000)
		{
				string[curr_index] = 'T';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 11300)
		{
				string[curr_index] = 'U';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 11130)
		{
				string[curr_index] = 'V';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 13300)
		{
				string[curr_index] = 'W';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31130)
		{
				string[curr_index] = 'X';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 31330)
		{
				string[curr_index] = 'Y';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
		else if (morse == 33110)
		{
				string[curr_index] = 'Z';
				curr_index ++;
				length ++;
				morse = 0;
		}	
		
	
		
		else if (morse == 13333)
		{
				string[curr_index] = '1';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 11333)
		{
				string[curr_index] = '2';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 11133)
		{
				string[curr_index] = '3';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 11113)
		{
				string[curr_index] = '4';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 11111)
		{
				string[curr_index] = '5';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 31111)
		{
				string[curr_index] = '6';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 33111)
		{
				string[curr_index] = '7';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 33311)
		{
				string[curr_index] = '8';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 33331)
		{
				string[curr_index] = '9';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		else if (morse == 33333)
		{
				string[curr_index] = '0';
				curr_index ++;
				length ++;
				morse = 0;
		}
		
		morse = 0;
				
}


void greenLED_On(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;     
	  
	GPIOE->MODER &= ~(0x03<<(2*8)) ;   

	GPIOE->MODER |= (1<<16);  
	GPIOE->ODR |= GPIO_ODR_ODR_8;
	
}

void greenLED_Off(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;     
	
	GPIOE->MODER &= ~(0x03<<(2*8)) ;   

	GPIOE->MODER &= ~(1<<16);  
	GPIOE->ODR &= ~GPIO_ODR_ODR_8;	
}



void redLED_On(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;     
	  
	GPIOB->MODER &= ~(0x03<<(2*2)) ;   

	GPIOB->MODER |= (1<<4);  
	GPIOB->ODR |= GPIO_ODR_ODR_2;
	
}

void redLED_Off(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;     
	
	GPIOB->MODER &= ~(0x03<<(2*2)) ;   

	GPIOB->MODER &= ~(1<<4);  
	GPIOB->ODR &= ~GPIO_ODR_ODR_2;	
}


void movingString(uint8_t* str, uint8_t len) {
	// Scrolls a string across the LCD	
	
	if (len <= 6)
	{
		LCD_DisplayString(str);
	}
	
	else
	{
	
		uint8_t i;
		
		//Print string with padding at the end
		for (i = 0; i < len; i ++)
		{
			uint8_t* temp = malloc (6 * sizeof(uint8_t));
			uint8_t j;
			for (j = 0; j < 6; j ++)
			{
				if (i + j >= len)
				{
					temp[j] = ' ';
				}
				else if (i + j < len)
				{
					temp[j] = str[i + j];
				}
			}	
		
			LCD_DisplayString(temp);
			Delay(500);		
			free(temp);
		}		
		
		//Circle back around to beginning of the string with padding
		for (i = 6; i > 1; i --)
		{
			uint8_t* temp = malloc (6 * sizeof(uint8_t));
			uint8_t j;
			for (j = 0; j < i - 1; j ++)
			{
				temp[j] = ' ';
			}
			for (j = i - 1; j < 6; j ++)
			{
				temp[j] = str[j - i + 1];
			}
			
			LCD_DisplayString(temp);
			Delay(500);		
			free(temp);		
		}
}
}


// ticks: number of ticks between two interrupts
void SysTick_Initialize(uint32_t ticks) {
	
	// Disable SysTick IRQ and SysTick counter
	SysTick->CTRL = 0;
	
	// Set reload register
	SysTick->LOAD = ticks - 1;
	
	// Set interrupt priority of SysTick
	// Make SysTick least urgent (i.e. highest priority number)
	// __NVIC_PRIO_BITS: number of bits for priority levels, defined in CMSIS
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	
	// Reset the SysTick counter value
	SysTick->VAL = 0;
	
	// Select processor clock
	// 1 = processor clock; 0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	
	// Enable SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does no assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Enable SysTick timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

// SysTick interrupt service routine
void SysTick_Handler(void) {
	if (time > 0)
			time--;
}

// nTime: specifies the delay time length
void Delay(uint32_t nTime) {
	time = nTime;
	while(time != 0);
}

