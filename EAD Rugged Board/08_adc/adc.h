#ifndef _ADC_H
#define _ADC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define ONESHOT "oneshot"
#define CONTINUOUS "continuous"

struct adc_config_t {
    char *adc_mode;         /* ADC mode - oneshot or continuous */
    int capture;            /* 1 - Enable buffer, 0 - disable buffer */
    unsigned int buff_length; /* buffer length */
    int adc_channel;        /* ADC channel to use (0-7) */
    unsigned char buf[100]; /* Buffer for various operations */
};

/* Below Functions used in ADC - Library/Test-Program */
int adc_init(struct adc_config_t *);
int adc_set_channel(struct adc_config_t *, int);
int adc_output(struct adc_config_t *, int);

#endif

