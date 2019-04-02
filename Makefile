# Compiler Settings
CC = g++
CFLAGS = -c -Wall -O2 -std=c++11
LFLAGS = -lncurses

# Directories
SRC_DIR = src
OBJ_DIR = obj
VPATH = $(SRC_DIR)

# Program and Objects
PROGRAM = starbucksSimulator
OBJS = starbucksSimulator.o ui.o inputProcessing.o


###############
# BUILD RULES #
###############
$(PROGRAM): $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(OBJS))
	$(CC) $(addprefix $(OBJ_DIR)/,$(OBJS)) -o $(PROGRAM) $(LFLAGS)

$(OBJ_DIR)/starbucksSimulator.o: starbucksSimulator.cpp ui.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/ui.o: ui.cpp ui.h inputProcessing.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/inputProcessing.o: inputProcessing.cpp inputProcessing.h
	$(CC) $< -o $@ $(CFLAGS)


################
# HELPER RULES #
################
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	@rm -f $(addprefix $(OBJ_DIR)/,$(OBJS))
	@rm -f $(PROGRAM)
