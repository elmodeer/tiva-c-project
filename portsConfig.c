#include "tm4c1294ncpdt.h"
#include <stdio.h>

void configPortL(void)
{
    SYSCTL_RCGCGPIO_R |= (1 << 10);  //activate port L clock
    while ((SYSCTL_PRGPIO_R & 1 << 10) == 0)
        ;    //wait for port L

    GPIO_PORTL_DEN_R |= 0x0001;   //enable pin 0 of port L
    GPIO_PORTL_DIR_R &= ~0x0001;   //set the direction of pin 0 to input
    GPIO_PORTL_IS_R &= ~0x01; // sense to edge-sensitive
    GPIO_PORTL_IBE_R &= ~0x01; // trigger set to both edges
    GPIO_PORTL_IEV_R |= 0x01;
    GPIO_PORTL_ICR_R |= 0x01; // clear interrupt PORTL(0)
    GPIO_PORTL_IM_R |= 0x01; // unmask PORTL(0)

    NVIC_EN1_R |= 1<<(53-32);  // enable PORTL interrupt in NVIC
}

// usage of pins PM0 for servo control and PM1 for motor control
void configPortM(void)
{
    SYSCTL_RCGCGPIO_R |= 0x808;                      // Port M clock ini
    while ((SYSCTL_PRGPIO_R & 0x00000800) == 0)
        ;     // Port M ready ?
    // Digital enable
    GPIO_PORTM_DEN_R = 0x03; //M(1:0) port enable
    // Set direction
    GPIO_PORTM_DIR_R = 0x03;  //(1:0) symbols output of the chip


}

void configPortD(void)
{
    //SYSCTL_RCGCGPIO_R |= 0x008;                      // Port M clock ini
    while ((SYSCTL_PRGPIO_R & 0x00000008 ) == 0)
        ;     // Port M ready ?
    // Digital enable
    GPIO_PORTD_AHB_DEN_R = 0xFF; //M(7:0) port enable
    // Set direction
    GPIO_PORTD_AHB_DIR_R = 0xFF  ;  //(7:0) symbols output of the chip
}

