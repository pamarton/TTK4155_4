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

	
const char mainmenu_entry_0[12] PROGMEM = "Start";
const char mainmenu_entry_1[12] PROGMEM = "Highscore";
const char mainmenu_entry_2[12] PROGMEM = "Debug";
const char mainmenu_entry_3[12] PROGMEM = "Options";
const char highscore_entry_0[12] PROGMEM = "Highscore:";
const char highscore_entry_1[12] PROGMEM = "2nd";
const char highscore_entry_2[12] PROGMEM = "3rd";
const char option_entry_0[12] PROGMEM = "Music";
const char option_entry_1[12] PROGMEM = "Contrast";
const char option_entry_2[12] PROGMEM = "opt2";
const char option_entry_3[12] PROGMEM = "Inv. colors";
const char debug_entry_0[12] PROGMEM = "Reset";
const char debug_entry_1[12] PROGMEM = "Calibrate";
const char debug_entry_2[12] PROGMEM = "debug2";
const char debug_entry_3[12] PROGMEM = "debug3";


char temp[12];

// menu highscore_0;
// menu highscore_1;
// menu highscore_2;
menu option_0;
menu option_1;
//menu option_2;
//menu option_3;
menu debug_0;
menu debug_1;
menu mainmenu_0;//Highscore
menu mainmenu_1;
menu mainmenu_2;
//menu mainmenu_3;

void initialize_menu(void){
	//setup_menu(&highscore_0,NULL,&mainmenu_0,&mainmenu_0,1,highscore_entry_0);
	//setup_menu(&highscore_1,&highscore_2,&mainmenu_0,NULL,3,highscore_entry_1);
	//setup_menu(&highscore_2,&highscore_0,&mainmenu_0,NULL,3,highscore_entry_2);
	
	setup_menu(&mainmenu_0,&mainmenu_1,NULL,NULL,3,mainmenu_entry_1);
	setup_menu(&mainmenu_1,&mainmenu_2,NULL,&debug_0,3,mainmenu_entry_2);
	setup_menu(&mainmenu_2,&mainmenu_0,NULL,&option_0,3,mainmenu_entry_3);
	
	setup_menu(&option_0,&option_1,&mainmenu_0,NULL,2,option_entry_0);
	setup_menu(&option_1,&option_0,&mainmenu_0,NULL,2,option_entry_1);
	//setup_menu(&option_2,&option_3,&mainmenu_2,NULL,4,option_entry_2);
	//setup_menu(&option_3,&option_0,&mainmenu_2,NULL,4,option_entry_3);
	
	setup_menu(&debug_0,&debug_1,&mainmenu_0,NULL,2,debug_entry_0);
	setup_menu(&debug_1,&debug_0,&mainmenu_0,NULL,2,debug_entry_1);
	
	
	current_head = &mainmenu_0;
	current_selected = &mainmenu_0;
	
}
	

void menu_update(void){
	if(navigate_menu()){
		oled_reset();
		for (int i = 0; i < current_head->n_sib; i++)
		{
			oled_goto_line(i);
			
			strcpy_P(temp,current_head->title);
			oled_print_char(128 + (current_head == current_selected));
			oled_print(temp);
			current_head = current_head->ptr_sib_down;
			
		}
	}	
}

int x = 0;
int y = 0;

int navigate_menu(void){
	int joystick_reading = read_control_input('Y');
	if(joystick_reading > NAVIGATION_TRHESHOLD && y <= NAVIGATION_TRHESHOLD){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
		y = 100;
		return 1;
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && y >= -NAVIGATION_TRHESHOLD)
	{
		current_selected = current_selected->ptr_sib_down;
		y = -100;
		return 1;
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		y = 0;
	}
	
	
	joystick_reading = read_control_input('X');
	if(joystick_reading > NAVIGATION_TRHESHOLD && x <= NAVIGATION_TRHESHOLD){
		if(current_selected->ptr_child != NULL){
			current_head = current_selected->ptr_child;
			current_selected = current_selected->ptr_child;
		}else{
			strcpy_P(temp,current_selected->title);
			printf("running function %s\n",temp);
			
			// function calls
			if(current_selected == &mainmenu_0){ // mainmenu->highscore
				oled_reset();
				for (unsigned int j = 0; j < 3; j++)
				{
					oled_goto_line(j);
					oled_print_char(0x31+j);
					oled_print(" Highscore");
					
				}
				while(read_control_input('X') > NAVIGATION_TRHESHOLD){}	
			}else if(current_selected == &option_1){ // mainmenu->option->contrast
				while (read_control_input('X') > NAVIGATION_TRHESHOLD)
				{
					write_c(0x81);
					write_c(readADC(3)/2);
				}
			}
		}
		x = 100;
		return 1;
		
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && x >= -NAVIGATION_TRHESHOLD)
	{
		if(current_selected->ptr_parent != NULL){
			current_head = current_selected->ptr_parent;
			current_selected = current_selected->ptr_parent;
			x = -100;
			return 1;
		}
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		x = 0;
	}
	
	return 0;
}