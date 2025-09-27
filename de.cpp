#include <iostream>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>

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
    cpp_int element, d, n;
    std::vector<cpp_int> cipher;
    std::cout << "Enter d and n respecively: ";
    std::cin >> d >> n;
    std::cout << "Enter integers of the ciphertext, type a non-integer at the end to stop the input: ";
    while(std::cin >> element){
        cipher.push_back(element);
    }
    std::cin.clear();
    for (int i=0; i<cipher.size(); ++i){
        std::cout << cipher[i] << " ";
    }

    std::string decrypted_message = "";

for (int i=0; i<cipher.size(); ++i) {
    cpp_int decrypted_value = power(cipher[i], d, n);
    
    int char_code = decrypted_value.convert_to<int>();
    char decrypted_char = static_cast<char>(char_code); 
    
    decrypted_message += decrypted_char;
}

std::cout << "\nDecrypted Message: " << decrypted_message << "\n";
return 0;
}
