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

## 配置语法

描述域：使用 set_xx、add_xxx 等配置接口进行的配置区域。

脚本域：使用 on_xx、after_xxx 和 before_xxx 等配置接口的内部区域。

## 脚本配置域

```
target("hello")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"foo\"")
    after_build(function (target)
        print("my path: %s", target:targetfile())
    end)
```

```
target("hello")
    set_kind("binary")
    add_files("*.c")
    on_load(function (target)
        target:add("defines", "WORD=\"foo\"")
    end)
```

## 分离脚本域配置脚本

```
.
├── main.c
├── modules
│   └── load.lua
└── xmake.lua
```

```
// modules/load.lua

function main(target)
    target:add("defines", "WORD=\"foo\"")
end
```

```
target("hello")
    set_kind("binary")
    add_files("*.c")
    on_load("modules.load")
```

### 多目标程序配置

```
target("test1")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST1\"")

target("test2")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST2\"")
```

也可以显式的加上 target_end() 来明确每个 target 定义块的作用范围

```
target("test1")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST1\"")
target_end()

target("test2")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST2\"")
target_end()
```

## 全局配置和子配置

```
add_defines("ROOT")
set_optimize("fastest")
set_languages("c99")
add_includedirs("/tmp")

target("test1")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST1\"")

target("test2")
    set_kind("binary")
    add_files("*.c")
    add_defines("WORD=\"TEST2\"")
```

## 链接和编译的依赖控制

```
arget("test1")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("test2")

target("test2")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("test3")

target("test3")
    set_kind("binary")
    add_files("src/*.cpp")
```

test1 依赖 test2， test2 依赖 test3。

那么执行编译的时候的，test3 会优先编译，然后是编译 test2，最后才编译 test1。

即使设置 add_deps，xmake 默认也仅仅控制链接的依赖顺序，不控制源码编译的依赖顺序。

如果程序确实还是需要每个 target 的源码都要严格按照 add_deps 指定的依赖顺序去控制编译，那么我们只需要设置下编译策略，禁用跨目标并行编译即可

```
set_policy("build.across_targets_in_parallel", false)

target("test1")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("test2")

target("test2")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("test3")

target("test3")
    set_kind("binary")
    add_files("src/*.cpp")
```

## 静态库的依赖编译和继承

如何实现静态库和可执行程序的组合编译，通常我们开发一个静态库程序，都会同时写一个可执行程序去链接并使用库里面的接口。

如果我们使用 add_links 和 add_linkdirs 去链接依赖的静态库就会比较繁琐，既然这两者之间原本就是有依赖关系的，那么我们可以在配置 add_deps 后，通过可执行程序去自动集成对应的静态库的链接信息来简化配置。

通过配置 add_deps 可以集成依赖的静态库目标程序中的大部分链接信息，因此仅仅只需要通过关联依赖，就能够自动集成和使用静态库。

```
add_links
add_linkdirs
add_includedirs

--> 依赖继承

add_deps
```

```
xmake create -t static foo
```

```
// foo/xmake.lua

target("foo")
    set_kind("static")
    add_files("src/interface.cpp")

target("foo_demo")
    set_kind("binary")
    add_deps("foo")
    add_files("src/main.cpp")
```

其中 foo 就是静态库目标程序，而 foo_demo 是可执行目标程序，它们之间通过 add_deps("foo") 进行依赖关联，使得 foo_demo 可以自动集成 foo 静态库，而不再需要额外添加 add_linkdirs、add_links 等配置信息。

## 依赖配置的可见性设置

add_deps 除了能够自动继承静态库依赖的链接信息，还可以继承一些其它的配置信息，比如：add_includedirs、add_defines 等大部分配置都是可以被继承的。

不过只有这些配置被设置了 public、interface 等对外可见性设置，才能够支持对其它 target 导出配置被继承。

```
target("foo")
    set_kind("static")
    add_files("src/interface.cpp")
    add_defines("TEST", {public = true})
    add_includedirs("src", {interface = true})

target("foo_demo")
    set_kind("binary")
    add_deps("foo")
    add_files("src/main.cpp")
```

通过设置 {public = true} 将 -DTEST 的宏定义设置公开给其它依赖的子 target 继承，并且 foo 自身也会被定义。

而 add_includedirs("src", {interface = true}) 会把 src 作为头文件搜索目录，以接口的方式仅仅开放给其它 target 继承，而 foo 自身不会去设置它。

```
private : 默认设置，作为当前 target 的私有配置，不会被依赖的其它 target 所继承

public	: 公有配置，当前 target 依赖的子 target 都会被设置

interface : 接口设置，仅被依赖的子 target 所继承设置，当前 target 不参与
```

## 级联依赖继承

将依赖继承的层级加深一层，foo_demo 依赖 foo 静态库，而 foo 依赖 bar 静态库，并且我们把额外的 public 导出配置放置到 bar 目标程序中

```lua
target("bar")
    set_kind("static")
    add_files("src/interface.cpp")
    add_defines("TEST", {public = true})
    add_includedirs("src", {interface = true})

target("foo")
    set_kind("static")
    add_files("src/interface.cpp")
    add_deps("bar")

target("foo_demo")
    set_kind("binary")
    add_deps("foo")
    add_files("src/main.cpp")
```

xmake 在编译最终的 foo_demo 时候，也会自动继承 foo 和 bar 里面的静态库信息，并且继承上 public 和 interface 的导出配置，也就是说 add_deps 的继承是完全支持级联依赖的

## 动态库的依赖编译

只需要把之前的 xmake.lua 里面的 foo 目标类型改成 shared，就能编译生成动态库，并且自动关联上可执行程序

```lua
target("foo")
    set_kind("shared")
    add_files("src/interface.cpp")
    add_defines("TEST", {public = true})
    add_includedirs("src", {interface = true})

target("foo_demo")
    set_kind("binary")
    add_deps("foo")
    add_files("src/main.cpp")
```

通过 add_deps("foo") 配置的依赖继承关系，在 foo_demo 链接的时候，除了自动加了 -Lxx -lfoo 等链接信息外，还额外追加了 rpath 信息用来设置动态库的加载路径信息(-Wl,-rpath=$ORIGIN)

## 使用 Phony 目标组合多个依赖程序

它用于设置给定 target 作为一个空的目标对象，并不会参与实际的源码编译。

虽然不会参与实际编译，但是它可以和 add_deps 配合使用，用来组合一些需要一起编译的几个 target，实现一组 target 目标同时编译。

```lua
target("foo")
    set_kind("binary")
    add_files("src/*.cpp")

target("bar")
    set_kind("binary")
    add_files("src/*.cpp")

target("baz")
    set_kind("binary")
    add_files("src/*.cpp")

target("group")
    set_kind("phony")
    add_deps("foo", "bar")
```

通过 add_deps("foo", "bar") 关联上 foo 和 bar 这两个目标程序，相当于将它们组合到一起同时被 group 目标依赖

xmake build group 指定编译 group 目标，就会触发 foo 和 bar 这两个程序的编译，而 baz 目标由于没有被依赖，所以就不会被编译。

## 条件判断语法

```lua
if expr then
    -- ...
elseif not expr then
    -- ...
else
    -- ...
end
```

```lua
if a > b and not c or d then
    -- ...
end
```

## 判断当前目标平台

```lua
target("test")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_plat("linux") then
        add_defines("LINUX")
        add_files("src/linux/*.cpp")
    end
```

is_plat("linux") 来判断当前的目标平台是否为 Linux，

目标编译平台是可以通过 xmake f -p linux 显式设置的，它会跟 is_plat("linux") 保持一致，如果编译前没有配置过平台，那么默认会使用当前主机平台来作为目标编译平台。

显式指定编译平台，通常在交叉编译时候非常有用

## 判断编译指令架构

```lua
target("test")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_plat("linux") then
        add_defines("LINUX")
        add_files("src/linux/*.cpp")
    end
    if is_arch("x86_64") then
        add_files("src/x86_64/*.S")
    end
```

## 判断宿主平台架构

有时候我们还需要判断当前宿主环境的系统平台和指令架构（也就是编译器实际运行的系统平台）。

比如我们在 Linux 上编译生成 Android 系统的 so 库程序，那么 Linux 就是宿主平台，而 android 就是实际的目标程序平台，这通常在交叉编译环境中，更需要做如此区分。

但是对于编译的目标程序也是在当前系统环境下运行的，那么宿主平台和目标平台是完全一致的。

可以通过 is_host() 配置接口来判断宿主平台，xmake 不会从 xmake f -p/--plat 中去取目标平台的实际值，因为宿主平台在 xmake 运行时候就是固定的，所以我们可以直接从 os.host() 和 os.arch() 接口去取对应的值

```
xmake l os.host
xmake l os.arch
```

除了一些已知的 Android，Iphoneos 等特定系统平台，其它各种交叉编译工具链平台，我们都可以统一使用 xmake -p cross 交叉编译平台来编译。

## 判断编译模式

xmake f -m debug 切换各种编译模式，

不过有时候内置的 mode.debug，mode.release 等编译模式不一定完全满足需求。

这个时候，就需要大家自己来判断当前处于什么编译模式，然后自己去控制编译优化、调试符号等各种编译选项的开启和关闭。

```lua
if is_mode("release") then
    set_symbols("hidden")
    set_optimize("fastest")
    set_strip("all")
elseif is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
end

target("test")
    set_kind("binary")
    add_files("src/*.cpp")
```

## 判断自定义配置选项

```
xmake f --myopt=hello
```

```lua
option("myopt")
    set_showmenu(true)
    set_description("The test config option")
option_end()
```

set_showmenu(true) 用于启用对外导出，这样 help 帮助菜单中才能看到这个选项，用户才能在命令下使用。

```
xmake f --help | grep myopt
```

```lua
option("myopt")
    set_showmenu(true)
    set_description("The test config option")
option_end()

target("test")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_config("myopt", "hello") then
        add_defines("HELLO")
    end
```

```
xmake f --myopt=hello
xmake -rv
```

## 内置变量

xmake 提供了 $(varname) 的语法，来支持在配置字符串中直接传递内置变量

```
add_cxflags("-I$(projectdir)")
```

## 配置传递项目根目录

直接执行如下命令快速打印输出内置变量进行测试。

```
xmake l print '$(projectdir)'
```

```lua
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("$(projectdir)/inc")
```

```
$(buildir)：实际构建输出目录。
$(tmpdir)：临时目录。
$(curdir)：当前运行目录。
$(scriptdir)：当前 xmake.lua 配置脚本所在目录。
$(programdir)：xmake 安装程序的 lua 脚本根目录。
```

## 获取环境变量

我们还可以通过 $(env varname) 内置变量，在字符串中快速获取指定环境变量。

```lua
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("$(env HOME)")
```

```
// 打印所有的环境变量
xmake l os.getenvs
```

## 执行获取 shell 输出内容

调用 pkg-config 获取到实际的第三方链接库名

```lua
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_plat("linux") then
        add_ldflags("$(shell pkg-config --libs sqlite3)")
    end
```

不过通过执行外部 shell 命令来集成依赖库，我们并不推荐

## 读取配置选项

除了 xmake 内置的这些变量以外，只要是在 xmake f/config 配置命令中的所有参数选项配置，都是可以通过内置变量的方式来获取使用

```lua
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    set_targetdir("$(projectdir)/bin/$(plat)/$(arch)/$(mode)")
```

既然任意的 xmake f/config 配置选项参数都可以通过内置变量的方式获取到，那么我们自定义的配置选项，也可以用同样的方式获取到。

```lua
option("myopt")
    set_showmenu(true)
    set_description("The test config option")
option_end()

target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_defines("$(myopt)")
```

```
xmake f --myopt=TEST1
xmake -rv
```

# 大型c++项目组织

## 使用 includes 引入目录和文件

我们需要通过在每个子工程模块里面，单独创建 xmake.lua 来维护它们，然后使用 xmake 提供的 includes 接口，将它们按层级关系包含进来，最终变成一个树状结构。

```
tree .
.
├── src
│   ├── main.cpp
│   └── xmake.lua
├── tests
│   ├── main.cpp
│   └── xmake.lua
└── xmake.lua
```

```
// root
includes("src", "tests")
```

通过 includes 关联子工程的好处就是，我们不需要再手动进入每个子工程目录下执行 xmake 编译，所有的 xmake 命令操作还是可以在项目根目录下统一完成，因为通过 includes 引入后，整个项目不管结构多复杂，都是一个整体

默认情况下通过 includes("tests") 引用子目录，就可以直接导入子目录下 xmake.lua 配置，如果要导入其它文件名的配置文件，可以指定文件全名到 includes，例如 includes("tests/xmake.lua")。

## 模式匹配实现批量 includes

```
includes("*/xmake.lua")
```

通过 */xmake.lua 模式匹配，xmake 会自动遍历当前所有一级子目录下的 xmake.lua 文件，将其引入。整个模式匹配的用法跟 add_files 是完全一致的，因此我们也可以使用 **/xmake.lua 来实现递归模式匹配

## 根 xmake.lua 配置

```lua
set_project("hello")
set_version("1.0.1")

add_rules("mode.release", "mode.debug")

set_warnings("all", "error")
set_languages("c++11")
add_defines("ROOT")

includes("*/xmake.lua")
```

## 跨 xmake.lua 间目标依赖

只要是通过 includes 引用的所有 xmake.lua，其中的 target 定义即使在不同的子 xmake.lua 中，xmake 也会将它们全部加载进来，因此这些 target 之间的依赖关系还是可以正常配置，哪怕是跨 xmake.lua 也不会有任何影响。

```lua
add_defines("TEST")
target("test")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("foo", "bar")
```

## 预编译头文件

创建并编辑 src/stdafx.h 头文件，引入一些常用的 C++ 头文件。

```
#ifndef HEADER_H
#define HEADER_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <utility>
#include <exception>
#include <list>
#include <stack>
#include <complex>
#include <fstream>
#include <cstdio>
#include <iomanip>

#endif
```

预编译头文件的名字并不一定非得是 stdafx.h，可以取任意名字，这里仅仅只是沿用了 vs 项目里面的命名而已

添加 set_pcxxheader("src/stdafx.h") 的预编译设置

告诉编译器将 stdafx.h 作为预编译头文件，开启预编译模式

```lua
target("pcxxheader")
    set_kind("binary")
    add_files("src/*.cpp")
    set_pcxxheader("src/stdafx.h")
```

## 不同编译器对预编译的处理

xmake 会优先调用 gcc 去编译 stdafx.h 头文件，生成 stdafx.pch 命名的预编译头文件。然后，后续的其它源文件编译通过 -include stdafx.h 将其引入进来。

```
gcc -c -x c++-header -o src/stdafx.pch src/stdafx.h
gcc -c -include src/stdafx.h -o build/test.o src/test1.cpp
```

## 配置使用 C 预编译头文件

需要从 set_pcxxheader 改成 set_pcheader

```c
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#endif
```

```lua
target("pcheader")
    set_kind("binary")
    add_files("src/*.c")
    set_pcheader("src/stdafx.h")
```

# other

## 生成 compile_commands.json

```
xmake project -k compile_commands
```

## Build and run targets with given group pattern #1913

https://github.com/xmake-io/xmake/issues/1913


##

https://xmake.io/#/manual/builtin_variables?id=xmake-installation-script-directory

```lua
target("test")
    on_run(function (target)
        -- Copy the header file in the current script directory to the output directory
        os.cp("$(scriptdir)/xxx.h", "$(buildir)/inc")
    end)
```

```lua
after_install(function (target)
    os.cp("xxx/oldname", path.join(target:installdir(), "newname"))
end)
```

## option

https://github.com/xmake-io/xmake/issues/183

https://tboox.org/cn/2016/08/07/custom-option/


## valgrind

https://github.com/xmake-io/xmake/issues/636