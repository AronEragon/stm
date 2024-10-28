#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define LED_DISCO_GREEN_PORT GPIOD
#define LED_DISCO_GREEN_PIN GPIO12

static void clock_setup(void)
{
rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
/* Enable GPIOD clock for LED & USARTs. */
rcc_periph_clock_enable(RCC_GPIOD);
rcc_periph_clock_enable(RCC_GPIOA);

/* Enable clocks for USART2 and dac */
rcc_periph_clock_enable(RCC_USART2);
rcc_periph_clock_enable(RCC_DAC);

/* And ADC*/
rcc_periph_clock_enable(RCC_ADC1);
}

static void adc_setup(void)
{
gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);

adc_power_off(ADC1);
adc_disable_scan_mode(ADC1);
adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);

adc_power_on(ADC1);
}

static void dac_setup(void)
{
gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO5);
dac_disable(DAC1, DAC_CHANNEL2);
dac_disable_waveform_generation(DAC1, DAC_CHANNEL2);
dac_enable(DAC1, DAC_CHANNEL2);
dac_set_trigger_source(DAC1, DAC_CR_TSEL2_SW);
}

static uint16_t read_adc_naiive(uint8_t channel)
{
uint8_t channel_array[16];
channel_array[0] = channel;
adc_set_regular_sequence(ADC1, 1, channel_array);
adc_start_conversion_regular(ADC1);
while (!adc_eoc(ADC1));
uint16_t reg16 = adc_read_regular(ADC1);
return reg16;
}

int main(void)
{
    int i;
clock_setup();
adc_setup();
dac_setup();

/* green led for ticking */
gpio_mode_setup(LED_DISCO_GREEN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			LED_DISCO_GREEN_PIN);

while (1) {
uint16_t input_adc0 = read_adc_naiive(0);
dac_load_data_buffer_single(DAC1, input_adc0, DAC_ALIGN_RIGHT12, DAC_CHANNEL2);
dac_software_trigger(DAC1, DAC_CHANNEL2);
/* LED on/off */
gpio_toggle(LED_DISCO_GREEN_PORT, LED_DISCO_GREEN_PIN);

for (i = 0; i < 1000000; i++) { /* Wait a bit. */
__asm__("NOP");
}
}
return 0;
}