/*
 * File: pwm_buzzer.h
 *
 * Music player buzzer-specific PWM header interface
 * Author credits: Trevor Jedrzejas and Justin Skariah at UIC for ECE 266 SP26 (C/M: SP26/SP26)
 */

#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>

#ifndef PWM_BUZZER_H_
#define PWM_BUZZER_H_


// Initialize the Buzzer's PWM Timer
void PwmBuzzerInit();
// Set the PWM Timer Parameters for the Buzzer
void PwmBuzzerSet(int pulse_period, int pulse_width);

#endif /*PWM_BUZZER_H_*/
