#include <iostream>
#include <stdint.h>
#include <stack>

void fastIo(){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

auto main() -> int32_t{
    fastIo();
    while(true){
        std::string s;
        std::getline(std::cin, s);

        if(s == "."){
            break;
        }

        bool check = true;
        std::stack<int> my_stk;

        for(std::size_t i = 0; i < s.size(); i++){
            if(s[i] == ')'){
                if(my_stk.size() == 0 || my_stk.top() == '['){
                    check = false;
                    break;
                }
                else{
                    my_stk.pop();
                }
            }
            if(s[i] == ']'){
                if(my_stk.size() == 0 || my_stk.top() == '('){
                    check = false;
                    break;
                }
                else{
                    my_stk.pop();
                }
            }
            if(s[i] == '('){
                my_stk.emplace(s[i]);
            }
            if(s[i] == '['){
                my_stk.emplace(s[i]);
            }
        }
        if(check && my_stk.size() == 0){
            std::cout << "yes\n";
        }
        else{
            std::cout << "no\n";
        }
    }
    return 0;
}
