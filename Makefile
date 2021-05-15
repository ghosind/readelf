ifndef GCCPREFIX
GCCPREFIX :=
endif

DIR_BIN := ./bin
DIR_SRC := ./src
DIR_INC := ./include
DIR_OBJ := ./obj

OUTPUT := $(DIR_BIN)/readelf

SRCS := $(wildcard ${DIR_SRC}/*.c)
OBJS = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRCS}))

CC := $(GCCPREFIX)gcc

CFLAGS += -Wall -Wno-format -Wno-unused
CFLAGS += -std=gnu99
CFLAGS += -I $(DIR_INC)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@if [ ! -d $(DIR_OBJ) ]; then mkdir $(DIR_OBJ); fi;
	$(CC) $(CFLAGS) -c  $< -o $@

all: ${OBJS}
	@if [ ! -d $(DIR_BIN) ]; then mkdir $(DIR_BIN); fi;
	$(CC) $(CFLAGS) -o $(OUTPUT) $^

clean:
	rm -f ${DIR_BIN}/*
	rm -f $(DIR_OBJ)/*.o

.PHONY: all
