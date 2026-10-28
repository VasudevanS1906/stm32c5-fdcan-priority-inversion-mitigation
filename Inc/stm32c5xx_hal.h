#ifndef STM32C5XX_HAL_H
#define STM32C5XX_HAL_H

#include <stdint.h>

#define HAL_OK     0x00U
#define HAL_ERROR  0x01U
#define HAL_BUSY   0x02U
#define HAL_TIMEOUT 0x03U

typedef uint32_t HAL_StatusTypeDef;

typedef struct {
    void *Instance;
} FDCAN_HandleTypeDef;

typedef struct {
    uint32_t Identifier;
    uint32_t IdType;
    uint32_t TxBufferIndex;
} FDCAN_TxHeaderTypeDef;

#endif /* STM32C5XX_HAL_H */
