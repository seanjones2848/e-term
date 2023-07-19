DIR_Config	 = ./lib/Config
DIR_EPD		 = ./lib/e-Paper
DIR_FONTS	 = ./lib/Fonts
DIR_GUI		 = ./lib/GUI
DIR_Examples = ./examples
DIR_BIN		 = ./bin
DIR_SRC		 = ./src

EPD = epd5in83
OBJ_C_EPD = ${DIR_SRC}/EPD_5in83.c
OBJ_C_Examples = ${DIR_Examples}/EPD_5in83_test.c

OBJ_C = $(wildcard ${DIR_GUI}/*.c ${DIR_SRC}/*.c ${DIR_FONTS}/*.c )
TEST_OBJ_C = $(wildcard ${OBJ_C_EPD} ${DIR_GUI}/*.c ${OBJ_C_Examples} ${DIR_Examples}/main.c ${DIR_Examples}/ImageData2.c ${DIR_Examples}/ImageData.c ${DIR_FONTS}/*.c )
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

DEBUG = -D DEBUG

USELIB_RPI = USE_BCM2835_LIB

LIB_RPI=-Wl,--gc-sections
LIB_RPI += -lbcm2835 -lm

DEBUG_RPI = -D $(USELIB_RPI) -D RPI

.PHONY : RPI clean

RPI:RPI_epd

TARGET = epd
CC = gcc
MSG = -g -O -ffunction-sections -fdata-sections -Wall
CFLAGS += $(MSG) -D $(EPD)

RPI_epd:${OBJ_O}
	echo $(@)
	$(CC) $(CFLAGS) -D RPI $(OBJ_O) -o $(TARGET) $(LIB_RPI) $(DEBUG)

$(shell mkdir -p $(DIR_BIN))

${DIR_BIN}/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c	$< -o $@ $(DEBUG)

${DIR_BIN}/%.o:$(DIR_FONTS)/%.c 
	$(CC) $(CFLAGS) -c	$< -o $@ $(DEBUG)
	
${DIR_BIN}/%.o:$(DIR_GUI)/%.c
	$(CC) $(CFLAGS) -c	$< -o $@ -I $(DIR_Config) $(DEBUG)

clean :
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 

