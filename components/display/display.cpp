#include "display.h"
#include "u8g2.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

static const char *TAG = "display";

#define I2C_SDA_PIN GPIO_NUM_21
#define I2C_SCL_PIN GPIO_NUM_22
#define OLED_I2C_ADDR 0x3C

static u8g2_t u8g2;
static i2c_master_bus_handle_t i2c_bus;
static i2c_master_dev_handle_t i2c_dev;


void display_init() {
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus));

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_I2C_ADDR,
        .scl_speed_hz = 400000
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus, &dev_config, &i2c_dev));
}

