/*
 * The following firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
 *  MA  02110-1301, USA.
 *
 * Copyright (C) VICTOR DEGTEREV
 */
/*!
 * \file       gyrolib.h
 * \brief      Gyroscope & accelerometer function prototypes and constants.
 *
 * \details The Gyroscope may only be used to determine the speed of angle change
 *			in micro-degrees per second. To get the real angle you need to know
 *			the time and the source point.
 *
 * \version    1.0
 * \date       20.05.2016
 * \author     Victor Degterev
 *
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __GYROLIB_INCLUDED__
#define __GYROLIB_INCLUDED__

/* Public constants & macros ------------------------------------------------*/
/*! \defgroup p_constants Public constants and macros

@{
*/

/*! \defgroup l3gd20_regs L3GD20 Register Addresses
	\ingroup p_constants

@{
*/
enum {
	GYRO_WHO_AM_I  = 0x0F,
	GYRO_CTRL_REG1 = 0x20,
	GYRO_CTRL_REG2 = 0x21,
	GYRO_CTRL_REG3 = 0x22,
	GYRO_CTRL_REG4 = 0x23,
	GYRO_CTRL_REG5 = 0x24,
	GYRO_REFEREBCE = 0x25,
	GYRO_OUT_TEMP  = 0x26,
	GYRO_STATUS_RG = 0x27,
	GYRO_OUT_X_L   = 0x28,
	GYRO_OUT_X_H   = 0x29,
	GYRO_OUT_Y_L   = 0x2A,
	GYRO_OUT_Y_H   = 0x2B,
	GYRO_OUT_Z_L   = 0x2C,
	GYRO_OUT_Z_H   = 0x2D,
	GYRO_FIFO_CTRL = 0x2E,
	GYRO_FIFO_SRC  = 0x2F,
	GYRO_INT1_CFG  = 0x30,
	GYRO_INT1_SRC  = 0x31,
	GYRO_INT1_THS_XH  = 0x32,
	GYRO_INT1_THS_XL  = 0x33,
	GYRO_INT1_THS_YH  = 0x34,
	GYRO_INT1_THS_YL  = 0x35,
	GYRO_INT1_THS_ZH  = 0x36,
	GYRO_INT1_THS_ZL  = 0x37,
	GYRO_INT1_DURATION = 0x38
};
///@}

/*! \defgroup lsm303_regs LSM303 Register Addresses
	\ingroup p_constants

@{
*/
enum {
	ACCEL_TEMP_OUT_L	=	0x05,
	ACCEL_TEMP_OUT_H	=	0x06,
	ACCEL_STATUS_M		=	0x07,
	ACCEL_OUT_X_L_M		=	0x08,
	ACCEL_OUT_X_H_M		=	0x09,
	ACCEL_OUT_Y_L_M		=	0x0A,
	ACCEL_OUT_Y_H_M		=	0x0B,
	ACCEL_OUT_Z_L_M		=	0x0C,
	ACCEL_OUT_Z_H_M		=	0x0D,
	ACCEL_WHO_AM_I		=	0x0F,
	ACCEL_INT_CTRL_M	=	0x12,
	ACCEL_INT_SRC_M		=	0x13,
	ACCEL_INT_THS_L_M	=	0x14,
	ACCEL_INT_THS_H_M	=	0x15,
	ACCEL_OFFSET_X_L_M	=	0x16,
	ACCEL_OFFSET_X_H_M	=	0x17,
	ACCEL_OFFSET_Y_L_M	=	0x18,
	ACCEL_OFFSET_Y_H_M	=	0x19,
	ACCEL_OFFSET_Z_L_M	=	0x1A,
	ACCEL_OFFSET_Z_H_M	=	0x1B,
	ACCEL_REFERENCE_X	=	0x1C,
	ACCEL_REFERENCE_Y	=	0x1D,
	ACCEL_REFERENCE_Z	=	0x1E,
	ACCEL_CTRL0			=	0x1F,
	ACCEL_CTRL1			=	0x20,
	ACCEL_CTRL2			=	0x21,
	ACCEL_CTRL3			=	0x22,
	ACCEL_CTRL4			=	0x23,
	ACCEL_CTRL5			=	0x24,
	ACCEL_CTRL6			=	0x25,
	ACCEL_CTRL7			=	0x26,
	ACCEL_STATUS_A		=	0x27,
	ACCEL_OUT_X_L_A		=	0x28,
	ACCEL_OUT_X_H_A		=	0x29,
	ACCEL_OUT_Y_L_A		=	0x2A,
	ACCEL_OUT_Y_H_A		=	0x2B,
	ACCEL_OUT_Z_L_A		=	0x2C,
	ACCEL_OUT_Z_H_A		=	0x2D,
	ACCEL_FIFO_CTRL		=	0x2E,
	ACCEL_FIFO_SRC		=	0x2F,
	ACCEL_IG_CFG1		=	0x30,
	ACCEL_IG_SRC1		=	0x31,
	ACCEL_IG_THS1		=	0x32,
	ACCEL_IG_DUR1		=	0x33,
	ACCEL_IG_CFG2		=	0x34,
	ACCEL_IG_SRC2		=	0x35,
	ACCEL_IG_THS2		=	0x36,
	ACCEL_IG_DUR2		=	0x37,
	ACCEL_CLICK_CFG		=	0x38,
	ACCEL_CLICK_SRC		=	0x39,
	ACCEL_CLICK_THS		=	0x3A,
	ACCEL_TIME_LIMIT	=	0x3B,
	ACCEL_TIME_LATENCY	=	0x3C,
	ACCEL_TIME_WINDOW	=	0x3D,
	ACCEL_ACT_THS		=	0x3E,
	ACCEL_ACT_DUR		=	0x3F
};
///@}

#define ACCEL_SLAVE_ADDRESS	0x3A	///< LSM303 I2C Address
#define GYRO_SLAVE_ADDRESS	0xD6	///< L3GD20 I2C Address
#define I2C_DEFAULT_TIMEOUT	35		///< I2C default timeout in ms that need to transfer some bytes

/*! \defgroup l3gd20_consts L3GD20 Register Constants
	\ingroup p_constants

@{
*/
#define GYRO_CTRL1_ENABLE_3AXIS		0x07	///< L3GD20 CTRL_REG1 bits: set to enable X, Y and Z axis
#define GYRO_CTRL1_PD_BIT			0x08	///< L3GD20 CTRL_REG1 bits: set to exit from power down mode
#define GYRO_CTRL1_FULL_PWROFF		0x00	///< L3GD20 CTRL_REG1 bits: clear reg to disable the Gyro

#define GYRO_CHIP_ID	0xD4	///< L3GD20 Device identification value
#define ACCEL_CHIP_ID	0x49	///< LSM303 Device identification value

#define GYRO_CTRL4_BDU_BIT			0x80	///< L3GD20 CTRL_REG4 bits: Set to 0 to disable block data update (default)
#define GYRO_CTRL4_BLE_BIT			0x40	///< L3GD20 CTRL_REG4 bits: Set to 1 to enable big endian data format (default)
#define GYRO_CTRL4_SCALE_250DPS		0x00	///< L3GD20 CTRL_REG4 bits: 250 dps scale selection (default)
#define GYRO_CTRL4_SCALE_500DPS		0x10	///< L3GD20 CTRL_REG4 bits: 500 dps scale selection
#define GYRO_CTRL4_SCALE_2000DPS	0x20	///< L3GD20 CTRL_REG4 bits: 2000 dps scale selection

#define GYRO_250DPS_LSB_VALUE_UDPS	8750	///< L3GD20 one bit scale in micro-degrees per second with 250 dps scale
#define GYRO_500DPS_LSB_VALUE_UDPS	17500	///< L3GD20 one bit scale in micro-degrees per second with 500 dps scale
#define GYRO_2000DPS_LSB_VALUE_UDPS	70000	///< L3GD20 one bit scale in micro-degrees per second with 2000 dps scale

#define GYRO_TEMPERATURE_BASE_LEVEL	40	///< L3GD20 temperature base level to calculate the real temperature outside the chip

#define ACCEL_CTRL1_ENABLE_3AXIS	0x07	///< LSM303 CTRL1 bits: set to enable X, Y and Z axis
#define ACCEL_CTRL1_BDU_BIT			0x08	///< LSM303 CTRL1 bits: Set to 0 to disable block data update (default)
#define ACCEL_CTRL1_FULL_PWROFF		0x00	///< LSM303 CTRL1 bits: clear reg to disable the Accelerometer
#define ACCEL_CTRL1_DATARATE_3_125	0x10	///< LSM303 CTRL1 bits: Data rate 3.125 Hz
#define ACCEL_CTRL1_DATARATE_6_25	0x20	///< LSM303 CTRL1 bits: Data rate 6.25 Hz
#define ACCEL_CTRL1_DATARATE_12_5	0x30	///< LSM303 CTRL1 bits: Data rate 12.5 Hz
#define ACCEL_CTRL1_DATARATE_25		0x40	///< LSM303 CTRL1 bits: Data rate 25 Hz
#define ACCEL_CTRL1_DATARATE_50		0x50	///< LSM303 CTRL1 bits: Data rate 50 Hz
#define ACCEL_CTRL1_DATARATE_100	0x60	///< LSM303 CTRL1 bits: Data rate 100 Hz
#define ACCEL_CTRL1_DATARATE_200	0x70	///< LSM303 CTRL1 bits: Data rate 200 Hz
#define ACCEL_CTRL1_DATARATE_400	0x80	///< LSM303 CTRL1 bits: Data rate 400 Hz
#define ACCEL_CTRL1_DATARATE_800	0x90	///< LSM303 CTRL1 bits: Data rate 800 Hz
#define ACCEL_CTRL1_DATARATE_1600	0xA0	///< LSM303 CTRL1 bits: Data rate 1600 Hz

#define ACCEL_CTRL2_SCALE_2G		0x00	///< LSM303 CTRL2 bits: Acceleration ful scale is +/-2g
#define ACCEL_CTRL2_SCALE_4G		0x08	///< LSM303 CTRL2 bits: Acceleration ful scale is +/-4g
#define ACCEL_CTRL2_SCALE_6G		0x10	///< LSM303 CTRL2 bits: Acceleration ful scale is +/-6g
#define ACCEL_CTRL2_SCALE_8G		0x18	///< LSM303 CTRL2 bits: Acceleration ful scale is +/-8g
#define ACCEL_CTRL2_SCALE_16G		0x20	///< LSM303 CTRL2 bits: Acceleration ful scale is +/-16g

#define ACCEL_SCALE_2G_LSB_VALUE_UG		61	///< LSM303 LSB value in micro-g for 2g scale
#define ACCEL_SCALE_4G_LSB_VALUE_UG		122	///< LSM303 LSB value micro-g for 4g scale
#define ACCEL_SCALE_6G_LSB_VALUE_UG		183	///< LSM303 LSB value micro-g for 6g scale
#define ACCEL_SCALE_8G_LSB_VALUE_UG		244	///< LSM303 LSB value micro-g for 8g scale
#define ACCEL_SCALE_16G_LSB_VALUE_UG	488	///< LSM303 LSB value micro-g for 16g scale
///@}

///@}

/*! \defgroup p_types Public types and structures

@{
*/
/// 3-Axis speed/acceleration data
typedef struct {
	int32_t ax;
	int32_t ay;
	int32_t az;
} TAxisData;
///@}

/*! \defgroup f_protos Public function prototypes

@{
*/

/// Initializes the Gyroscope and returns nonzero if successfull
char gyro_init( void );
/// Writes to the specified register in the Gyroscope and returns nonzero if successfull
char gyro_wr_reg( int rg_addr, char val );
/// Reads the specified register from the Gyroscope and returns nonzero if successfull
char gyro_rd_reg( int rg_addr, char *pval );
/// Puts the Gyroscope in the power down mode and returns nonzero if successfull
char gyro_power_down( void );
/// Awakes the Gyroscope from the power down mode to the full working and returns nonzero if successfull
char gyro_awake( void );
/// Gets the angle speeds from the Gyroscope in micro-degrees per second and returns nonzero if successfull
char gyro_get_value( TAxisData *pval, int32_t lsb_value );
/// Gets the temperature from the Gyroscope and returns nonzero if successfull
char gyro_get_temp( int *ptemp );

/// Initializes the Accelerometer and returns nonzero if successfull
char accel_init( int data_rate, int scale );
/// Writes to the specified register in the Accelerometer and returns nonzero if successfull
char accel_wr_reg( int rg_addr, char val );
/// Reads the specified register from the Accelerometer and returns nonzero if successfull
char accel_rd_reg( int rg_addr, char *pval );
/// Puts the Accelerometer in the power down mode and returns nonzero if successfull
char accel_power_down( void );
/// Awakes the Accelerometer from the power down mode to the full working and returns nonzero if successfull
char accel_awake( int data_rate );
/// Gets the acceleration from the Accelerometer in micro-g and returns nonzero if successfull
char accel_get_value( TAxisData *pval, int32_t lsb_value );

///@}

#endif // __GYROLIB_INCLUDED__
