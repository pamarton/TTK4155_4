/*
 * menu.c
 *
 * Created: 28.09.2017 20:18:00
 *  Author: dirkpr
 */ 
#include "menu.h"

menu* current_head;
menu* current_selected;

void setup_menu(menu * new_menu,menu * ptr_up, menu * ptr_down, menu * ptr_prev, menu * ptr_next,int n_siblings,PGM_P name){
	new_menu->title = name;
	new_menu->ptr_up = ptr_up;
	new_menu->ptr_down = ptr_down;
	new_menu->ptr_next = ptr_next;
	new_menu->ptr_prev = ptr_prev;
	new_menu->n_siblings = n_siblings;
}

const char mainmenu_n0[] PROGMEM = "Start";
const char mainmenu_n1[] PROGMEM = "Leaderboard";
const char mainmenu_n2[] PROGMEM = "Options";
const char mainmenu_n3[] PROGMEM = "Debug";
const char leaderboard_n0[] PROGMEM = "0";
const char leaderboard_n1[] PROGMEM = "1";
const char leaderboard_n2[] PROGMEM = "2";
const char leaderboard_n3[] PROGMEM = "3";
const char leaderboard_n4[] PROGMEM = "4";
const char leaderboard_n5[] PROGMEM = "5";
const char leaderboard_n6[] PROGMEM = "6";
const char leaderboard_n7[] PROGMEM = "7";
const char option_n0[] PROGMEM = "opt0";
const char option_n1[] PROGMEM = "opt1";
const char option_n2[] PROGMEM = "opt2";
const char option_n3[] PROGMEM = "Contrast";
const char debug_n0[] PROGMEM = "debug0";
const char debug_n1[] PROGMEM = "debug1";
const char debug_n2[] PROGMEM = "debug2";
const char debug_n3[] PROGMEM = "debug3";


char temp[16];
int counter;

void initialize_menu(void){
	menu* leaderboard_0 = malloc(sizeof(menu));
	menu* leaderboard_1 = malloc(sizeof(menu));
	menu* leaderboard_2 = malloc(sizeof(menu));
	menu* leaderboard_3 = malloc(sizeof(menu));
	menu* leaderboard_4 = malloc(sizeof(menu));
	menu* leaderboard_5 = malloc(sizeof(menu));
	menu* leaderboard_6 = malloc(sizeof(menu));
	menu* leaderboard_7 = malloc(sizeof(menu));
	menu* option_0 = malloc(sizeof(menu));
	menu* option_1 = malloc(sizeof(menu));
	menu* option_2 = malloc(sizeof(menu));
	menu* option_3 = malloc(sizeof(menu));
	menu* debug_0 = malloc(sizeof(menu));
	menu* debug_1 = malloc(sizeof(menu));
	menu* debug_2 = malloc(sizeof(menu));
	menu* debug_3 = malloc(sizeof(menu));
	menu* mainmenu_0 = malloc(sizeof(menu));
	menu* mainmenu_1 = malloc(sizeof(menu));
	menu* mainmenu_2 = malloc(sizeof(menu));
	menu* mainmenu_3 = malloc(sizeof(menu));
	
	setup_menu(leaderboard_0,leaderboard_7,leaderboard_1,mainmenu_1,NULL,8,leaderboard_n0);
	setup_menu(leaderboard_1,leaderboard_0,leaderboard_2,mainmenu_1,NULL,8,leaderboard_n1);
	setup_menu(leaderboard_2,leaderboard_1,leaderboard_3,mainmenu_1,NULL,8,leaderboard_n2);
	setup_menu(leaderboard_3,leaderboard_2,leaderboard_4,mainmenu_1,NULL,8,leaderboard_n3);
	setup_menu(leaderboard_4,leaderboard_3,leaderboard_5,mainmenu_1,NULL,8,leaderboard_n4);
	setup_menu(leaderboard_5,leaderboard_4,leaderboard_6,mainmenu_1,NULL,8,leaderboard_n5);
	setup_menu(leaderboard_6,leaderboard_5,leaderboard_7,mainmenu_1,NULL,8,leaderboard_n6);
	setup_menu(leaderboard_7,leaderboard_6,leaderboard_0,mainmenu_1,NULL,8,leaderboard_n7);
	
	setup_menu(option_0,option_3,option_1,mainmenu_2,NULL,4,option_n0);
	setup_menu(option_1,option_0,option_2,mainmenu_2,NULL,4,option_n1);
	setup_menu(option_2,option_1,option_3,mainmenu_2,NULL,4,option_n2);
	setup_menu(option_3,option_2,option_0,mainmenu_2,NULL,4,option_n3);
	
	setup_menu(debug_0,debug_3,debug_1,mainmenu_3,NULL,4,option_n0);
	setup_menu(debug_1,debug_0,debug_2,mainmenu_3,NULL,4,option_n1);
	setup_menu(debug_2,debug_1,debug_3,mainmenu_3,NULL,4,option_n2);
	setup_menu(debug_3,debug_2,debug_0,mainmenu_3,NULL,4,option_n3);
	
	setup_menu(mainmenu_0,mainmenu_3,mainmenu_1,NULL,NULL/*BYTT*/,4,mainmenu_n0);
	setup_menu(mainmenu_1,mainmenu_0,mainmenu_2,NULL,leaderboard_0,4,mainmenu_n1);
	setup_menu(mainmenu_2,mainmenu_1,mainmenu_3,NULL,option_0,4,mainmenu_n2);
	setup_menu(mainmenu_3,mainmenu_2,mainmenu_0,NULL,debug_0,4,mainmenu_n3);
	
	current_head = debug_0;
	current_selected = debug_0;
}
	

void menu_update(void){
	
	
	for(counter = 0 ; counter < 4; counter++){
		strcpy_P(temp,current_head->title);
		
		oled_goto_line(counter);
		oled_print(temp);
		
		if(current_selected == current_head){
			oled_print(" <-");
		}
		current_head = current_head->ptr_down;
	}
}