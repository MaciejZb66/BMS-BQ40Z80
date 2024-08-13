
#ifdef __cplusplus
extern "C"
{
#endif

#include <bq40z80.h>

    void BQ40Z80_init(uint8_t i2c_scl_io, uint8_t i2c_sda_io, I2C_HandleTypeDef* hi2c, uint8_t device_address)
    {
    	HAL_SMBUS_Init(hi2c);

//    	device_adress = 0x0b;
//        this->DEVICE_ADDRESS = device_address;
//        this->I2C_MASTER_NUM = i2c_master_num;
//
//        smbus_config_t conf;
//        conf.mode = I2C_MODE_MASTER;
//        conf.sda_io_num = i2c_sda_io;
//        conf.scl_io_num = i2c_scl_io;
//        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
//        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
//        conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
//        conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;
//
//        ESP_ERROR_CHECK(i2c_param_config(i2c_master_num, &conf));
//
//        ESP_ERROR_CHECK(i2c_driver_install(i2c_master_num, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));
    }

//    BQ40Z80::~BQ40Z80()
//    {
//        i2c_driver_delete(this->I2C_MASTER_NUM);
//    }

    /***************************** Public Functions *****************************/
    uint16_t get_battery_mode(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_BatteryMode, &buf, hi2c);
        return buf;
    }

    void set_battery_mode(uint16_t val, I2C_HandleTypeDef* hi2c)
    {
        smbus_write_word(BQ40Z80_SBS_BatteryMode, val, hi2c);
        // this->update_basic_info();
    }

    uint16_t get_temperature(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_Current, &buf, hi2c);
        return buf - 2732; // raw data unit: 0.1 Kelvin
    }

    uint16_t get_voltage(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_Voltage, &buf, hi2c);
        return buf;
    }

    uint16_t get_current(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_Current, &buf, hi2c);
        return buf;
    }

    uint8_t get_rsoc(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_RelativeStateOfCharge, &buf, hi2c);
        return buf;
    }

    uint16_t get_remaining_capacity(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_RemainingCapacity, &buf, hi2c);
        return buf;
    }

    uint16_t get_full_charge_capacity(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_FullChargeCapacity, &buf, hi2c);
        return buf;
    }

    uint16_t get_average_time_to_empty(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_AverageTimeToEmpty, &buf, hi2c);
        return buf;
    }

    uint16_t get_average_time_to_full(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_AverageTimeToFull, &buf, hi2c);
        return buf;
    }

    uint16_t get_cycle_count(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_CycleCount, &buf, hi2c);
        return buf;
    }

    uint16_t get_design_capacity(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_DesignCapacity, &buf, hi2c);
        return buf;
    }

    uint16_t get_design_voltage(I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf;
        smbus_read_word(BQ40Z80_SBS_DesignVoltage, &buf, hi2c);
        return buf;
    }

    uint16_t get_cell_voltage(uint8_t cell, I2C_HandleTypeDef* hi2c)
    {
        assert(1 <= cell && cell <= 7); //!< range check

        if (cell <= 4)
        {
            DA_STATUS_1 da_status_1_data;
            read_da_status_1(&da_status_1_data, hi2c);
            switch (cell)
            {
            case 1:
                return da_status_1_data.cell_voltage_1;
                break;
            case 2:
                return da_status_1_data.cell_voltage_2;
                break;
            case 3:
                return da_status_1_data.cell_voltage_3;
                break;
            case 4:
                return da_status_1_data.cell_voltage_4;
            default:
                break;
            }
        }
        else
        {
            DA_STATUS_3 da_status_3_data;
            read_da_status_3(&da_status_3_data, hi2c);
            switch (cell)
            {
            case 5:
                return da_status_3_data.cell_voltage_5;
                break;
            case 6:
                return da_status_3_data.cell_voltage_6;
                break;
            case 7:
                return da_status_3_data.cell_voltage_7;
                break;
            default:
                break;
            }
        }
        return 0;
    }

    void set_capm(bool val, I2C_HandleTypeDef* hi2c)
    {
        uint16_t buf = get_battery_mode(hi2c);
        if (val){
            buf |= 0x8000;
        }else{
            buf &= 0x7fff;
        }
        set_battery_mode(buf, hi2c);
    }

    void read_da_status_1(DA_STATUS_1 *data, I2C_HandleTypeDef* hi2c)
    {
        uint8_t buf[32];

        mfa_read_block(BQ40Z80_MFA_DA_STATUS_1, buf, 32, hi2c);

        data->cell_voltage_1 = (buf[1] << 8) | buf[0];
        data->cell_voltage_2 = (buf[3] << 8) | buf[2];
        data->cell_voltage_3 = (buf[5] << 8) | buf[4];
        data->cell_voltage_4 = (buf[7] << 8) | buf[6];
        data->bat_voltage = (buf[9] << 8) | buf[8];
        data->pack_voltage = (buf[11] << 8) | buf[10];
        data->cell_current_1 = (buf[13] << 8) | buf[12];
        data->cell_current_2 = (buf[15] << 8) | buf[14];
        data->cell_current_3 = (buf[17] << 8) | buf[16];
        data->cell_current_4 = (buf[19] << 8) | buf[18];
        data->cell_power_1 = (buf[21] << 8) | buf[20];
        data->cell_power_2 = (buf[23] << 8) | buf[22];
        data->cell_power_3 = (buf[25] << 8) | buf[24];
        data->cell_power_4 = (buf[27] << 8) | buf[26];
        data->power = (buf[29] << 8) | buf[28];
        data->average_power = (buf[31] << 8) | buf[30];

        return;
    }

    void read_da_status_3(DA_STATUS_3 *data, I2C_HandleTypeDef* hi2c)
    {
        uint8_t buf[18];

        mfa_read_block(BQ40Z80_MFA_DA_STATUS_3, buf, 18, hi2c);

        data->cell_voltage_5 = (buf[1] << 8) | buf[0];
        data->cell_current_5 = (buf[3] << 8) | buf[2];
        data->cell_power_5 = (buf[5] << 8) | buf[4];
        data->cell_voltage_6 = (buf[7] << 8) | buf[6];
        data->cell_current_6 = (buf[9] << 8) | buf[8];
        data->cell_power_6 = (buf[11] << 8) | buf[10];
        data->cell_voltage_7 = (buf[13] << 8) | buf[12];
        data->cell_current_7 = (buf[15] << 8) | buf[14];
        data->cell_power_7 = (buf[17] << 8) | buf[16];

        return;
    }

    /***************************** Private Functions *****************************/

    HAL_StatusTypeDef smbus_read_word(uint8_t reg_addr, uint16_t *data, I2C_HandleTypeDef* hi2c)
    {
    	HAL_StatusTypeDef err;
        uint8_t buf[2];
        err = HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS << 1, &reg_addr, 1, 100);
//        HAL_Delay(3);
		if(err == HAL_OK){
			err = HAL_I2C_Master_Receive(hi2c, BQ40Z80_ADDRESS << 1, buf, 2, 100);
		}
//        err = i2c_master_write_read_device(I2C_MASTER_NUM, DEVICE_ADDRESS, &reg_addr, 1, buf, 2, I2C_MASTER_TIMEOUT_TICK);

        *data = (buf[1] << 8) | buf[0];

        return err;
    }

    HAL_StatusTypeDef smbus_write_word(uint8_t reg_addr, uint16_t data, I2C_HandleTypeDef* hi2c)
    {
        HAL_StatusTypeDef err;
        uint8_t buf[2];
        buf[0] = data & 0x00FF;
        buf[1] = data >> 8;

//        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//        i2c_master_start(cmd);
// ?       HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS, (BQ40Z80_ADDRESS << 1), 1, SMBUS_FIRST_FRAME);
//        i2c_master_write_byte(cmd, (DEVICE_ADDRESS << 1) | I2C_MASTER_WRITE, true);
        HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS << 1, &reg_addr, 1, 100);
//        i2c_master_write_byte(cmd, reg_addr, true);
        err = HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS << 1, buf, 2, 100);
//        i2c_master_write(cmd, buf, 2, true);
//        i2c_master_stop(cmd);

//        err = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
//        i2c_cmd_link_delete(cmd);

        return err;
    }

    HAL_StatusTypeDef smbus_read_block(uint8_t reg_addr, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c)
    {
        HAL_StatusTypeDef err;
        uint8_t slave_len = 0;
        err = HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS << 1, &reg_addr, 1, 100);
        if (err != HAL_OK) {
            return err;
        }

        err = HAL_I2C_Master_Receive(hi2c, BQ40Z80_ADDRESS << 1, &slave_len, 1, 100);
        if (err != HAL_OK) {
            return err;
        }
        err = HAL_I2C_Master_Receive(hi2c, BQ40Z80_ADDRESS << 1, data, slave_len, 100);
        return err;
    }

    HAL_StatusTypeDef smbus_write_block(uint8_t reg_addr, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c)
    {
        HAL_StatusTypeDef err;
        uint8_t buffer[256];
        buffer[0] = reg_addr;
        buffer[1] = len;
        memcpy(&buffer[2], data, len);
        err = HAL_I2C_Master_Transmit(hi2c, BQ40Z80_ADDRESS << 1, buffer, len + 2, 100);

//        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//        i2c_master_start(cmd);
//        i2c_master_write_byte(cmd, (DEVICE_ADDRESS << 1) | I2C_MASTER_WRITE, true);
//        i2c_master_write_byte(cmd, reg_addr, true);
//        i2c_master_write_byte(cmd, len, true);
//        i2c_master_write(cmd, data, len, true);
//        i2c_master_stop(cmd);
//
//        err = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
//        i2c_cmd_link_delete(cmd);

        return err;
    }

    HAL_StatusTypeDef mfa_read_block(uint16_t mfa_command, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c)
    {
        HAL_StatusTypeDef err;
        uint8_t command[2];
        command[0] = mfa_command & 0x00ff;
        command[1] = mfa_command >> 8;
        err = smbus_write_block(BQ40Z80_SBS_ManufacturerBlockAccess, command, 2, hi2c);
        if (err != HAL_OK)
            return err;

        err = smbus_read_block(BQ40Z80_SBS_ManufacturerData, data, len, hi2c);
        return err;
    }

#ifdef __cplusplus
}
#endif
