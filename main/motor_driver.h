#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// #include <Arduino.h>

#include "motor_driver.h"

//using namespace L298N_Motor_Driver;

namespace L298N_Motor_Driver
{
    void init(int pin_enable, int pin_in1, int pin_in2);
    void set_speed(int speed);
}
using namespace L298N_Motor_Driver;

namespace Encoder
{
    void init(int pin_a, int pin_b);
    void update();
    void reset();
    int get_count();
}
using namespace Encoder;

namespace PID
{
    void init(double kp, double ki, double kd, double dt);
    void set_kp(double kp);
    void set_ki(double ki);
    void set_kd(double kd);
    void set_dt(double dt);
    double get_kp();
    double get_ki();
    double get_kd();
    double get_dt();
    double get_error();
    double get_integral();
    double get_derivative();
    double get_output();
    void update(int error);
}
using namespace PID;

#endif
