CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -fdiagnostics-color=always -g -Wall -Wpedantic
LIBRARIES := -lfmt

all: clean main.exe

main.exe: main.cpp 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

run: all
	./main.exe

clean:
	rm -f *.exe
