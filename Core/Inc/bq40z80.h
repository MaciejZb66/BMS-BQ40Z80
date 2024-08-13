#ifndef __BQ40Z80_H
#define __BQ40Z80_H

// struct bq40z80_battery_status
// {
//     bool OCA, TCA, OTA, TDA, RCA, RTA, INIT, DSG, FC, FD, EC3, EC2, EC1, EC0;
// };

#ifdef __cplusplus
extern "C"
{
#endif
#include <string.h>
#include "bq40z80_sbs.h"
#include "bq40z80_mfa.h"
#include "bq40z80_registers.h"
#include "main.h"
//#include "driver/i2c.h"
//#include "esp_log.h"


#define I2C_MASTER_FREQ_HZ 50000    /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_TICK 100
#define BQ40Z80_ADDRESS 0x0b
//    class BQ40Z80
//    {
//    public:

        /**
         * @brief Initlize the I2C bus
         * @param i2c_scl_io GPIO number used for I2C master clock
         * @param i2c_sda_io GPIO number used for I2C master data
         * @param i2c_master_num I2C master i2c port number,
         *                       the number of i2c peripheral interfaces available will depend on the chip,
         *                       such as I2C_NUM_0
         * @param device_address 7-bit address of BQ40Z80 chip, default to 0x0b
         */
        void BQ40Z80_init(uint8_t i2c_scl_io, uint8_t i2c_sda_io,  I2C_HandleTypeDef* hi2c, uint8_t device_address);

//        ~BQ40Z80();

        /**
         * @brief Get the BatteryMode (0x03)
         * @return 16-bit value of BatteryStatus
         */
        uint16_t get_battery_mode(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Set the BatteryMode (0x03)
         * @param val 16-bit value of BatteryStatus
         */
        void set_battery_mode(uint16_t val, I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the temperature of device (0x08)
         * @note The source of this temperature is configured by DataFlash, see TRM
         * @return temperature, unit: 0.1 degree celsius
         */
        uint16_t get_temperature(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the battery voltage (0x09)
         * @return voltage, unit: millivolts
         */
        uint16_t get_voltage(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the battery current (0x0A)
         * @return voltage, unit: milliamps
         */
        uint16_t get_current(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the relative state of charge(RSOC) (0x0D)
         * @note RSOC is the predicted remaining battery capacity as a percentage of FCC
         * @return RSOC value, unit: percantage
         */
        uint8_t get_rsoc(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the predicted remaining battery capacity (0x0F)
         * @note If BatteryMode()[CAPM] = 0, then the data reports in mAh.
         *       If BatteryMode()[CAPM] = 1, then the data reports in cWh.
         * @return Remaining capacity value of battery, unit: mAh/cWh
         */
        uint16_t get_remaining_capacity(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the full charge capacity(FCC) (0x10)
         * @note FCC is the predicted battery capacity when fully charged
         *       If BatteryMode()[CAPM] = 0, then the data reports in mAh.
         *       If BatteryMode()[CAPM] = 1, then the data reports in cWh.
         * @return Full charge capacity, unit: mAh/cWh
         */
        uint16_t get_full_charge_capacity(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the predicted remaining battery capacity based on AverageCurrent (0x12)
         * @return average time to empty, return 65535 if battery is not being discharged. unit: minutes
         */
        uint16_t get_average_time_to_empty(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the predicted time-to-full charge based on AverageCurrent (0x13)
         * @return average time to full, return 65535 if battery is not being charged. unit: minutes
         */
        uint16_t get_average_time_to_full(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the number of discharge cycles the battery has experienced (0x17)
         * @return Cycle count of battery
         */
        uint16_t get_cycle_count(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the the theoretical pack capacity (0x18)
         * @note If BatteryMode()[CAPM] = 0, then the data reports in mAh.
         *       If BatteryMode()[CAPM] = 1, then the data reports in cWh.
         * @return Design capacity value of battery, unit: mAh/cWh
         */
        uint16_t get_design_capacity(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the the theoretical pack voltage (0x19)
         * @return Design voltage value of battery, unit: mV
         */
        uint16_t get_design_voltage(I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read the voltage of single cell
         * @param cell cell number, from 1 to 7
         * @return Voltage value of the specified cell, unit: mV
         */
        uint16_t get_cell_voltage(uint8_t cell, I2C_HandleTypeDef* hi2c);

        /**
         * @brief Set the BatteryMode(0x03)[CAPM]
         * @note If [CAPM] = 0, then the FCC and RC data reports in mAh.
         *       If [CAPM] = 1, then the FCC and RC data reports in cWh.
         * @param val bool value of CAPM bit
         */
        void set_capm(bool val, I2C_HandleTypeDef* hi2c);

        void read_da_status_1(DA_STATUS_1 *buf, I2C_HandleTypeDef* hi2c);

        void read_da_status_3(DA_STATUS_3 *buf, I2C_HandleTypeDef* hi2c);

//    private:
//        i2c_port_t I2C_MASTER_NUM;
//        uint8_t DEVICE_ADDRESS;

        /**
         * @brief Read a two-byte word from the device using SMBus
         * @category Basic SMBus operation
         * @note The data received over I2C is in little-endian format (with the low byte first).
         *       The data in the 'data' buffer is in big-endian format (with the low byte last).
         * @param reg_addr 8-bit register address or SBS Command
         * @param data Data buffer to store the read data
         * @return Error code
         */
        HAL_StatusTypeDef smbus_read_word(uint8_t reg_addr, uint16_t *data, I2C_HandleTypeDef* hi2c);

        /**
         * @brief Write a two-byte word to the device using SMBus
         * @category Basic SMBus operation
         * @note The data to be sent over I2C is in little-endian format (with the low byte first).
         *       The data in the 'data' buffer is in big-endian format (with the low byte last).
         * @param reg_addr 8-bit register address or SBS Command
         * @param data Data to be written
         * @return Error code
         */
        HAL_StatusTypeDef smbus_write_word(uint8_t reg_addr, uint16_t data, I2C_HandleTypeDef* hi2c);

        /**
         * @brief Read a block from the device using SMBus
         * @category Basic SMBus operation
         * @note The order of bytes transmitted on the I2C bus follows the increasing index order of the 'data' array
         * @param reg_addr 8-bit register address or SBS Command
         * @param data Data buffer to store the read data
         * @param len Length of data
         * @return Error code,
         */
        HAL_StatusTypeDef smbus_read_block(uint8_t reg_addr, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c);

        /**
         * @brief Write a block to the device using SMBus
         * @category Basic SMBus operation
         * @note The order of bytes transmitted on the I2C bus follows the increasing index order of the 'data' array
         * @param reg_addr 8-bit register address or SBS Command
         * @param data Data to be written
         * @param len Length of data
         * @return Error code
         */
        HAL_StatusTypeDef smbus_write_block(uint8_t reg_addr, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c);

        HAL_StatusTypeDef mfa_read_block(uint16_t mfa_command, uint8_t *data, uint8_t len, I2C_HandleTypeDef* hi2c);
//    };

#ifdef __cplusplus
}
#endif
#endif
