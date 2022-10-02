
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>


static void clock_setup(void)
{
    /* Enable clocks for USART2. */
    rcc_periph_clock_enable(RCC_USART2);

    /* Enable clocks for TIM1 */
    rcc_periph_clock_enable(RCC_TIM1);
}

static void usart_setup(void)
{
    /* Setup USART2 parameters. */
    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    /* Finally enable the USART. */
    usart_enable(USART2);
}

static void gpio_setup(void)
{
    /* Setup GPIO pins for USART2 transmit. */
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);

    /* Setup USART2 TX pin as alternate function. */
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

}

static void systick_setup(void)
{
    systick_set_reload(1UL << 22);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_interrupt_enable();
    systick_counter_enable();
}

int _write(int file, char *ptr, int len);
int _write(int file, char *ptr, int len)
{
    int i;

    if (file == STDOUT_FILENO || file == STDERR_FILENO)
    {
        for (i = 0; i < len; i++)
        {
            if (ptr[i] == '\n')
            {
                usart_send_blocking(USART2, '\r');
            }
            usart_send_blocking(USART2, ptr[i]);
        }
        return i;
    }
    errno = EIO;
    return -1;
}

int main(void)
{
    uint16_t count = 0;
    clock_setup();
    gpio_setup();
    usart_setup();
    systick_setup();

    while (1)
    {
        // __asm("wfi"); /* Uncomment this line to delay printing */
        printf("it's going to hang soon, promise!\n");
    }

    return 0;
}