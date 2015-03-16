#include "compile_config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "avr_utils.h"
 
void rotr_leds1(volatile uint8_t* P) { rotr_bits(P, 1); }
void rotr_leds2(volatile uint8_t* P) { rotr_bits(P, 2); }
void rotl_leds1(volatile uint8_t* P) { rotl_bits(P, 1); }
void rotl_leds2(volatile uint8_t* P) { rotl_bits(P, 2); }
void reset_leds(volatile uint8_t *P) { *P = 0x01; }
 
int main(void)
{
    clear_reg(SW_DDR);
    set_reg(LED_DDR);
    set_bit(LED_PORT, 0);
     
    switch_class sw[] = { {0, rotl_leds1}, {0, rotr_leds1}, {0, rotl_leds2}, {0, rotr_leds2}, {0, reset_leds} };
    sint8_t op = -1; 
     
    while(1)
    {
        op = leftmost_set_bit(SW_PIN & 0x1F);
        #if RUN_MODE == 0
            if((op > -1) && (op < 5)) {
                if(!sw[op].last_state) 
                    sw[op].on_switch_set(&LED_PORT);
                uint8_t i;
                for(i = 0; i <= op; i++) 
                    sw[i].last_state = (SW_PIN >> i) & 0x01;
            }
        #elif RUN_MODE == 1
            sw[op].on_switch_set(&LED_PORT);
            _delay_ms(500);
        #else
            while(SW_PIN & 0x1F);
            sw[op].on_switch_set(&LED_PORT);
        #endif
    }
    return 0;
}
