#include "adc.h"

/* ADC - Initialization */
int adc_init(struct adc_config_t *adc_desc)
{
	/* Set ADC mode */
	int mode_fd;

	// mode_fd = open("/sys/bus/iio/devices/iio:device0/in_conversion_mode", O_WRONLY);
	// write(mode_fd, (char *)adc_desc->adc_mode, 10);
	// close(mode_fd);

	/* ADC - Enable or disable buffer */
	int capture_fd;

	capture_fd  = open("/sys/bus/iio/devices/iio:device0/buffer/enable", O_WRONLY);
	if (capture_fd < 0) {
		perror("open buffer enable error");
	}
	if (adc_desc->capture)
		write(capture_fd, "1", 2);
	else
		write(capture_fd, "0", 2);

	close(capture_fd);

	/* ADC - SET BUFFER LENGTH */
	int length_fd;

	length_fd  = open("/sys/bus/iio/devices/iio:device0/buffer/length", O_WRONLY);
	if (length_fd < 0) {
		perror("open buffer length error");
	}

	snprintf((char *)adc_desc->buf, sizeof(adc_desc->buf), "%d", adc_desc->buff_length);
	write(length_fd, adc_desc->buf, strlen((char *)adc_desc->buf));

	close(length_fd);

	return 0;
}

/* ADC - SET CHANNEL */
int adc_set_channel(struct adc_config_t *adc_desc, int channel)
{
	int channel_fd;

	sprintf((char *)adc_desc->buf, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage%d_en", channel);
	channel_fd  = open((char *)adc_desc->buf, O_WRONLY);
	if (channel_fd < 0) {
		perror("open scan_elements/in_voltage error");
	}

	write(channel_fd, "1", 2);

	close(channel_fd);

	return 0;
}

/* ADC - READ OUTPUT DATA */
int adc_output(struct adc_config_t *adc_desc, int channel)
{
	int output_fd, adc_data;
	char result[10];
	ssize_t ret;

	sprintf((char *)adc_desc->buf, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", channel);
	output_fd  = open((char *)adc_desc->buf, O_RDONLY);
	if (output_fd < 0) {
		perror("open in_voltage_raw error");
	}

	ret = read(output_fd, result, sizeof(result));
	if (ret < 0) {
		perror("read error");
		close(output_fd);
		return -1;
	}
	result[ret] = '\0';

	adc_data = atoi(result);

	close(output_fd);

	return adc_data;
}


