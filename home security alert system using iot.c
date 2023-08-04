/* EIGHT CHANNEL FAULT DETECTOR:
    FOR TESTING THE CIRCUIT:
        CONNECT 8 LEDs TO PORT A(ACTIVE HIGH)
        CONNECT 8 LEDs TO PORT D(ACTIVE LOW)
        CONNECT 8 SWITCHES TO PORT B(ACTIVE HIGH)
        CONNECT ALARM RESET SWITCH TO PORT C.7 PIN
        CONNECT ALPHANUMERIC LCD TO PORT C 
        LCD PIN CONNECTION( C.0>>RS  C.1>>RD  C.2>>EN  C.3>>D4  C.4>>D5  C.5>>D6  C.6>>D7 )      
*/
#include<mega16a.h>
#include<mega16_bits.h>
#include<alcd.h>
#include<delay.h>
char a=1;                         //a is used for alarm reset
char f[8]={0,0,0,0,0,0,0,0};      //f is used as fault status flag
char d[8]={0,0,0,0,0,0,0,0};      //d is used as fault detected flag
int i=0;                          //i is used as counter variable in lcd display update
int t=0;                          //t is used as multiplier for timer0
unsigned int time_ms=1000;         //pulse width of output (complement)
unsigned int time_delay=1000;     //TIME DELAY between two outputs(INPUT is not captured during this delay)
int s=0;

interrupt [TIM0_OVF] void timer(void)         //Interrupt for updating LCD data
{                                           
    TCNT0=0x00;
    if(t==80)                                 //Increase t value to increase time delay between LCD update
    {
        t=0;
label1: if(i>7)
            i=0;
        if(f[i]==1)
        {
            PORTA=0x00;
            PORTB=0xff;
            #asm("cli");
            delay_ms(time_delay); 
            TCNT0=0x00;
            TIFR=0x01;
            #asm("sei");
        }
        if(d[i]==1)
        {
        lcd_clear();
        switch(i)
        {
            case 0:
                lcd_puts("FIRE AT ZONE-1");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b00000001;
                        PORTD=0b11111110;                        
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11111110;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11111110;
                }
                s=0;
                break;
            case 1:
                lcd_puts("FIRE AT ZONE-2");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b00000010;
                        PORTD=0b11111101;                                                
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11111101;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11111101;
                }
                s=1;
                break;
            case 2:
                lcd_puts("OVRLOAD AT SC345");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {  
                        PORTA=0b00000100;
                        PORTD=0b11111011;                         
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11111011;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11111011;
                }
                s=2;
                break;
            case 3:
                lcd_puts("BUSTRIP AT SS-31");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b00001000;
                        PORTD=0b11110111;                               
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11110111;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11110111;
                }
                s=3;
                break;
            case 4:
                lcd_puts("LOWVOLT AT SC674");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b00010000;
                        PORTD=0b11101111;                               
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11101111;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11101111;
                }
                s=4;
                break;
            case 5:
                lcd_puts("LOW-PF AT  SC872");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b00100000;
                        PORTD=0b11011111;                           
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b11011111;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b11011111;
                }
                s=5;
                break;
            case 6:
                lcd_puts("LIGHTNING AT P73");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b01000000;
                        PORTD=0b10111111;                            
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b10111111;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b10111111;
                }
                s=6;
                break;
            case 7:
                lcd_puts("LG FAULT AT SS42");
                lcd_gotoxy(0,1);
                lcd_puts("STATUS: ");
                if(f[i]==1)
                {
                    lcd_puts("EXISTING");
                        if(a==1)
                    {   
                        PORTA=0b10000000;
                        PORTD=0b01111111;                                
                        #asm("cli");
                        delay_ms(time_ms); 
                        TCNT0=0x00;
                        TIFR=0x01;
                        #asm("sei");
                        PORTD=0b01111111;
                    }                    
                }
                else
                {
                    lcd_puts("CLEARED");
                    PORTA=0b00000000;
                    PORTD=0b01111111;
                }
                s=7;
                break;
            default:
                {
                    lcd_puts("MONITORING>>>");
                }
        }
        i++;
        }        
        else
        {
            i++;
            if(s<6)
            {
                s++;
                goto label1;
            }        
        }
    }
    s=0;
    t++;
    TCNT0=0x00;
    #asm("sei");        
}     
void main()                                                               
{
    DDRA=0xff;        //PORTA AS OUTPUT (normal output)
    DDRB=0x00;        //PORTB AS INPUT
    DDRC=0x7f;        //PORTC AS OUTPUT (FOR LCD) WITH PORTC.7 AS INPUT FOR ALARM RESET
    DDRD=0xff;        //PORTD AS OUTPUT (complement output)
    PORTA=0x00;       
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0xff;       //output normally high for complement output  
    lcd_init(16);
    lcd_puts(" SMART FIRE");
    lcd_gotoxy(0,1);
    lcd_puts("MONITORING>>>");
    TCCR0=0x05;
    TIMSK=0x01;
    #asm("sei");
    while(1)
    {
        if(PINB.0==1)
        {
            delay_ms(100);
            if(PINB.0==1)
            {
                f[0]=1;
                d[0]=1;
            }
        }
        else
        {
            f[0]=0;
        }
        if(PINB.1==1)
        {
            delay_ms(100);
            if(PINB.1==1)
            {
                f[1]=1;
                d[1]=1;
            }
        }
        else
        {
            f[1]=0;
        }
        if(PINB.2==1)
        {
            delay_ms(100);
            if(PINB.2==1)
            {
                f[2]=1;
                d[2]=1;
            }
        }
        else
        {
            f[2]=0;
        }
        if(PINB.3==1)
        {
            delay_ms(500);
            if(PINB.3==1)
            {
                f[3]=1;
                d[3]=1;
            }
        }
        else
        {
            f[3]=0;
        }
        if(PINB.4==1)
        {
            delay_ms(100);
            if(PINB.4==1)
            {
                f[4]=1;
                d[4]=1;
            }
        }
        else
        {
            f[4]=0;
        }
        if(PINB.5==1)
        {          
            delay_ms(100);
            if(PINB.5==1)
            {
                f[5]=1;
                d[5]=1;
            }
        }
        else
        {
            f[5]=0;
        }
        if(PINB.6==1)
        {
            delay_ms(100);
            if(PINB.6==1)
            {
                f[6]=1;
                d[6]=1;
            }
        }
        else
        {
            f[6]=0;
        }
        if(PINB.7==1)
        {
            delay_ms(100);
            if(PINB.7==1)
            {
                f[7]=1;
                d[7]=1;
            }
        }   
        else
        {
            f[7]=0;
        } 
        if(PINC.7==1)                            //To reset the alarm
        {
            delay_ms(100);
            if(PINC.7==1)
            {
                a=0;
                PORTC=0x00;
                PORTD=0xff;
            }
        }
        if(PINB==0x00)                    //To re-enable alarm when all faults are removed
        {
            delay_ms(1);
            if(PINB==0x00)
            {
                a=1;
            }
        }    }	}            
