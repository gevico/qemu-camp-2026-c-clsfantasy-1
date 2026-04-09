# src/mysed/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

# 库名称
LIBNAME := mysed
# 静态库输出名：libmysed.a
LIB := lib$(LIBNAME).a
# 最终库输出目录（比如 ./obj/src/mysed/）
OBJDIR ?= ./obj
# 最终 .a 文件路径
LIB_PATH := $(OBJDIR)/$(LIB)

# 源文件
SRCS := mysed.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

all: $(LIB_PATH)

$(LIB_PATH): $(OBJS)
	@mkdir -p $(OBJDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)/*.o $(LIB_PATH)