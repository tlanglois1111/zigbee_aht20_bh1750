| Supported Targets | ESP32-C6 | ESP32-H2 |
| ----------------- | -------- | -------- |

# Zigbee AHT20 and BH1750 multi sensor example

The ESP Zigbee SDK provides more examples and tools for productization:
* [ESP Zigbee SDK Docs](https://docs.espressif.com/projects/esp-zigbee-sdk)
* [ESP Zigbee SDK Repo](https://github.com/espressif/esp-zigbee-sdk)

## Hardware Required

* One development board with ESP32-H2 or C6 SoC acting as Zigbee end-device
* an AHT20 and BH1750 sensor connected to I2C bus of ESP32
* A USB cable for power supply and programming

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py --preview set-target TARGET` command.
By default the I2C ports are SCL 22, SDA 23. Edit i2c_driver.h to change the defaults.

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)



