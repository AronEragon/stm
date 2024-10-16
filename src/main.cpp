#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

// PA0 TIM5_CH1. AF2 PA8


const uint32_t timer_peri = TIM1; // устройство таймер
const enum tim_oc_id oc_id = TIM_OC3; // указатель выходного канала сравнения

int main(void)
{

    // setup PA0 for PWM
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM1); // включить таймерные часы
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10); // pin PA11 Alt Function
    gpio_set_af(GPIOA, GPIO_AF2, GPIO10);

    int freq = 16000;
    timer_set_prescaler(timer_peri, 16-1); // s/b 1MHz
    int period = 1000000/freq; // предварительная настройка масштабирования на 1 МГц
    timer_enable_preload(timer_peri); // заставляет счетчик загружаться из своего ARR только при следующем событии обновления
    timer_set_period(timer_peri, period); // установить период таймера в регистре автоперезагрузки (ARR) set the timer period in the (ARR) auto-reload register
    timer_set_oc_value(timer_peri, oc_id, period * 1/4); // установить рабочий цикл 25%
    timer_set_counter(timer_peri, 0); // TIM_CNT
    
    timer_enable_oc_preload(timer_peri, oc_id);
    timer_set_oc_mode(timer_peri, oc_id, TIM_OCM_PWM1); // выход активен, когда счетчик равен lt compare register
    timer_enable_oc_output(timer_peri, oc_id); // включить таймер вывода сравнение
    timer_continuous_mode(timer_peri); // включить непрерывную работу таймера
    timer_generate_event(timer_peri, TIM_EGR_UG); // required!
    timer_enable_counter(timer_peri);
    //timer_enable_irq(timer_peri, TIM_DIER_COMIE);  //включить прерывание коммутации
    //nvic_enable_irq(NVIC_TIM1_CC_IRQ);

    // Для расширенных таймеров, таких как TIM1, необходимо дополнительно включить выход:
    timer_enable_break_main_output(timer_peri);

    while (1);
}