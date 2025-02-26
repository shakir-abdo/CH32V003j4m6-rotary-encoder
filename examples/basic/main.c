/*
Connection:
CLK (A) connects to PC2
DT (B) connects to PC4
SW connects to PC1
VCC to 3.3V
GND to GND
*/

#include <stdio.h>

#include "rotary_encoder.h"

int main() {
    SystemInit();
    encoder_init();

    int32_t last_count = 0;
    bool last_switch_state = false;

    printf("\n\rRotary Encoder Demo\n\r");

    while (1) {
        encoder_update();

        int32_t current_count = encoder_get_count();
        bool switch_pressed = encoder_switch_pressed();

        // Check for changes
        if (current_count != last_count ||
            switch_pressed != last_switch_state) {
            // Print current state
            printf("Count: %ld | ", current_count);

            // Direction (if count changed)
            if (current_count != last_count) {
                printf("Direction: %s | ",
                       (current_count > last_count) ? "RIGHT" : "LEFT");
            }

            // Button state
            printf("Button: %s\n\r", switch_pressed ? "PRESSED" : "RELEASED");

            last_count = current_count;
            last_switch_state = switch_pressed;
        }

        Delay_Ms(1);
    }
}
