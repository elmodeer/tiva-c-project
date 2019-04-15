#include "int_handler.h"
#include "tm4c1294ncpdt.h"
#include "functions.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>

// PM0 servo, PM1 motor
void commandRecieved(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART4_BASE, true); //get interrupt status
    UARTIntClear(UART4_BASE, ui32Status); //clear the asserted interrupts
    gucRxChar = UARTCharGet(UART4_BASE);
    // g -> 126
    // l -> 224
    // r -> 24
    // s -> 30
    //TODO! there is no error any more but the characters are not corresponding to the right hex values
    gucNewData = gucRxChar == 126 ? go = true :
                     gucRxChar == 30 ? stop = true :
                         gucRxChar == 24 ? right = true :
                             gucRxChar == 224 ? left = true : 30;// g for -> going straight forward
//    {
//     gucNewData = 126;
//    }
//    if (gucRxChar == 30)  // s for -> stop
//    {
//        gucNewData = 30;
//    }
//    if (gucRxChar == 24)
//    {  // c
//        printf("straight");
//    }

    //	if (UART4_MIS_R & (1 << 4)) {
//		UART4_ICR_R = (1 << 4);
//
//		// put your code here
//		gucRxChar = UART4_DR_R;
//		gucNewData = 1;
//	}
////

}
