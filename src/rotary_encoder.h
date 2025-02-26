#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdbool.h>
#include <stdint.h>

#include "ch32v003fun.h"

// Encoder pins
#define ENCODER_CLK_PIN PC2  // Clock/A pin
#define ENCODER_DT_PIN PC4   // Data/B pin
#define ENCODER_SW_PIN PC1   // Switch pin

// Function declarations
void encoder_init(void);
void encoder_update(void);
int32_t encoder_get_count(void);
void encoder_set_count(int32_t value);
bool encoder_switch_pressed(void);

#endif  // ROTARY_ENCODER_H
