#include "tm4c1294ncpdt.h"
#include "functions.h"

// work on PK0 as U4Rx
void UARTConfig(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 9);              // port k
	while (!(SYSCTL_PRGPIO_R & (1 << 9)))
		;
	GPIO_PORTK_DEN_R |= 0x01;                   // enable pin PK0
	GPIO_PORTK_AFSEL_R |= 0x01;                 // enable alternate function
	GPIO_PORTK_PCTL_R |= 0x01;                  // enable U4Rx

	SYSCTL_RCGCUART_R |= (1 << 4);              // UART 4
	while (!(SYSCTL_PRUART_R & (1 << 4)))
		;
	UART4_CTL_R &= ~0x01;                       // disable the UART4
    //	UART4_IBRD_R = 17;                      // baud rate of 57600 bit/s
    //	UART4_FBRD_R = 23;
	//  BRD = 104.16666667
	UART4_IBRD_R = 104;                         // baud rate of 9600 bit/s
	UART4_FBRD_R = 10;
	UART4_LCRH_R = 0x60;                        // 8N1    bits frame and no parity bit
	UART4_CTL_R |= 0x201;                       // enable the UART4 as Rx
	UART4_ICR_R = 0xE7FF;                       // clear all interrupts
	UART4_IM_R |= 1 << 4; 	                    // activate UART4 Rx interrupts
	NVIC_EN1_R |= 1<< (57-32); // enable UART2 interrupt in the nested vector interrupt controller
}

// TODO! not yet completed
//PP0 -> RX , PP1 -> TX
void UARTConfigGPS(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 13);              // port P
    while (!(SYSCTL_PRGPIO_R & (1 << 13)))
        ;
    GPIO_PORTP_DEN_R |= 0x03;                    // enable pin PP0, PP1
    GPIO_PORTP_AFSEL_R |= 0x03;                  // enable alternate function
    GPIO_PORTP_PCTL_R |= 0x01;                   // enable U6Rx

    SYSCTL_RCGCUART_R |= (1 << 6);               // UART 4
    while (!(SYSCTL_PRUART_R & (1 << 6)))
        ;
    UART6_CTL_R &= ~0x01;                        // disable the UART6
    //  UART4_IBRD_R = 17;                       // baud rate of 57600 bit/s
    //  UART4_FBRD_R = 23;
    //  BRD = 104.16666667
    UART6_IBRD_R = 104;                          // baud rate of 9600 bit/s
    UART6_FBRD_R = 10;
    UART6_LCRH_R = 0x60;                         // 8N1    bits frame and no parity bit
    UART6_CTL_R |= 0x221;                        // enable the UART4 as Rx
    UART6_ICR_R = 0xE7FF;                        // clear all interrupts
    UART6_IM_R |= 1 << 4;                        // activate UART4 Rx interrupts
    NVIC_EN1_R |= 1<< (57-32);                   // enable UART2 interrupt in the nested vector interrupt controller
}
// switch the the 25MHZ clock for more precision
void clock_change(void){

	// switch over to main quartz oscillator at 25MHz
        // clear MOSC power down, high oscillator range setting, and no crystal present setting
        SYSCTL_MOSCCTL_R &= ~(SYSCTL_MOSCCTL_OSCRNG | SYSCTL_MOSCCTL_PWRDN |SYSCTL_MOSCCTL_NOXTAL);
        SYSCTL_MOSCCTL_R |= SYSCTL_MOSCCTL_OSCRNG;                             // increase the drive strength for MOSC
        SYSCTL_RSCLKCFG_R = SYSCTL_RSCLKCFG_OSCSRC_MOSC;                    // set the main oscillator as main clock source
}
