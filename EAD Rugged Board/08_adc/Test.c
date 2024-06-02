#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "adc.h"

/**************************************** 	     
		 MAIN
*****************************************/
int main(int argc, char **argv, char **envp)
{
	int digital_val;
	struct adc_config_t adc_desc;
	float analog_val;
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <adc_channel>\n", argv[0]);
		return 1;
	}

	adc_desc.adc_mode = ONESHOT;
	adc_desc.capture  = 0;
	adc_desc.buff_length = 100;
	adc_desc.adc_channel = atoi(argv[1]);
	printf("\n   *** ADC TESTING UTILITY ***   \n");

	adc_init(&adc_desc);
	adc_set_channel(&adc_desc, adc_desc.adc_channel);

	while (1)
	{
		digital_val = adc_output(&adc_desc, adc_desc.adc_channel);
		analog_val = (digital_val * 0.805664062)/4095;

		printf("Digital Value on Channel %d = %d\n", adc_desc.adc_channel, digital_val);
		printf("Analog Value on Channel %d = %f\n", adc_desc.adc_channel, analog_val);
		sleep(1);
	}

	return 0;
}


