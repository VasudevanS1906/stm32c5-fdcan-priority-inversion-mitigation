/**
 ******************************************************************************
 * @file    stm32c5_fdcan_anti_inversion.h
 * @author  Vasudevan Swornampillai
 * @brief   Software mitigation for STM32C5 FDCAN Tx FIFO priority inversion
 *          described in ES0676 Section 2.13.2.
 *
 * Copyright (c) 2026 Vasudevan Swornampillai
 *
 * Licensed under the MIT License.
 * You may obtain a copy of the License at:
 *
 * https://opensource.org/licenses/MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files, to deal
 * in the Software without restriction, subject to the conditions of the
 * MIT License.
 *
 ******************************************************************************
 */

#ifndef STM32C5_FDCAN_ANTI_INVERSION_H
#define STM32C5_FDCAN_ANTI_INVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32c5xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/*===========================================================================
 * Configuration
 *===========================================================================*/

/**
 * @brief Default transmission timeout in milliseconds.
 */
#define FDCAN_AI_TX_TIMEOUT_MS    (10U)

/**
 * @brief Router operating status.
 */
typedef enum
{
    FDCAN_AI_OK = 0,
    FDCAN_AI_ERROR,
    FDCAN_AI_TIMEOUT,
    FDCAN_AI_INVALID_PARAM
} FDCAN_AI_Status_t;

/*===========================================================================
 * Router Context
 *===========================================================================*/

/**
 * @brief Router state object.
 */
typedef struct
{
    FDCAN_HandleTypeDef *hfdcan;

    uint32_t tx_buffer_a;
    uint32_t tx_buffer_b;

    uint32_t active_buffer;

    uint32_t successful_tx_count;

    uint32_t timeout_count;

    uint32_t error_count;

} FDCAN_AntiInversion_t;

/*===========================================================================
 * Public API
 *===========================================================================*/

/**
 * @brief Initialize anti-inversion router.
 *
 * @param router Pointer to router context.
 * @param hfdcan Pointer to initialized FDCAN handle.
 * @param buffer_a First dedicated TX buffer.
 * @param buffer_b Second dedicated TX buffer.
 *
 * @return HAL status.
 */
HAL_StatusTypeDef FDCAN_AntiInversion_Init(
    FDCAN_AntiInversion_t *router,
    FDCAN_HandleTypeDef *hfdcan,
    uint32_t buffer_a,
    uint32_t buffer_b);

/**
 * @brief Transmit frame through controlled dedicated-buffer path.
 *
 * @param router Pointer to router context.
 * @param txHeader CAN Tx header.
 * @param txData Payload buffer.
 *
 * @return HAL status.
 */
HAL_StatusTypeDef FDCAN_AntiInversion_Transmit(
    FDCAN_AntiInversion_t *router,
    FDCAN_TxHeaderTypeDef *txHeader,
    const uint8_t *txData);

/**
 * @brief Reset diagnostics counters.
 *
 * @param router Pointer to router context.
 */
void FDCAN_AntiInversion_ResetStats(
    FDCAN_AntiInversion_t *router);

/**
 * @brief Get successful transmission count.
 *
 * @param router Pointer to router context.
 *
 * @return Number of transmitted frames.
 */
uint32_t FDCAN_AntiInversion_GetTxCount(
    const FDCAN_AntiInversion_t *router);

/**
 * @brief Get error count.
 *
 * @param router Pointer to router context.
 *
 * @return Error counter value.
 */
uint32_t FDCAN_AntiInversion_GetErrorCount(
    const FDCAN_AntiInversion_t *router);

#ifdef __cplusplus
}
#endif

#endif /* STM32C5_FDCAN_ANTI_INVERSION_H */
