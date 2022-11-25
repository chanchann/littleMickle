## basic

xmake create 

xmake run

## debug

```
xmake f -m debug
xmake
xmake run -d
```

## install 

```
xmake (un)install -y
```

```
xmake [task] [options] [target]
```

## build

```
-v/--verbose：查看详细完整的编译命令。
-r/--rebuild：强制重新编译所有代码。
-j/--jobs：指定多任务编译的并行任务数。
-w/--warning：编译过程中显示编译警告信息。
```

## 切换编译输出目录

```
xmake f -o /tmp/build
```

## config

```
(xmake f 是 xmake config 的简写)

xmake f -v
```

## 添加 C/C++ 编译选项

```
--cflags：仅仅添加 C 编译选项。
--cxxflags：仅仅添加 C++ 编译选项。
--cxflags：同时添加 C/C++ 编译选项。

xmake f --cxflags="-DTEST"
xmake -rv
```

## 添加链接库和搜索路径

```
xmake f --ldflags="-L/tmp -lpthread"
xmake -rv

xmake f --links="pthread" --linkdirs="/tmp"
xmake -rv
```

## 切换到 clang 编译器

```
xmake f --toolchain=clang
xmake -rv
```

## 重置所有配置

```
xmake f -c
xmake -rv
```

## show

```
xmake show
```

```
xmake show -t hello
```

## update

```
xmake update -f
```

## xmake.lua 

```c
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")

4 typs : phony, binary, static, shared
```

## static / shared

```
xmake create -t static(shared) hello_static

add_rules("mode.debug", "mode.release")

target("hello_shared")
    set_kind("shared") -- 设置为动态库目标程序
    add_files("src/interface.cpp")

target("hello_shared_demo")
    set_kind("binary")
    add_deps("hello_shared")
    add_files("src/main.cpp")

add_deps("hello_shared") 进行依赖关联
```

## 编译选项

```
add_rules("mode.debug", "mode.release")

target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_cxflags("-DTEST1")
```

## 添加宏定义

add_defines

```
add_rules("mode.debug", "mode.release")

target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_cxflags("-DTEST1")
    add_defines("TEST2")
```

## 头文件路径和链接库配置

```
add_includedirs：添加头文件搜索目录。
add_linkdirs：添加库搜索目录。
add_links：添加链接库。
add_syslinks：添加系统链接库。
```

add_syslinks 通常用于添加一些系统依赖库，比如 pthread，这样 xmake 会把这些系统库链接放置的更靠后些。

```
add_rules("mode.debug", "mode.release")

target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_cxflags("-DTEST1")
    add_defines("TEST2")
    add_links("z")
    add_syslinks("pthread")
    add_linkdirs("/tmp")
    add_includedirs("/tmp")
```

## 设置语言标准

```
-- 设置 c 代码标准：c99， c++ 代码标准：c++11
set_languages("c99", "c++11")
```

## 设置编译优化

```
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_cxflags("-DTEST1")
    add_defines("TEST2")
    add_links("z")
    add_syslinks("pthread")
    add_linkdirs("/tmp")
    add_includedirs("/tmp")
    set_languages("c99", "c++11")
    if is_mode("release") then
        set_optimize("fastest") 
        set_strip("all")
        set_symbols("hidden")
    end
```

其中 set_optimize("fastest") 就是添加 -O3 的编译优化开关，而 set_strip("all") 和 set_symbols("hidden") 用于去掉调试符号数据，使得程序更小。

## 添加源文件

```
add_files("src/test_*.c", "src/**.cpp")
```

其中通配符 * 表示匹配当前目录下源文件，而 ** 则递归匹配多级目录下的源文件。

```
add_rules("mode.debug", "mode.release")

target("hello")
    set_kind("binary")
    add_files("**.cpp")
```

## 过滤源文件

```
use | 

target("hello")
    set_kind("binary")
    add_files("src/**.cpp|test/*.cpp")
```

还有需要注意的一点是，为了使得描述上更加的精简，| 之后的过滤描述都是基于前一个模式：src/**.cpp 中 * 所在的目录作为根目录，也就是 src 目录的基础上来过滤匹配的，所以后面的过滤子模式只需要设置 test/*.cpp 而不是 src/test/*.cpp。

## thirdparty

直接集成使用系统库

```
xmake create -l c crc32
```

-l c 参数指定当前创建的 crc32 工程是基于 C 语言的，

```
target("crc32")
    set_kind("binary")
    add_files("src/*.c")
    add_links("z")
    add_linkdirs("/usr/lib/x86_64-linux-gnu")
```

## 自动查找系统库

为了更加通用化的适配系统库路径，可以使用 find_packages 来自动查找 zlib 库所在的位置，通过这种方式集成之前，我们可以先尝试直接执行下面的命令，来探测 zlib 库的位置信息，对这个接口返回的信息有个大概的了解。

```
xmake l find_packages zlib
{
  {
    linkdirs = {
      "/usr/lib/x86_64-linux-gnu"
    },
    links = {
      "z"
    }
  }
}
```

在 target 定义下面新增一个 on_load() 脚本块，在里面调用 find_packages("zlib") 将探测到的 zlib 库信息直接动态设置到 target 里面去就行了

```
target("crc32")
    set_kind("binary")
    add_files("src/*.c")
    add_links("z")
    add_linkdirs("/usr/lib/x86_64-linux-gnu")
    on_load(function (target)
        target:add(find_packages("zlib"))
    end)
```

不过需要注意的一点是：xmake 默认会缓存依赖包的检测结果，并不是每次编译都会重新检测，如果之前检测失败，那么结果也会缓存，这个时候我们可以执行 xmake f -c 在配置时候，忽略之前的缓存内容，就会自动重新触发各种检测。

## add_requires

```
add_requires("zlib", {system = false})

target("crc32")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("zlib")
```

需要注意的一点是，上面的配置中我们额外加上了 {system = false} 是因为当前的实验环境中已经存在了 zlib 库，所以 add_requires("zlib") 默认会优先自动检测系统环境中的 zlib 库，如果存在就直接使用，也就是内置了 find_packages("zlib") 的逻辑。

而这里出于演示远程下载的逻辑，我们通过配置 {system = false} 强制触发远程下载，人为忽略了系统库的探测逻辑，在实际项目中，大家可根据自己的需求来决定是否配置这个选项。

我们的包检测结果都是有本地缓存的，第二次编译并不会再触发依赖包的下载安装，会直接参与集成编译。

## 卸载和重装依赖包

xmake require --uninstall zlib

不过需要注意的是，虽然卸载了包，但是当前项目的配置缓存还在，如果继续执行 xmake 命令，还是会使用缓存的 zlib 包信息。

因此可以添加 -c 参数给 xmake config，也就是执行下 xmake f -c 命令，强制忽略缓存配置，触发依赖包的重新检测逻辑。

## 语义版本设置

```
add_requires("zlib", {system = false})
add_requires("tbox 1.6.*", "pcre2 >10.0")

target("crc32")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("zlib", "tbox", "pcre2")
```

如果当前依赖包有 git 仓库，也可以集成 git 仓库的 master/dev 分支依赖包，只需要把版本号换成对应的分支名就行了

```
add_requires("tbox master")
add_requires("tbox dev")
```

## 查看依赖库信息

xmake require --info zlib

## conan

```
add_requires("CONAN::zlib/1.2.11@conan/stable", {alias = "zlib"})

target("crc32")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("zlib")
```



