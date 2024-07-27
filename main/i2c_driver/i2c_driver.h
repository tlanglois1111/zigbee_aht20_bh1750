/*
 
 */

#include "esp_err.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_I2C_MASTER_SCL GPIO_NUM_22  /*!< gpio number for I2C master clock */
#define CONFIG_I2C_MASTER_SDA GPIO_NUM_23  /*!< gpio number for I2C master data  */

esp_err_t i2c_init();

#ifdef __cplusplus
} // extern "C"
#endif
