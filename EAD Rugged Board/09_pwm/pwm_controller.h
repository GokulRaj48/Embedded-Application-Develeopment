#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

// Function prototypes
void export_pwm_pin();
void set_pwm_period(int period);
void enable_pwm();
void generate_pwm_signal(int period, int initial_duty_cycle);

#endif
