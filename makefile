# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -O0 -Wall -Wextra -g -Iinclude -Isrc/frontend
LDFLAGS := -lfl
LDFLAGS += -static-libstdc++

# Build directories
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

# Parser files
YACC_SRC := src/frontend/sysy.y
LEX_SRC := src/frontend/sysy.l

# Generated parser outputs
YACC_CPP := src/frontend/sysy.y.cpp
YACC_HPP := src/frontend/sysy.y.hpp
LEX_CPP := src/frontend/sysy.l.cpp

# Source files
SRC_DIR := src
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' ! -path "$(YACC_CPP)" ! -path "$(LEX_CPP)")

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
OBJS += $(OBJ_DIR)/frontend/sysy.y.o
OBJS += $(OBJ_DIR)/frontend/sysy.l.o

# Final executable
TARGET := $(BIN_DIR)/compiler

# Default target
all: $(TARGET)

# 1. 确保解析器文件首先生成
parser: $(YACC_CPP) $(LEX_CPP) $(YACC_HPP)
.PHONY: parser

# 生成解析器源文件
$(YACC_CPP) $(YACC_HPP): $(YACC_SRC)
	bison -d -o $(YACC_CPP) $<

$(LEX_CPP): $(LEX_SRC) $(YACC_HPP)
	flex -o $@ $<

# 2. 编译规则
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(YACC_HPP) | parser $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 特殊规则处理生成的解析器代码 - 关键修改在这里
$(OBJ_DIR)/frontend/sysy.y.o: $(YACC_CPP) | parser $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 特殊处理 Flex 生成的 C 文件 - 添加 -x c++ 选项
$(OBJ_DIR)/frontend/sysy.l.o: $(LEX_CPP) | parser $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -x c++ -c $< -o $@

# 3. 链接可执行文件 - 调整链接顺序
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# 创建构建目录
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# 清理构建文件
clean:
	rm -rf $(BUILD_DIR) $(YACC_CPP) $(YACC_HPP) $(LEX_CPP)

test:
	./build/bin/compiler ./test/test2.sy

debug:
	gdb --args ./build/bin/compiler ./test/test2.sy

.PHONY: all clean parser