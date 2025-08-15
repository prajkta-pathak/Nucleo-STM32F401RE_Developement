/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Prajkta Pathak
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

// Base addresses
#define PERIPH_BASE        (0x40000000UL)
#define AHB1PERIPH_OFFSET  (0x00020000UL)
#define AHB1PERIPH_BASE    (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET       (0x0000UL)
#define GPIOA_BASE         (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET         (0x00003800UL)
#define RCC_BASE           (AHB1PERIPH_BASE + RCC_OFFSET)

// Register offsets
#define RCC_AHB1ENR_OFFSET  (0x30UL)
#define GPIOx_MODER_OFFSET  (0x00UL)
#define GPIOx_ODR_OFFSET    (0x14UL)

// Register pointers
#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET))
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_MODER_OFFSET))
#define GPIOA_ODR     (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_ODR_OFFSET))

// Bit positions
#define RCC_AHB1ENR_GPIOA_EN  (1U << 0)   // Enable clock for GPIOA
#define LED_PIN               (1U << 5)  // PA5 (LD2)

// Simple delay
void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < (ms * 1600); i++) // Adjust for clock speed
    {
        __asm__("nop"); // 1 nop = 1 CPU cycle, so delays with nop loops are very approximate — for accurate delays, you’d use a hardware timer instead.
    }
}

int main(void)
{
    // 1. Enable clock for GPIOA
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOA_EN;

    // 2. Set PA5 as output (MODER5 = 01)
    GPIOA_MODER &= ~(3U << 10); // Clear bits for pin 5
    GPIOA_MODER |=  (1U << 10); // Set to output mode

    // 4. Turn LED OFF
    GPIOA_ODR &= ~LED_PIN;

    while (1)
    {
            GPIOA_ODR ^= LED_PIN; // Toggle PA5
            delay_ms(100);
        // Stay here forever
    }
}
