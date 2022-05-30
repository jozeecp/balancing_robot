// TODO: Finish building out the menus in Serial UI

// Balancing Robot MK-I code. 
//#include "stdio.h"
//#include "stddef.h"
#include "Arduino.h"
//#include <Arduino.h>;
#include "motor_driver.h"
//#include "signal_utils.h"



void setup() {
    Serial.begin(9600);

    // Initialize Serial UI
    Serial.println("Initializing Serial UI...");
    SerialUI::init(9600, "Balancing Robot MK-I v0.1, by Jose FC Palomo (Github @jozeecp)");

    // Initialize Menu
    SerialUI::add_option("enable verbose");
    SerialUI::add_option("disable verbose");
    SerialUI::add_option("enable debug");

    // Display Menu
    SerialUI::clear_screen();
    
    // Initialize the motor driver
    Serial.println("Initializing motor driver");
    L298N_Motor_Driver::init(9, 10, 11);

    // Initialize the encoder
    Serial.println("Initializing encoder");
    Encoder::init(12, 13);

    // Initialize the PID controller
    Serial.println("Initializing PID controller");
    Serial.println("kp = 0.5, ki = 0.0, kd = 0.0, dt = 0.1");
    PID::init(  0.1,    // kp
                0.1,    // ki
                0.1,    // kd
                0.1);   // dt

    // Reset the encoder
    Serial.println("Resetting encoder");
    Encoder::reset();

    // Initialize variables
    int speed = 0;
    int error = 0;

    // 
}

void loop() {
    // Update the encoder
    Encoder::update();

    int desired_position = 0;

    int motor_position = Encoder::get_count();
    int error = motor_position - desired_position;
    
    // Update the PID controller
    PID::update(error);
    int motor_speed = PID::get_output();

    // Set the motor speed
    L298N_Motor_Driver::set_speed(motor_speed);

    // Logging
    Serial.print("Desired position = ", desired_position);
    Serial.print("Motor position: ", motor_position);
    Serial.print("Error: ", error);
    Serial.print("Motor speed: ", motor_speed);
    Serial.println();
}
