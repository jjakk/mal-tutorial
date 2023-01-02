CXXFLAGS ?= -std=c++17 -g -Wall -Wextra -Werror

build: step0_repl step1_read_print

step0_repl: step0_repl.cpp
	$(CXX) $(CXXFLAGS) -o step0_repl step0_repl.cpp

step0_repl: step1_read_print.cpp
	$(CXX) $(CXXFLAGS) -o step1_read_print step1_read_print.cpp