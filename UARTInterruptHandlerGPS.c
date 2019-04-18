#include "int_handler.h"
#include "tm4c1294ncpdt.h"
#include "functions.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>

//PP0 -> RX , PP1 -> TX
void GPSPosition(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART6_BASE, true);       //get interrupt status
    UARTIntClear(UART6_BASE, ui32Status);               //clear the asserted interrupts
    gucRxChar = UARTCharGet(UART6_BASE);
//    printf("Coordinate : %c",gucRxChar);
    // i want to print the content here to the serial console
//    UARTCharPutNonBlocking(UART0_BASE, gucRxChar);
//    while(UARTCharsAvail(UART0_BASE)){
      UARTCharPut(UART0_BASE, gucRxChar);
//    }
    //UARTCharPut(UART0_BASE, '\n');

}
