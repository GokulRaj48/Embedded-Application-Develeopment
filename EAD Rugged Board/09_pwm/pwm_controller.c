#include "pwm_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

char export_path[] = "/sys/class/pwm/pwmchip0/export";
char pwm_periods[] = "/sys/class/pwm/pwmchip0/pwm1/period";
char pwm_enable[] = "/sys/class/pwm/pwmchip0/pwm1/enable";
char duty_cycle[] = "/sys/class/pwm/pwmchip0/pwm1/duty_cycle";

void export_pwm_pin() {
    int fd = open(export_path, O_WRONLY);
    if (fd < 0) {
        perror("export path error \n");
        exit(1);
    }
    write(fd, "1", 2);
    close(fd);
}

void set_pwm_period(int period) {
    int fd = open(pwm_periods, O_WRONLY);
    if (fd < 0) {
        perror("period  error \n");
        exit(1);
    }
    char period_str[5];
    snprintf(period_str, sizeof(period_str), "%d", period);
    write(fd, period_str, strlen(period_str));
    close(fd);
}

void enable_pwm() {
    int fd = open(pwm_enable, O_WRONLY);
    if (fd < 0) {
        perror("enable  error \n");
        exit(1);
    }
    write(fd, "1", 2);
    close(fd);
}

void generate_pwm_signal(int period, int initial_duty_cycle) {
    int fd = open(duty_cycle, O_WRONLY);
    if (fd < 0) {
        perror("duty cycle  error \n");
        exit(1);
    }

    int value = initial_duty_cycle;
    char value_str[5];

    while (1) {
        snprintf(value_str, sizeof(value_str), "%d", value);
        write(fd, value_str, strlen(value_str));
        printf("pwm value : %d \n", value);
        value++;
        usleep(100000);
        if (value >= period) {
            value = 0;
        }
    }

    close(fd);
}
