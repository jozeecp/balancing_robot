// TODO: Add a way to specify the serial port to use
// TODO: Add a way to add multiple menus


#include "serial_ui.h"
#include <vector>

// -----------------------------------------------------------------------------
// Serial Input
// -----------------------------------------------------------------------------
void Serial_UI::line_buffer, line;

void Serial_UI::init(int baud_rate, std::string title) {
    Serial.begin(baud_rate);
    Serial.println("");
    Serial.println("Serial UI by Jose FC Palomo (Github @jozeecp");
    Serial.println("v0.1");

    delay(1000);

    clear_screen();

    Serial.println(title);
    Serial.println("");
    Serial.println("
-----------------------------------------------------------------------------
 ______     ________       __           ______       ___ __ __      ______      
/_____/\   /_______/\     /_/\         /_____/\     /__//_//_/\    /_____/\     
\:::_ \ \  \::: _  \ \    \:\ \        \:::_ \ \    \::\| \| \ \   \:::_ \ \    
 \:(_) \ \  \::(_)  \ \    \:\ \        \:\ \ \ \    \:.      \ \   \:\ \ \ \   
  \: ___\/   \:: __  \ \    \:\ \____    \:\ \ \ \    \:.\-/\  \ \   \:\ \ \ \  
   \ \ \      \:.\ \  \ \    \:\/___/\    \:\_\ \ \    \. \  \  \ \   \:\_\ \ \ 
    \_\/       \__\/\__\/     \_____\/     \_____\/     \__\/ \__\/    \_____\/ 
                                                                                
 __           ________        _______       ______                              
/_/\         /_______/\     /_______/\     /_____/\                             
\:\ \        \::: _  \ \    \::: _  \ \    \::::_\/_                            
 \:\ \        \::(_)  \ \    \::(_)  \/_    \:\/___/\                           
  \:\ \____    \:: __  \ \    \::  _  \ \    \_::._\:\                          
   \:\/___/\    \:.\ \  \ \    \::(_)  \ \     /____\:\                         
    \_____\/     \__\/\__\/     \_______\/     \_____\/                                                                                                   
-----------------------------------------------------------------------------
    ");

    for(int i = 0; i < 5; i++) {
        count = i + 1;
        Serial.print(count, "...  ");
        delay(1000);
    }

    clear_screen();
}

void Serial_UI::read_line() {
    // Read the serial input
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n') {
            // End of line
            // Check if the line is empty
            if (line_buffer.length() == 0) {
                // Empty line
                // Do nothing
            } else {
                // Line is not empty
                // Process the line
                // char *line = line_buffer.c_str();
                process_line(line);
            }
            // Reset the line buffer
            line_buffer = "";
        } else {
            // Add the character to the line buffer
            line_buffer += c;
        }
    }

    if(Serial.availableForWrite()) {
        // Write the serial output
        Serial.print('Received: ')
        Serial.print(line);
        Serial.println("");
    }
}

void Serial_UI::process_line() {
    char *line = line_buffer.c_str();
    line_buffer = "";
}

char Serial_UI::get_line() {
    char last_line = line;
    return last_line;
}

char Serial_UI::reset_line() {
    line_buffer = "";
}

void Serial_UI::print_line() {
    Serial.print(line);
}

// -----------------------------------------------------------------------------
// Screen + State Machine
// -----------------------------------------------------------------------------
std::vector< int > options;

void Serial_UI::clear_screen() {
    Serial.println("\033[2J");
}

void Serial_UI::add_option(int option) {
    options.push_back(option);
}

int Serial_UI::state_machine() {
    read_line();
    char *option = get_line();
    int state = atoi(option);
    return state;
}

void Serial_UI::print_options() {
    for(int i = 0; i < options.size(); i++) {
        Serial.print(options[i]);
        Serial.print(".");
    }
    Serial.println("");
}

void Serial_UI::print_options_with_index() {
    for(int i = 0; i < options.size(); i++) {
        Serial.print(i);
        Serial.print(") ");
        Serial.print(options[i]);
        Serial.print(".  ");
        if(i%4 == 3) {
            Serial.println("");
        }
    }
    Serial.println("");
}