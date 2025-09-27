#include <iostream>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

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
    cpp_int p, q, e;
    cpp_int n = p * q;
    std::cout << "Enter p, q and e respectively: ";
    std::cin >> p >> q >> e;
    cpp_int r = (p - 1) * (q - 1);
    cpp_int d = mod_inverse(e, r);
    if (d == -1) {
        std::cerr << "Error: Modular inverse of e does not exist.\n";
        return 1;
    }
    std::cout << "Public key: " << p*q << "\nPrivate key: " << d << "\n";
    


}
