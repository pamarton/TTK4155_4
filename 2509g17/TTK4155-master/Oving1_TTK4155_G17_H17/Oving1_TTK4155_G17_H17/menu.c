/*
 * menu.c
 *
 * Created: 28.09.2017 20:18:00
 *  Author: dirkpr
 */ 
#include "menu.h"

menu* current_head;
menu* current_selected;

void setup_menu(menu * new_menu, menu * ptr_sib_down, menu * ptr_parent, menu * ptr_child, int n_sib, PGM_P title){
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
const char debug_entry_0[12] PROGMEM = "fit screen";
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

	setup_menu(&mainmenu_0,&mainmenu_1,NULL,NULL,3,mainmenu_entry_1);
	setup_menu(&mainmenu_1,&mainmenu_2,NULL,&debug_0,3,mainmenu_entry_2);
	setup_menu(&mainmenu_2,&mainmenu_0,NULL,&option_0,3,mainmenu_entry_3);
	
	setup_menu(&option_0,&option_1,&mainmenu_0,NULL,2,option_entry_0);
	setup_menu(&option_1,&option_0,&mainmenu_0,NULL,2,option_entry_1);

	setup_menu(&debug_0,&debug_1,&mainmenu_0,NULL,2,debug_entry_0);
	setup_menu(&debug_1,&debug_0,&mainmenu_0,NULL,2,debug_entry_1);
	
	// current_head is the top entry of the current menu.
	current_head = &mainmenu_0;
	
	// current_selected is the selected menu entry of the current menu.
	current_selected = &mainmenu_0;
	
}

void menu_update(void){
	if(navigate_menu()){
		for (int j = 0; j < 7; j++)
		{
			sram_clear_line(j);
		}
		sram_clear_line(0);
		sram_clear_line(1);
		sram_clear_line(2);
		sram_clear_line(3);
		//sram_init();
		
		for (int i = 0; i < current_head->n_sib; i++)
		{
			oled_goto_line(i);
			oled_goto_column(0);
			strcpy_P(temp,current_head->title);
			
			
			//oled_print_char(128 + (current_head == current_selected));
			sram_write_char(128 + (current_head == current_selected));
			//oled_print(temp);
			sram_write_string(temp);
			current_head = current_head->ptr_sib_down;
		}
		
	}
	sram_scroll_data(7);
	write_screen();
}



int navigate_menu(void){
	int joystick_reading_x = read_control_input('X');
	int joystick_reading_y = read_control_input('Y');
	
	if(joystick_reading_y > NAVIGATION_TRHESHOLD){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
	}
	else if (joystick_reading_y < -NAVIGATION_TRHESHOLD){
		current_selected = current_selected->ptr_sib_down;
	}
	else if(joystick_reading_x > NAVIGATION_TRHESHOLD && current_selected->ptr_child != NULL){;
		current_head = current_selected->ptr_child;
		current_selected = current_selected->ptr_child;
		//USE FUNCTIONS HERE
	}
	else if (joystick_reading_x < -NAVIGATION_TRHESHOLD && current_selected->ptr_parent != NULL){
		current_head = current_head->ptr_parent;
		current_selected = current_selected->ptr_parent;
	}else{
	}
	return 1;
	/*
	
	// Navigate up/down, i.e. navigate within the displayed menu.
	int joystick_reading = read_control_input('Y');
	
	// Navigate up.
	if(joystick_reading > NAVIGATION_TRHESHOLD && y_lock <= NAVIGATION_TRHESHOLD){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
		y_lock = RANGE_MAX;
		return 1;
	// Navigate down.
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && y_lock >= -NAVIGATION_TRHESHOLD)
	{
		current_selected = current_selected->ptr_sib_down;
		y_lock = RANGE_MIN;
		return 1;
	// No navigation input on y-axis.
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		y_lock = 0;
	}
	
	// Navigate left/right, i.e. go to sub-menu or call associated function.
	joystick_reading = read_control_input('X');
	
	// Navigate to sub-menu or call function associated to menu-entry.
	if(joystick_reading > NAVIGATION_TRHESHOLD && x_lock <= NAVIGATION_TRHESHOLD){
		//If menu-entry has a child, navigate to it.
		if(current_selected->ptr_child != NULL){
			current_head = current_selected->ptr_child;
			current_selected = current_selected->ptr_child;
		// function calls
		}else{ 
			strcpy_P(temp,current_selected->title);
			printf("running function %s\n",temp);

			// main-menu->highscore
			if(current_selected == &mainmenu_0){ 
				oled_reset();
				for (unsigned int j = 0; j < 3; j++)
				{
					oled_goto_line(j);
					oled_print_char(0x31+j);
					oled_print(" Highscore");
					
				}
				// Keep joystick pressed to the right. -> Show highscore on screen.
				while(read_control_input('X') > NAVIGATION_TRHESHOLD){}	
			// main-menu->option->contrast
			}else if(current_selected == &option_1){ 
				// Keep joystick pressed to the right. -> Change contrast by using left slider.
				while (read_control_input('X') > NAVIGATION_TRHESHOLD)
				{
					write_c(0x81);
					write_c(readADC(3)/2);
				}
			}else if(current_selected == &debug_0){
				
				int calibrate = 0x3f;
				
				oled_goto_line(0);
				oled_print("               ");
				oled_print_char(131);
				oled_goto_line(7);
				oled_print_char(130);
				while(read_control_input('X') > -NAVIGATION_TRHESHOLD){
					calibrate += read_control_input('Y')/100;
					_delay_ms(200);
					write_c(0xd3);			//offset fix on the screen
					write_c(calibrate);			//value of the offsett
					
				}
				x_lock = RANGE_MIN;
				return 1;
			}
		}
		x_lock = RANGE_MAX;
		return 1;
		
	// Navigate to parent.
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && x_lock >= -NAVIGATION_TRHESHOLD){
		if(current_selected->ptr_parent != NULL){
			current_head = current_selected->ptr_parent;
			current_selected = current_selected->ptr_parent;
			x_lock = -100;
			return 1;
		}
	// No navigation input on x-axis.
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		x_lock = 0;
	}
	*/
	return 0;
}

