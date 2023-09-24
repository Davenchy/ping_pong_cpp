SRC := components/
BUILD := build/

SOURCE := $(wildcard $(SRC)/*.cpp)
OBJECT := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCE))

.PHONY: run

cping_pong: $(OBJECT) $(BUILD)/main.o
	gcc -Wall -lraylib -lm -o $@ $^

$(BUILD)/main.o: main.cpp
	gcc -Wall -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	gcc -Wall -c $< -o $@

run: cping_pong
	@./cping_pong
