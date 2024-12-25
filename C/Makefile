SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/world.out
 
CC = cc
CFLAGS = -Wall
 
# ./src/*.c
SRCS = $(shell find $(SRC_DIR) -name '*.c')
# ./src/*.c => ./build/*.o
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
# ./src/*.c => ./build/*.d
DEPS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRCS))
 
# 默认目标:
all: $(TARGET)
 
# build/xyz.d 的规则由 src/xyz.c 生成:
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MM $< > $@
 
 
# build/xyz.o 的规则由 src/xyz.c 生成:
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
 
# 链接:
$(TARGET): $(OBJS)
	@echo "buiding $@..."
	@mkdir -p $(dir $@)
	$(CC) -o $(TARGET) $(OBJS)
 
.PHONY: clean build
# 清理 build 目录:
clean:
	@echo "clean..."
	rm -f $(BUILD_DIR)/*
# 生成标准的C目录框架
build:
	mkdir -p build src bin tests
	touch LICENSE README.md
 
# 引入所有 .d 文件:
-include $(DEPS)