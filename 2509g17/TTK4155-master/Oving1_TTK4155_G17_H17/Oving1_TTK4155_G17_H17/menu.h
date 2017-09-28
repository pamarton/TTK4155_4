/*
 * menu.h
 *
 * Created: 28.09.2017 20:18:12
 *  Author: dirkpr
 */ 


#ifndef MENU_H_
#define MENU_H_
#include "oled.h"
#include <avr/pgmspace.h>
#include "uart.h"
#include "input_conversion.h"


#include <stdlib.h>//malloc
typedef struct menu menu;

struct menu {
	PGM_P title;
	int n_siblings;
	menu * ptr_up;
	menu * ptr_down;
	menu * ptr_next;
	menu * ptr_prev;
};

void menu_update(void);
void initialize_menu(void);
void setup_menu(menu * new_menu,menu * ptr_up, menu * ptr_down, menu * ptr_prev, menu * ptr_next,int n_siblings,PGM_P name);

#endif /* MENU_H_ */