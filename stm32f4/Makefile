#	Makefile
#	2019-03-10	Markku-Juhani O. Saarinen <mjos@pqshield.com>

PROJECT	= r5test
SRCS	= $(wildcard bench/*.c ../src/*.c ../src/*.S)
CC	= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
STFLASH = st-flash

CFLAGS	= -Wall -Ofast
CFLAGS	+= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS	+= -DSTM32F4 -DSTM32F4CCM -DSTM32F407VGT6 -DR5_ARMV7_ASM
CFLAGS	+= -D$(ROUND5) -I../src
CFLAGS	+= -I. -I../libopencm3/include
LDFLAGS	= -Tstm32f407vgt6.ld -L../libopencm3/lib -nostartfiles
LIBS	= -lopencm3_stm32f4 \
		-Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group
UARTDEV	= /dev/ttyUSB0

# Compiles everything at once

$(PROJECT).elf:	$(SRCS)
ifndef ROUND5
	@echo "Which one? You must set: make ROUND5=R5_variant)"
else
	$(CC) $(LDFLAGS) $(CFLAGS) $(SRCS) $(LIBS) -o $(PROJECT).elf
endif

$(PROJECT).bin:	$(PROJECT).elf
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

clean:
	rm -f $(OBJS) $(PROJECT).elf $(PROJECT).bin

flash:	$(PROJECT).bin
	$(STFLASH) write $(PROJECT).bin 0x8000000

run:	flash
	stty -F $(UARTDEV) 115200 cs8 -cstopb -parenb eof \^d
	cat < $(UARTDEV)

