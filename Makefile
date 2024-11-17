CC=g++ -std=c++17
FLAGS=#-Wall -Werror -Wextra

OBJ_DIR = ./obj

SRC_DIR = ./src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_DIR = ./tests/src
TEST_FILES=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_FILES))


TARGET = s21_containers
AR = ar

OS=$(shell uname -s)

ifeq ($(OS), Darwin)
	IGTEST=-I$(shell brew --prefix googletest)/include 
	LGTEST=-L$(shell brew --prefix googletest)/lib -lgtest -lgmock -pthread
endif

ifeq ($(OS), Linux)
	IGTEST=-I/usr/include 
	LGTEST=-L/usr/lib -lgtest -lgmock -pthread
endif


all: $(TARGET)
	./$(TARGET)

map:clean
	$(CC) $(FLAGS) ./tests/src/map_tests.cpp ./tests/src/s21_containers_tests.cpp $(LGTEST) $(IGTEST)
	./a.out

vec:clean
	$(CC) $(FLAGS) ./tests/src/vector_tests.cpp  ./tests/src/s21_containers_tests.cpp $(LGTEST) $(IGTEST)
	./a.out
test:clean $(SRC_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(FLAGS)  $(SRC_OBJECTS) $(TEST_OBJECTS) -o $(TARGET)_test $(LGTEST)
	./$(TARGET)_test


$(TARGET): $(SRC_OBJECTS)
	$(CC) $(FLAGS) $^ -o $(TARGET)

$(TARGET).a: $(SRC_OBJECTS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@
	
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< $(IGTEST) -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET).a
	rm -rf *_test
	rm -rf *.out


.PHONY: all clean
