#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>

static void clock_setup(void)
{

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_TIM1);
}

//gdhghgdfh
static void timer1_setup(void)
{
	rcc_periph_reset_pulse(RST_TIM1);
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT,
			   TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

	timer_set_prescaler(TIM1, 0);
	timer_set_repetition_counter(TIM1, 0);
	timer_enable_preload(TIM1);
	timer_continuous_mode(TIM1);

	// Period (32kHz)
	timer_set_period(TIM1, rcc_apb2_frequency*2 / 32000);

	timer_set_deadtime(TIM1, 10);
	timer_set_enabled_off_state_in_idle_mode(TIM1);
	timer_set_enabled_off_state_in_run_mode(TIM1);
	timer_disable_break(TIM1);
	timer_set_break_polarity_high(TIM1);
	timer_disable_break_automatic_output(TIM1);
	timer_set_break_lock(TIM1, TIM_BDTR_LOCK_OFF);
	timer_disable_oc_output(TIM1, TIM_OC3);
	timer_disable_oc_output(TIM1, TIM_OC3N);
	timer_disable_oc_clear(TIM1, TIM_OC3);
	timer_enable_oc_preload(TIM1, TIM_OC3);
	timer_set_oc_slow_mode(TIM1, TIM_OC3);
	timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM1, TIM_OC3);
	timer_set_oc_idle_state_set(TIM1, TIM_OC3);
	timer_set_oc_polarity_high(TIM1, TIM_OC3N);
	timer_set_oc_idle_state_set(TIM1, TIM_OC3N);

	/* Set the capture compare value for OC3. 50% duty */
	timer_set_oc_value(TIM1, TIM_OC3, rcc_apb2_frequency / 10000);

	timer_enable_oc_output(TIM1, TIM_OC3);
	timer_enable_oc_output(TIM1, TIM_OC3N);
	timer_enable_preload(TIM1);
	timer_enable_break_main_output(TIM1);
	timer_enable_counter(TIM1);
}

static void gpio_setup(void)
{
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