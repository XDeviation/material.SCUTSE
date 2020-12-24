TARGET = Server

# files dir
SRC = ./src
OBJ = ./obj
INC = ./inc

# compile option
INCLUDES = -I ${INC}
FLAGS = -std=c++17 -Wextra -O0 -lpthread

# files list
SOURCE = $(wildcard ${SRC}/*.cpp)
OBJECT = $(patsubst %.cpp,${OBJ}/%.o,$(notdir ${SOURCE}))

# links
$(TARGET):$(OBJECT)
	g++ -o $@ $^ -lpthread

# complie
${OBJ}/%.o:${SRC}/%.cpp
	@if [ ! -d "obj" ];then mkdir ${OBJ};fi
	g++ -c -o $@ $< ${INCLUDES} ${FLAGS}

.PHONY: clean
clean:
	-rm ${TARGET}
	-rm -rf ${OBJ}
