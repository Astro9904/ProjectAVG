#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#define TRIGGER_LINKS_DIR DDRB
#define TRIGGER_LINKS_BIT PB2
#define TRIGGER_LINKS_ON PORTB |= (_BV(PB2))
#define TRIGGER_LINKS_OFF PORTB &= ~(_BV(PB2))

#define TRIGGER_RECHTS_DIR DDRB
#define TRIGGER_RECHTS_BIT PB3
#define TRIGGER_RECHTS_ON PORTB |= (_BV(PB3))
#define TRIGGER_RECHTS_OFF PORTB &= ~(_BV(PB3))

volatile uint16_t g_PrevCountLinks = 0;				// Previous value of Timer4
volatile uint16_t g_PulseWidthLinks = 0;				// Width of echo pulse from sensor, in uS (microseconds)
volatile uint8_t g_measurement_flagLinks = 1;		// Flag used in interruption, should be 1 at the beginning
volatile uint16_t g_PrevCountRechts = 0;				// Previous value of Timer4
volatile uint16_t g_PulseWidthRechts = 0;				// Width of echo pulse from sensor, in uS (microseconds)
volatile uint8_t g_measurement_flagRechts = 1;		// Flag used in interruption, should be 1 at the beginning

void TIMERS_init() {
    TCCR4B = (1 << CS41) | (1 << ICES4);		// Prescaler 8 and trigger on rising edge at the beginning
    TIMSK4 = (1 << ICIE4);						// Input Capture Mode on (interrupt from input)
    TCCR5B = (1 << CS51) | (1 << ICES5);		// Prescaler 8 and trigger on rising edge at the beginning
    TIMSK5 = (1 << ICIE5);	
}

void HC_SR04_init() {
    TIMERS_init();
    TRIGGER_RECHTS_DIR |= (1 << TRIGGER_RECHTS_BIT);			// Setting trigger pin as output
    TRIGGER_LINKS_DIR |= (1 << TRIGGER_LINKS_BIT);
}

void measurementLinks_start() {
    TRIGGER_LINKS_ON;
    _delay_us(10);								// High state by 10 us = triggering of measurement
    TRIGGER_LINKS_OFF;
}
void measurementRechts_start() {
    TRIGGER_RECHTS_ON;
    _delay_us(10);								// High state by 10 us = triggering of measurement
    TRIGGER_RECHTS_OFF;
}

uint16_t measurementLinks_value() {
    if (g_PulseWidthLinks > 30000) {					// When PulseWidth is higher than sensor's range
        return 10000;			
    } else if (g_measurement_flagLinks < 1) {		// Checking if 2 edges passed
        return 10000;		
    }
    return g_PulseWidthLinks / 116;					// Distance in cm
}
uint16_t measurementRechts_value() {
    if (g_PulseWidthRechts > 30000) {					// When PulseWidth is higher than sensor's range
        return 10000;			
    } else if (g_measurement_flagRechts < 1) {		// Checking if 2 edges passed
        return 10000;		
    }
    return g_PulseWidthRechts / 116;					// Distance in cm
}

ISR(TIMER4_CAPT_vect) {
    uint16_t actual = ICR4;					// Get the input capture value
    TCCR4B ^= (1 << ICES4);					// Toggle edge detection (rising/falling)

    g_PulseWidthLinks = actual - g_PrevCountLinks;
    g_PrevCountLinks = actual;

    if (g_measurement_flagLinks > 1) {				// Automatic sending measured distance through UART
        Serial.println("Afstand links");
        Serial.println(measurementLinks_value());
        g_measurement_flagLinks -= 2;				// Reset flag status
    }

    g_measurement_flagLinks++;
}
ISR(TIMER5_CAPT_vect) {
    uint16_t actual = ICR5;					// Get the input capture value
    TCCR5B ^= (1 << ICES5);					// Toggle edge detection (rising/falling)

    g_PulseWidthRechts = actual - g_PrevCountRechts;
    g_PrevCountRechts = actual;

    if (g_measurement_flagRechts > 1) {				// Automatic sending measured distance through UART
        Serial.println("Afstand rechts");
        Serial.println(measurementRechts_value());
        g_measurement_flagRechts -= 2;				// Reset flag status
    }

    g_measurement_flagRechts++;
}

int main() {
    HC_SR04_init();
    Serial.begin(9600);
    sei();										// Enable global interrupts

    while (1) {
        measurementRechts_start();
        _delay_ms(100);
       // measurementLinks_start();
       // _delay_ms(100);
    }
    return 0;
}
