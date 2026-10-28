/**
 * @file test_fdcan_router.c
 * @brief Unit tests for FDCAN Anti-Inversion state machine and buffer toggling logic.
 */

#include <assert.h>
#include <stdio.h>
#include "stm32c5_fdcan_anti_inversion.h"

// Mock HAL stubs for testing state logic without target hardware
HAL_StatusTypeDef HAL_FDCAN_AddMessageToTxBuffer(FDCAN_HandleTypeDef *hfdcan, 
                                                 FDCAN_TxHeaderTypeDef *pHeader, 
                                                 const uint8_t *pData, 
                                                 uint32_t BufferIndex) 
{
    (void)hfdcan;
    (void)pHeader;
    (void)pData;
    (void)BufferIndex;
    return HAL_OK; // Simulate successful queueing
}

void test_buffer_alternation(void) 
{
    FDCAN_AntiInversion_t router;
    FDCAN_HandleTypeDef mock_handle;
    FDCAN_TxHeaderTypeDef mock_header;
    uint8_t dummy_data[8] = {0};

    // Initialize with Buffer 4 and Buffer 5
    assert(FDCAN_AntiInversion_Init(&router, &mock_handle, 4, 5) == HAL_OK);
    assert(router.active_buffer == 4);

    // First transmission should use Buffer 4, then toggle to 5
    assert(FDCAN_AntiInversion_Transmit(&router, &mock_header, dummy_data) == HAL_OK);
    assert(router.active_buffer == 5);
    assert(router.successful_tx_count == 1);

    // Second transmission should use Buffer 5, then toggle back to 4
    assert(FDCAN_AntiInversion_Transmit(&router, &mock_header, dummy_data) == HAL_OK);
    assert(router.active_buffer == 4);
    assert(router.successful_tx_count == 2);

    printf("SUCCESS: FDCAN anti-inversion buffer alternation tests passed!\n");
}

int main(void) 
{
    test_buffer_alternation();
    return 0;
}
