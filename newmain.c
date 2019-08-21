#include <xc.h> 
 
#include "newxc8_header.h" 
#include "USART.h" 
 
 
 
void USART_Init(long baud_rate)
{  float temp;  
ANSELC=1;
TRISC6=0;                    /*Make Tx pin as output*/ 
TRISC7=1;                       /*Make Rx pin as input*/
temp=Baud_value;
SPBRG=(int)temp;         /* SPBRG=(F_CPU /(64*9600))-1*/   
TXSTA=0x20;                     /*Transmit Enable(TX) enable*/
RCSTA=0x90;                     /*Receive Enable(RX) enable         and serial port enable */ 
 
} 
 
void USART_TransmitChar(char out) {                
    while(TXIF==0);          /*wait for transmit interrupt flag*/
    TXREG=out;
} 
 
char USART_ReceiveChar() { 
 
while(RCIF==0);/*wait for receive interrupt flag*/
return(RCREG);                  /*receive data is stored in    RCREG register and return to main program */
} 
 
void USART_SendString(const char *out) 
{    while(*out!='\0')    
{                     
    USART_TransmitChar(*out);
    out++;
}
} 
 
void MSdelay(unsigned int val) {
    unsigned int i,j;
    for(i=0;i<=val;i++)  
        for(j=0;j<81;j++);     
} 
 
void main() 
{
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD4 = 0;
    OSCCON=0x62;              /* use internal oscillator frequency                                          which is set to * MHz */
int data_in; 
ANSELD=0;
TRISD = 0;
/* set PORT as output port */ 
USART_Init(9600);  
MSdelay(50);
while(1)   
{
    data_in=USART_ReceiveChar();
    if(data_in=='1') 
    {
        PORTDbits.RD0 = 0;                      /* turn ON LED */ 
        USART_SendString("LED_OFF");         }        
    if(data_in=='2')                          
    {             
        PORTDbits.RD0= 1; 
       
        USART_SendString("LED_ON"); 
    } 
 if(data_in=='3') 
    {
        PORTDbits.RD1 = 0;                      /* turn ON LED */ 
        USART_SendString("LED_2_OFF");         }        
   if(data_in=='4')                          
    {             
        PORTDbits.RD1= 1; 
        
        USART_SendString("LED_2_ON"); 
    }      
    
 if(data_in=='5') 
    {
        PORTDbits.RD4= 0;                      /* turn ON LED */ 
        USART_SendString("FAN_OFF");         }        
    if(data_in=='6')                          
    {             
        PORTDbits.RD4= 1; 
      
        USART_SendString("FAN_ON"); 
    }      
        
    
    MSdelay(100);
}
} 