/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file lcd1602.h
 * @author Kumka, Potoczek
 * @date Jan 2021
 * @brief File containing declarations for lcd1602
 * @ver 0.1
 */
 
#ifndef LCD1602_H
#define LCD1602_H

#include "frdm_bsp.h"
#include "i2c.h"
#include "stdio.h"

/**
 * @brief LCD1602 initialization.
 */
void LCD1602_Init(void);
/**
 * @brief Print on the display.
 *
 * @param String to display.
 */
void LCD1602_Print(const char *str);
/**
 * @brief Print number on the display.
 *
 * @param Number to display.
 */
void LCD1602_PrintNum(int number);
/**
 * @brief Clear whole display.
 */
void LCD1602_ClearAll(void);
/**
 * @brief Set cursor on display.
 *
 * @param Column.
 * @param Row.
 */
void LCD1602_SetCursor(uint8_t col, uint8_t row);
/**
 * @brief Backlight turn on/off.
 *
 * @param State of the backlight.
 */
void LCD1602_Backlight(uint8_t state);

#endif  /* LCD1602_H */
