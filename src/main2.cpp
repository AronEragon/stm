#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>

static void clock_setup(void)
{
/*rcc_clock_setup_hsi(&rcc_clock_setup_hsi[RCC_CLOCK_HSI_64MHZ]);*/

/* Enable GPIOE clock. */
rcc_periph_clock_enable(RCC_GPIOA);

/* Enable TIM1 clock. */
rcc_periph_clock_enable(RCC_TIM1);
}

static void timer1_setup(void)
{
/* Reset TIM1 peripheral. */
rcc_periph_reset_pulse(RST_TIM1);

/* Timer global mode:
* - No divider
* - Alignment edge
* - Direction up
*/
timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT,
TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

/* Reset prescaler value. */
timer_set_prescaler(TIM1, 0);

/* Reset repetition counter value. */
timer_set_repetition_counter(TIM1, 0);

/* Enable preload. */
timer_enable_preload(TIM1);

/* Continuous mode. */
timer_continuous_mode(TIM1);

/* Period (32kHz). */
/* TIM1 uses a clock from APB2, see reg RCC_APB2ENR in STM32F407 RM */
/* APB2 PREESC was set to 2, so APB2 timer clocks is */
/* 2 x rcc_apb2_frequency, see clock tree in STM32F407 RM */
timer_set_period(TIM1, rcc_apb2_frequency*2 / 32000);

/* Configure break and deadtime. */
timer_set_deadtime(TIM1, 10);
timer_set_enabled_off_state_in_idle_mode(TIM1);
timer_set_enabled_off_state_in_run_mode(TIM1);
timer_disable_break(TIM1);
timer_set_break_polarity_high(TIM1);
timer_disable_break_automatic_output(TIM1);
timer_set_break_lock(TIM1, TIM_BDTR_LOCK_OFF);

/* -- OC3 configuration -- */
/* Disable outputs. */
timer_disable_oc_output(TIM1, TIM_OC3);
timer_disable_oc_output(TIM1, TIM_OC3N);

/* Configure global mode of line 3. */
timer_disable_oc_clear(TIM1, TIM_OC3);
timer_enable_oc_preload(TIM1, TIM_OC3);
timer_set_oc_slow_mode(TIM1, TIM_OC3);
timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);

/* Configure OC3. */
timer_set_oc_polarity_high(TIM1, TIM_OC3);
timer_set_oc_idle_state_set(TIM1, TIM_OC3);

/* Configure OC3N. */
timer_set_oc_polarity_high(TIM1, TIM_OC3N);
timer_set_oc_idle_state_set(TIM1, TIM_OC3N);

/* Set the capture compare value for OC3. 50% duty */
timer_set_oc_value(TIM1, TIM_OC3, rcc_apb2_frequency / 20000);

/* Reenable outputs. */
timer_enable_oc_output(TIM1, TIM_OC3);
timer_enable_oc_output(TIM1, TIM_OC3N);

/* ARR reload enable. */
timer_enable_preload(TIM1);

/* Enable outputs in the break subsystem. */
timer_enable_break_main_output(TIM1);

/* Counter enable. */
timer_enable_counter(TIM1);
}

static void gpio_setup(void)
{
/* Set GPIOE12 and GPIO13 to 'output push-pull' and AF1 (TIM1_CH3N, TIM1_CH3). */
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10);
gpio_set_af(GPIOA, GPIO_AF6, GPIO10);
gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO10);
}

int main(void)
{
clock_setup();
gpio_setup();
timer1_setup();

while (1);

return 0;
}