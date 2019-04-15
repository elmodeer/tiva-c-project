 #include "tm4c1294ncpdt.h"

void timerConfig()
{
    // configure Timer 0
    SYSCTL_RCGCTIMER_R |= (1 << 0); // timer 0
    while (!(SYSCTL_PRTIMER_R & (1 << 0)))
        ; // wait for timer 0 activation
    TIMER0_CTL_R &= ~0x0001; // disable Timer 0
    TIMER0_CFG_R = 0x04; // 2 x 16-bit mode

    // compare mode, down, periodic: TAMR=0x2 -no match  value
    TIMER0_TAMR_R |= 1 << 1; //last 8 bits: 0000 0010
                             //4th bit = counts down, 2nd bit = 0x02 - periodic

}
//void timerWait(unsigned short usec)
//{
//    timerConfig();
//
//    long pre = 5;  //ceil((fCPU / pow(2.0, 16)) * 0.01); //prescaler Tmax = 10ms
//
//    TIMER0_TAPR_R = pre - 1;
//    TIMER0_TAILR_R =  53120 - 1; //0.5? probably needs also rounding //ceil((fCPU / pre) * (double)usec * pow(10.0, -6)) - 1; //load value
//    TIMER0_TAILR_R = 5120- 1; //0.5? probably needs also rounding //ceil((fCPU / pre) * (double)usec * pow(10.0, -6)) - 1; //load value
//
//    TIMER0_CTL_R |= 0x0001; //start TImer0A
//
//    while (!(TIMER0_RIS_R & 0x0001))
//        ; //flag set when 0x0000 reached(time-out)
//    TIMER0_ICR_R |= 0x01; //clear TIMER0_RIS_R(0) bit
//    TIMER0_CTL_R &= ~0x0001; //disable the Timer0A
//
//}
//make a delay of usec(up to 16.6 ms)
void timerWait(unsigned short usec)
{
    timerConfig();

    long pre = 5;  //ceil((fCPU / pow(2.0, 16)) * 0.01); //prescaler Tmax = 16.6 ms

    TIMER0_TAPR_R = pre - 1;
    TIMER0_TAILR_R = 16 / pre * usec - 1; //0.5? probably needs also rounding //ceil((fCPU / pre) * (double)usec * pow(10.0, -6)) - 1; //load value
    TIMER0_CTL_R |= 0x0001; //start TImer0A

    while (!(TIMER0_RIS_R & 0x0001))
        ; //flag set when 0x0000 reached(time-out)
    TIMER0_ICR_R |= 0x01; //clear TIMER0_RIS_R(0) bit
    TIMER0_CTL_R &= ~0x0001; //disable the Timer0A

}
