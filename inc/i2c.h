/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file i2c.h
 * @author Kumka, Potoczek
 * @date Jan 2021
 * @brief File containing declarations for i2c
 * @ver 0.1
 */
 
#ifndef I2C_H
#define I2C_H

#include "frdm_bsp.h"

/**
 * @brief I2C initialization.
 */
void I2C_Init(void);
/**
 * @brief I2C write operation.
 *
 * @param Address.
 * @param Data.
 */
uint8_t I2C_Write(uint8_t address, uint8_t data);
	
#endif /* I2C_H */
