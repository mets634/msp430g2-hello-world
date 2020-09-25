#include<msp430.h>


#define SET_BIT(__register, __bit) (__register |= __bit)
#define UNSET_BIT(__register, __bit) (__register &= ~__bit)
#define TOGGLE_BIT(__register, __bit) (__register ^= __bit)

#define EXTERNAL_LED (BIT3)
#define INTERNAL_LED (BIT6)
#define BUTTON (BIT3)

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	TOGGLE_BIT(P1OUT, INTERNAL_LED);
	TOGGLE_BIT(P2OUT, EXTERNAL_LED);
	UNSET_BIT(P1IFG, BUTTON);
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog.

	// Setup output external LED.
	SET_BIT(P2DIR, EXTERNAL_LED);
	UNSET_BIT(P2OUT, EXTERNAL_LED);

	// Setup output internal LED.
	SET_BIT(P1DIR, INTERNAL_LED);
	UNSET_BIT(P1OUT, INTERNAL_LED);

	// Setup input button.
	UNSET_BIT(P1DIR, BUTTON);
	SET_BIT(P1IE, BUTTON);
	UNSET_BIT(P1IFG, BUTTON);
	SET_BIT(P1REN, BUTTON);
	SET_BIT(P1OUT, BUTTON);

	// Stop CPU and enable interrupts.
	__bis_SR_register(CPUOFF | GIE);

	return 0;
}
