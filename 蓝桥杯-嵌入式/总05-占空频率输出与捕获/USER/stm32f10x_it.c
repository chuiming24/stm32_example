/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

extern u32 TimingDelay;
u8 KeyFlag;
u16 KeyCount;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
	
	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
uint8_t RxBuffer2[16];
uint8_t RxCounter2 = 0;

u16 rxTimeCount = 500;
u8 rxon = 0;
u8 usart_flag = 0;

void SysTick_Handler(void)
{
	TimingDelay--;
	KeyCount++;
	if(KeyCount == 100){
		KeyFlag = 1;
		KeyCount = 0;
	}
	
	if(rxTimeCount > 0)
		rxTimeCount--;
	else if(!rxTimeCount && rxon){
		rxTimeCount = 500;
		RxCounter2 = 0;
		usart_flag = 1;
		rxon = 0;
	}
	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

void USART2_IRQHandler(void)
{
	u8 clear;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		//usart_flag = 1;
    if(RxCounter2 != 16)
    {
			/* Read one byte from the receive data register */
			RxBuffer2[RxCounter2++] = USART_ReceiveData(USART2);
			
			rxTimeCount = 500;
			rxon = 1;
    }
  } 
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)	//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
	{
		(void)USART_ReceiveData(USART2);
	}	  
}

__IO uint16_t IC2ReadValue1 = 0, IC2ReadValue2 = 0;
__IO uint16_t CaptureNumber_CH2 = 0;
__IO uint32_t Capture_CH2 = 0;
__IO uint32_t TIM2Freq_CH2 = 0;

__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber_CH3 = 0;
__IO uint32_t Capture_CH3 = 0;
__IO uint32_t TIM2Freq_CH3 = 0;
void TIM2_IRQHandler(void)
{ 
	

  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == SET) 
  {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
    if(CaptureNumber_CH2 == 0)
    {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture2(TIM2);
      CaptureNumber_CH2 = 1;
    }
    else if(CaptureNumber_CH2 == 1)
    {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture2(TIM2); 
      
      /* Capture computation */
      if (IC2ReadValue2 > IC2ReadValue1)
      {
        Capture_CH2 = (IC2ReadValue2 - IC2ReadValue1); 
      }
      else
      {
        Capture_CH2 = ((0xFFFF - IC2ReadValue1) + IC2ReadValue2); 
      }
      /* Frequency computation */ 
      TIM2Freq_CH2 = (uint32_t) 1000000 / Capture_CH2;
      CaptureNumber_CH2 = 0;
    }
  }
	

  if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET) 
  {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
    if(CaptureNumber_CH3 == 0)
    {
      /* Get the Input Capture value */
      IC3ReadValue1 = TIM_GetCapture3(TIM2);
      CaptureNumber_CH3 = 1;
    }
    else if(CaptureNumber_CH3 == 1)
    {
      /* Get the Input Capture value */
      IC3ReadValue2 = TIM_GetCapture3(TIM2); 
      
      /* Capture computation */
      if (IC3ReadValue2 > IC3ReadValue1)
      {
        Capture_CH3 = (IC3ReadValue2 - IC3ReadValue1); 
      }
      else
      {
        Capture_CH3 = ((0xFFFF - IC3ReadValue1) + IC3ReadValue2); 
      }
      /* Frequency computation */ 
      TIM2Freq_CH3 = (uint32_t) 1000000 / Capture_CH3;
      CaptureNumber_CH3 = 0;
    }
  }	
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
