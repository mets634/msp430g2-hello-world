#include <stdint.h>

#include<msp430.h>


#define SET_BIT(__register, __bit) (__register |= __bit)
#define UNSET_BIT(__register, __bit) (__register &= ~__bit)
#define TOGGLE_BIT(__register, __bit) (__register ^= __bit)

#define LED (BIT0 | BIT6)

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_a0_isr(void) {
	TOGGLE_BIT(P1OUT, LED);
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog.

	// Setup output LED.
	SET_BIT(P1DIR, LED);
	UNSET_BIT(P1OUT, LED);

	// Setup Timer
	TACCR0 = 0;
	SET_BIT(TACCTL0, CCIE);
	TACTL = TASSEL_2 + ID_3 + MC_1;
	TACCR0 = 60000;  // This is arbitrary

	// Stop CPU and enable interrupts.
	__bis_SR_register(CPUOFF | GIE);
	
	return 0;
}
