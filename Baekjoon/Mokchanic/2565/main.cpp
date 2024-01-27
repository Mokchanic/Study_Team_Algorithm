#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    int n = 0, a = 0, b = 0, len = 0;
    int lis[504] = {0};
    std::vector<std::pair<int, int>> v_line;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        std::cin >> a >> b;
        v_line.push_back({a, b});
    }
    std::sort(v_line.begin(), v_line.end());
    for(std::size_t i = 0; i < v_line.size(); i++){
        auto iter = std::lower_bound(lis, lis + len, v_line[i].second);
        if(*iter == 0){
            ++len;
        }
        *iter = v_line[i].second;
    }
    std::cout << n - len << "\n";
    return 0;
}
