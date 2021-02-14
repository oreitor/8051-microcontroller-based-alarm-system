#include <REGX51.H>
#include <stdio.h> 
#include <string.h>

#define keypad P1
#define LCD P2

sbit mrs_sensor=P3^2;
sbit pir_sensor=P3^3;
sbit rs =P3^4;
sbit en =P3^5;
sbit bzr_l = P3^6;
sbit bzr_h = P3^7;
sbit alarm_led=P0^5;
sbit pir_led=P0^6;
sbit rs_led=P0^7;

int count = 1;
unsigned int lcd_cursor;

char a = '1';
char b = '2';
char c = '5';
char d = '8';
unsigned char e;
unsigned char f;
unsigned char g;
unsigned char h;

void string(char *);
void dely(unsigned int dly);
void lcd_cmd(unsigned char ch);
void lcd_data(unsigned char ch);
void lcd_str(unsigned char *str);
char get_keypad_key(void);

void main(void)
{	
	char KeyVal =0;
	alarm_led = 0;
	pir_led = 0;
	rs_led = 0;
	bzr_l = 1;
	bzr_h = 1;
	
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x10);
	lcd_cmd(0x0C);
	lcd_cmd(0x80);	
	string("ALARM KURULUMU");				
	dely(500);
	lcd_cmd(0x01);	
	
	while(1)
	{	
		string("SIFRE: ");
			
    while(1)
    {					
		alarm_led = 0;
		dely(100);
				
		if(lcd_cursor < 4)
		{
			lcd_cmd(0x88+lcd_cursor);
			if(lcd_cursor == 1)
				e = KeyVal;
			if(lcd_cursor == 2)
				f = KeyVal;
			if(lcd_cursor == 3)
				g = KeyVal;
		}
				
		if(lcd_cursor == 4)
		{	
			dely(100);
			h = KeyVal;
			lcd_cmd(0x88 + lcd_cursor);
			KeyVal = get_keypad_key();
			lcd_data(KeyVal);
			dely(100);
					
			if(KeyVal == '*')
			{
				dely(200);
							
				if(a == e && b == f && c == g && d == h)
				{
					lcd_cmd(0x01);
					string("SIFRE DOGRU");
					dely(200);
					lcd_cmd(0x01);
					string("ALARM AKTIF");
							
					while(count < 30)
					{									
						alarm_led = 1;
						bzr_l = 0;
						dely(300);
						bzr_l = 1;
						alarm_led = 0;
						dely(300);
						count++;
					}
								
					e = 'x';
					f = 'x';
					g = 'x';
					h = 'x';								
					count = 0;
								
					while(pir_sensor == 0 && mrs_sensor == 0)
					{	
						alarm_led = 1;
						pir_led = 1;
						rs_led = 1;
						dely(200);
					}
							
					lcd_cmd(0x01);
					string("GUVENLIK IHLALI");
					dely(500);
					lcd_cmd(0x01);
					lcd_cursor = 0;
							
					while(count < 50)
					{
						string("SIFRE: ");
								
						while(1)
						{	
							alarm_led = 0;
							pir_led = 0;
							rs_led = 0;
							bzr_l = 1;
							dely(50);
									
							if(lcd_cursor < 4)									
							{
								lcd_cmd(0x88+lcd_cursor);
								if(lcd_cursor == 1)
									e = KeyVal;
								if(lcd_cursor == 2)
									f = KeyVal;
								if(lcd_cursor == 3)
									g = KeyVal;
								dely(50);
								}						
										
							if(lcd_cursor == 4)
							{	
								dely(100);										
								h = KeyVal;
								lcd_cmd(0x88 + lcd_cursor);
								KeyVal = get_keypad_key();
								lcd_data(KeyVal);
								dely(100);
										
								if(KeyVal == '*')
								{	
									dely(200);
												
									if(a == e && b == f && c == g && d == h)
									{			
										lcd_cmd(0x01);
										string("SIFRE DOGRU");
										dely(200);
										lcd_cmd(0x01);
										string("ALARM PASIF");
													
										alarm_led = 0;
										pir_led = 0;
										rs_led = 0;
										bzr_l = 1;
													
										while(1)
										{
											dely(100);
										}
									}
										
									else
									{	
										count = 0;
										lcd_cmd(0x01);
										string("GUVENLIK IHLALI");
													
										while(count < 300)
										{
											alarm_led = 1;
											pir_led = 1;
											rs_led = 1;
											bzr_h = 0;
														
											SCON = 0X50;
											TMOD = 0X20;
											TH1 = -3;
											TR1 = 1;
											SBUF = '1';
														
											while(TI == 0);
											TI = 0;
														
											dely(300);														
											alarm_led = 0;
											pir_led = 0;
											rs_led = 0;
											bzr_h = 1;														
											dely(300);
										}
									}												
								}
											
								else
								{
									lcd_cmd(0x01);
									lcd_cursor = 0;
									break;
								}												
							}
									
							alarm_led = 1;
							pir_led = 1;
							rs_led = 1;
							bzr_l = 0;									
							dely(100);
									
							KeyVal = get_keypad_key();
							lcd_data(KeyVal);									
							dely(100);
							count++;	
										
							if (lcd_cursor > 4 || KeyVal == '#')	
							{
								lcd_cmd(0x01);
								lcd_cursor = 0;
								break;
							}
						}
					}
				}
							
				else
				{	
					lcd_cmd(0x01);
					string("HATALI SIFRE");
					dely(200);
					lcd_cmd(0x01);
					lcd_cursor = 0;
					count = 0;
					break;
				}		
			}
						
			else
			{		
				lcd_cmd(0x01);
				lcd_cursor = 0;
				count = 0;
				break;
			}						
		}
				
		alarm_led = 1;
		dely(100);
				
		KeyVal = get_keypad_key();
		lcd_data(KeyVal);
		dely(100);				
				
		if (lcd_cursor > 4 || KeyVal == '#')	
		{
			lcd_cmd(0x01);
			lcd_cursor = 0;
			count = 0;
			break;
		}
    }
	}	
}

char get_keypad_key(void)
{
	char key_val =0;
	       keypad = 0xFE;		
          if(keypad == 0xee) // button 1
					{
           key_val = '1';
					lcd_cursor++;
					}	
          if(keypad == 0xde) // button 2
					{
           key_val = '2';
						lcd_cursor++;
					}	
					 if(keypad == 0xbe) // button 3
					{
           key_val = '3';
						lcd_cursor++;
					}						
				keypad = 0xFD;
					if(keypad == 0xED) // button 4
					{
					key_val = '4';
						lcd_cursor++;
					}	
					if(keypad == 0xDD) // button 5
					{
					key_val = '5';
						lcd_cursor++;
					}	
					 if(keypad == 0xBD) // button 6
					{
					key_val = '6';
						lcd_cursor++;
					}						
				keypad = 0xFB;
					if(keypad == 0xEB) // button 7
					{
					key_val = '7';
						lcd_cursor++;
					}	
					if(keypad == 0xDB) // button 8
					{
					key_val = '8';
						lcd_cursor++;
					}	
					 if(keypad == 0xBB) // button 9
					{
					key_val = '9';
						lcd_cursor++;
					}					
				keypad = 0xF7;
					if(keypad == 0xE7) // button *
					{
					key_val = '*';
						lcd_cursor++;
					}	
					if(keypad == 0xD7) // button 0
					{
					key_val = '0';
						lcd_cursor++;
					}	
					 if(keypad == 0xB7) // button #
					{
					key_val = '#';
						lcd_cursor++;
					}	
	return key_val;
}

void lcd_str(unsigned char *str)
{
	unsigned int loop =0;
	for(loop =0; str[loop]!= '\0'; loop++)
	{
		lcd_data(str[loop]);
	}
}

void lcd_data(unsigned char ch)
{
	LCD = ch;
	rs = 1;
	en = 1;
	dely(10);
	en = 0;
}

void lcd_cmd(unsigned char ch)
{
	LCD = ch;
	rs = 0;
	en = 1;
	dely(10);
	en = 0;
}

void string(char *p)
{
	while(*p)
	{
		lcd_data(*p++);
	}
}

void dely(unsigned int dly)
{
	unsigned int loop =0;
	unsigned int delay_gen =0;
	for(loop =0; loop < dly; loop++)
	for(delay_gen =0; delay_gen < 1000; delay_gen++);
}