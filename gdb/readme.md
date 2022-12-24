|命令	|简写形式	|说明|
| ----- | --------- | ----------- |
|list	|l|	查看源码|
|backtrace	|bt、where|	打印函数栈信息|
|next	|n|	执行下一行|
|step	|s	|一次执行一行，遇到函数会进入|
|finish|		运行到函数结束|
|continue|	c	|继续运行|
|break|	b	|设置断点|
|info breakpoints|		显示断点信息|
|delete	|d|	删除断点|
|print|	p	|打印表达式的值|
|run	|r|	启动程序|
|until	|u	|执行到指定行|
|info|	i|	显示信息|
|help|	h	|帮助信息|

### 执行外部命令

```
(gdb) !shell 命令
```

### list

```
list lineno

list filename:lineno

list funcname

list filename:funcname
```

## break

```
break 行号

break 文件名 : 行号

break 函数名

break 文件名 : 函数名

info breakpoints
```

```
Num 列代表断点编号，该编号可以作为 delete/enable/disable 等控制断点命令的参数
Type 列代表断点类型，一般为 breakpoint
Disp 列代表断点被命中后，该断点保留(keep)、删除(del)还是关闭(dis)
Enb 列代表该断点是 enable(y) 还是 disable(n)
Address 列代表该断点处虚拟内存的地址
What 列代表该断点在源文件中的信息
```

```
delete Num

delete，不带任何参数，默认删除所有断点：
```

```
disable Num

disable，不带任何参数，默认关闭所有断点。

enable Num，启用指定断点

enable，不带任何参数，默认启用所有断点。
```

```
enable once Num，断点 hit 一次之后关闭该断点

enable delete Num，断点 hit 一次之后删除该断点

// 这两个命令影响的是 info breakpoints 的 Disp 列，表示该断点被命中之后的行为。
```

## 打印变量

```
info locals

打印当前断点处所在函数的所有局部变量的值，不包括函数参数。
```

```
print 变量或表达式

打印表达式的值，可显示当前函数的变量的值、全局变量的值等

print/FMT 可以控制打印的格式，常见的有x(十六进制)、t(二进制)、c(显示为字符)等。
```

## 启动程序

```
run

// 不带任何参数，启动待调试程序，不传递参数。

run 参数

// 有些程序需要跟参数，直接带上参数列表即可，会传递给 main 函数的 argc、argv 变量。
```

## 单步命令

```

```


