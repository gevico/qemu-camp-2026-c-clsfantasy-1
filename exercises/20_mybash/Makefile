# =============================================
# 主 Makefile
# 功能：
#   - mybash：生成二进制，放到 bin/
#   - 其他模块（mysed, myfile, mywc, mytrans）：生成静态库 .a，放到 obj/xxx/，.o 放到 obj/xxx/（或 out/，但建议统一）
#   - 所有子模块 Makefile 应支持 OBJDIR 和 BINDIR 参数
# =============================================

# 所有子模块目录（静态库：生成 .a）
SUBDIRS := \
	mysed \
	myfile \
	mywc \
	mytrans

OBJ_ROOT := ../../obj
BIN_ROOT := ../../bin

# 默认目标：构建 mybash（依赖其他库）
all: mybash

# 通用规则：构建每个子模块（静态库）
$(SUBDIRS):
	$(MAKE) -C src/$@ OBJDIR=$(OBJ_ROOT)/$@

# 构建 mybash（可执行文件，依赖上面的库）
mybash: $(SUBDIRS)
	$(MAKE) -C src/mybash BINDIR=$(BIN_ROOT) OBJDIR=$(OBJ_ROOT)/mybash LINKLIBS="-L$(OBJ_ROOT)/mysed -L$(OBJ_ROOT)/myfile -L$(OBJ_ROOT)/mywc -L$(OBJ_ROOT)/mytrans"

# 清理所有生成的文件
clean:
	rm -rf obj bin

.PHONY: all $(SUBDIRS) mybash clean
