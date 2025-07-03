# 编译器设置
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILDDIR)/dep/$*.d
CXXFLAGS += $(DEPFLAGS)

# 链接器设置
LDFLAGS =
LDLIBS =

# 目录设置
SRCDIR = src
INCDIR = include
TESTDIR = test
BUILDDIR = build
DEPDIR = $(BUILDDIR)/dep

# 可配置的外部库路径（例如 Homebrew）
EXT_INCDIR ?= /opt/homebrew/include
CXXFLAGS += -I$(EXT_INCDIR)

# 主程序入口
MAIN_SOURCE = $(SRCDIR)/main.cpp  # 假设主程序在 src/main.cpp
MAIN_OBJECT = $(BUILDDIR)/main.o

# 测试程序入口
TEST_MAIN_SOURCE = $(TESTDIR)/BasicOperationTest.cpp
TEST_MAIN_OBJECT = $(BUILDDIR)/test_BasicOperationTest.o

# 自动发现源文件（支持子目录）
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
TEST_SOURCES := $(shell find $(TESTDIR) -name '*.cpp')

# 生成目标文件路径
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TEST_OBJECTS := $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BUILDDIR)/test_%.o)

# 排除主程序对象文件
LIB_OBJECTS = $(filter-out $(MAIN_OBJECT), $(OBJECTS))

# 目标程序
TARGET = $(BUILDDIR)/my_program
TEST_TARGET = $(BUILDDIR)/run_tests

# 调试/发布配置
BUILD_TYPE ?= debug
ifeq ($(BUILD_TYPE),debug)
    CXXFLAGS += -g -O0
else ifeq ($(BUILD_TYPE),release)
    CXXFLAGS += -O2
endif

# 默认目标
all: $(TARGET)

# 主程序构建
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# 测试程序构建
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS) | $(BUILDDIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# 从 src 目录编译
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR) $(DEPDIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 从 test 目录编译
$(BUILDDIR)/test_%.o: $(TESTDIR)/%.cpp | $(BUILDDIR) $(DEPDIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建 build 和 dep 目录
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

# 构建并运行测试
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# 清理
clean:
	rm -rf $(BUILDDIR)

# 包含依赖文件
DEPFILES := $(OBJECTS:$(BUILDDIR)/%.o=$(DEPDIR)/%.d) $(TEST_OBJECTS:$(BUILDDIR)/%.o=$(DEPDIR)/%.d)
-include $(DEPFILES)

# 声明伪目标
.PHONY: all test clean