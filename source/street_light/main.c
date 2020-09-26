#include<msp430.h>


// Bit-register utilities.
#define SET_BIT(__register, __bit) (__register |= __bit)
#define UNSET_BIT(__register, __bit) (__register &= ~__bit)
#define TOGGLE_BIT(__register, __bit) (__register ^= __bit)

// Pins I/O.
#define LED_RED (BIT5)
#define LED_YELLOW (BIT4)
#define LED_GREEN (BIT3)
#define LEDS (LED_RED | LED_YELLOW | LED_GREEN)
#define BUTTON (BIT3)


#define TRANSITION(__current_state, __next_state) \
        case (__current_state):                   \
            enter_state(__next_state);            \
            break


typedef enum {
    OFF,
    RED,
    YELLOW,
    GREEN,
} state_t;

state_t current_state = OFF;


void enter_state(state_t new_state) {
    current_state = new_state;

    switch (new_state) {
        case RED:
            SET_BIT(P2OUT, LED_RED);
            UNSET_BIT(P2OUT, LED_YELLOW);
            UNSET_BIT(P2OUT, LED_GREEN);
            break;
        case YELLOW:
            UNSET_BIT(P2OUT, LED_RED);
            SET_BIT(P2OUT, LED_YELLOW);
            UNSET_BIT(P2OUT, LED_GREEN);
            break;
        case GREEN:
            UNSET_BIT(P2OUT, LED_RED);
            UNSET_BIT(P2OUT, LED_YELLOW);
            SET_BIT(P2OUT, LED_GREEN);
            break;
        case OFF:
            UNSET_BIT(P2OUT, LED_RED);
            UNSET_BIT(P2OUT, LED_YELLOW);
            UNSET_BIT(P2OUT, LED_GREEN);
            break;
    }
}


void handle_button_click(void) {
    switch (current_state) {
        TRANSITION(OFF, RED);
        TRANSITION(RED, OFF);
        TRANSITION(YELLOW, OFF);
        TRANSITION(GREEN, OFF);
    }
}

void handle_timer_expired(void) {
    switch (current_state) {
        TRANSITION(RED, YELLOW);
        TRANSITION(YELLOW, GREEN);
        TRANSITION(GREEN, RED);
    }
}


#pragma vector=PORT1_VECTOR
__interrupt void toggle_on_or_off(void)
{
	handle_button_click();
	TOGGLE_BIT(P1OUT, BIT6);
	UNSET_BIT(P1IFG, BUTTON);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void transition_to_next_led(void) {
	handle_timer_expired();
	// TOGGLE_BIT(P1OUT, LED);
}


int main(void) {
	WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog.

	// Setup output LEDs.
	SET_BIT(P2DIR, LEDS);
	UNSET_BIT(P2OUT, LEDS);

	// DEBUG
	SET_BIT(P1DIR, BIT6);
	UNSET_BIT(P1OUT, BIT6);

	// Setup input button.
	UNSET_BIT(P1DIR, BUTTON);
	SET_BIT(P1IE, BUTTON);
	UNSET_BIT(P1IFG, BUTTON);
	SET_BIT(P1REN, BUTTON);
	SET_BIT(P1OUT, BUTTON);

	enter_state(OFF);

	// Stop CPU and enable interrupts.
	__bis_SR_register(CPUOFF | GIE);

	return 0;
}
