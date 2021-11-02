// 通过继承的方式展开参数包
//

#include <iostream>
using namespace std;

//定义整型序列
template <int...>
struct IndexSeq{};

//继承方式展开参数包
template <int N,int... Indexes>
struct MakeIndexs : MakeIndexs <N-1,N-1,Indexes...>{};

//模板特化，终止展开的条件
template <int... Indexes>
struct MakeIndexs<0,Indexes...>{
    typedef IndexSeq<Indexes...> type;
};
int main(int argc,char *argv[])
{
    MakeIndexs<3>::type m3;
    MakeIndexs<6>::type m6;

    cout << typeid(m3).name() <<endl;
    cout << typeid(m6).name() <<endl;
    return 0;
}
