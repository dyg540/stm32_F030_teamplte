
#include "stm32f0xx.h"
#include "delay.h"

u16 fac_ms; //ȫ�ֱ���
u8 fac_us;	//ȫ�ֱ���

void delay_ms(u16 nms)
{
	SysTick->LOAD = (u32)fac_ms * nms - 1; //����ʱ��ֵ
	SysTick->VAL = 1;					   //���д��ֵ��������ؼĴ�����ֵ
	SysTick->CTRL |= BIT(0);			   // SysTickʹ��
	while (!(SysTick->CTRL & (1 << 16)))
		;					  //�ж��Ƿ����0
	SysTick->CTRL &= ~BIT(0); //�ر�SysTick
}

void Delay_Init(u8 SYSCLK)
{
	SysTick->CTRL &= ~BIT(2); //ѡ���ⲿʱ��
	SysTick->CTRL &= ~BIT(1); //�رն�ʱ������0����ж�����
	fac_us = SYSCLK / 8;	  //�����SysTick����ֵ
	fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 nus)
{
	SysTick->LOAD = (u32)fac_us * nus - 1; //����ʱ��ֵ
	SysTick->VAL = 1;					   //���д��ֵ��������ؼĴ�����ֵ
	SysTick->CTRL |= BIT(0);			   // SysTickʹ��
	while (!(SysTick->CTRL & (1 << 16)))
		;					  //�ж��Ƿ����0
	SysTick->CTRL &= ~BIT(0); //�ر�SysTick
}
