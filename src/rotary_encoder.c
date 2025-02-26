#include "rotary_encoder.h"

#include <stdbool.h>

static volatile int32_t encoder_count = 0;
static uint8_t last_encoded = 0;
static uint8_t encoder_state = 0;

void encoder_init(void) {
    // Enable GPIOC clock
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;

    // Configure PC2(CLK) and PC4(DT) as inputs with pull-up
    GPIOC->CFGLR &= ~(0xF << (2 * 4) | 0xF << (4 * 4));
    GPIOC->CFGLR |=
        (GPIO_CNF_IN_PUPD << (2 * 4)) | (GPIO_CNF_IN_PUPD << (4 * 4));

    // Enable pull-ups
    GPIOC->BSHR = (1 << 2) | (1 << 4);

    // Configure PC1(SW) as input with pull-up
    GPIOC->CFGLR &= ~(0xF << (1 * 4));
    GPIOC->CFGLR |= (GPIO_CNF_IN_PUPD << (1 * 4));
    GPIOC->BSHR = (1 << 1);
}

void encoder_update(void) {
    uint8_t MSB = (GPIOC->INDR & (1 << 2)) ? 1 : 0;  // CLK pin
    uint8_t LSB = (GPIOC->INDR & (1 << 4)) ? 1 : 0;  // DT pin

    uint8_t encoded = (MSB << 1) | LSB;
    uint8_t sum = (last_encoded << 2) | encoded;

    switch (sum) {
        case 0b1101:
        case 0b0100:
        case 0b0010:
        case 0b1011:
            encoder_count++;
            break;
        case 0b1110:
        case 0b0111:
        case 0b0001:
        case 0b1000:
            encoder_count--;
            break;
    }

    last_encoded = encoded;
}

int32_t encoder_get_count(void) { return encoder_count; }

void encoder_set_count(int32_t value) { encoder_count = value; }

bool encoder_switch_pressed(void) {
    static uint8_t debounce_count = 0;
    static bool last_state = false;
    bool current_state = !(GPIOC->INDR & (1 << 1));

    if (current_state != last_state) {
        debounce_count++;
        if (debounce_count >= 5) {
            last_state = current_state;
            debounce_count = 0;
        }
    } else {
        debounce_count = 0;
    }

    return last_state;
}
