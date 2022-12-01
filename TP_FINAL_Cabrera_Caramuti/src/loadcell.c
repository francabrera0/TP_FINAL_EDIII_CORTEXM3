#include "LPC17xx.h"
#include "loadcell.h"
#include "macros.h"


uint16_t getWeight(void){
	uint16_t weight = ((LPC_ADC->ADDR0)>>4) & 0xFFF;
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
	return ((~weight) & 0xFFF);
}

static void blink(void){
	for(int i=0; i<8; i++){
		for(int j=0; j<400000; j++);
		LPC_GPIO0->FIOPIN0 |= (i%2)<<1;
	}
	LPC_GPIO0->FIOCLR |= (TARE_LED);
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOSET |= (STOP_LED);
}

uint16_t getTare(uint16_t weight){
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOCLR |= (STOP_LED);
	LPC_GPIO0->FIOCLR |= (TARE_LED);

	if(weight < MINWEIGHT){
		blink();
		return 0;
	}

	LPC_GPIO0->FIOSET |= (TARE_LED);
	return weight;
}

void start(uint16_t tare, uint8_t* iterator){
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOCLR |= (STOP_LED);
	LPC_GPIO0->FIOCLR |= (TARE_LED);

	if(tare < MINWEIGHT){
		blink();
		return;
	}
	*iterator = 2;
	LPC_GPIO0->FIOSET |= (START_LED);
}

void stop(uint16_t* tare, uint8_t* iterator){
	*tare = 0;
	*iterator = 0;
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOSET |= (STOP_LED);
	LPC_GPIO0->FIOCLR |= (TARE_LED);
}




