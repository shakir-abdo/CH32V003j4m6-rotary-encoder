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


// ANSI color codes for prettier output
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"

int main() {
    SystemInit();

    // Initialize encoder
    encoder_init();

    int32_t last_count = 0;
    bool last_switch_state = false;

    printf("\n\r" COLOR_BLUE "Rotary Encoder Demo Started!\n\r" COLOR_RESET);
    printf("Turn the encoder or press the button...\n\r");

    while (1) {
        // Update encoder state
        encoder_update();

        int32_t current_count = encoder_get_count();
        bool switch_pressed = encoder_switch_pressed();

        // Check if count has changed
        if (current_count != last_count) {
            // Determine direction
            const char* direction =
                (current_count > last_count) ? "RIGHT" : "LEFT";
            printf(COLOR_GREEN "Position: %ld | Direction: %s" COLOR_RESET
                               "\n\r",
                   current_count, direction);

            last_count = current_count;
        }

        // Check if switch state has changed
        if (switch_pressed != last_switch_state) {
            if (switch_pressed) {
                printf(COLOR_YELLOW
                       "Button: PRESSED  | Position: %ld" COLOR_RESET "\n\r",
                       current_count);
            } else {
                printf(COLOR_YELLOW
                       "Button: RELEASED | Position: %ld" COLOR_RESET "\n\r",
                       current_count);
            }
            last_switch_state = switch_pressed;
        }

        Delay_Ms(1);  // Small delay for stability
    }
}
