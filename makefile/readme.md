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




