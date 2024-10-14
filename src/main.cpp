#define PROD 1

#if PROD == 1

#include <memory>

#include "beer_selector/beer_selector.h"
#include "esp32/object_factory.h"
#include "esp32/uart.h"
#include "esp32/configuration_manager.h"
#include "esp32/nvs.h"

// Dependencies
std::shared_ptr<ds::esp32::UART> uart = std::make_shared<ds::esp32::UART>();
std::shared_ptr<ds::esp32::NVS> nvs = std::make_shared<ds::esp32::NVS>("ac24");

// Object factory
std::shared_ptr<ds::PlatformObjectFactory> object_factory = std::make_shared<ds::esp32::ESP32ObjectFactory>(
    uart,
    nvs,
    GPIO_NUM_27,
    GPIO_NUM_26);

// App object. Dependencies are injected.
std::shared_ptr<BeerSelector> beer_selector = std::make_shared<BeerSelector>(object_factory);

extern "C"
void app_main(void)
{
    beer_selector->start();
}

#else

#include <cstdio>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

SemaphoreHandle_t xSemaphore;

void task_function(void* arg) {
    gpio_num_t gpio_num = static_cast<gpio_num_t>(reinterpret_cast<uintptr_t>(arg));
    while (true)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            // Debounce delay
            vTaskDelay(50 / portTICK_PERIOD_MS);
            if (gpio_get_level(gpio_num) == 1) continue;

            printf("Button pressed\n");
            while (gpio_get_level(gpio_num) == 0) {
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            printf("Button released\n");
        }
    }
}

void IRAM_ATTR gpio_isr_handler(void* arg) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}

extern "C" void app_main(void) {
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL) {
        printf("Semaphore incorrect\n");
        return;
    }

    xTaskCreate(task_function, "Task", 2048, (void*)GPIO_NUM_23, 10, NULL);

    gpio_config_t button_gpio_config;
    button_gpio_config.intr_type = GPIO_INTR_NEGEDGE;
    button_gpio_config.mode = GPIO_MODE_INPUT;
    button_gpio_config.pin_bit_mask = 1ULL << GPIO_NUM_23;
    button_gpio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    button_gpio_config.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&button_gpio_config);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_23, gpio_isr_handler, (void*) GPIO_NUM_23);

    // Main loop
    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay to keep the task alive
    }
}

#endif