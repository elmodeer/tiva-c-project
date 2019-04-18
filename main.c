/**
 * main.c
 */
#include <stdio.h>
#include "tm4c1294ncpdt.h"
#include "functions.h"
#include "int_handler.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include <stdbool.h>

#define PWM_PERIOD  16666
#define PWM_MIN  1100
#define PWM_MAX  1900
// speed
int pwmServo = 1600;
volatile unsigned int gucNewData = 0;
volatile unsigned char gucRxChar = 0;
volatile unsigned char left = false;
volatile unsigned char right = false;
volatile unsigned char go = false;
volatile unsigned char stop = false;

int pwmServoDelta = 10; // up faster
int pwmMotorDelta = 90; // up faster
int i;


void systemConfig();
void SysCtlDelay();
void steerLeft();
void steerRight();

void delay(int s) {
    SysCtlDelay(s * 40000); /*in milliseconds*/
}

int main(void) {

    // Run from the PLL at 120 MHz.

//    //Setting up serial port
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
//    {//Often goes into fault interrupt if this isn't here
//    }
//
//    MAP_UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600 ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_EVEN));
//    MAP_UARTFIFOEnable(UART0_BASE);
    systemConfig();
    while (1) {
        if (stop) {
            go = false;
            stop = false;
        }
        while (go && !stop) {
            if (left)
                steerLeft();
            if (right)
                steerRight();

            pwmServo += pwmMotorDelta;
            if ((pwmServo >= PWM_MAX) || (pwmServo <= PWM_MAX)) {
                pwmMotorDelta = -pwmMotorDelta;
            }
            GPIO_PORTM_DATA_R |= 0x02;
            timerWait(pwmServo);
            GPIO_PORTM_DATA_R &= ~0x02;
            timerWait(PWM_PERIOD - pwmServo);
        }

    }
 }
void steerLeft() {
     left = false;
     for(i = 0 ; i < 50 ; i ++) {
         GPIO_PORTM_DATA_R &= ~0x01 ;
         timerWait(pwmServoDelta);
         GPIO_PORTM_DATA_R |= 0x01;
         timerWait(PWM_PERIOD - pwmServoDelta);
     }
}

void steerRight() {
    right = false;
    for(i = 0 ; i < 50 ; i ++) {
        GPIO_PORTM_DATA_R |= 0x01;
        timerWait(pwmServoDelta);
        GPIO_PORTM_DATA_R &= ~0x01;
        timerWait(PWM_PERIOD - pwmServoDelta);
    }
}
////         go right servo
////         i can be used as position
//        GPIO_PORTM_DATA_R |= 0x01;
//        timerWait(PWM_PERIOD - pwmServo);
//        GPIO_PORTM_DATA_R &= ~0x01;
//        timerWait(pwmServo);

//        }
//         go left servo
//        for(i = 0 ; i < 50 ; i ++){
//            GPIO_PORTM_DATA_R &= ~0x01 ;
//            timerWait(pwmServo);
//            GPIO_PORTM_DATA_R |= 0x01;
//            timerWait(PWM_PERIOD - pwmServo);
//        }

