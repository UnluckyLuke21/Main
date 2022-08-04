CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -fdiagnostics-color=always -g -Wall -Wpedantic `pkg-config --cflags opencv4`
LIBRARIES := -lfmt `pkg-config --libs opencv4`

SRC     := src
INCLUDE := include

all: clean main.exe

main.exe: main.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

run: all
	./main.exe

clean:
	rm -f *.exe
