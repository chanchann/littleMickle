#include <iostream>
using namespace std;
/**
 * @brief  
 * const 文件间共享
 * @note   
 * 这里声明了带extern，实现也带extern，就去其他地方寻找
 * @retval None
 */

extern const int a;

int main() {
    cout << a << endl;
    return 0;
}

