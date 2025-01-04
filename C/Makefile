SRC_DIR = ./src/list/src
TEST_DIR = ./src/list/tests
BUILD_DIR = ./build
BIN_DIR = ./bin
TARGET = $(BIN_DIR)/main.out
TEST_TARGET = $(BIN_DIR)/test.out

CC = cc
CFLAGS = -Wall -g -std=c99 
 
 
# ./src/*.c
SRC_SRCS := $(wildcard $(SRC_DIR)/*.c)
# ./tests/*.c
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)

# ./src/*.c => ./build/*.o
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_SRCS))
# ./tests/*.c => ./build/*.o
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))
# ./src/*.c => ./build/*.d
SRC_DEPS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC_SRCS))
# ./tests/*.c => ./build/*.d
TEST_DEPS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.d,$(TEST_SRCS))
 

# 默认目标:构建src目录下的可执行文件
all: $(TARGET)
#	运行src下编译的可执行程序
run: $(TARGET)
	./$(TARGET)

# 构建测试文件目标
test: $(TEST_TARGET) $(TEST_OBJS)
	@echo "building test objects..."
# 运行测试可执行文件
test_run: $(TEST_TARGET) $(TEST_OBJS)
	./$(TEST_TARGET)

# build/*.d 的规则由 src/和tests/*.c文件生成:
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MM  $< > $@

# build/*.o 的规则由 src/*.c 生成:
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
 
# build/*.o 的规则由 test/*.c 生成:
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
 
# 链接src中可执行文件:
$(TARGET): $(SRC_OBJS)
	@echo "buiding $@..."
	@mkdir -p $(dir $@)
	$(CC) -o $(TARGET) $(SRC_OBJS)

# 链接测试可执行文件：
$(TEST_TARGET): $(TEST_OBJS) $(SRC_OBJS)
	@echo "buiding $@..."
	@mkdir -p $(dir $@)
	$(CC) -o $(TEST_TARGET) $(TEST_OBJS) $(SRC_OBJS)

.PHONY: clean build all run test test_run
# 清理 build 目录:
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*
# 生成标准的C目录框架
build:
	@echo "Creating directory structure..."
	mkdir -p $(BUILD_DIR) $(SRC_DIR) $(TEST_DIR) $(BIN_DIR)
	touch LICENSE README.md
 
# 引入所有 .d 文件内的依赖规则:
-include $(SRC_DEPS)
-include $(TEST_DEPS)
