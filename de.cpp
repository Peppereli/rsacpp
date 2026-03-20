#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

cpp_int modexp(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main() {
    cpp_int d, n, x;
    std::vector<cpp_int> cipher;

    std::cout << "Enter d and n respectively: ";
    std::cin >> d >> n;

    std::cout << "Enter ciphertext integers (non-number to stop): ";

    while (std::cin >> x) {
        cipher.push_back(x);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<unsigned char> bytes;
    bytes.reserve(cipher.size());

    for (const cpp_int& c : cipher) {
        cpp_int m = modexp(c, d, n);

        if (m < 0 || m >= n) {
            std::cerr << "Warning: invalid RSA block ignored: " << m << "\n";
            continue;
        }

        unsigned int val = m.convert_to<unsigned int>();

        if (val > 255) {
            std::cerr << "Warning: non-byte value ignored: " << val << "\n";
            continue;
        }

        bytes.push_back(static_cast<unsigned char>(val));
    }

    std::string message(bytes.begin(), bytes.end());

    std::cout << "\nDecrypted Message:\n";
    std::cout << message << "\n";

    return 0;
}
