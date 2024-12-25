# 编译器标志。-g 启用调试信息，-O2 启用优化，-Wall 启用所有警告，-Wextra 启用额外的警告，-Isrc 添加 src 目录到包含路径，-rdynamic 保留符号信息，-DNDEBUG 禁用调试代码（通常在发布版本中启用）。
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
# 链接器标志，-ldl 链接动态链接库（libdl，用于动态加载）。$(OPTLIBS) 可以包含额外的库链接。
LIBS=-ldl $(OPTLIBS)
# 安装路径，默认为 /usr/local。?= 表示如果没有定义 PREFIX 变量，它就使用默认值。
PREFIX?=/usr/local

# 递归的获取src文件夹中所有 .c 源文件
SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

# 获取 tests 目录下所有以 _tests.c 结尾的文件，将其后缀替换为空，得到测试文件名
TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# 静态库目标文件（libYOUR_LIBRARY.a），存放在 build 目录中
TARGET=build/libYOUR_LIBRARY.a
# 动态库目标文件（libYOUR_LIBRARY.so），存放在 build 目录中
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests

# 开发模式
dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

# 生成位置无关代码（Position Independent Code）。该选项用于编译动态库时，使得生成的目标文件可以在内存中任意位置加载，适用于动态库的构建。
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
       # ar 命令创建静态库，rcs 参数分别表示创建、替换、生成符号表。
	ar rcs $@ $(OBJECTS)
       # 生成静态库的索引，以加快链接速度。
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	# -shared 参数生成动态链接库，-o 参数指定输出文件。
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# 使用 valgrind 来检查内存泄漏。VALGRIND 变量设置了 valgrind 命令，日志输出到 /tmp/valgrind-%p.log,%p 是当前进程 ID。
valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# 安装构建好的静态库到指定目录。install -d 创建目标目录，install 命令将 $(TARGET) 文件复制到安装目录。
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
