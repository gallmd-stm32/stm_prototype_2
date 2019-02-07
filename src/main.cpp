/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2019-01-19

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "gpio.h"
#include "i2c.h"
#include "display.h"


/* Private macro */
/* Private variables */
volatile bool buttonPressed;

I2CMaster* I2CMaster::handlers[1] = {0};
I2CMaster i2c(I2C::BaseRegisters::I2C1_Base);




/* Private function prototypes */
void Delay(__IO uint32_t nCount);
void EXTI_Init(void);



extern "C"
{
	void EXTI0_IRQHandler(void)
	{
		// Checks whether the interrupt from EXTI0 or not
		if (EXTI_GetITStatus(EXTI_Line0))
		{
			buttonPressed= true;
			Delay(0xFFFFF);
			// Clears the EXTI line pending bit
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
	}
}



/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

  int i = 0;

  buttonPressed = false;

  Delay(0xFFFFF);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


  SYSCFG->EXTICR[1] = SYSCFG_EXTICR1_EXTI0_PA;

  EXTI->IMR |= EXTI_IMR_MR0;
  EXTI->RTSR |= EXTI_RTSR_TR0;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn; //TIM4 IRQ Channel
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//Preemption Priority
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //Sub Priority
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitTypeDef NVIC_InitStructure2;

  NVIC_InitStructure2.NVIC_IRQChannel = I2C1_ER_IRQn; //TIM4 IRQ Channel
  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0;//Preemption Priority
  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0; //Sub Priority
  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure2);

  NVIC_EnableIRQ(EXTI0_IRQn);
  NVIC_SetPriority(EXTI0_IRQn, 0);

  __enable_irq();





  const GPIO<GPIOxBaseRegisters::GPIO_B,
  	  PINS::PIN12,
  	  GpioModes::Output,
  	  OutputTypes::PushPull,
  	  OutputSpeed::MediumSpeed,
  	  PullUpPullDown::NoPullUpPullDown,
  	  AlternateFunction::AF0>greenLED;

//  greenLED.toggle();

  //set PA15 as input
  const GPIO<GPIOxBaseRegisters::GPIO_C,
  	  PINS::PIN13,
	  GpioModes::Input,
	  OutputTypes::PushPull,
	  OutputSpeed::MediumSpeed,
	  PullUpPullDown::NoPullUpPullDown,
	  AlternateFunction::AF0>buttonPin;

  const GPIO<GPIOxBaseRegisters::GPIO_B,
  	  PINS::PIN6,
  	  GpioModes::AlternateFunction,
  	  OutputTypes::OpenDrain,
  	  OutputSpeed::HighSpeed,
  	  PullUpPullDown::NoPullUpPullDown,
  	  AlternateFunction::AF4>sdaPin;

  const GPIO<GPIOxBaseRegisters::GPIO_B,
  	  PINS::PIN7,
  	  GpioModes::AlternateFunction,
  	  OutputTypes::OpenDrain,
  	  OutputSpeed::HighSpeed,
  	  PullUpPullDown::NoPullUpPullDown,
  	  AlternateFunction::AF4>sclPin;


  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /* TODO - Add your application code here */
  I2C::send_buffer_type osc_on = {0x21, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  i2c.sendBytes(osc_on, 0x070);

  Delay(0xFFFFF);
  I2C::send_buffer_type no_blink = {0x81, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  i2c.sendBytes(no_blink, 0x070);

  Delay(0xFFFFF);
  I2C::send_buffer_type brightness = {0xEF, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  i2c.sendBytes(brightness, 0x070);

  Delay(0xFFFFF);
  I2C::send_buffer_type all_on = {0x00, 0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00};
  i2c.sendBytes(all_on, 0x070);

  Delay(0xFFFFF);
  const std::array<uint8_t, 17> all_off = {0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  i2c.sendBytes(all_off, 0x070);

  Delay(0xFFFFF);
  const std::array<uint8_t, 17> testA = {0x00, 0x7F,0x00,0x88,0x00,0x88,0x00,0x88,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  i2c.sendBytes(testA, 0x070);

  bool panelOn = false;
  int displayAddress = 0x70;

  /* Infinite loop */
  while (1)
  {
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::A, displayAddress);

	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::B, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::C, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::D, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::E, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::F, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::G, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::H, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::I, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::J, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::K, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::L, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::M, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::N, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::O, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::P, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::Q, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::R, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::S, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::T, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::U, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::V, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::W, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::X, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::Y, displayAddress);
	  Delay(0xFFFFF);
	  i2c.sendBytes(display::characters::Z, displayAddress);

	  if(buttonPressed){
	  greenLED.toggle();
	  buttonPressed = false;

	  	  if(panelOn){
	  		  i2c.sendBytes(all_off, 0x70);
	  		  panelOn = false;
	  	  }else if(!panelOn){
	  		  i2c.sendBytes(all_on, 0x70);
	  		  panelOn = true;
	  	  }
	  }
	i++;
  }
}
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}






