/*  
 *  Compile time configuration file compile_config.h
 *  must be included first. Sets the variables RUN_MODE, SW_P, LED_P and F_CPU
 */
#ifndef COMPILE_CONFIG_H_
#define COMPILE_CONFIG_H_
 
/*
 *  F_CPU is the microprocessor speed
 *  RUN_MODE = 0 => switch mode / action occurs one time
 *  RUN_MODE = 1 => switch mode / action occurs continuously until overriden
 *  RUN_MODE = 2 => push button mode
 *  SW_P = 'A' | 'B' | 'C' | 'D' the input port where the switches are connected
 *  LED_P = 'A' | 'B' | 'C' | 'D' the output port where the leds are connected
 */
#ifndef F_CPU
#define F_CPU   8000000
#endif

#define SW_P        'C'
#define LED_P       'A'
 
 
#endif /* COMPILETIM_CONFIG_H_ */