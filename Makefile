CC=g++ -std=c++17
FLAGS=-Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage 

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
	$(CC) $(FLAGS) ./tests/src/map.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out
mmap:clean
	$(CC) $(FLAGS) ./tests/src/multimap.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

vec:clean
	$(CC) $(FLAGS) ./tests/src/vector.cpp  ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

deq:clean
	$(CC) $(FLAGS) ./tests/src/deque.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out
stack: clean
	$(CC) $(FLAGS) ./tests/src/stack.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out
set: clean
	$(CC) $(FLAGS) ./tests/src/set.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

mset: clean
	$(CC) $(FLAGS) ./tests/src/multiset.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

tree: clean
	$(CC) $(FLAGS) ./tests/src/tree.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out
list: clean
	$(CC) $(FLAGS) ./tests/src/list.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out
arr: clean
	$(CC) $(FLAGS) ./tests/src/array.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

test:clean $(SRC_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(FLAGS)  $(SRC_OBJECTS) $(TEST_OBJECTS) -o $(TARGET)_test $(LGTEST)
	./$(TARGET)_test

que: clean
	$(CC) $(FLAGS) ./tests/src/queue.cpp ./tests/src/tests.cpp $(LGTEST) $(IGTEST)
	./a.out

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
	rm -f $(TARGET).info *.gcda *.gcno gcov_report.out
	rm -rf ./report

.PHONY: all clean

gcov_report:
	$(CC) $(FLAGS) $(GCOV_FLAGS) --coverage -o gcov_report.out  ./tests/src/*.cpp  $(LGTEST) $(IGTEST)
	./gcov_report.out
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d . --ignore-errors mismatch,inconsistent,corrupt
	genhtml -o report --ignore-errors inconsistent,inconsistent $(TARGET).info -q
	@rm -f $(TARGET).info *.gcda *.gcno gcov_report.out
