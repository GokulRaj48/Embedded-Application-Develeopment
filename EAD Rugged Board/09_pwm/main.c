#include "pwm_controller.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <period> <initial_duty_cycle>\n", argv[0]);
        return 1;
    }

    int period = atoi(argv[1]);
    int initial_duty_cycle = atoi(argv[2]);

    export_pwm_pin();
    set_pwm_period(period);
    enable_pwm();
    generate_pwm_signal(period, initial_duty_cycle);

    return 0;
}
