set(LINKER_FILE nrf52dk/linker/gcc_nrf52.ld)
set(COMPILE_DEFINITIONS BOARD_PCA10056 NRF52840_XXAA USE_APP_CONFIG CONFIG_GPIO_AS_PINRESET FLOAT_ABI_HARD NRF52840_XXAA __HEAP_SIZE=8192 __STACK_SIZE=8192)