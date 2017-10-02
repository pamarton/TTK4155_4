/*
 * oled.c
 *
 * Created: 28.09.2017 16:22:41
 *  Author: dirkpr
 */ 


#include "oled.h"
#include "font.h"
#include "input_conversion.h"
#include <avr/io.h>



volatile char *oled_cmd = (char *) 0x1000; // Start address for the OLED_Command
volatile char *oled_data = (char *) 0x1200; // Start address for the OLED_DATA

int page,col;

void write_c(uint8_t cmd)
{
	*oled_cmd = cmd;
}


void write_d(uint8_t data)
{
	*oled_data = data;
}

void oled_ini(void)
{
	//Enable the external memory interface
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	write_c(0xae);        //display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //displayc divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x50);
	write_c(0xd9);        //set  pre-charge  period
	write_c(0x21);
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x00);
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        //out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	
	write_c(0xd3);			//offset fix on the screen
	write_c(0x76);			//value of the offset
	oled_reset();
	oled_home();

}


void oled_reset(void)
{		
	for(int i = 0; i < 8;i++){
		oled_clear_line(i);
	}
}

void oled_home(void)
{
	page = 0;
	col = 0;
	
	
	write_c(0x21); // set column (left to right)
	write_c(0x00); // column start
	write_c(0x7f); // column end
	
	write_c(0x22); // set row (top to bottom)
	write_c(0x00); // row start
	write_c(0x7); // row end
	
	//write_c(0x00);
	//write_c(0x10);
}

void oled_goto_line(unsigned int line){
	oled_home();
	page = line;
	if(line >= 8){
		printf("parameter too big, oled_goto_line\n");
	}else{
		write_c(0x00);
		write_c(0x10);
		write_c(0xB0 | line);
	}
}


void oled_goto_column(unsigned int column){
	if(column > 128){
		printf("parameter too big, oled_goto_column\n");
	}else{
	
	}
}

void oled_clear_line(unsigned int line){
	if(line < 8){
		for(unsigned int i = 0; i < 128; i++){
			write_d(0b00000000);
		}
	}else{
		printf("parameter too big, oled_clear_line\n");
	}
} 

void oled_pos(unsigned int row,unsigned int column){
	if(row > 64 || column > 128){
		printf("parameter too big, oled_pos\n");
	}else{
		
	}
}
int oled_print_char(char letter){
	if(letter != '\0'){
		//printf("%c",letter);
		for(unsigned int i = 0; i < 8; i++){
			 * oled_data = pgm_read_byte(&font[letter-' '][i]);
		}
		return 1;
	}else{
		return 0;	
	}
}

int oled_print_char_effect(char letter, char effect){
	if(letter != '\0'){
		//printf("%c",letter);
		for(unsigned int i = 0; i < 8; i++){
			* oled_data = pgm_read_byte(&font[letter-' '][i]) | effect;
		}
		return 1;
	}else{
		return 0;
	}
}


void oled_print(char* letters){
	unsigned int i = 0;
	while (oled_print_char(letters[i++])){
	}
}

void oled_print_effect(char* letters, char effect){
	unsigned int i = 0;
	while (oled_print_char_effect(letters[i++],effect)){
	}
}



