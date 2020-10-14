CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -g -Og

all: main

main: src/main.cpp src/board.cpp src/player.cpp src/game.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^