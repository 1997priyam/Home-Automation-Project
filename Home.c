#include<reg51.h>
#include <stdlib.h>

sbit LED1=P3^2;
sbit LED2=P3^3;
sbit d0=P2^0;
sbit d1=P2^1;
sbit d2=P2^2;
sbit d3=P2^3;
sbit dht11=P2^4;

int flag;

char str;


void dhth();
void dhtt();
void autom();
void delay(unsigned int i);

void main (void)
{
	
	
	while(1)
	{
		TMOD=0x20;
	TH1=0xFD;
	SCON=0x50;
	TR1=1;
		
		
		while(RI==0);
		
		RI=0;
		str=SBUF;
		TH1=0;
		TR1=0;
		
		
		if(str=='7')
		{
		autom();
		}
		
		else if(str=='5')
		{
		dhth();
		}
		
		else if(str=='6')
		{
		dhtt();
		}
		if(str=='1')
		{
			d0=0;
		d1=0;
		d2=0;
		d3=0;
			
		}
    else if(str=='2')
		{
			
			d0=1;
		d1=1;
		d2=1;
		d3=1;
		}
		else if(str=='3')
		{
			LED2=0;
			
		}
		
		else if(str=='4')
		{
			
			LED2=1;
		}
		
	}
}	



void dhth()
{
unsigned int bytes,bits;
	unsigned char rec_byte,data_array[5],disp_hum[3],bit_time;
	
	dht11=1;
	TMOD=0x21;
	TH1=0;
	
	//TR1=1;
	//led=~led;
	
		dht11=0;
		delay(5);
		dht11=1;
		while(dht11);		//initially high
		while(!dht11);		//start low
		while(dht11);		//start high
		for(bytes=0;bytes<5;bytes++){
			for(bits=0;bits<8;bits++){
				while(!dht11);
				TR1=1;
				while(dht11);
				TR1=0;
				bit_time=TL1;
				TL1=0;
				rec_byte=rec_byte<<1;
				if(bit_time>50)
					rec_byte=rec_byte|1;
			}
			data_array[bytes]=rec_byte;
			//led=~led;
		}
		//displaying only 1 byte
		
		disp_hum[0]=data_array[0]%10;
		disp_hum[1]=(data_array[0]/10)%10;
		disp_hum[2]=data_array[0]/100;
		TH1=0xFD;
	SCON=0x50;
	TR1=1;
		for(bytes=3;bytes>0;bytes--){
			
		SBUF=disp_hum[bytes-1]+0x30;
			
			while(TI==0);
		TI=0;
					
		}
	TR1=0;	
	
}


void dhtt()
{
unsigned int bytes,bits;
	unsigned char rec_byte,data_array[5],disp_hum[3],bit_time;
	
	dht11=1;
	TMOD=0x21;
	TH1=0;
	
	//TR1=1;
	//led=~led;
	
		dht11=0;
		delay(5);
		dht11=1;
		while(dht11);		//initially high
		while(!dht11);		//start low
		while(dht11);		//start high
		for(bytes=0;bytes<5;bytes++){
			for(bits=0;bits<8;bits++){
				while(!dht11);
				TR1=1;
				while(dht11);
				TR1=0;
				bit_time=TL1;
				TL1=0;
				rec_byte=rec_byte<<1;
				if(bit_time>50)
					rec_byte=rec_byte|1;
			}
			data_array[bytes]=rec_byte;
			//led=~led;
		}
		//displaying only 1 byte
		
		disp_hum[0]=data_array[2]%10;
		disp_hum[1]=(data_array[2]/10)%10;
		disp_hum[2]=data_array[2]/100;
		TH1=0xFD;
	SCON=0x50;
	TR1=1;
		for(bytes=3;bytes>0;bytes--){
			
		
	
			SBUF=disp_hum[bytes-1]+0x30;
			
			while(TI==0);
		TI=0;
		
			
		}
		TR1=0;
	
}


void autom()
{
	char temp[3];
		int temp1;
	unsigned int bytes,bits;
	unsigned char rec_byte,data_array[5],disp_hum[3],bit_time;
	while(str!='2')
	{
		
TMOD=0x21;
		TH1=0;
		dht11=0;
		delay(2);
		dht11=1;
		while(dht11);		//initially high
		while(!dht11);		//start low
		while(dht11);		//start high
		for(bytes=0;bytes<5;bytes++)
		{
			for(bits=0;bits<8;bits++)
			{
				while(!dht11);
				TR1=1;
				while(dht11);
				TR1=0;
				bit_time=TL1;
				TL1=0;
				rec_byte=rec_byte<<1;
				if(bit_time>50)
					rec_byte=rec_byte|1;
			}
			data_array[bytes]=rec_byte;
			//led=~led;
		}
		//displaying only 1 byte
		
		//delay(10);
		disp_hum[0]=data_array[2]%10;
		disp_hum[1]=(data_array[2]/10)%10;
		disp_hum[2]=data_array[2]/100;
		
		flag=0;
		for(bytes=3;bytes>0;bytes--)
		{
			temp[flag]=disp_hum[bytes-1]+0x30;
			flag++;
		}
		
		temp1=atoi(temp);
		
	
	if(temp1>=35)
	{
	d0=0;
		d1=0;
		d2=0;
		d3=0;
	}
		
	else if (temp1>=32 && temp1<35)
	{
		d0=1;
		d1=1;
		d2=0;
		d3=0;
	}
	
	else if (temp1>=28 && temp1<32)
	{		
	 d0=0;
		d1=1;
		d2=0;
		d3=1;
	}
	
	else
	{
	d0=1;
		d1=1;
		d2=1;
		d3=1;
		
	}
TMOD=0x20;
	TH1=0xFD;
	SCON=0x50;
	TR1=1;
	str='z';
	delay(70);	
	//while(RI==0);
	if(RI==1)
	{
		str=SBUF;
	}
	RI=0;
		TH1=0;
		TR1=0;
	
	if(str=='5')
	{
		
	dhth();
	
	}
	
	else if(str=='6')
	{
	
	dhtt();
		
	}
	
  else if(str=='3')
		{
		
			LED2=0;
				
		}
		
		else if(str=='4')
		{
			
			LED2=1;
			
		}
		else if (str=='2')
		{
		d0=1;
			d1=1;
			d2=1;
			d3=1;
		
		}
	}
		}
void delay(unsigned int i)
	{
		unsigned int k;
	  unsigned int j;
		for(j=0;j<i;j++)        //loop goes from 0 to input(75 )
		for(k=0;k<7500;k++);     //loop goes from 0 to 7500 
	}
