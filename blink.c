#define DDRB	*((unsigned char*)0x37)
#define PORTB	*((unsigned char*)0x38)
#define TCCR0B	*((unsigned char*)0x53)
#define TIMSK	*((unsigned char*)0x59)
#define SREG	*((unsigned char*)0x5F)

char iterCounter = 0;

void __vector_5() __attribute__ ((signal));

void __vector_5() 
{
	if (iterCounter == 16){ //1 iterration = 15.81 ms
		PORTB ^= (1 << 1);
		iterCounter = 0; 
	}
	else iterCounter++;
}

int main()
{
	DDRB |= (1 << 1);

	TCCR0B = (1 << 2) | (1 << 0);

	TIMSK |= (1 << 1);

	SREG |= (1 << 7);

	while (1)
	{

	}
}
