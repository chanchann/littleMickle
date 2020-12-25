## 流

c++流是读写(输入和输出)逻辑的通用实现，能够统一的模式读写数据。

cin遇到空白停止插入，需要整行输入包括空白getline()

## std::fstream 处理文件

open(),close()

只想读取文件，务必使用ifstream, 反之只想写入文件

务必is_open核实

记得close

## https://www.zhihu.com/question/24734041