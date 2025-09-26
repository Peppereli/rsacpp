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

int main() {
    cpp_int p, q, e;
    std::string plaintext;
    std::vector<cpp_int> ciphertext;
    std::cout << "Enter your plaintext: ";
    std::getline(std::cin, plaintext);
    std::cout << "Enter your p, q and e: ";
    std::cin >> p >> q >> e;

    cpp_int n = p * q;
    cpp_int r = (p - 1) * (q - 1);
    cpp_int d = mod_inverse(e, r);

    if (d == -1) {
        std::cerr << "Error: Modular inverse of e does not exist.\n";
        return 1;
    }

    for (char c : plaintext) {
        cpp_int encrypted_char = power(c, e, n);
        ciphertext.push_back(encrypted_char);
    }

    std::cout << "Ciphertext: ";
    for (cpp_int encrypted_char : ciphertext) {
        std::cout << encrypted_char << " ";
    }
    std::cout << "\n";

    std::string decrypted_text;
    for (cpp_int encrypted_char : ciphertext) {
        cpp_int decrypted_char = power(encrypted_char, d, n);
        char decrypted = static_cast<char>(decrypted_char.convert_to<long>());
        decrypted_text += decrypted;
    }

    std::cout << "Decrypted text: " << decrypted_text << "\n";
    std::cout << "r: " << r << " d: " << d << "\n";
    return 0;
}
