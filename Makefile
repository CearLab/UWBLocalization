MAIN = main

BIN_DIR = bin
SRC_DIR = source
INC_DIR = include
OBJ_DIR = object

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS += -Wall -Wextra -O2 -I$(INC_DIR)
CPP = g++
CPPFLAGS += -Wall -Wextra -O2 -I$(INC_DIR) -std=c++11
LDFLAGS += -L. -L./libraries/
LDLIBS += -lm -lpthread -lrt -lUWBranging

#keyboard control
DEFINES += -DNCURSES

.PHONY: clean

$(MAIN): main.o $(OBJ)
	$(CPP) -DMAIN $(LDFLAGS) $^ $(LDLIBS) -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEFINES) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) main.o
