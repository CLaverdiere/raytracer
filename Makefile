CC=g++
BUILD_DIR=./bin
SRC_DIR=./src
CFLAGS=-std=c++11 -g -Wall
SRCS=$(SRC_DIR)/raytracer.cpp $(SRC_DIR)/surfaces.cpp $(SRC_DIR)/scene.cpp $(SRC_DIR)/vec.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/util.cpp $(SRC_DIR)/parser.cpp 
OBJS=$(SRCS:.cpp=.o)
EXEC=$(BUILD_DIR)/trace

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
