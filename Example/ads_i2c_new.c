
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"


#include "rtc_ds1307.h"
#ifndef ESP_I2C_NEW
    #include "driver/i2c.h"
#else
    #include "driver/i2c_master.h"
    static i2c_master_bus_handle_t bus_handle;
static i2c_master_bus_config_t bus_conf;

#endif



void app_main(void)
{
printf("hello world");

    #ifndef ESP_I2C_NEW
        i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
        i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = GPIO_NUM_21,
            .scl_io_num = GPIO_NUM_22,
            .master.clk_speed = 400000,
        };
    i2c_param_config(I2C_NUM_0, &conf);
    #else
        bus_conf.i2c_port = I2C_NUM_0;
        bus_conf.scl_io_num = GPIO_NUM_22;
        bus_conf.sda_io_num = GPIO_NUM_21;
        bus_conf.clk_source = I2C_CLK_SRC_DEFAULT;
        bus_conf.flags.enable_internal_pullup = true;
        i2c_new_master_bus(&bus_conf, &bus_handle);
        DS1307_custom(bus_handle);

    #endif
    DS1307_I2C_init();
    uint8_t arr[8] = {0};
    DS1307_read(TIME,&arr[0]);
    int iterant = 0;
    for(iterant = 0 ; iterant < sizeof(arr); iterant++){
        printf("%d :",arr[iterant]);
    }
    printf("\n");
}
