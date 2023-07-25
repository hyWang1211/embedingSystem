#include <REGX52.H>

//????:
sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_EN=P2^2;
#define LCD_DataPort P0

//????:
/**
  * @brief  LCD1602????,12MHz?????1ms
  * @param  ?
  * @retval ?
  */
void LCD_Delay()
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602???
  * @param  Command ??????
  * @retval ?
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602???
  * @param  Data ??????
  * @retval ?
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602??????
  * @param  Line ???,??:1~2
  * @param  Column ???,??:1~16
  * @retval ?
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}

/**
  * @brief  LCD1602?????
  * @param  ?
  * @retval ?
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//??????,????,5*7??
	LCD_WriteCommand(0x0c);//???,???,???
	LCD_WriteCommand(0x06);//???????,??????,????
	LCD_WriteCommand(0x01);//????,??
}

/**
  * @brief  ?LCD1602???????????
  * @param  Line ???,??:1~2
  * @param  Column ???,??:1~16
  * @param  Char ??????
  * @retval ?
  */
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
  * @brief  ?LCD1602?????????????
  * @param  Line ?????,??:1~2
  * @param  Column ?????,??:1~16
  * @param  String ???????
  * @retval ?
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  ???=X?Y??
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief  ?LCD1602????????????
  * @param  Line ?????,??:1~2
  * @param  Column ?????,??:1~16
  * @param  Number ??????,??:0~65535
  * @param  Length ????????,??:1~5
  * @retval ?
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ?LCD1602???????????????????
  * @param  Line ?????,??:1~2
  * @param  Column ?????,??:1~16
  * @param  Number ??????,??:-32768~32767
  * @param  Length ????????,??:1~5
  * @retval ?
  */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ?LCD1602?????????????????
  * @param  Line ?????,??:1~2
  * @param  Column ?????,??:1~16
  * @param  Number ??????,??:0~0xFFFF
  * @param  Length ????????,??:1~4
  * @retval ?
  */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

/**
  * @brief  ?LCD1602????????????????
  * @param  Line ?????,??:1~2
  * @param  Column ?????,??:1~16
  * @param  Number ??????,??:0~1111 1111 1111 1111
  * @param  Length ????????,??:1~16
  * @retval ?
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}
