#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "variant.h"

struct MyVisitor
{
    template<class T>
    void operator()(T& _in){_in += _in;}
};

template<class... T>
struct VariantContainer
{
    template<class V>
    void visit(V&& visitor)
    {
        for (auto& object : objects)
        {
            mpark::visit(visitor, object);
        }
    }
    using value_type = mpark::variant<T...>;
    std::vector<value_type> objects;
};

int main()
{    
    VariantContainer<int, double, std::string> variantCollection;
    variantCollection.objects.emplace_back(1);
    variantCollection.objects.emplace_back(2.2);
    variantCollection.objects.emplace_back("foo");
    
    

}