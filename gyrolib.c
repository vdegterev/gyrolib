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
 * \file       gyrolib.c
 * \brief      Gyroscope & accelerometer function bodies.
 *
 * \version    1.0
 * \date       20.05.2016
 * \author     Victor Degterev
 *
 */

/* Includes -----------------------------------------------------------------*/
#include <string.h>
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "lptim.h"
#include "adc.h"
#include "usart.h"
#include "gyrolib.h"

/* Private constants & macros -----------------------------------------------*/

/* Private variables --------------------------------------------------------*/

/* Function bodies ----------------------------------------------------------*/

/// Writes to the specified register in the Gyroscope and returns nonzero if successfull
char gyro_wr_reg( int rg_addr, char val )
{
	//HAL_StatusTypeDef stat;
	
	if( HAL_OK == HAL_I2C_Mem_Write( &hi2c1, GYRO_SLAVE_ADDRESS, rg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&val, 1, I2C_DEFAULT_TIMEOUT ) ){
		return 1;
	}
	return 0;
}

/// Reads the specified register from the Gyroscope and returns nonzero if successfull
char gyro_rd_reg( int rg_addr, char *pval )
{
	//HAL_StatusTypeDef stat;
	
	if( HAL_OK == HAL_I2C_Mem_Read( &hi2c1, GYRO_SLAVE_ADDRESS, rg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)pval, 1, I2C_DEFAULT_TIMEOUT ) ){
		return 1;
	}
	return 0;
}

/// Puts the Gyroscope in the power down mode and returns nonzero if successfull
char gyro_power_down( void )
{
	return gyro_wr_reg( GYRO_CTRL_REG1, GYRO_CTRL1_FULL_PWROFF );
}

/// Awakes the Gyroscope from the power down mode to the full working and returns nonzero if successfull
char gyro_awake( void )
{
	return gyro_wr_reg( GYRO_CTRL_REG1, (GYRO_CTRL1_ENABLE_3AXIS | GYRO_CTRL1_PD_BIT) );
}

/// Initializes the Gyroscope and returns nonzero if successfull
char gyro_init( void )
{
	char rz;
	
	if( gyro_awake() ){
		if( gyro_rd_reg( GYRO_WHO_AM_I, &rz ) ){
			if( rz == GYRO_CHIP_ID ){
				return 1;
			}
		}
	}
	return 0;
}

/// Gets the angle speeds from the Gyroscope in micro-degrees per second and returns nonzero if successfull
char gyro_get_value( TAxisData *pval, int32_t lsb_value )
{
	int16_t buf[3];	// 2 bytes per axis, 3 axis, 2*3=6 bytes
	int rg, i;
	uint8_t *pbuf;
	
	memset( buf, 0, sizeof(buf) );
	pbuf = (uint8_t *)buf;
	rg = GYRO_OUT_X_L;
	for( i=0; i<6; i++ ){
		if( HAL_OK != HAL_I2C_Mem_Read( &hi2c1, GYRO_SLAVE_ADDRESS, rg, I2C_MEMADD_SIZE_8BIT, pbuf, 1, I2C_DEFAULT_TIMEOUT ) ){
			return 0;
		}
		++rg;
		++pbuf;
	}
	pval->ax = (int32_t)buf[0] * lsb_value;
	pval->ay = (int32_t)buf[1] * lsb_value;
	pval->az = (int32_t)buf[2] * lsb_value;
	return 1;
}

/// Gets the temperature from the Gyroscope and returns nonzero if successfull
char gyro_get_temp( int *ptemp )
{
	int8_t temp;
	
	if( HAL_OK == HAL_I2C_Mem_Read( &hi2c1, GYRO_SLAVE_ADDRESS, GYRO_OUT_TEMP, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&temp, 1, I2C_DEFAULT_TIMEOUT ) ){
		*ptemp = (int)GYRO_TEMPERATURE_BASE_LEVEL - (int)temp;
		return 1;
	}
	return 0;
}

/// Writes to the specified register in the Accelerometer and returns nonzero if successfull
char accel_wr_reg( int rg_addr, char val )
{
	//HAL_StatusTypeDef stat;
	
	if( HAL_OK == HAL_I2C_Mem_Write( &hi2c1, ACCEL_SLAVE_ADDRESS, rg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&val, 1, I2C_DEFAULT_TIMEOUT ) ){
		return 1;
	}
	return 0;
}

/// Reads the specified register from the Accelerometer and returns nonzero if successfull
char accel_rd_reg( int rg_addr, char *pval )
{
	//HAL_StatusTypeDef stat;
	
	if( HAL_OK == HAL_I2C_Mem_Read( &hi2c1, ACCEL_SLAVE_ADDRESS, rg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)pval, 1, I2C_DEFAULT_TIMEOUT ) ){
		return 1;
	}
	return 0;
}

/// Puts the Accelerometer in the power down mode and returns nonzero if successfull
char accel_power_down( void )
{
	return accel_wr_reg( ACCEL_CTRL1, ACCEL_CTRL1_FULL_PWROFF );
}

/// Awakes the Accelerometer from the power down mode to the full working and returns nonzero if successfull
char accel_awake( int data_rate )
{
	return accel_wr_reg( ACCEL_CTRL1, (ACCEL_CTRL1_ENABLE_3AXIS | data_rate) );
}

/// Initializes the Accelerometer and returns nonzero if successfull
char accel_init( int data_rate, int scale )
{
	char rz;
	
	if( !accel_awake(data_rate) ){
		return 0;
	}
	if( !accel_rd_reg( ACCEL_WHO_AM_I, &rz ) ){
		return 0;
	}
	if( rz != ACCEL_CHIP_ID ){
		return 0;
	}
	if( !accel_wr_reg( ACCEL_CTRL2, scale ) ){
		return 0;
	}
	return 1;
}

/// Gets the acceleration from the Accelerometer in micro-g and returns nonzero if successfull
char accel_get_value( TAxisData *pval, int32_t lsb_value )
{
	int16_t buf[3];	// 2 bytes per axis, 3 axis, 2*3=6 bytes
	int rg, i;
	uint8_t *pbuf;
	
	memset( buf, 0, sizeof(buf) );
	pbuf = (uint8_t *)buf;
	rg = ACCEL_OUT_X_L_A;
	for( i=0; i<6; i++ ){
		if( HAL_OK != HAL_I2C_Mem_Read( &hi2c1, ACCEL_SLAVE_ADDRESS, rg, I2C_MEMADD_SIZE_8BIT, pbuf, 1, I2C_DEFAULT_TIMEOUT ) ){
			return 0;
		}
		++rg;
		++pbuf;
	}
	pval->ax = (int32_t)buf[0] * lsb_value;
	pval->ay = (int32_t)buf[1] * lsb_value;
	pval->az = (int32_t)buf[2] * lsb_value;
	return 1;
}

/************************** (C) COPYRIGHT Victor Degterev *****END OF FILE****/
