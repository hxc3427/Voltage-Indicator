#include <cstdlib>
#include <iostream>
#include <sys/mman.h>
#include <hw/inout.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <sched.h>
#include <sys/neutrino.h>
#include <string>

#define Port_Length 1
#define Data_Base 0x280  //base value of digital io port

uintptr_t dir_ptr=mmap_device_io(Port_Length,Data_Base +0xB); //pointer for setting direction of io ports
uintptr_t da_ptr=mmap_device_io(Port_Length,Data_Base +0x8);  //pointer to port A
uintptr_t ADC_channel=mmap_device_io(Port_Length,Data_Base +0x2);  //pointer to ADC board channel
uintptr_t ADC_input=mmap_device_io(Port_Length,Data_Base +0x3);  //pointer to ADC board channel
uintptr_t ADC_CMD=mmap_device_io(Port_Length,Data_Base +0x0);  //pointer to ADC board channel
uintptr_t ADC_MSB=mmap_device_io(Port_Length,Data_Base +0x1);  //pointer to ADC board channel
uintptr_t ADC_LSB=mmap_device_io(Port_Length,Data_Base +0x0);  //pointer to ADC board channel

int calValue=4;
signed char MSB;
signed char LSB;
signed short int reading;
float voltage;
float period;

void * ADC_Function(void* ){

	        while(1)
			{
			out8(ADC_CMD,0x80);  //initiate ADC conversion
			while(in8(ADC_input)& 0x08 !=0)
			{};
			LSB = in8(ADC_LSB);
			MSB = in8(ADC_MSB);
			reading = (MSB*256) + LSB;
			voltage = reading;

			voltage = ((voltage/32768)*10);
	      //  printf("Measured value is %f \n",voltage);
			}



}
//Map voltage to PWM
void * Output_Function(void* ){

 while(1){

	 /*
	period = ((voltage/5)*5) +10-calValue ;   //range of -5v to +5v maps to 50ms to 150ms period; 100ms is 0 v; subtracted 1 for propagation delay
	out8(da_ptr,0x02);
	delay(period/2);
	out8(da_ptr,0x00);
	delay(period/2);
	//printf("Period is %f \n",period);

     */
	 printf("Measured value is %f \n",voltage);
	 if(voltage < -5 || voltage >5)   // output 0
	 {    out8(da_ptr,0x00);
	     printf("Output is set to 0\n");
	 }


	 if(voltage >= -5 && voltage <-4.28)
	 {
		 out8(da_ptr,0x01);
		 printf("Output is set to 1\n");
	 }

	 if(voltage >= -4.28 && voltage <-3.57)
		 {
			 out8(da_ptr,0x02);
			 printf("Output is set to 2\n");
		 }
	 if(voltage >= -3.57 && voltage <-2.85)
			 {
				 out8(da_ptr,0x03);
				 printf("Output is set to 3\n");
			 }
	 if(voltage >= -2.85 && voltage <-2.14)
				 {
					 out8(da_ptr,0x04);
					 printf("Output is set to 4\n");
				 }
	 if(voltage >=-2.14 && voltage <-1.42)
	 				 {
	 					 out8(da_ptr,0x05);
	 					printf("Output is set to 5\n");
	 				 }
	 if(voltage >= -1.42 && voltage <-.714)
	 	 				 {
	 	 					 out8(da_ptr,0x06);
	 	 					printf("Output is set to 6\n");
	 	 				 }
	 if(voltage >= -.714 && voltage <0)
	 	 	 				 {
	 	 	 					 out8(da_ptr,0x07);
	 	 	 					printf("Output is set to 7\n");
	 	 	 				 }
	 if(voltage >= 0 && voltage <.714)
	 	 	 	 				 {
	 	 	 	 					 out8(da_ptr,0x08);
	 	 	 	 					printf("Output is set to 8\n");
	 	 	 	 				 }
	 if(voltage >= .714 && voltage <1.42)
	 	 	 	 				 {
	 	 	 	 					 out8(da_ptr,0x09);
	 	 	 	 					printf("Output is set to 9\n");
	 	 	 	 				 }

	 if(voltage >= 1.42 && voltage <=2.14)
	 	 	 	 				 {
	 	 	 	 					 out8(da_ptr,0x0A);
	 	 	 	 					printf("Output is set to 10\n");
	 	 	 	 				 }


	 if(voltage >= 2.14 && voltage <=2.85)
		 	 	 	 				 {
		 	 	 	 					 out8(da_ptr,0x0B);
		 	 	 	 					printf("Output is set to 11\n");
		 	 	 	 				 }

	 if(voltage >= 2.85 && voltage <=3.57)
		 	 	 	 				 {
		 	 	 	 					 out8(da_ptr,0x0C);
		 	 	 	 					printf("Output is set to 12\n");
		 	 	 	 				 }
	 if(voltage >= 3.57 && voltage <=4.28)
		 	 	 	 				 {
		 	 	 	 					 out8(da_ptr,0x0D);
		 	 	 	 					printf("Output is set to 13\n");
		 	 	 	 				 }


	 if(voltage >= 4.28 && voltage <= 5)
		 	 	 	 				 {
		 	 	 	 					 out8(da_ptr,0x0E);
		 	 	 	 					printf("Output is set to 14\n");
		 	 	 	 				 }

 }



}


int main(int argc, char *argv[]) {

	pthread_t sample_ADC;   // polling and triggering thread
	pthread_t Output;

	    if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)   // root permission
					{

					perror("Failed to get I/O access permission");
					return 1;
					}
		if(dir_ptr == MAP_DEVICE_FAILED)  // test for root permission
					{
					perror("Failed to map control register");
					return 2;
					}

		if(da_ptr == MAP_DEVICE_FAILED) // test for root permission
					{
					perror("Failed to map control register");
					return 2;
					}

		out8(dir_ptr,0x00);  //Select direction of Digital IO
		out8(ADC_channel,0x44); //select channel 4 or Pin 43
		delay(100);
		out8(ADC_input,0x00);   //select input range of -10 to 10
		delay(100);

		pthread_create( &sample_ADC, NULL, &ADC_Function, NULL );
		pthread_create( &Output, NULL, &Output_Function, NULL );


		pthread_join( Output, NULL );
		pthread_join( sample_ADC, NULL );








}
