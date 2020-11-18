#openocd -c "gdb_port 3333" -c "telnet_port 4444" -f interface/jlink.cfg -f board/nordic_nrf52_dk.cfg -c "bindto 172.17.0.1" -c 'init; reset init; halt"

JLinkGDBServerCLExe -select USB -device nRF52840_xxAA -endian little -if SWD -speed auto -noir -noLocalhostOnly --help