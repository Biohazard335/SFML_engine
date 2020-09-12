BIN_DIR=../bin/
CXXFLAGS= -O3 -g -std=c++14 -no-pie
CXX= g++-5
LD=g++-5

LDFLAGS= -Wl,-rpath=$(ORIGIN)../lib

EXEC_FILE=./CORE

LIBS=-L$(SFML_PATH) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system


SFML_PATH= ../lib
INC_DIR= -I/home/daniel/Downloads/sfml/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/include

SOURCES := $(shell find -type f -name '*.cpp') 
OBJECTS := $(patsubst ./%.cpp,$(BIN_DIR)%.o,$(SOURCES))
DEPENDS := $(patsubst ./%.cpp,$(BIN_DIR)%.d,$(SOURCES))

#WARNING := -Wall -Wextra
WARNING := -w

.PHONY: clean run remake print windows win_dyn

make: $(OBJECTS)
		$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $(EXEC_FILE) $(LDFLAGS) $(LIBS) 

-include $(DEPENDS)

$(BIN_DIR)%.o: %.cpp makefile
		$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@ $(INC_DIR)


clean:
		$(RM) $(OBJECTS) $(DEPENDS) $(EXEC_FILE)

run:
	$(EXEC_FILE)


remake: clean make

print:
	$(printf) $(OBJECTS)

windows:
	make -f Windows.mak

win_dyn:
	make -f win_dyn.mak