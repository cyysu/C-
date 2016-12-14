/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stdio.h"
#include "systick.h"
#include "stm32f10x_systick.h"

#define ADC_Data_Start2 0xff
#define ADC_Data_Start1 0xfe


extern u8 ADC_BUFFER_Finish;
extern u16 num_test;
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
  * @brief   This function handles NMI exception.
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
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void DMA1_Channel4_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC4);
  DMA_ClearITPendingBit(DMA1_IT_TE4);  
  DMA_Cmd(DMA1_Channel4, DISABLE);//�ر�����DMA
    /*֡���ݽ���λ���� ����2��0xfe*/
 /* USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_SendData(USART1,ADC_Data_End); 
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_SendData(USART1,ADC_Data_End);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	 
  USART_ClearFlag(USART1,USART_FLAG_TC);  */
  /*֡���ݽ���λ���� ����2��0xfe*/
  	 
   if(ADC_BUFFER_Finish)
   {
	ADC_BUFFER_Finish = 0;
   if(num_test > 0)	  //������Ϊ�˲��Թ̶����������ݽ������ 
   //���Ҫ������һֱ���ϵط��� ȥ�����if ����֮��Ӧ��else����
   {
	delay_ms(5);   //��ʱ3���� 	
	num_test --; 
    DMA_Cmd(DMA1_Channel1, ENABLE);//����ADC_DMA  	 
	}
	 else
	 { 
	 num_test = 0;
	 }  
   }   
}



void DMA1_Channel1_IRQHandler(void)
{ 
  /*֡������ʼλ���� ����2��0xff*/
  /*9��25����ı� ֡ͷӦ��Ϊ0xfe,0xff ������ͬ�������*/
  USART_SendData(USART1,ADC_Data_Start1);
  USART_ClearFlag(USART1,USART_FLAG_TC);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_SendData(USART1,ADC_Data_Start2);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  USART_ClearFlag(USART1,USART_FLAG_TC);
  /*֡������ʼλ���� ����2��0xff*/
  DMA_Cmd(DMA1_Channel1, DISABLE);//�ر�����DMA 
//  ADC_Cmd(ADC1, DISABLE); 
  DMA_ClearITPendingBit(DMA1_IT_TC1);
  DMA_ClearITPendingBit(DMA1_IT_TE1); 
//  ADC_Cmd(ADC1, ENABLE);  
  ADC_BUFFER_Finish=1;//��DMA�������
  DMA_Cmd(DMA1_Channel4, ENABLE);//����USART_DMA  
//  DMA_Cmd(DMA1_Channel1, DISABLE);//�ر�DMA  
}

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


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
