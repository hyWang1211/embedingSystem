#ifndef __INFRARED_H__
#define __INFRARED_H__

void infrared_init();
unsigned char IR_get_data_flag();
unsigned char IR_get_repeat_flag();
unsigned char IR_get_data_addr();
unsigned char IR_get_data_command();
#endif