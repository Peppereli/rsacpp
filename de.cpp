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
    cpp_int element, d, n;
    std::vector<cpp_int> cipher;
    std::cout << "Enter d and n respecively: ";
    std::cin >> d >> n;
    std::cout << "Enter integers of the ciphertext, type a non-integer at the end to stop the input: ";
    while(std::cin >> element){
        cipher.push_back(element);
    }
    for (int i=0; i<cipher.size(); ++i){
        std::cout << cipher[i] << " ";
    }
    std::vector<std::string> s;
    for (int i=0; i<cipher.size(); ++i){
        cpp_int decrypted = power(cipher[i], d, n);
        std::string de_ch = static_cast<std::string>(decrypted.convert_to<long>());
        s.push_back(de_ch);
    }
    for (int i=0; i<s.size(); ++i){
        std::cout << s[i] << " ";
    }
}
