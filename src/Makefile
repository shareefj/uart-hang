PROJECT = hangy
BUILD_DIR = bin

CFILES = hangy.c

DEVICE=stm32f407vgt6

INCLUDES += $(patsubst %,-I%, .)
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
