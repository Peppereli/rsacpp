#include <iostream>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

cpp_int power(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

cpp_int gcd(cpp_int a, cpp_int b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

cpp_int ext_gcd(cpp_int a, cpp_int b, cpp_int &x, cpp_int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    cpp_int x1, y1;
    cpp_int d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

cpp_int mod_inverse(cpp_int a, cpp_int m) {
    if (gcd(a, m) != 1) return -1;
    cpp_int x, y;
    ext_gcd(a, m, x, y);
    return (x % m + m) % m;
}

int main(){
    std::string s;
    std::vector<cpp_int> ciphertext;
    cpp_int n, e;
    std::cout << "Enter a plaintext: ";
    std::getline(std::cin, s);
    std::cout << "Enter n and e respectively: ";
    std::cin >> n >> e;
    for (char c:s){
        cpp_int en = power(c, e, n);
        ciphertext.push_back(en);
    }
    for (int i=0; i<ciphertext.size(); ++i){
        std::cout << ciphertext[i] << " ";
    }
    std::cout << "\n";
}
