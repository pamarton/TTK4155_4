/*
 * oled.h
 *
 * Created: 28.09.2017 16:23:56
 *  Author: dirkpr
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>
void write_c(uint8_t cmd);
void write_d(uint8_t data);

void oled_home(void);
void oled_ini(void);
void oled_reset(void);
void oled_goto_line(unsigned int line);
void oled_print(char * letters);
void oled_print_effect(char * letters, char effect);
int oled_print_char(char letter);
int oled_print_char_effect(char letter, char effect);
void oled_reset(void);
void oled_clear_line(unsigned int line);




void sram_init(void);
void sram_write(int rad,int kol, char data);
void sram_write_and(int rad,int kol, char data);
void sram_write_or(int rad,int kol, char data);
void write_screen(void);

int sram_pixel(int x, int y);
void sram_draw_line(int x0, int y0, int x1, int y1);
int sram_write_char(char letter);
void sram_write_string(char letters[]);
void sram_draw_circle(int x0, int y0, int radius);

#endif /* OLED_H_ */