#include <libopencm3/stm32/gpio.h>     // Подключение библиотеки для работы с GPIO STM32
#include <libopencm3/stm32/rcc.h>      // Подключение библиотеки для настройки тактовых частот
#include <libopencm3/cm3/systick.h>    // Подключение библиотеки для работы с системным таймером

// Определяем порты и пины для подключения шагового двигателя
#define IN1_PORT GPIOA
#define IN1_PIN GPIO0
#define IN2_PORT GPIOA
#define IN2_PIN GPIO1
#define IN3_PORT GPIOA
#define IN3_PIN GPIO2
#define IN4_PORT GPIOA
#define IN4_PIN GPIO3

// Количество шагов для полного оборота (для 28BYJ-48 это около 4096 шагов)
const int stepsPerRevolution = 4096;

// Время задержки между шагами для управления скоростью вращения (в миллисекундах)
int stepDelay = 2;

// Последовательность шагов для управления обмотками шагового двигателя в режиме полушагов
uint8_t stepSequence[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

// Переменная для отслеживания текущего шага
int currentStep = 0;

// Функция задержки в миллисекундах
void delay_ms(int ms) {
    for (int i = 0; i < ms * 8000; i++) {
        asm("nop"); // Небольшая пустая операция для создания паузы
    }
}

// Функция настройки GPIO для управления шаговым двигателем
void setup_gpio(void) {
    // Включаем тактирование для порта GPIOA
    rcc_periph_clock_enable(RCC_GPIOA);
    
    // Настраиваем пины PA0, PA1, PA2 и PA3 как выходы
    gpio_mode_setup(IN1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, IN1_PIN | IN2_PIN | IN3_PIN | IN4_PIN);
}

// Функция, выполняющая один шаг мотора, активируя нужные пины
void stepMotor(int step) {
    // Управляем каждым из 4 пинов в соответствии с текущим шагом из последовательности
    if (stepSequence[step][0]) {
        gpio_set(IN1_PORT, IN1_PIN);  // Устанавливаем пин PA0 в состояние "высокий уровень"
    } else {
        gpio_clear(IN1_PORT, IN1_PIN); // Сбрасываем пин PA0 в состояние "низкий уровень"
    }

    if (stepSequence[step][1]) {
        gpio_set(IN2_PORT, IN2_PIN);  // Устанавливаем пин PA1 в состояние "высокий уровень"
    } else {
        gpio_clear(IN2_PORT, IN2_PIN); // Сбрасываем пин PA1 в состояние "низкий уровень"
    }

    if (stepSequence[step][2]) {
        gpio_set(IN3_PORT, IN3_PIN);  // Устанавливаем пин PA2 в состояние "высокий уровень"
    } else {
        gpio_clear(IN3_PORT, IN3_PIN); // Сбрасываем пин PA2 в состояние "низкий уровень"
    }

    if (stepSequence[step][3]) {
        gpio_set(IN4_PORT, IN4_PIN);  // Устанавливаем пин PA3 в состояние "высокий уровень"
    } else {
        gpio_clear(IN4_PORT, IN4_PIN); // Сбрасываем пин PA3 в состояние "низкий уровень"
    }
}

// Функция для вращения мотора на заданное количество шагов в указанном направлении
void rotateMotor(int steps, bool clockwise) {
    // Цикл выполняет заданное количество шагов
    for (int i = 0; i < steps; i++) {
        if (clockwise) {
            // Если вращение по часовой стрелке, увеличиваем текущий шаг на 1 (с проверкой на переполнение)
            currentStep = (currentStep + 1) % 8;
        } else {
            // Если против часовой стрелки, уменьшаем текущий шаг на 1 (с проверкой на отрицательный индекс)
            currentStep = (currentStep - 1 + 8) % 8;
        }
        // Выполняем текущий шаг
        stepMotor(currentStep);
        // Задержка между шагами для контроля скорости
        delay_ms(stepDelay);
    }
}

// Главная функция программы
int main(void) {
    // Включаем тактирование для порта GPIOA и настраиваем GPIO
    rcc_periph_clock_enable(RCC_GPIOA);
    setup_gpio();

    // Основной цикл программы
    while (1) {
        // Вращаем двигатель на полный оборот вперед (по часовой стрелке)
        rotateMotor(stepsPerRevolution, true);
        delay_ms(1000); // Пауза на 1 секунду

        // Вращаем двигатель на половину оборота назад (против часовой стрелки)
        rotateMotor(stepsPerRevolution / 2, false);
        delay_ms(1000); // Пауза на 1 секунду
    }

    return 0; // Программа завершена (на практике эта строка не выполняется, т.к. цикл while бесконечный)
}