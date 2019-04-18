#ifndef INT_HANDLER_H_
#define INT_HANDLER_H_

void IntPortLHandler(void);
void commandRecieved(void);
void GPSPosition(void);

extern volatile unsigned int gucNewData;
extern volatile unsigned char gucRxChar;
extern volatile unsigned char left;
extern volatile unsigned char right;
extern volatile unsigned char go;
extern volatile unsigned char stop;

#endif
