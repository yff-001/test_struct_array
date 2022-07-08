CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega2560
CONF_DIR = C:\Users\sunny\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\etc\avrdude.conf

PORT = com4

all: main.out

main.out: main.o uart.o
	$(CC) $(CFLAGS) main.o uart.o -o main.out

%.o: %.c
	$(CC) $(CFLAGS) -c $^

# $<: first prerequisite $@: target
main.hex: main.out
	${OBJCOPY} -O ihex -R .eeprom $< $@

install.main: main.hex
	avrdude -C ${CONF_DIR} -v -V -D -c wiring -p m2560 -P ${PORT} -b 115200 -U flash:w:$<

clean:
	del *.o *.out *.hex