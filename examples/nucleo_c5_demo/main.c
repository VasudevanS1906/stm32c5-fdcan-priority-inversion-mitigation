int main(void)
{
    HAL_Init();

    MX_FDCAN1_Init();

    FDCAN_AntiInversion_t router;

    FDCAN_AntiInversion_Init(
        &router,
        &hfdcan1);

    while(1)
    {
        FDCAN_AntiInversion_Transmit(
            &router,
            &txHeader,
            txData);
    }
}
