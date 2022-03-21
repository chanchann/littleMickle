## ref

https://seisman.github.io/how-to-write-makefile/overview.html#

## 规则

```
target ... : prerequisites ...
    command
    ...
    ...
```

```
prerequisites中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。
```

```
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
# 重点1 : tab
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o

main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
# 重点2
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

## make如何工作

1. 找makefile

2. 找第一个目标文件，作为最终的目标文件

edit

3. edit文件不存在，或是edit所依赖的后面的 .o 文件的文件修改时间要比 edit 这个文件新，那么，他就会执行后面所定义的命令来生成 edit 这个文件

4. 如果 edit 所依赖的 .o 文件也不存在，那么make会在当前文件中找目标为 .o 文件的依赖性，如果找到则再根据那一个规则生成 .o 文件

一层又一层地去找文件的依赖关系，直到最终编译出第一个目标文件

makefile最重要的是依赖, 时间

## 使用变量

理解成C语言中的宏

```
objects = main.o kbd.o command.o display.o \
     insert.o search.o files.o utils.o
```

使用:  $(objects)

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)
main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
clean :
    rm edit $(objects)
```

## 自动推导

只要make看到一个 .o 文件，它就会自动的把 .c 文件加在依赖关系中

如果make找到一个 whatever.o ，那么 whatever.c 就会是 whatever.o 的依赖文件。

并且 cc -c whatever.c 也会被推导出来

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

.PHONY 表示 clean 是个伪目标文件。

## 另类风格的makefiles(optional)

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```

## 清空目标文件

一般

```
clean:
    rm edit $(objects)
```

更稳健

```
.PHONY : clean
clean :
    -rm edit $(objects)
```

rm 命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事

不成文的规矩是——“clean从来都是放在文件的最后”。

## Makefile里有什么

1. 显式规则

2. 隐晦规则

3. 变量

4. 文件指示

5. 注释

Makefile中的命令，必须要以 Tab 键开始。

## include 

```
include foo.make *.mk $(bar)

== 

include foo.make a.mk b.mk c.mk e.mk f.mk
```

寻找顺序

1. 当前文件夹

2. 有 -I 或 --include-dir 参数

3. 目录 <prefix>/include （一般是： /usr/local/bin 或 /usr/include 

不理那些无法读取的文件，而继续执行，"-"

```
-include <filename>
```

## make工作时的执行步骤

1. 读入所有的Makefile。

2. 读入被include的其它Makefile。

3. 初始化文件中的变量。

4. 推导隐晦规则，并分析所有规则。

5. 为所有的目标文件创建依赖关系链。

6. 根据依赖关系，决定哪些目标要重新生成。

7. 执行生成命令。

## 规则中的通配符

```
*  /  ?  /  ~
```

## *

```
# demo1
clean:
    rm -f *.o

# demo2
print: *.c
    lpr -p $?
    touch print

# $? 是一个自动化变量
```

```
# demo3 
objects = *.o
```

objects的值就是 *.o 。

如果你要让通配符在变量中展开，也就是让objects的值是所有 .o 的文件名的集合

```
objects := $(wildcard *.o)
```

```
# demo4
# 1. 列出一确定文件夹中的所有 .c 文件。
objects := $(wildcard *.c)

# 2. 列出(1)中所有文件对应的 .o 文件，在（3）中我们可以看到它是由make自动编译出的:
$(patsubst %.c,%.o,$(wildcard *.c))

# 由(1)(2)两步，可写出编译并链接所有 .c 和 .o 文件
objects := $(patsubst %.c,%.o,$(wildcard *.c))
foo : $(objects)
    cc -o foo $(objects)
```

## 文件搜寻

```
VPATH = src:../headers
```

## 伪目标

取名不能和文件名重名

```
clean:
    rm *.o temp
```

为了避免和文件重名的这种情况，我们可以使用一个特殊的标记“.PHONY”来显式地指明一个目标是“伪目标”

```
.PHONY : clean
```

可以为伪目标指定所依赖的文件。伪目标同样可以作为“默认目标”，只要将其放在第一个

```
# 一口气生成若干个可执行文件

all : prog1 prog2 prog3
.PHONY : all

prog1 : prog1.o utils.o
    cc -o prog1 prog1.o utils.o

prog2 : prog2.o
    cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
    cc -o prog3 prog3.o sort.o utils.o
```

目标也可以成为依赖。所以，伪目标同样也可成为依赖

```
.PHONY : cleanall cleanobj cleandiff

cleanall : cleanobj cleandiff
    rm program

cleanobj :
    rm *.o

cleandiff :
    rm *.diff
```

## 多目标

自动化变量 **$@**

这个变量表示着目前规则中所有的目标的集合

```
bigoutput littleoutput : text.g
    generate text.g -$(subst output,,$@) > $@
```

```
bigoutput : text.g
    generate text.g -big > bigoutput
littleoutput : text.g
    generate text.g -little > littleoutput
```

`-$(subst output,,$@)` 中的 `$` 表示执行一个Makefile的函数，函数名为subst，后面的为参数。

这个函数是替换字符串的意思， `$@` 表示目标的集合，就像一个数组， `$@` 依次取出目标，并执于命令

## 静态模式

```
# demo1 

objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

我们的目标从`$object`中获取

`%.o` 表明要所有以 `.o` 结尾的目标，也就是 `foo.o bar.o` ，也就是变量 `$object` 集合的模式

而依赖模式 `%.c` 则取模式 `%.o` 的 `%` ，也就是 `foo bar` ，并为其加下 `.c` 的后缀，于是，我们的依赖目标就是 `foo.c bar.c` 。

而命令中的 `$<` 和 `$@` 则是自动化变量， `$<` 表示第一个依赖文件， `$@` 表示目标集（也就是“foo.o bar.o”）

等价于

```
foo.o : foo.c
    $(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
    $(CC) -c $(CFLAGS) bar.c -o bar.o
```

```
# demo2

files = foo.elc bar.o lose.o

$(filter %.o,$(files)): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
$(filter %.elc,$(files)): %.elc: %.el
    emacs -f batch-byte-compile $<
```

`$(filter %.o,$(files))`表示调用Makefile的filter函数，过滤`$files`集，只要其中模式为`%.o`的内容
1
## 书写命令