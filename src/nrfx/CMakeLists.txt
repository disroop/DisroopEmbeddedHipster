cmake_minimum_required(VERSION 3.16)
PROJECT(NRFXLib C ASM)

add_library(cmsis INTERFACE)
target_include_directories(cmsis INTERFACE ${CMAKE_CURRENT_LIST_DIR}/cmsis/CMSIS/Core/Include)

set(MDK_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/mdk/system_nrf52840.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/mdk/gcc_startup_nrf52840.S)
add_library(mdk STATIC ${MDK_SOURCES})
target_include_directories(mdk PUBLIC ${CMAKE_CURRENT_LIST_DIR}/nrfx/mdk)
target_compile_definitions(mdk PUBLIC NRF52840_XXAA)
target_link_libraries(mdk PUBLIC cmsis)

SET(DRIVERS_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/prs
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/prs/nrfx_prs.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/prs/nrfx_prs.h
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_adc.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_clock.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_comp.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_dppi.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_egu.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_gpiote.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_i2s.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_ipc.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_lpcomp.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_nfct.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_nvmc.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_pdm.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_power.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_ppi.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_pwm.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_qdec.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_qspi.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_rng.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_rtc.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_saadc.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_spi.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_spim.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_spis.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_systick.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_temp.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_timer.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_twi.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_twi_twim.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_twim.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_twis.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_uart.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_uarte.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_usbd.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_usbreg.c
        ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/src/nrfx_wdt.c)

add_library(drivers STATIC ${DRIVERS_SOURCES})
target_include_directories(drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/nrfx/drivers/include)
target_include_directories(drivers PRIVATE ${CMAKE_CURRENT_LIST_DIR}/nrfx ${CMAKE_CURRENT_LIST_DIR}/nrfx/templates)
target_link_libraries(drivers PUBLIC mdk)

add_library(soc STATIC ${CMAKE_CURRENT_LIST_DIR}/nrfx/soc/nrfx_atomic.c)
target_include_directories(soc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/nrfx/soc)
target_include_directories(soc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/nrfx ${CMAKE_CURRENT_LIST_DIR}/nrfx/templates)
target_link_libraries(soc PUBLIC mdk)