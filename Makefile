# Author: Eric Claerhout, Henry Lin
# Student ID: 1532360, 1580649
# CMPUT 275 Winter 2019
#
# Final Project: Starbucks Simulator
# ##################################

# Compiler Settings
CC = g++
CFLAGS = -c -Wall -O2 -std=c++11
LFLAGS = -lncurses

# Directories
SRC_DIR = src
ALGS_DIR = algs
OBJ_DIR = obj
VPATH = $(SRC_DIR):$(SRC_DIR)/$(ALGS_DIR)

# Program and Objects
PROGRAM = starbucksSimulator
OBJS = starbucksSimulator.o ui.o uiHelper.o cpu.o preprocess.o levenshtein-distance.o soundex.o nysiis.o metaphone.o


###############
# BUILD RULES #
###############
$(PROGRAM): $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(OBJS))
	$(CC) $(addprefix $(OBJ_DIR)/,$(OBJS)) -o $(PROGRAM) $(LFLAGS)

$(OBJ_DIR)/starbucksSimulator.o: starbucksSimulator.cpp ui.h cpu.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/ui.o: ui.cpp ui.h uiHelper.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/uiHelper.o: uiHelper.cpp uiHelper.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/cpu.o: cpu.cpp cpu.h levenshtein-distance.h soundex.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/preprocess.o: preprocess.cpp preprocess.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/levenshtein-distance.o: levenshtein-distance.cpp levenshtein-distance.h preprocess.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/soundex.o: soundex.cpp soundex.h preprocess.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/nysiis.o: nysiis.cpp nysiis.h preprocess.h
	$(CC) $< -o $@ $(CFLAGS)

$(OBJ_DIR)/metaphone.o: metaphone.cpp metaphone.h
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
