
#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// <h> nRF_Drivers
//==========================================================

// <e> NRF_CLOCK_ENABLED - nrf_drv_clock - CLOCK peripheral driver - legacy layer
// NOTE: Legacy CLOCK driver is still used, because
//       - it supports request and release HFCLK (implements request handling)
//       - and legacy driver is used by SDK module nfc_platform.c (used for NFC tag)
//==========================================================
#ifndef NRF_CLOCK_ENABLED
#define NRF_CLOCK_ENABLED 1
#endif

// <e> NRFX_CLOCK_ENABLED - nrfx_clock - CLOCK peripheral driver
//==========================================================
#ifndef NRFX_CLOCK_ENABLED
#define NRFX_CLOCK_ENABLED 1
#endif

// <e> NRFX_GPIOTE_ENABLED - nrfx_gpiote - GPIOTE peripheral driver
//==========================================================
#ifndef NRFX_GPIOTE_ENABLED
#define NRFX_GPIOTE_ENABLED 1
#endif

// <o> NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS - Number of lower power input pins
#ifndef NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS
#define NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS 4
#endif

// <e> NRFX_POWER_ENABLED - nrfx_power - POWER peripheral driver
//==========================================================
#ifndef NRFX_POWER_ENABLED
#define NRFX_POWER_ENABLED 0
#endif

// <e> APP_TIMER_ENABLED - app_timer - Application timer functionality
//==========================================================
#ifndef APP_TIMER_ENABLED
#define APP_TIMER_ENABLED 1
#endif

// <o> APP_TIMER_CONFIG_RTC_FREQUENCY  - Configure RTC prescaler.
// <0=> 32768 Hz
// <1=> 16384 Hz
// <3=> 8192 Hz
// <7=> 4096 Hz
// <15=> 2048 Hz
// <31=> 1024 Hz
#ifndef APP_TIMER_CONFIG_RTC_FREQUENCY
#define APP_TIMER_CONFIG_RTC_FREQUENCY 2
#endif

// <o> APP_TIMER_CONFIG_OP_QUEUE_SIZE - Capacity of timer requests queue.
// <i> Size of the queue depends on how many timers are used
// <i> in the system, how often timers are started and overall
// <i> system latency. If queue size is too small app_timer calls
// <i> will fail.
#ifndef APP_TIMER_CONFIG_OP_QUEUE_SIZE
#define APP_TIMER_CONFIG_OP_QUEUE_SIZE 20
#endif

// <q> APP_TIMER_KEEPS_RTC_ACTIVE  - Enable RTC always on
// <i> If option is enabled RTC is kept running even if there is no active timers.
// <i> This option can be used when app_timer is used for timestamping.
#ifndef APP_TIMER_KEEPS_RTC_ACTIVE
#define APP_TIMER_KEEPS_RTC_ACTIVE 1
#endif

// <q> HARDFAULT_HANDLER_ENABLED  - hardfault_default - HardFault default handler for debugging and release
//==========================================================
#ifndef HARDFAULT_HANDLER_ENABLED
#define HARDFAULT_HANDLER_ENABLED 1
#endif

// <h> nRF_Log
//==========================================================

// <e> NRF_LOG_ENABLED - Logging module for nRF5 SDK
//==========================================================
#ifndef NRF_LOG_ENABLED
#define NRF_LOG_ENABLED 1
#endif

// <i> Must be power of 2 and multiple of 4.
// <i> If NRF_LOG_DEFERRED = 0 then buffer size can be reduced to minimum.
// <128=> 128
// <256=> 256
// <512=> 512
// <1024=> 1024
// <2048=> 2048
// <4096=> 4096
// <8192=> 8192
// <16384=> 16384
#ifndef NRF_LOG_BUFSIZE
#define NRF_LOG_BUFSIZE 4096
#endif

// <o> NRF_LOG_DEFAULT_LEVEL  - Default Severity level
// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug
#ifndef NRF_LOG_DEFAULT_LEVEL
#define NRF_LOG_DEFAULT_LEVEL 3
#endif

// <e> NRF_LOG_USES_TIMESTAMP - Enable timestamping
// <i> Function for getting the timestamp is provided by the user
#ifndef NRF_LOG_USES_TIMESTAMP
#define NRF_LOG_USES_TIMESTAMP 1
#endif

// <q> NRF_LOG_STR_FORMATTER_TIMESTAMP_FORMAT_ENABLED  - nrf_log_str_formatter - Log string formatter
#ifndef NRF_LOG_STR_FORMATTER_TIMESTAMP_FORMAT_ENABLED
#define NRF_LOG_STR_FORMATTER_TIMESTAMP_FORMAT_ENABLED 0
#endif

// <e> NRF_LOG_BACKEND_RTT_ENABLED - nrf_log_backend_rtt - Log RTT backend
//==========================================================
#ifndef NRF_LOG_BACKEND_RTT_ENABLED
#define NRF_LOG_BACKEND_RTT_ENABLED 1
#endif

// <o> NRF_LOG_BACKEND_RTT_TEMP_BUFFER_SIZE - Size of buffer for partially processed strings.
// <i> Size of the buffer is a trade-off between RAM usage and processing.
// <i> if buffer is smaller then strings will often be fragmented.
// <i> It is recommended to use size which will fit typical log and only the
// <i> longer one will be fragmented.
#ifndef NRF_LOG_BACKEND_RTT_TEMP_BUFFER_SIZE
#define NRF_LOG_BACKEND_RTT_TEMP_BUFFER_SIZE 64
#endif

// <o> NRF_LOG_BACKEND_RTT_TX_RETRY_DELAY_MS - Period before retrying writing to RTT
#ifndef NRF_LOG_BACKEND_RTT_TX_RETRY_DELAY_MS
#define NRF_LOG_BACKEND_RTT_TX_RETRY_DELAY_MS 1
#endif

// <o> NRF_LOG_BACKEND_RTT_TX_RETRY_CNT - Writing to RTT retries.
// <i> If RTT fails to accept any new data after retries
// <i> module assumes that host is not active and on next
// <i> request it will perform only one write attempt.
// <i> On successful writing, module assumes that host is active
// <i> and scheme with retry is applied again.
#ifndef NRF_LOG_BACKEND_RTT_TX_RETRY_CNT
#define NRF_LOG_BACKEND_RTT_TX_RETRY_CNT 3
#endif

// <e> NRF_LOG_BACKEND_UART_ENABLED - nrf_log_backend_uart - Log UART backend
//==========================================================
#ifndef NRF_LOG_BACKEND_UART_ENABLED
#define NRF_LOG_BACKEND_UART_ENABLED 0
#endif

#ifndef NRF_LOG_BACKEND_UART_TEMP_BUFFER_SIZE
#define NRF_LOG_BACKEND_UART_TEMP_BUFFER_SIZE 256
#endif

#ifndef NRF_LOG_BACKEND_UART_TX_PIN
#define NRF_LOG_BACKEND_UART_TX_PIN 36
#endif

#ifndef NRF_LOG_BACKEND_UART_BAUDRATE
#define NRF_LOG_BACKEND_UART_BAUDRATE NRF_UARTE_BAUDRATE_115200
#endif



#endif // ifndef _APP_CONFIG_H_