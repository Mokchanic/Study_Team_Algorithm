#include <cstdint>
#include <iostream>
#include <stack>

void fastIo(){
    std::ios_base::sync_with_stdio(0);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    return;
}

int32_t main(){
    fastIo();
    int n, ret = 0, cnt = 0;
    int d[200001] = {0}; // Initialization.. Code failure if not initialized.
    std::string s;
    std::stack<int> my_stk;
    std::cin >> n >> s;
    for(int i = 0; i < n; i++){
        if (s[i] == '('){
            my_stk.emplace(i);
        }
        else if (my_stk.size()){
            d[i] = d[my_stk.top()] = 1;
            my_stk.pop();
        }
    }
    for (int i = 0; i < n; i++){
        if (d[i]) {
            cnt++;
            ret = std::max(ret, cnt);
        }
        else {
            cnt = 0;
        }
    }
    std::cout << ret << "\n";
    return 0;
}
