#include <iostream>
#include <string>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

cpp_int modularExponentiation(const cpp_int& base, const cpp_int& exponent, const cpp_int& modulus) {
    cpp_int result = 1;
    cpp_int exp = exponent;
    cpp_int b = base % modulus;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * b) % modulus;
        }
        b = (b * b) % modulus;
        exp /= 2;
    }

    return result;
}

cpp_int generateRandomPrime(int numBits) {
    cpp_int prime;

    do {
        prime = random_prime(numBits);
    } while (prime.bits() != numBits);

    return prime;
}

cpp_int generateRandomRelativelyPrime(const cpp_int& phi) {
    cpp_int e;

    do {
        e = random_below(phi);
    } while (gcd(e, phi) != 1);

    return e;
}

std::string rsaEncrypt(const std::string& plaintext, const cpp_int& e, const cpp_int& n) {
    std::string ciphertext = "";

    for (char c : plaintext) {
        cpp_int m(c);
        cpp_int encryptedChar = modularExponentiation(m, e, n);
        ciphertext += static_cast<char>(encryptedChar.convert_to<int>());
    }

    return ciphertext;
}

std::string rsaDecrypt(const std::string& ciphertext, const cpp_int& d, const cpp_int& n) {
    std::string plaintext = "";

    for (char c : ciphertext) {
        cpp_int encryptedChar(c);
        cpp_int decryptedChar = modularExponentiation(encryptedChar, d, n);
        plaintext += static_cast<char>(decryptedChar.convert_to<int>());
    }

    return plaintext;
}

int main() {
    std::string plaintext;
    cpp_int p, q, n, phi, e, d;

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, plaintext);

    // Generate random prime numbers p and q
    p = generateRandomPrime(256);
    q = generateRandomPrime(256);

    // Calculate n = p * q
    n = p * q;

    // Calculate phi = (p - 1) * (q - 1)
    phi = (p - 1) * (q - 1);

    // Generate random relatively prime number e
    e = generateRandomRelativelyPrime(phi);

    // Calculate d as the multiplicative inverse of e modulo phi
    d = powm(e, -1, phi);

    // Measure encryption time
    auto startEncrypt = std::chrono::steady_clock::now();
    std::string ciphertext = rsaEncrypt(plaintext, e, n);
    auto endEncrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> encryptTime = endEncrypt - startEncrypt;

    // Measure decryption time
    auto startDecrypt = std::chrono::steady_clock::now();
    std::string decryptedText = rsaDecrypt(ciphertext, d, n);
    auto endDecrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> decryptTime = endDecrypt - startDecrypt;

    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    // Print the measured times
    std::cout << "Encryption Time: " << encryptTime.count() << " seconds" << std::endl;
    std::cout << "Decryption Time: " << decryptTime.count() << " seconds" << std::endl;

    return 0;
}
