// Special Function Register Offset = 0x20

// Port B Data Direction Register
#define DDRB	*((unsigned char*)0x37) // 0x17

// Port B data register 
#define PORTB	*((unsigned char*)0x38) // 0x18

// Timer/Counter0 Control Register B
#define TCCR0B	*((unsigned char*)0x53) // 0x33

// Timer/Counter Interrupt Mask Register
#define TIMSK	*((unsigned char*)0x59) // 0x39

// AVR Status Register 
#define SREG	*((unsigned char*)0x5F) // 0x3F

// Iteration Counter
char iterCounter = 0; 

// Handler function for the TIMER0_OVF (Timer/Counter0 Overflow) interrupt
// ISR Vector 0x0005 
void __vector_5() __attribute__ ((signal)); 

// Function to be called during every TIMER0_OVF interrupt
void __vector_5()
{	
	// 1 iteration = 15.81 ms
	if (iterCounter == 16){ 
		// Change state of bit 1 of Port B data register
		// It toggles PB1
		PORTB ^= (1 << 1);
		iterCounter = 0; 
	}
	else iterCounter++;
}

int main()
{
	// Set Port B Data Direction Register to bit 1
	// It sets PB1 to Output
	DDRB |= (1 << 1);

	// Set Timer/Counter0 Control Register B to bit 2 and 0
	// 0b00000100
	// 0b00000001
	// bitwise OR
  // = 0b00000101
	// It sets prescale timer to 1/1024th the clock rate
	TCCR0B = (1 << 2) | (1 << 0);

	// Set Timer/Counter Interrupt Mask Register to bit 1
	// It enables timer overflow interrupt
	TIMSK |= (1 << 1);

	// Set AVR Status Register to bit 7
	// SEI instruction (set Global Interrupt Enable)
	SREG |= (1 << 7);

	while (1)
	{

	}
}
