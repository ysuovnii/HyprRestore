
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

all: build/save build/restore

build/save: src/save.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

build/restore: src/restore.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build/*

install:
	bash install.sh

uninstall:
	bash uninstall.sh  