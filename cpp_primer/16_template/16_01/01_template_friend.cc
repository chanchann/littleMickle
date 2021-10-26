// https://www.jianshu.com/p/6613dbd0827d

// 1. 如果一个类模板包含一个非模板友元，则友元被授权可以访问所有类模板实例。
// 2. 如果一个非模板类包含一个模板友元，则所有友元实例被授权可以访问该类。
// 3. 如果一个类模板与友元模板拥有相同的类型参数，则类与友元为一对一的友好关系。
// 4. 如果一个类模板与友元模板拥有不同的类型参数，则类的每一个实例授权给所有模板实例。

// 3. 如果一个类模板与友元模板拥有相同的类型参数，则类与友元为一对一的友好关系。

//前置声明，在Blob中声明友元需要的
template <typename> class BlobPtr;
template <typename> class Blob; //运算符==中的参数所需要的
template <typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
    //每个Blob实例将访问权限授予与相同类型实例化的BlobPtr和相等运算符
    friend class BlobPtr<T>;
    friend  bool operator==(const Blob<T>&, const Blob<T>&);
};

Blob<char> ca; //BlobPtr<char>和operator==<char>都是本对象的友元
Blob<int> ia; //BlobPtr<int>和operator==<int>都是本对象的友元



