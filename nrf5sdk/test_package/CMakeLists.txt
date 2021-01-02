cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(blinky LANGUAGES C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)



add_executable(${CMAKE_PROJECT_NAME}
  "main.c"
)
find_package(nrf5sdk)
if(TARGET nrf5sdk::nrf5sdk)
  #add_definitions(-DNRF52840_XXAA)
  #add_definitions(-DNRF52840_XXAA -DBOARD_PCA10056)
  nrf5_target(${CMAKE_PROJECT_NAME})
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    nrf5_nrfx_common
    nrf5_delay
    nrf5_boards
  )
endif()