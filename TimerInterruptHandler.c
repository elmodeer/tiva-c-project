#include "int_handler.h"
#include "tm4c1294ncpdt.h"

#define AR_SIZE  30
#define DELAY 4000          //
#define SMALL_DELAY 2000

void timerWait(unsigned short);
void IntPortLHandler(void) {
//	// unsigned char c = GPIO_PORT_DATA_R;
//	GPIO_PORTL_ICR_R |= 0x0001; // clear interrupt source
//	int i = 0;
//	int k = 0;
//	timerWait(DELAY);
//	while (isGameOver) {
//		for (i = k; k < AR_SIZE; k++) {
//			GPIO_PORTM_DATA_R = gameOver[k];
//			timerWait(SMALL_DELAY);
//			isGameOver = 0;
//		}
//	}
//	for (i = j; i < AR_SIZE; i++, k++) {
//		GPIO_PORTM_DATA_R = obstacles[i];
//		if (up) {
//			GPIO_PORTD_AHB_DATA_R = ballJumb[k];
//		} else {
//			GPIO_PORTD_AHB_DATA_R = ball[k];
//		}
//		if (GPIO_PORTM_DATA_R & GPIO_PORTD_AHB_DATA_R ) {
//			isGameOver = 1;
//		}
//		timerWait(SMALL_DELAY);
//		if (j == 9)
//			j = 0;
//	}
//	j++;
}

