#include "bme280.h"
// We need to uncomment BME280_FLOAT_ENABLE in bme280_defs.h since we want floating points values.

// We are using I2C so we follow what's written in the readme from the API : 

int main() {
	struct bme280_dev dev;
	struct bme280_data comp_data;
	int result = -1;
	
	result = initializeBME(&dev)
	
	if(result == 0)
	{
		getBMEValues(&dev, &comp_data);
		// send value to printer
	}
	else
	{
		
	}
}

int initializeBME(struct bme280_dev *dev)
{
	int8_t rslt = BME280_OK;
	uint8_t settings_sel;
	
	dev->dev_id = BME280_I2C_ADDR_PRIM;
	dev->intf = BME280_I2C_INTF;
	dev->read = user_i2c_read;
	dev->write = user_i2c_write;
	dev->delay_ms = user_delay_ms;
	
	//Set the settings
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	rslt = bme280_init(dev);
	if(rslt != BME280_OK)
		return -1;
	
	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);
	
	if(rslt == BME280_OK)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int8_t getBMEValues(struct bme280_dev *dev, truct bme280_data *comp_data)
{
	int8_t rslt;
	
	while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_ms(70);
		rslt = bme280_get_sensor_data(BME280_ALL, comp_data, dev);
	}

	return rslt;
}