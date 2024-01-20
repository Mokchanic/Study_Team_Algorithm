#include <iostream>

typedef long long ll;

ll go(ll A, ll B, ll C){
    if (B == 0)
        return 1;
    if(B == 1)
        return A % C;

    ll ret = go(A, B/2, C);
    ret = (ret * ret) % C;

    if(B % 2){
        ret = (ret * A) % C;
    }

    return ret;
}

int main(){
    ll A, B, C, result;
    std::cin >> A >> B >> C;

    result = go(A, B, C);
    std::cout << result << std::endl;

    return 0;
}
