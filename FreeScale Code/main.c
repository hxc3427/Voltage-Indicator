/******************************************************************************
 * Timer Output Compare Demo
 *
 * Description:
 *
 * This demo configures the timer to a rate of 1 MHz, and the Output Compare
 * Channel 1 to toggle PORT T, Bit 1 at rate of 10 Hz. 
 *
 * The toggling of the PORT T, Bit 1 output is done via the Compare Result Output
 * Action bits.  
 * 
 * The Output Compare Channel 1 Interrupt is used to refresh the Timer Compare
 * value at each interrupt
 * 
 * Author:
 *  Jon Szymaniak (08/14/2009)
 *  Tom Bullinger (09/07/2011)	Added terminal framework
 *
 *****************************************************************************/


// system includes
#include <hidef.h>      /* common defines and macros */
#include <stdio.h>      /* Standard I/O Library */
#include <stdlib.h>
// project includes
#include "types.h"
#include "derivative.h" /* derivative-specific definitions */                


int ADC_Value=0;
UINT8 duty=0;




void InitializeSerialPort(void)
{
    // Set baud rate to ~9600 (See above formula)
    SCI0BD = 13;          
    
    // 8N1 is default, so we don't have to touch SCI0CR1.
    // Enable the transmitter and receiver.
    SCI0CR2_TE = 1;
    SCI0CR2_RE = 1;
}

void TERMIO_PutChar(INT8 ch)
{
    // Poll for the last transmit to be complete
    do
    {
      // Nothing  
    } while (SCI0SR1_TC == 0);
    
    // write the data to the output shift register
    SCI0DRL = ch;
}


void setPWM()                    //PWM PIN 9 to motor
{
  //Set up clock pre scalers
		PWMPRCLK=6;   //set clock A pre scale
		PWMSCLA=1;    //set clockSA pre scale
  //Set up parameters for both PWMs
		PWMCLK=0x03;  //select clockSA for PWM0 and PWM1 channel
		PWMPOL=0x03;  //PWM0 and PWM1 channel O/P start high at beginning of period. 
		PWMCAE=0x03;  //PWM0 and PWM1 channel are center aligned
	//Set PWM Period
	
		PWMPER0=150;  //set PWM0 channel period to X  usec
	
    PWMDTY0=duty;

                  
		PWMCNT0=0x01; //reset PWM0 channel counter
    PWME =0x03;   //enable PWM0
	
}     


void main (void)
{  
   int ADC_old;
   int c;
   int z;
   int k;
   InitializeSerialPort();
   DDRA=0x00;  //Set entire portA to input
   DDRB=0x00;  //Set port B to be input
   ADC_old = PORTA;
    
    
   c= PORTB; 
   while(c==244) {                //Pushbutton to pin 51
   c=PORTB;
   }
  
  
  
  
                                //ADC QNX ( 1,2,3,4) corresponse to pin 39,37 35 ,33
   DDRB=0xff;                    //change port B to be output for LED
   
   
     
     while(1){
     
     
     
     
      for (z=0;z<100;z++)
      {
      
      
         for (k=0;k<500;k++)    
         
         {
          
         }
      
      
      
      }
     
     
          
      ADC_Value = PORTA &0x0f;   //read values from PORTA
      
      (void)printf("Input value is %d \r\n",ADC_Value);
      
      if(ADC_Value != ADC_old) {   //check if PWM needs to be updated
      
      
      
      ADC_old=ADC_Value;
      
      if(ADC_Value ==0)            //LED to pin 49
      { PORTB=0xff;         
      }
      
      if(ADC_Value !=0)
      { PORTB=0x00;         
      }                               //ADC value to determine position
      
      
      if(ADC_Value ==1)
      { duty=2;      
        setPWM();         
      }
      
      if(ADC_Value ==2)               //ADC value to determine position
      { duty=4;      
        setPWM();         
      }
      
      if(ADC_Value ==3)
      { duty=6;      
        setPWM();         
      }
       
      if(ADC_Value ==4)
      { duty=8;      
        setPWM();         
      }
                                       //ADC value to determine position
      if(ADC_Value ==5)
      { duty=9;      
        setPWM();         
      }
            
      if(ADC_Value ==6)
      { duty=9;      
        setPWM();         
      }
                                        //ADC value to determine position
      if(ADC_Value ==7)
      { duty=10;      
        setPWM();         
      }
      if(ADC_Value ==8)
      { duty=11;      
        setPWM();         
      }
      if(ADC_Value ==9)
      { duty=12;      
        setPWM();         
      }
      if(ADC_Value ==10)
      { duty=13;      
        setPWM();         
      }
      
      if(ADC_Value ==11)
      { duty=14;      
        setPWM();         
      }
      if(ADC_Value ==12)
      { duty=15;      
        setPWM();         
      }                                     //ADC value to determine position
      if(ADC_Value ==13)
      { duty=16;      
        setPWM();         
      }
 
      if(ADC_Value ==14)
      { duty=17;      
        setPWM();         
      }
      
  
      } 
      
      
     }
     
}

      
  
     
  

     
  
  
