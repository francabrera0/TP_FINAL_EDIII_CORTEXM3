/*
===============================================================================
 Name        : TP_FINAL_Cabrera_Caramuti.c
 Author      : FranCabrera, IvoCaramuti
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "stdio.h"
#include "LPC17xx.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "initialconfig.h"
#include "loadcell.h"
#include "macros.h"


uint16_t weight = 0;
uint16_t array[NUMSAMPLES];
uint16_t tare = 0;
uint8_t level = 1;
uint32_t duty_cycle[3] = {20,15,17};
uint8_t  iterator = 0;


void sendData(void);
void finish(void);

int main(void) {

	initialConfigurations();

	for(int i=0; i<NUMSAMPLES; i++)
		array[i] = 0;

    while(1) {
    	if((weight-tare) > 280 && tare!=0)
    		finish();
    	if(1.5*weight < tare)
    		stop(&tare, &iterator);
    }
    return 0 ;

}

/*
 * START
 * Abrir el servo y empezar a cargar.
 */
void EINT0_IRQHandler(void){
	start(tare, &iterator);
	LPC_SC->EXTINT |= (START_LED);
}

/*
 * STOP
 *
 */
void EINT1_IRQHandler(void){
	stop(&tare, &iterator);
	TIM_Cmd(LPC_TIM0, ENABLE);
	LPC_SC->EXTINT |= (STOP_LED);
	weight = 0;
}

/*
 * TARE
 */
void EINT2_IRQHandler(void){
	tare = getTare(weight);
	LPC_SC->EXTINT |= (TARE_LED);
}

/*
 * CERRAR SERVO
 */
void finish(void){
	TIM_Cmd(LPC_TIM0, DISABLE);
	iterator = 0;
	while(tare!=0){

	}
	weight = 0;
}


void EINT3_IRQHandler(void){
	level = (uint8_t) (LPC_GPIO0->FIOPIN>>6)&0xF;
	level = ~(level) & 0xF;
	LPC_GPIOINT->IO0IntClr |= (0xF<<6);
}

uint8_t counter = 0;
void ADC_IRQHandler(void){

	array[counter] = getWeight();
	uint32_t average = 0;
	for(int i=0; i<NUMSAMPLES; i++)
		average+=array[i];
	counter++;
	if(counter == NUMSAMPLES)
		counter = 0;
	weight = average>>3;
	sendData();

}


void TIMER1_IRQHandler(void){
	TIM_UpdateMatchValue(LPC_TIM1, 0, duty_cycle[iterator]);
	if ((LPC_TIM1->IR & 0x1)==1){
		LPC_GPIO2->FIOSET |= 1<<3;
		TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
	}
	if (((LPC_TIM1->IR>>1) & 0x1)==1){
		LPC_GPIO2->FIOCLR |= 1<<3;
		TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
	}
}


void sendData(void){
	char weightToSend[6];
	sprintf(weightToSend,"W%4d\n",weight);
	UART_Send(LPC_UART1, (uint8_t*)weightToSend, sizeof(weightToSend), BLOCKING);
	char tareToSend[6];
	sprintf(tareToSend,"T%4d\n",tare);
	UART_Send(LPC_UART1, (uint8_t*)tareToSend, sizeof(tareToSend), BLOCKING);
	char levelToSend[6];
	sprintf(levelToSend,"L%4d\n",level);
	UART_Send(LPC_UART1, (uint8_t*)levelToSend, sizeof(levelToSend), BLOCKING);
}
















