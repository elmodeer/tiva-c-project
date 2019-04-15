
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

//configurations
void timerConfig(void);
void timerWait(unsigned short usec);
void configPortLForI2C(void);
void configPortM(void);
void configPortD(void);
void systemConfig(void);
void UARTConfig(void);
void clock_change(void);
void commandRecieved(void);

#endif
