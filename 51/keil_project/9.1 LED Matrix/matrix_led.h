#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

void _74HC595_WriteByte(unsigned int row);
void Show_Colum(unsigned int col, unsigned rows);
void Matrix_intit();
void show_dynamic_img_init(unsigned int start);

#endif