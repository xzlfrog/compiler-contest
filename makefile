# 编译器设置
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILDDIR)/$*.d
CXXFLAGS += $(DEPFLAGS)

# 目录设置
SRCDIR = src
INCDIR = include
TESTDIR = test
BUILDDIR = build

# 主程序入口
MAIN_SOURCE = $(TESTDIR)/BasicOperationTest.cpp
MAIN_OBJECT = $(BUILDDIR)/main.o

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

# 默认目标
all: $(TARGET)

# 主程序构建
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $^ -o $@

# 测试程序构建
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS) | $(BUILDDIR)
	$(CXX) $^ -o $@

# 从 src 目录编译
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@mkdir -p $(@D)  # 创建子目录
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 从 test 目录编译
$(BUILDDIR)/test_%.o: $(TESTDIR)/%.cpp | $(BUILDDIR)
	@mkdir -p $(@D)  # 创建子目录
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建 build 目录
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# 构建并运行测试
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# 清理
clean:
	rm -rf $(BUILDDIR)

# 声明伪目标
.PHONY: all test clean