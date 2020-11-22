/*
 * IncFile1.h
 *
 * Created: 9/22/2016 6:06:29 PM
 *  Author: Ali Harman
 */ 


#ifndef ADC_H_
#define ADC_H_
void setChannel(int8_t);
void adjADC(int);
void initADC();
void setInt();
void setADC();
int16_t getADC();
int16_t readADC();
#define LEFT 1
#define RIGHT 2



void setChannel(int8_t i)
{
	//if(i>8)
	ADMUX|=(0x0F)&i;
}
void adjADC(int adj)
{
	if(adj==1)
	ADMUX|=(1<<ADLAR);
}
void initADC()
{
	setChannel(0);
	ADMUX|=(1<<REFS0); // select AVcc as reference
	//ADCSRA=0b10000111;
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);		//ADC enable/ set clk f_cpu/128
	//ADCSRA|=(1<<ADIE); //set to use special function register
	//SFIOR|=(1<<ADTS0)|(1<<ADTS1); // special function register, start convention at every TIMER0 COMP match
}
void setInt()
{
	ADCSRA|=(1<<ADIE); // complete interrupt
}

int16_t getADC()
{
	if(!(ADMUX&(1<<ADLAR)))
	return ADC;
	else
	return ADCH;
}

int8_t getADCH()
{
	return ADCH;
}

int8_t getADCL()
{
	return ADCL;
}
int16_t readADC()
{
	ADCSRA|=(1<<ADSC);
	//PORTC|=2;
	if(!(ADCSRA&(1<<ADIE)))
	{
		while(ADCSRA&(1<<ADSC))
		;
		//PORTC&=~2;
		return ADC;
	}
	else
		return 0;
}
void setADC()
{
	ADCSRA|=(1<<ADSC);
}

#endif /* ADC_H_ */