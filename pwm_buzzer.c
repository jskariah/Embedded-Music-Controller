/*
 * File: pwm_buzzer.c
 *
 * Music player buzzer-specific PWM functions
 * Author credits: Trevor Jedrzejas and Justin Skariah at UIC for ECE 266 SP26 (C/M: SP26/SP26)
 */

#include <pwm_buzzer.h>

void PwmBuzzerInit()
{
    // Enable Wide Timer 0 (for PWM) and GPIO Port C (for GPIO) peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Configure the Timer Peripheral to use the GPIO Port & Pin pair
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PC5_WT0CCP1);
    // Configure the Timer Peripheral to use one of the two half-width pwm timers (B)
    TimerConfigure(WTIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM));
    // Configure the Control Level for the Match and Load value readings
    TimerControlLevel(WTIMER0_BASE, TIMER_B, true /*---*/);
    // Enable the Timer for the Buzzer (WT0B)
    TimerEnable(WTIMER0_BASE, TIMER_B);
}

void PwmBuzzerSet(int pulse_period, int pulse_width)
{
    TimerLoadSet(WTIMER0_BASE, TIMER_B, pulse_period - 1);
    TimerMatchSet(WTIMER0_BASE, TIMER_B, pulse_width - 1);
}
