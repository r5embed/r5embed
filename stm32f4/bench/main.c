//  main.c
//  2019-03-10  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2019, PQShield Ltd.

//  Compiled from OpenCM3 examples and little bit of PQM4

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include <libopencm3/stm32/flash.h>
#include <libopencm3/cm3/systick.h>

#include "main.h"

//  clock wraparound

uint64_t tick_high = 1;

//  interrupt handler

void sys_tick_handler()
{
    tick_high++;
}

//  return total number of ticks

uint64_t get_cycles()
{
    return (tick_high << 24) - ((uint64_t) systick_get_value());
}

void my_print(const char *str)
{
    int i;

    for (i = 0; str[i] != 0; i++) {
        usart_send_blocking(USART2, str[i]);
    }
}

//  == setup ==

/* 24 MHz */
static const struct rcc_clock_scale benchmarkclock = {
    .pllm = 8, //VCOin = HSE / PLLM = 1 MHz
    .plln = 192, //VCOout = VCOin * PLLN = 192 MHz
    .pllp = 8, //PLLCLK = VCOout / PLLP = 24 MHz (low to have 0WS)
    .pllq = 4, //PLL48CLK = VCOout / PLLQ = 48 MHz (required for USB, RNG)
    .hpre = RCC_CFGR_HPRE_DIV_NONE,
    .ppre1 = RCC_CFGR_PPRE_DIV_2,
    .ppre2 = RCC_CFGR_PPRE_DIV_NONE,
    .flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_0WS,
    .apb1_frequency = 12000000,
    .apb2_frequency = 24000000,
};

static void clock_setup_bench()
{
    rcc_clock_setup_hse_3v3(&benchmarkclock);

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_RNG);
    flash_prefetch_enable();

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_set_reload(0xFFFFFF);
    systick_interrupt_enable();
    systick_counter_enable();
}

static void usart_setup()
{
    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_enable(USART2);
}

static void gpio_setup()
{
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

//  == entry point ===

int test_stack();       // bench.c prototypes
int test_speed();

int main(void)
{
    int i;

    clock_setup_bench();
    gpio_setup();
    usart_setup();

    //  little wait
    usart_send_blocking(USART2, '\n');
    for (i = 0; i < 1000000; i++) {
        __asm__("NOP");
    }
    my_print("(RESET)\n");

    test_speed();       // bench.c
    test_stack();

    //  send "EOF"
    usart_send_blocking(USART2, 4);     // we use ascii 4 as end marker
    usart_send_blocking(USART2, '\n');

    while(1);           // press reset to run it again

    return 0;
}

