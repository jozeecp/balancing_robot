#include "motor_driver.h"
// #include "std.io"
#include "Arduino.h"

// -----------------------------------------------------------------------------
// L298N Motor Driver
// -----------------------------------------------------------------------------

void L298N_Motor_Driver::_pin_enable, _pin_in1, _pin_in2;

void L298N_Motor_Driver::init(int pin_enable, int pin_in1, int pin_in2) {
    pinMode(pin_enable, OUTPUT);
    pinMode(pin_in1, OUTPUT);
    pinMode(pin_in2, OUTPUT);
    _pin_enable = pin_enable;
    _pin_in1 = pin_in1;
    _pin_in2 = pin_in2;
}

void L298N_Motor_Driver::set_speed(int speed) {
    if (speed > 0) {
        digitalWrite(_pin_in1, HIGH);
        digitalWrite(_pin_in2, LOW);
    } else if (speed < 0) {
        digitalWrite(_pin_in1, LOW);
        digitalWrite(_pin_in2, HIGH);
    } else {
        digitalWrite(_pin_in1, LOW);
        digitalWrite(_pin_in2, LOW);
    }
    analogWrite(_pin_enable, abs(speed));
}


// -----------------------------------------------------------------------------
// Encoder
// -----------------------------------------------------------------------------

int Encoder::_pin_a, _pin_b, _last_state, _count;

void Encoder::init(int pin_a, int pin_b) {
    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    _pin_a = pin_a;
    _pin_b = pin_b;
    _last_state = digitalRead(_pin_a);
    _last_state = digitalRead(_pin_b);
}

void Encoder::update() {
    int state = digitalRead(_pin_a);
    if (state != _last_state) {
        if (digitalRead(_pin_b) != state) {
            _count++;
        } else {
            _count--;
        }
    }
    _last_state = state;
}

void Encoder::reset() {
    _count = 0;
}

int Encoder::get_count() {
    return _count;
}


// -----------------------------------------------------------------------------
// PID Controller
// -----------------------------------------------------------------------------
void PID:_kp, _ki, _kd, _dt, _error, _integral, _derivative, _output;

void PID::init(float kp, float ki, float kd, float dt) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _dt = dt;
    _last_error = 0;
    _integral = 0;
}

int PID::update(int error) {
    _integral += error * _dt;
    int derivative = (error - _last_error) / _dt;
    _last_error = error;
    _output =  _kp * error + _ki * _integral + _kd * derivative;
    return _output;
}

void PID::set_kp(float kp) {
    _kp = kp;
}

void PID::set_ki(float ki) {
    _ki = ki;
}

void PID::set_kd(float kd) {
    _kd = kd;
}

void PID::set_dt(float dt) {
    _dt = dt;
}

double PID::get_kp() {
    return _kp;
}

double PID::get_ki() {
    return _ki;
}

double PID::get_kd() {
    return _kd;
}

double PID::get_dt() {
    return _dt;
}

double PID::get_error() {
    return _error;
}

double PID::get_integral() {
    return _integral;
}

double PID::get_derivative() {
    return _derivative;
}

double PID::get_output() {
    return _output;
}