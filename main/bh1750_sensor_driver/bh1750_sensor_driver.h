/*
 
 */
#include "esp_err.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** Temperature sensor callback
 *
 * @param[in] temperature temperature value in degrees Celsius and humidity from sensor
 *
 */
typedef void (*bh1750_sensor_callback_t)(float luminosity);

/**
 * @brief init function for temp sensor and callback setup
 *
 * @param config                pointer of temperature sensor config.
 * @param update_interval       sensor value update interval in seconds.
 * @param cb                    callback pointer.
 *
 * @return ESP_OK if the driver initialization succeed, otherwise ESP_FAIL.
 */
esp_err_t bh1750_driver_init(uint16_t update_interval, bh1750_sensor_callback_t cb);

#ifdef __cplusplus
} // extern "C"
#endif
