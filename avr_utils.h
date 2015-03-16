/*
 * Custom mini library with basic abstraction 
 * for led - switch based IO
 */
 
/* include guard */
#ifndef AVR_UTILS_H_
#define AVR_UTILS_H_
 
/* define NULL outside of stdlib if not defined */
#ifndef NULL
    #define NULL (void *)0
#endif
 
/* define uint8_t if not defined */
#ifndef UINT8_MAX
    typedef unsigned char uint8_t;
#endif
 
/* define signed byte type */
typedef signed char sint8_t;
 
/* define function pointer type for switch operations */
typedef void (*switchop_t)(volatile uint8_t* P);
 
/* primitive class to store a switch's last state and the appropriate handler */
typedef struct {
    uint8_t last_state : 1;
    switchop_t on_switch_set;
}switch_class;
 
/* 
 * define SW_P and LED_P in an invalid value 
 * the values need to be provided externally
 */
#ifndef SW_P
    #define SW_P ''
#endif
 
#ifndef LED_P
    #define LED_P ''
#endif
 
/*
 * Conditionally compile the LED_PORT, LED_DDR and LED_PIN variables
 */
#if LED_P == 'A'
    #define LED_PORT        PORTA
    #define LED_DDR         DDRA
    #define LED_PIN         PINA
#elif LED_P == 'B'
    #define LED_PORT        PORTB
    #define LED_DDR         DDRB
    #define LED_PIN         PINB
#elif LED_P == 'C'
    #define LED_PORT        PORTC
    #define LED_DDR         DDRC
    #define LED_PIN         PINC
#elif LED_P == 'D'
    #define LED_PORT        PORTD
    #define LED_DDR         DDRD
    #define LED_PIN         PIND
#else 
    #error Please define LED_P as 'A', 'B', 'C' or 'D' before including 
#endif
 
/*
 * Conditionally compile the SW_PORT, SW_DDR and SW_PIN variables
 */
#if SW_P == 'A'
    #define SW_PORT         PORTA
    #define SW_DDR          DDRA
    #define SW_PIN          PINA
#elif SW_P == 'B'
    #define SW_PORT         PORTB
    #define SW_DDR          DDRB
    #define SW_PIN          PINB
#elif SW_P == 'C'
    #define SW_PORT         PORTC
    #define SW_DDR          DDRC
    #define SW_PIN          PINC
#elif SW_P == 'D'
    #define SW_PORT         PORTD
    #define SW_DDR          DDRD
    #define SW_PIN          PIND
#else   
    #error Please define SW_P as 'A', 'B', 'C' or 'D' before including
#endif
 
/*
 * macros to abstract useful bit level operations
 */
#define clear_reg(x)        ((x) = 0x00)
#define set_reg(x)          ((x) = 0xFF) 
#define BV(B)               (1 << (B))
#define set_bit(R,B)        ((R) |= BV(B))
#define clr_bit(R,B)        ((R) &= ~BV(B))
#define toggle_bit(R,B)     ((R) ^= BV(B))
#define high_bits(R)        (((R) & 0xF0) >> 4)
#define low_bits(R)         ((R) & 0x0F)
 
/* 
 * Useful functions for led-switch IO manipulation
 */
inline void
rotr_bits(volatile uint8_t *P, int N) {
    *P = ((*P >> N) | (*P << (8 - N))) & 0xFF;
}
 
inline void
rotl_bits(volatile uint8_t *P, int N) {
    *P = ((*P << N) | (*P >> (8 - N))) & 0xFF;
}
 
void
mov_bits(volatile uint8_t* P, char* dir) {
    if(*dir == 'l') {
        *dir = (*P == 0x80) ? 'r' : 'l';
        *P = (*P == 0x80) ? (*P >> 1) : (*P << 1);
    } 
    else if(*dir == 'r') {
        *dir = (*P == 0x01) ? 'l' : 'r';
        *P = (*P == 0x01) ? (*P << 1) : (*P >> 1);      
    }
}
 
int
leftmost_set_bit(volatile uint8_t P) {
    int pos = -1;
    while(P) {
        P >>= 1;
        pos++;
    }
    return pos;
}
 
int
leftmost_zro_bit(volatile uint8_t P) {
    return leftmost_set_bit(~P);
}
 
int
rightmost_set_bit(volatile uint8_t P) {
    int pos = -1;
    while(P) {
        P <<= 1;
        pos++;
    }
    return pos;
}
 
int
rightmost_zro_bit(volatile uint8_t P) {
    return rightmost_set_bit(~P);
}
 
#endif /* AVR_UTILS_H_ */   