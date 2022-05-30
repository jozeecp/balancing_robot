#include "signal_utils.h"
#include "Arduino.h"

int smooth_filter(int signal_pin){
    // read the analog value from the sensor
    // and smooth it out with a rolling average

    int s [10];
    
    s[0] = analogRead(signal_pin);
    for(int i = 1; i < 10; i++){
        s[i] = s[i-1];
    }

    int sum = 0;
    for(int i = 0; i < 10; i++){
        sum += s[i];
    }

    int smoothed_value = sum / 10;

    return smoothed_value;
}
