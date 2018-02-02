#include <reg51.h>
sbit fan= P3^3;
sbit lpgsensor= P2^1;
sbit buzzer= P3^2;
void GSM_init();
void GSM_write(unsigned char ch);
void Serialprintln(char *p);

void main(void)
{unsigned int i;
lpgsensor=1;
	while(1)
	{
	
if(lpgsensor==0)
{ 
	GSM_init();
fan=0;
	buzzer=0;
	Serialprintln("ATD+917830328765;\0");
	for(i=0;i<10000;i++);
}

}
	}

	void GSM_init()            // serial port initialization 
{
    TMOD=0x20;            // Timer 1 selected, Mode 2(8-bit auto-reload mode)
    TH1=0xFD;            // 9600 baudrate
    SCON=0x50;            // Mode 1(8-bit UART), receiving enabled
    TR1=1;                // Start timer
}

void GSM_write(unsigned char ch)    // Function to send commands to GSM
{
    SBUF=ch;        // Put byte in SBUF to send to GSM
    while(TI==0);        //wait until the byte trasmission
    TI=0;            //clear TI to send next byte.      
}

void Serialprintln(char *p)
{
  while(*p)
  {
    GSM_write(*p);
    p++;
  }
  GSM_write(0x0d);
}  

