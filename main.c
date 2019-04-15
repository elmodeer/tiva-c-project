/**
 * main.c
 */
#include <stdio.h>
#include "tm4c1294ncpdt.h"
#include "functions.h"
#include "int_handler.h"
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

    systemConfig();
    while (1) {
        if (stop) {
            go = false;
            stop = false;
        }
        while (go && !stop) {
//        while (1) {
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

