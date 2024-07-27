/*
 
 */

#include "bh1750_sensor_driver.h"
#include "i2c_driver.h"

#include "esp_err.h"
#include "esp_check.h"
#include "bh1750.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static bh1750_handle_t bh1750 = NULL;

/**
 * @brief:
 * This example code shows how to configure aht20 sensor.
 *
 * @note:
 * The callback will be called with updated temperature and humidity sensor values every $interval seconds.
 *
 */

/* call back function pointer */
static bh1750_sensor_callback_t func_ptr;
/* update interval in seconds */
static uint16_t interval = 1;

static const char *TAG = "ESP_BH1750_SENSOR_DRIVER";

static esp_err_t esp_bh1750_create(void) {
    bh1750 = bh1750_create(0, BH1750_I2C_ADDRESS_DEFAULT);

    if (bh1750 == NULL) {
        ESP_LOGI(TAG, "%-20s", "bh1750 is null ");
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief Tasks for updating the sensor value
 *
 * @param arg      Unused value.
 */
static void bh1750_sensor_driver_value_update(void *arg) {
    for (;;) {
        bh1750_measure_mode_t cmd_measure;
        float bh1750_data;

        // get data 
        cmd_measure = BH1750_CONTINUE_1LX_RES;
        ESP_ERROR_CHECK(bh1750_set_measure_mode(bh1750, cmd_measure));
        vTaskDelay(30 / portTICK_PERIOD_MS);

        ESP_ERROR_CHECK(bh1750_get_data(bh1750, &bh1750_data));

        if (func_ptr) {
            func_ptr(bh1750_data);
        }
        vTaskDelay(pdMS_TO_TICKS(interval * 1000));
    }
}

/**
 * @brief init temperature sensor
 *
 * @param config      pointer of temperature sensor config.
 */
static esp_err_t bh1750_sensor_init() {
    ESP_ERROR_CHECK(esp_bh1750_create());
    ESP_ERROR_CHECK(bh1750_power_on(bh1750));

    if (bh1750 == NULL) {
        ESP_LOGI(TAG, "bh1750 is null!");
        return ESP_FAIL;
    }
    return (xTaskCreate(bh1750_sensor_driver_value_update, "bh1750_update", 2048, NULL, 10, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t bh1750_driver_init(uint16_t update_interval,
                             bh1750_sensor_callback_t cb) {

    esp_err_t ret = bh1750_sensor_init();
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "%-20s: %s", "bh1750 error: ", esp_err_to_name(ret));
        return ret;
    }
    func_ptr = cb;
    interval = update_interval;
    return ESP_OK;
}
