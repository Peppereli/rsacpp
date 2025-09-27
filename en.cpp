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
