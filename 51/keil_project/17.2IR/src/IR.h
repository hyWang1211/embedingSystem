#ifndef __IR_H__
#define __IR_H__

void IR_init();
unsigned char IR_get_data_flag();
unsigned char IR_get_repeat_flag();
unsigned char IR_get_command();
unsigned char IR_get_addr();

#endif