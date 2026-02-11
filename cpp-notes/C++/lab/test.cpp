#include <iostream>
#include <vector>

int main() {
    // 1. 自动类型推导 (C++11)
    auto i = 10; 
    
    // 2. 初始化列表 (C++11)
    std::vector<int> v = {1, 2, 3}; 
    
    // 3. 范围 for 循环 (C++11)
    for (auto x : v) {
        std::cout << x << " ";
    }
    
    std::cout << "C++11 验证成功" << std::endl;
    return 0;
}