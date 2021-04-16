## priority_queue

#include <queue>

std::priority_queue:在优先队列中，优先级高的元素先出队列，并非按照先进先出的要求，类似一个堆(heap)。

priority_queue<Type, Container, Functional>, 其中Type为数据类型，Container为保存数据的容器，Functional为元素比较方式

Container必须是用数组实现的容器，比如 vector, deque. STL里面默认用的是vector. 比较方式默认用operator< , 所以如果把后面两个参数缺省的话，优先队列就是大顶堆，队头元素最大。

和队列基本操作相同:

top 访问队头元素

empty 队列是否为空

size 返回队列内元素个数

push 插入元素到队尾 (并排序)

emplace 原地构造一个元素并插入队列

pop 弹出队头元素

swap 交换内容

