/*ds1307 low level api - Reza Ebrahimi v1.0*/
#include "rtc_ds1307.h"

/*** EXAMPLE IMPLEMENTATION ***/
#include "freertos/FreeRTOS.h"
#include "driver/i2c.h"
#include "string.h"

/*function to transmit one byte of data to register_address on ds1307*/
void time_i2c_write_single(uint8_t device_address, uint8_t register_address, uint8_t *data_byte)
{
    uint8_t array[2] = {0};
    array[0] = register_address;
    array[1] = *data_byte;
    i2c_master_write_to_device(I2C_NUM_0, device_address,
                                     &array[0], 2,
                                     pdMS_TO_TICKS(1000));
}

/*function to transmit an array of data to device_address, starting from start_register_address*/
void time_i2c_write_multi(uint8_t device_address, uint8_t start_register_address, uint8_t *data_array, uint8_t data_length)
{
    uint8_t array[data_length + 1];
    memset(&array[0],0,data_length+1);
    array[0] = start_register_address;
    memcpy(&array[1],data_array,data_length);
    i2c_master_write_to_device(I2C_NUM_0, device_address,
                                     &array[0], data_length,
                                     pdMS_TO_TICKS(1000));
}

/*function to read one byte of data from register_address on ds1307*/
void time_i2c_read_single(uint8_t device_address, uint8_t register_address, uint8_t *data_byte)
{
    i2c_master_write_read_device(I2C_NUM_0, device_address,
                                       &register_address, 1,
                                       data_byte, 1,
                                       pdMS_TO_TICKS(1000));
                                      
}

/*function to read an array of data from device_address*/
void time_i2c_read_multi(uint8_t device_address, uint8_t start_register_address, uint8_t *data_array, uint8_t data_length)
{
    i2c_master_write_read_device(I2C_NUM_0, device_address,
                                       &start_register_address, 1,
                                       data_array, data_length,
                                       pdMS_TO_TICKS(1000));
}
static esp_err_t i2c_master_driver_initialize(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .master.clk_speed = 400000,
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    return i2c_param_config(I2C_NUM_0, &conf);
}
/*function to initialize I2C peripheral in 100khz*/
void DS1307_I2C_init()
{
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    i2c_master_driver_initialize();
}
