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

## 书写命令

### 显示命令

```
@echo 正在编译XXX模块......

echo 正在编译XXX模块......
```

前者不会显示命令

### 命令执行

如果你要让上一条命令的结果应用在下一条命令时，你应该在同一行上使用分号分隔这两条命令。

```
exec:
    cd /home/xxx; pwd
```

### 命令出错

每当命令运行完后，make会检测每个命令的返回码，如果命令返回成功，那么make会执行下一条命令，当规则中所有的命令成功返回后，这个规则就算是成功完成了。

如果一个规则中的某个命令出错了（命令退出码非零），那么make就会终止执行当前规则，这将有可能终止所有规则的执行。

命令的出错并不表示就是错误的, 忽略命令的出错，我们可以在Makefile的命令行前加一个减号 - （在Tab键之后），标记为不管命令出不出错都认为是成功的

```
clean:
    -rm -f *.o
```

全局的办法，给make加上 -i 或是 --ignore-errors 参数

-k 或是 --keep-going ，这个参数的意思是，如果某规则中的命令出错了，那么就终止该规则的执行，但继续执行其它规则。

## 嵌套执行make

模块化

```
subsystem:
    cd subdir && $(MAKE)

# == 

# 子目录叫subdir

subsystem:
    $(MAKE) -C subdir
```

定义$(MAKE)宏变量的意思是，也许我们的make需要一些参数

总控Makefile的变量可以传递到下级的Makefile中（如果你显示的声明），但是不会覆盖下层的Makefile中所定义的变量，除非指定了 -e 参数。

```
export <variable ...>;

unexport <variable ...>;
```

```
# demo1

export variable = value

# == 

variable = value
export variable

# == 
export variable := value

# == 
variable := value
export variable
```

```
# demo2

export variable += value

# ==

variable += value
export variable
```

一个是 SHELL ，一个是 MAKEFLAGS ，这两个变量不管你是否export，其总是要传递到下层 Makefile中(系统级的环境变量)

但是make命令中的有几个参数并不往下传递，它们是 -C , -f , -h, -o 和 -W 

如果你不想往下层传递参数

```
subsystem:
    cd subdir && $(MAKE) MAKEFLAGS=
```

还有一个在“嵌套执行”中比较有用的参数， -w 或是 --print-directory 会在make的过程中输出一些信息

```
make: Entering directory `/home/hchen/gnu/make'.

make: Leaving directory `/home/hchen/gnu/make'
```

当你使用 -C 参数来指定make下层Makefile时， -w 会被自动打开的。

如果参数中有 -s （ --slient ）或是 --no-print-directory ，那么， -w 总是失效的。


## 定义命令包

```
define run-yacc
yacc $(firstword $^)
mv y.tab.c $@
endef
```

```
foo.c : foo.y
    $(run-yacc)
```

$^ 就是 foo.y

$@ 就是 foo.c

## 使用变量

在Makefile中的定义的变量，就像是C/C++语言中的宏一样，他代表了一个文本字串，在Makefile中执行的时候其会自动原模原样地展开在所使用的地方。

不过可以改变他

## 变量基础

使用时，需要给在变量名前加上 $ 符号，但最好用小括号 () 或是大括号 {} 把变量给包括起来。如果你要使用真实的 $ 字符，那么你需要用 $$ 来表示。

```
# demo1

objects = program.o foo.o utils.o
program : $(objects)
    cc -o program $(objects)

$(objects) : defs.h
```

```
# demo2 

foo = c
prog.o : prog.$(foo)
    $(foo)$(foo) -$(foo) prog.$(foo)

==

prog.o : prog.c
    cc -c prog.c

# 这里说明展开，但是不要这么用
```

## 变量中的变量

1. =

```
foo = $(bar)
bar = $(ugh)
ugh = Huh?

all:
    echo $(foo)
```

变量是可以使用后面的变量来定义

注意坏处 : 递归定义

```
CFLAGS = $(CFLAGS) -O

# or 

A = $(B)
B = $(A)
```

2. :=

```
x := foo
y := $(x) bar
x := later

# ==

y := foo bar
x := later
```

前面的变量不能使用后面的变量，只能使用前面已定义好了的变量

```
ifeq (0,${MAKELEVEL})
cur-dir   := $(shell pwd)
whoami    := $(shell whoami)
host-type := $(shell arch)
MAKE := ${MAKE} host-type=${host-type} whoami=${whoami}
endif
```

系统变量“MAKELEVEL”, 会记录了我们的当前Makefile的调用层数。

```
nullstring :=
space := $(nullstring) # end of the line
```

这里代表一个空格(empty +(空格) + #)

```
dir := /foo/bar    # directory to put the frobs in
```

dir这个变量的值是“/foo/bar”，后面还跟了4个空格，如果我们这样使用这样变量来指定别的目录——“$(dir)/file”那么就完蛋了。

3. ?=

```
FOO ?= bar
```

如果FOO没有被定义过，那么变量FOO的值就是“bar”

果FOO先前被定义过，那么这条语将什么也不做

其等价于：

```
ifeq ($(origin FOO), undefined)
    FOO = bar
endif
```

## 变量高级用法

### 变量的替换

```
foo := a.o b.o c.o
bar := $(foo:.o=.c)
```

```
foo := a.o b.o c.o
bar := $(foo:%.o=%.c)
```

### 把变量的值再当成变量

```
x = y
y = z
a := $($(x))
```

$(x)的值是“y”，所以$($(x))就是$(y)，于是$(a)的值就是“z”

### 追加变量值 +=

```
objects = main.o foo.o bar.o utils.o
objects += another.o
```

如果变量之前没有定义过，那么， += 会自动变成 =

如果前面有变量定义，那么 += 会继承于前次操作的赋值符。如果前一次的是 := ，那么 += 会以 := 作为其赋值符, 前次的赋值符是 = ，所以 += 也会以 = 来做为赋值

### override 指示符

如果有变量是通常make的命令行参数设置的，那么Makefile中对这个变量的赋值会被忽略。

如果你想在Makefile中设置这类参数的值，那么，你可以使用“override”指示符

```
override <variable>; = <value>;

override <variable>; := <value>;

override <variable>; += <more text>;
```

### 多行变量 define

```
define two-lines
echo foo
echo $(bar)
endef
```

### 环境变量

CFLAGS

### 目标变量

作用范围只在这条规则以及连带规则中，所以其值也只在作用范围内有效。而不会影响规则链以外的全局变量的值

```
<target ...> : <variable-assignment>;

<target ...> : overide <variable-assignment>
```

```
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
    $(CC) $(CFLAGS) prog.o foo.o bar.o

prog.o : prog.c
    $(CC) $(CFLAGS) prog.c

foo.o : foo.c
    $(CC) $(CFLAGS) foo.c

bar.o : bar.c
    $(CC) $(CFLAGS) bar.c
```

不管全局的 $(CFLAGS) 的值是什么，在prog目标，以及其所引发的所有规则中（prog.o foo.o bar.o的规则）， $(CFLAGS) 的值都是 -g

### 模式变量

## 使用条件判断

```makefile
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq ($(CC),gcc)
    $(CC) -o foo $(objects) $(libs_for_gcc)
else
    $(CC) -o foo $(objects) $(normal_libs)
endif
```

更为简洁 : 

```makefile
libs_for_gcc = -lgnu
normal_libs =

ifeq ($(CC),gcc)
    libs=$(libs_for_gcc)
else
    libs=$(normal_libs)
endif

foo: $(objects)
    $(CC) -o foo $(objects) $(libs)
```

ifdef 只是测试一个变量是否有值，其并不会把变量扩展到当前位置

```
# demo1

bar =
foo = $(bar)
ifdef foo
    frobozz = yes
else
    frobozz = no
endif

# demo2

foo =
ifdef foo
    frobozz = yes
else
    frobozz = no
endif
```

make是在读取Makefile时就计算条件表达式的值，并根据条件表达式的值来选择语句

不要把自动化变量（如 $@ 等）放入条件表达式中，因为自动化变量是在运行时才有的。

## 使用函数

```makefile
comma:= ,
empty:=
space:= $(empty) $(empty)
foo:= a b c
bar:= $(subst $(space),$(comma),$(foo))
```

调用了函数 subst ，这是一个替换函数，这个函数有三个参数，第一个参数是被替换字串，第二个参数是替换字串，第三个参数是替换操作作用的字串。

这个函数也就是把 $(foo) 中的空格替换成逗号，所以 $(bar) 的值是 a,b,c 。

### 字符串处理函数

1. subst

字符串替换函数

```
$(subst <from>,<to>,<text>)
```

```
$(subst ee,EE,feet on the street)
```
2. patsubst

模式字符串替换函数。

```
$(patsubst <pattern>,<replacement>,<text>)
```

```
$(patsubst %.c,%.o,x.c.c bar.c)
```

把字串 x.c.c bar.c 符合模式 %.c 的单词替换成 %.o ，返回结果是 x.c.o bar.o

3. strip

去空格函数,去掉 <string> 字串中开头和结尾的空字符

```
$(strip <string>)
```

```
$(strip a b c )
```

4. findstring

查找字符串函数

在字串 <in> 中查找 <find> 字串。

```
$(findstring <find>,<in>)
```

```
$(findstring a,a b c)
$(findstring a,b c)
```

第一个函数返回 a 字符串，第二个返回空字符串

5. filter

过滤函数

以 <pattern> 模式过滤 <text> 字符串中的单词，保留符合模式 <pattern> 的单词。可以有多个模式。

```
$(filter <pattern...>,<text>)
```

```
sources := foo.c bar.c baz.s ugh.h
foo: $(sources)
    cc $(filter %.c %.s,$(sources)) -o foo
```

`$(filter %.c %.s,$(sources))` 返回的值是 `foo.c bar.c baz.s` 。

6. filter-out

以 <pattern> 模式过滤 <text> 字符串中的单词，去除符合模式 <pattern> 的单词。可以有多个模式。

```
$(filter-out <pattern...>,<text>)
```

```
objects=main1.o foo.o main2.o bar.o
mains=main1.o main2.o
```

$(filter-out $(mains),$(objects)) 返回值是 foo.o bar.o 。

7. sort

给字符串 <list> 中的单词排序（升序）。

```
$(sort <list>)
```

`$(sort foo bar lose)` 返回 `bar foo lose` 。

Be careful : sort 函数会去掉 <list> 中相同的单词。

