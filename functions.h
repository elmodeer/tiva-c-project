
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

//configurations
void timerConfig(void);
void timerWait(unsigned short usec);
void configPortLForI2C(void);
void configPortM(void);
void ROM_GPIOPinConfigure(uint32_t UxRX);
void ROM_SysCtlPeripheralEnable(uint32_t sysctl);
void ROM_GPIOPinTypeUART(uint32_t base, uint32_t pins);
void UARTStdioConfig(uint32_t UARTx, uint32_t baudRate, uint32_t sysctl);
void configPortD(void);
void systemConfig(void);
void UARTConfig(void);
void UARTConfigGPS(void);
void ConfigureUARTSerial(void);
void clock_change(void);
void commandRecieved(void);
void GPSPosition(void);

#endif
