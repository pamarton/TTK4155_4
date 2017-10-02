/*
 * menu.c
 *
 * Created: 28.09.2017 20:18:00
 *  Author: dirkpr
 */ 
#include "menu.h"

menu* current_head;
menu* current_selected;

void setup_menu(menu * new_menu, menu * ptr_sib_down, menu * ptr_parent, menu * ptr_child,int n_sib,PGM_P title){
	//new_menu->ptr_self = new_menu;
	//new_menu->ptr_sib_up = ptr_sib_up;
	new_menu->ptr_sib_down = ptr_sib_down;
	new_menu->ptr_child = ptr_child;
	new_menu->ptr_parent = ptr_parent;
	
	new_menu->title = title;
	new_menu->n_sib = n_sib;
}

	
const char mainmenu_entry_0[16] PROGMEM = "Start";
const char mainmenu_entry_1[16] PROGMEM = "highscore";
const char mainmenu_entry_2[16] PROGMEM = "Options";
const char mainmenu_entry_3[16] PROGMEM = "Debug";
const char highscore_entry_0[16] PROGMEM = "Puzzyzlayer69";
const char highscore_entry_1[16] PROGMEM = "X_xMlGPr0_x_Y";
const char highscore_entry_2[16] PROGMEM = "Dirk_tryhardt";
const char option_entry_0[16] PROGMEM = "opt0";
const char option_entry_1[16] PROGMEM = "opt1";
const char option_entry_2[16] PROGMEM = "opt2";
const char option_entry_3[16] PROGMEM = "Contrast";
const char debug_entry_0[16] PROGMEM = "debug0";
const char debug_entry_1[16] PROGMEM = "debug1";
const char debug_entry_2[16] PROGMEM = "debug2";
const char debug_entry_3[16] PROGMEM = "debug3";


char temp[16];

menu highscore_0;
menu highscore_1;
menu highscore_2;
menu option_0;
menu option_1;
menu option_2;
menu option_3;
menu debug_0;
menu debug_1;
menu debug_2;
menu debug_3;
menu mainmenu_0;
menu mainmenu_1;//Highscore
//menu mainmenu_2;
//menu mainmenu_3;

void initialize_menu(void){
	setup_menu(&highscore_0,&highscore_1,&mainmenu_1,NULL,3,highscore_entry_0);
	setup_menu(&highscore_1,&highscore_2,&mainmenu_1,NULL,3,highscore_entry_1);
	setup_menu(&highscore_2,&highscore_0,&mainmenu_1,NULL,3,highscore_entry_2);
	current_head = &highscore_0;
	current_selected = &highscore_1;
	//printf("%i\n",highscore_0.ptr_sib_down);
	//printf("%i\n",current_head->ptr_self);
	//strcpy_P(temp,(current_head->title));
	//printf("%s",temp);
	
	// call highscore 1 through highscore 0
	//strcpy_P(temp, current_head->title));
	//printf("highscore1, called by highscore 0; title: %s\n",(highscore_0.ptr_sib_up),(highscore_0.ptr_sib_down), temp);
	
	
	

	//strcpy_P(temp,highscore_0->title);
	//printf("0self %i up %i down %i prev %i next %i sibl %i title %s\n",highscore_0->ptr_self,highscore_0->ptr_sib_up);
	
	//printf("self %c up %c down %c prev %c next %c sibl %c title %s\n",(*highscore_0.ptr_self),(*highscore_0.ptr_sib_up),(*highscore_0.ptr_sib_down),(*highscore_0.ptr_parent),(*highscore_0.ptr_child),(*highscore_0.n_sib),temp);
	
	//setup_menu(&highscore_1,&highscore_0,&highscore_2,NULL,NULL,3,highscore_n1);
	//_delay_ms(1000);
	//strcpy_P(temp,highscore_0->title);
	//printf("0self %i up %i down %i prev %i next %i sibl %i title %s\n",(highscore_0.ptr_self),(highscore_0.ptr_sib_up),(highscore_0.ptr_sib_down),(highscore_0.ptr_parent),(highscore_0.ptr_child),(highscore_0.n_sib),temp);
	
	
	//strcpy_P(temp,(char*)pgm_read_word(&highscore_0->title));
	//printf("1self %i up %i down %i prev %i next %i sibl %i title %s\n",highscore_0->ptr_self,highscore_0->ptr_sib_up,highscore_0->ptr_sib_down,highscore_0->ptr_parent,highscore_0->ptr_child,highscore_0->n_sib,temp);
	
	
	//strcpy_P(temp,highscore_1->title);
	//printf("self %i up %i down %i prev %i next %i sibl %i title %s\n",&highscore_1->ptr_self,&highscore_1->ptr_sib_up,&highscore_1->ptr_sib_down,&highscore_1->ptr_parent,&highscore_1->ptr_child,highscore_1->n_sib,temp);
	
	
	/*setup_menu(highscore_2,highscore_1,highscore_0,mainmenu_1,NULL,3,highscore_n2);
	
	setup_menu(option_0,option_3,option_1,mainmenu_2,NULL,4,option_n0);
	setup_menu(option_1,option_0,option_2,mainmenu_2,NULL,4,option_n1);
	setup_menu(option_2,option_1,option_3,mainmenu_2,NULL,4,option_n2);
	setup_menu(option_3,option_2,option_0,mainmenu_2,NULL,4,option_n3);
	
	setup_menu(debug_0,debug_3,debug_1,mainmenu_3,NULL,4,option_n0);
	setup_menu(debug_1,debug_0,debug_2,mainmenu_3,NULL,4,option_n1);
	setup_menu(debug_2,debug_1,debug_3,mainmenu_3,NULL,4,option_n2);
	setup_menu(debug_3,debug_2,debug_0,mainmenu_3,NULL,4,option_n3);*/
	
	//setup_menu(mainmenu_0,mainmenu_3,mainmenu_1,NULL,NULL/*BYTT*/,4,mainmenu_n0);
	//setup_menu(mainmenu_1,mainmenu_0,mainmenu_2,NULL,highscore_0,4,mainmenu_n1);
	//setup_menu(mainmenu_2,mainmenu_1,mainmenu_3,NULL,option_0,4,mainmenu_n2);
	//setup_menu(mainmenu_3,mainmenu_2,mainmenu_0,NULL,debug_0,4,mainmenu_n3);
	//printf("%i",*current_head->ptr_self);
	
	/*
	current_head = highscore_0;
	strcpy_P(temp,current_head->title);
	printf("%s ",temp);
	current_selected = highscore_0;
	
	printf("%i",*current_selected);*/
}
	

void menu_update(void){
	if(navigate_menu()==1){
		for (int i = 0; i < current_head->n_sib; i++)
		{
			oled_goto_line(i);
			
			strcpy_P(temp,current_head->title);
			if(current_head == current_selected){
				oled_print_char(129);
				}else{
				oled_print_char(128);
			}
			oled_print(temp);
			current_head = current_head->ptr_sib_down;
			
		}
	}
	
	
	
	
	
}

int x = 0;
int y = 0;
#define NAVIGATION_TRHESHOLD 50
int navigate_menu(void){
	int joystick_reading = read_control_input('Y');
	if(joystick_reading > NAVIGATION_TRHESHOLD && x <= NAVIGATION_TRHESHOLD){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
		x = 100;
		return 1;
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && x >= -NAVIGATION_TRHESHOLD)
	{
		current_selected = current_selected->ptr_sib_down;
		x = -100;
		return 1;
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		x = 0;
	}
}