/**
 ******************************************************************************
 * @file    stm32c5_fdcan_anti_inversion.c
 * @author  Vasudevan Swornampillai
 * @brief   STM32C5 FDCAN Tx FIFO priority inversion mitigation.
 *
 * Copyright (c) 2026 Vasudevan Swornampillai
 * Licensed under the MIT License.
 ******************************************************************************
 */

#include "stm32c5_fdcan_anti_inversion.h"

HAL_StatusTypeDef FDCAN_AntiInversion_Init(
    FDCAN_AntiInversion_t *router,
    FDCAN_HandleTypeDef *hfdcan,
    uint32_t buffer_a,
    uint32_t buffer_b)
{
    if ((router == NULL) || (hfdcan == NULL))
    {
        return HAL_ERROR;
    }

    router->hfdcan = hfdcan;

    router->tx_buffer_a = buffer_a;
    router->tx_buffer_b = buffer_b;

    router->active_buffer = buffer_a;

    router->successful_tx_count = 0;
    router->timeout_count = 0;
    router->error_count = 0;

    return HAL_OK;
}


HAL_StatusTypeDef FDCAN_AntiInversion_Transmit(
    FDCAN_AntiInversion_t *router,
    FDCAN_TxHeaderTypeDef *txHeader,
    const uint8_t *txData)
{
    uint32_t timeout;
    uint32_t currentBuffer;

    if ((router == NULL) || (txHeader == NULL) || (txData == NULL))
    {
        return HAL_ERROR;
    }

    currentBuffer = router->active_buffer;

    if (HAL_FDCAN_AddMessageToTxBuffer(
            router->hfdcan,
            txHeader,
            (uint8_t *)txData,
            currentBuffer) != HAL_OK)
    {
        router->error_count++;
        return HAL_ERROR;
    }

    if (HAL_FDCAN_EnableTxBufferRequest(
            router->hfdcan,
            currentBuffer) != HAL_OK)
    {
        router->error_count++;
        return HAL_ERROR;
    }

    timeout = HAL_GetTick();

    while (HAL_FDCAN_IsTxBufferMessagePending(
               router->hfdcan,
               currentBuffer))
    {
        if ((HAL_GetTick() - timeout) > FDCAN_AI_TX_TIMEOUT_MS)
        {
            router->timeout_count++;
            return HAL_TIMEOUT;
        }
    }

    router->successful_tx_count++;

    if (router->active_buffer == router->tx_buffer_a)
    {
        router->active_buffer = router->tx_buffer_b;
    }
    else
    {
        router->active_buffer = router->tx_buffer_a;
    }

    return HAL_OK;
}


void FDCAN_AntiInversion_ResetStats(
    FDCAN_AntiInversion_t *router)
{
    if (router == NULL)
    {
        return;
    }

    router->successful_tx_count = 0;
    router->timeout_count = 0;
    router->error_count = 0;
}


uint32_t FDCAN_AntiInversion_GetTxCount(
    const FDCAN_AntiInversion_t *router)
{
    if (router == NULL)
    {
        return 0;
    }

    return router->successful_tx_count;
}


uint32_t FDCAN_AntiInversion_GetErrorCount(
    const FDCAN_AntiInversion_t *router)
{
    if (router == NULL)
    {
        return 0;
    }

    return router->error_count;
}
