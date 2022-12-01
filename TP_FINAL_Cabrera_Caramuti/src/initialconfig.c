#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "initialconfig.h"
#include "lpc17xx_uart.h"
#include "macros.h"


static void configEINT(void);
static void configPIN(void);
static void configADC(void);
static void configTIMER0(void);
static void configTIMER1(void);
static void configUART(void);
static void configGPIOInt(void);

int initialConfigurations(void){

	configEINT();
	configPIN();
	configADC();
	configTIMER0();
	configTIMER1();
	configUART();
	configGPIOInt();

	return 0;
}

static void configEINT(void){
	LPC_PINCON->PINSEL4 = 0x00;
	LPC_PINCON->PINSEL4 |= ((1 << 20));
	LPC_PINCON->PINSEL4 |= ((1 << 22));
	LPC_PINCON->PINSEL4 |= ((1 << 24));
	LPC_GPIO2->FIODIR1 |= (7<<2);
	LPC_SC->EXTMODE |= (7);
	LPC_SC->EXTPOLAR &= ~(7);
	LPC_SC->EXTINT |= (7);
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);
}

static void configPIN(void){
	LPC_PINCON->PINSEL0 &= ~(7);
	LPC_PINCON->PINMODE0 |= (42);
	LPC_GPIO0->FIODIR0 |= (7);
}

static void configADC(void){
	LPC_PINCON->PINSEL1 |= (1<<14);
	LPC_PINCON->PINMODE1 |= (1<<15);

	ADC_Init(LPC_ADC, 100000);
	//ADC_BurstCmd(LPC_ADC, DISABLE);
	ADC_StartCmd(LPC_ADC, ADC_START_ON_MAT01);
	ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
	ADC_EdgeStartConfig(LPC_ADC, 0);
	ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
}

static void configTIMER0(void){
	LPC_PINCON->PINSEL3 |= (15<<24);

	TIM_TIMERCFG_Type configTim;
	configTim.PrescaleOption = TIM_PRESCALE_TICKVAL;
	configTim.PrescaleValue = 999;

	TIM_MATCHCFG_Type configMatch;
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	configMatch.IntOnMatch = DISABLE;
	configMatch.MatchChannel = 1;
	configMatch.MatchValue = 5000;
	configMatch.ResetOnMatch = ENABLE;
	configMatch.StopOnMatch = DISABLE;

	TIM_ConfigMatch(LPC_TIM0, &configMatch);
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configTim);
	TIM_Cmd(LPC_TIM0, ENABLE);
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void configTIMER1(void){
	TIM_TIMERCFG_Type timerCon;
	timerCon.PrescaleOption = TIM_PRESCALE_TICKVAL;
	timerCon.PrescaleValue = 10000;//0.1*10^-3=(PS+1)*100*10^-6 =>PS=9999  tc se incrementa cada 0.1ms;

	TIM_MATCHCFG_Type matchCon;
	matchCon.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchCon.IntOnMatch = ENABLE;
	matchCon.ResetOnMatch = DISABLE;
	matchCon.StopOnMatch = DISABLE;
	matchCon.MatchValue = 10;
	matchCon.MatchChannel = 0;
	TIM_ConfigMatch(LPC_TIM1, &matchCon); //configuro M1.0  con el valor de dc y que interrumpa
	matchCon.MatchValue = 200;//CON ESTO SETEO LA PRECUENCIA DE 50HZ
	matchCon.ResetOnMatch = ENABLE;
	matchCon.MatchChannel = 1;
	TIM_ConfigMatch(LPC_TIM1, &matchCon); //configuro M1.1 con 10 para que resetee el tc y que interrumpa

	TIM_Init(LPC_TIM1,TIM_TIMER_MODE, &timerCon);
	LPC_SC->PCLKSEL0 |= (1<<4); //PONGO 01 EN EL PCLKSEL DEL TIMER1 (deja el cclk directo)

	TIM_Cmd(LPC_TIM1, ENABLE);
	NVIC_EnableIRQ(TIMER1_IRQn);

}

static void configUART(void){
	LPC_PINCON->PINSEL4 |= 2;

	UART_CFG_Type configUART;
	configUART.Baud_rate = 9600;
	configUART.Databits = UART_DATABIT_8;
	configUART.Parity = UART_PARITY_NONE;
	configUART.Stopbits = UART_STOPBIT_1;

	UART_Init(LPC_UART1, &configUART);
	UART_TxCmd(LPC_UART1, ENABLE);
}

void configGPIOInt(void){
	LPC_PINCON->PINMODE0 |= (0xAA<<12);
	LPC_GPIO0->FIODIR &= ~(0XF<<6);
	LPC_GPIOINT->IO0IntEnF |= (0xF<<6);
	LPC_GPIOINT->IO0IntEnR |= (0XF<<6);
	LPC_GPIOINT->IO0IntClr |= (0XF<<6);

	LPC_PINCON->PINSEL4 &= ~(3<<6);
	LPC_PINCON->PINMODE4 |= 1<<6; //SETEO P2.3 COMO SALIDA GPIO
	LPC_GPIO2->FIODIR |= 1<<3;

	NVIC_EnableIRQ(EINT3_IRQn);
}
