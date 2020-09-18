#include <stdint.h>

#include<msp430.h>


#define SET_BIT(__register, __bit) (__register |= __bit)
#define UNSET_BIT(__register, __bit) (__register &= ~__bit)
#define TOGGLE_BIT(__register, __bit) (__register ^= __bit)

#define LED (BIT6)
#define BUTTON (BIT3)

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	TOGGLE_BIT(P1OUT, LED);
	UNSET_BIT(P1IFG, BUTTON);
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog.

	// Setup output LED.
	SET_BIT(P1DIR, LED);
	SET_BIT(P1OUT, LED);

	// Setup input button.
	UNSET_BIT(P1DIR, BUTTON);
	SET_BIT(P1IE, BUTTON);
	UNSET_BIT(P1IFG, BUTTON);
	SET_BIT(P1REN, BUTTON);
	SET_BIT(P1OUT, BUTTON);
	SET_BIT(P1IES, BUTTON);

	// Stop CPU and enable interrupts.
	__bis_SR_register(CPUOFF | GIE);
	
	return 0;
}