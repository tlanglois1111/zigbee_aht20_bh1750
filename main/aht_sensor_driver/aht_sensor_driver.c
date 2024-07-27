/*
 
 */

#include "aht_sensor_driver.h"
#include "i2c_driver.h"

#include "esp_err.h"
#include "esp_check.h"
#include "aht20.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static aht20_dev_handle_t aht20 = NULL;

/**
 * @brief:
 * This example code shows how to configure aht20 sensor.
 *
 * @note:
 * The callback will be called with updated temperature and humidity sensor values every $interval seconds.
 *
 */

/* call back function pointer */
static aht_sensor_callback_t func_ptr;
/* update interval in seconds */
static uint16_t interval = 1;

static const char *TAG = "ESP_AHT20_SENSOR_DRIVER";


static esp_err_t aht20_create(void) {
    aht20_i2c_config_t aht20_conf = {
        .i2c_port = 0,
        .i2c_addr = AHT20_ADDRRES_0,
    };

    esp_err_t ret = aht20_new_sensor(&aht20_conf, &aht20);
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "%-20s: %s", "I2C aht20 error: ", esp_err_to_name(ret));
    }
    return ret;
}

/**
 * @brief Tasks for updating the sensor value
 *
 * @param arg      Unused value.
 */
static void aht_sensor_driver_value_update(void *arg) {
    for (;;) {
        uint32_t temperature_raw;
        uint32_t humidity_raw;
        float temperature;
        float humidity;

        ESP_ERROR_CHECK(aht20_read_temperature_humidity(aht20, &temperature_raw, &temperature, &humidity_raw, &humidity));
 
        if (func_ptr) {
            func_ptr(temperature, humidity);
        }
        vTaskDelay(pdMS_TO_TICKS(interval * 1000));
    }
}

/**
 * @brief init temperature sensor
 *
 * @param config      pointer of temperature sensor config.
 */
static esp_err_t aht_sensor_init() {
    ESP_ERROR_CHECK(aht20_create());
    if (aht20 == NULL) {
        ESP_LOGI(TAG, "aht20 is null!");
        return ESP_FAIL;
    }
    return (xTaskCreate(aht_sensor_driver_value_update, "aht20_update", 2048, NULL, 10, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t aht_driver_init(uint16_t update_interval,
                             aht_sensor_callback_t cb) {

    esp_err_t ret = aht_sensor_init();
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "%-20s: %s", "I2C error: ", esp_err_to_name(ret));
        return ret;
    }
    func_ptr = cb;
    interval = update_interval;
    return ESP_OK;
}
