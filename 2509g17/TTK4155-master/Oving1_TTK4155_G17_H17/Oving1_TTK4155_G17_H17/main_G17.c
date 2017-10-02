/*
 * Oving1_TTK4155_G17_H17.c
 *
 * Created: 04.09.2017 11:50:29
 *  Author: pamarton
 */ 
#include <stdio.h>
#define VERSION "l4d2"
#define F_CPU 4915200 // clock frequency in Hz
#define BAUDRATE 9600 // Valgt verdi data sendt pr sekund
#define UBBR 32 - 1 //F_CPU/(16*BAUDRATE)-1 //USART BAUD RATE REGISTER VALUE
#include "adc.h"
#include <avr/io.h>

#define UNDERLINE 0b10000000
#define STREAKTROUGH 0b00010000
#define CENCORED 0b11111111

//#include <avr/interrupt.h>
#include "uart.h"
#include "i_o.h"
#include "input_conversion.h"
#include "button_interrupts.h"

#define MAX_SIGNAL 0xFF
#define MIN_SIGNAL 0
void SRAM_test(void);
void initalize(void);
#include "oled.h"
#include "menu.h"

int main(void)
{
	
	initalize();	
	oled_ini();
	oled_reset();
	/*
	oled_print_effect("test", CENCORED);
	oled_goto_line(2);
	oled_print_char(128);
	
	oled_goto_line(3);
	oled_print_char(129);
	//char * abc = "penis\0";
	//oled_print(abc);
	*/
	
	initialize_menu();
	//oled_print_effect(__TIME__,STREAKTROUGH);
	oled_reset();
	
	
	
	
	while(1){
		
		
		menu_update();
	}
	
	//testUart();
	
}







void initalize(void){
	
	init_UART(UBBR);
	printf("LOADING g17_%s %s %s\nINITIALIZING...\n\nUART successfully initialized\n\n", VERSION,__DATE__,__TIME__);
	BIT_ON(MCUCR,SRE); //SET THIS IN SOME INITALIZE FUNBCTION
	
	
	BIT_ON(SFIOR,XMM2);//HVORFOR GJORDE DE DETTE I OLED?
	
	//initialize_menu();
	
	initialize_control_input();
	printf("control input successfully initialized\n\n");
	SRAM_test();
	printf("SRAM successfully initialized\n");
	initalize_interrupts();
	printf("Interrupts successfully initialized\n");
	printf("Interrupts activated\n");
	printf("\nINITIALIZATION COMPLETE\n");
}

#include <stdlib.h>
void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,	retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the writephase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors	in retrieval phase\n\n", write_errors, retrieval_errors);
}



