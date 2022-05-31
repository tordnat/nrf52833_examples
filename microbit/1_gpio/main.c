#include <stdint.h>


#define GPIO_BASE_ADDRESS0 0x50000000
#define GPIO_BASE_ADDRESS1 0x50000300

#define GPIO0 ((NRF_GPIO_REGS0*) GPIO_BASE_ADDRESS0 ) //gpio 0 base adress
#define GPIO1 ((NRF_GPIO_REGS1*) GPIO_BASE_ADDRESS1) //gpio 1 base adress

#define buttonA 14
#define buttonB 23

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_0[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS0;

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_1[118];
	volatile uint32_t PIN_CNF[10];
} NRF_GPIO_REGS1;

int main(){

	// Configure leds to output
	GPIO0->PIN_CNF[21] = 1; //Row 1
	GPIO0->PIN_CNF[22] = 1; //Row 2
	GPIO0->PIN_CNF[15] = 1; //Row 3
	GPIO0->PIN_CNF[24] = 1; //Row 4
	GPIO0->PIN_CNF[19] = 1; //Row 5

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 
	
	// Configure buttons configure input -> active low?
	GPIO0->PIN_CNF[buttonA] = 0; // button A 
	GPIO0->PIN_CNF[buttonB] = 0; // button B

	uint32_t buttonA_on = 0;
	uint32_t buttonB_on = 0;
	uint32_t matrix_on_gpio0_bitmask = ((1 << 21) | (1 << 22) | (1 << 15) | (1 << 24) | (1<< 19));
	int sleep = 0;
	while(1){
		buttonA_on = !(GPIO0->IN & (1 << buttonA));
		buttonB_on =  !(GPIO0->IN & (1 << buttonB));

		if (buttonB_on){
			GPIO0->OUTSET = (matrix_on_gpio0_bitmask);
		}
		if (buttonA_on){
			GPIO0->OUTCLR = matrix_on_gpio0_bitmask;

		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
