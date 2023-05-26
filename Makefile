CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -O2

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


clean:
	del /F /Q main.exe 2>NUL || true
