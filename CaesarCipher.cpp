#include <iostream>
#include <string>
#include <chrono>

std::string encryptCaesar(const std::string& plaintext, int key) {
    std::string ciphertext = "";

    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = (c - base + key) % 26 + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += c;
        }
    }

    return ciphertext;
}

std::string decryptCaesar(const std::string& ciphertext, int key) {
    return encryptCaesar(ciphertext, 26 - key);
}

int main() {
    std::string plaintext;
    int key;

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, plaintext);

    std::cout << "Enter the key (a number from 1 to 25): ";
    std::cin >> key;

    // Measure encryption time
    auto startEncrypt = std::chrono::steady_clock::now();
    std::string ciphertext = encryptCaesar(plaintext, key);
    auto endEncrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> encryptTime = endEncrypt - startEncrypt;

    // Measure decryption time
    auto startDecrypt = std::chrono::steady_clock::now();
    std::string decryptedText = decryptCaesar(ciphertext, key);
    auto endDecrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> decryptTime = endDecrypt - startDecrypt;

    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    // Print the measured times
    std::cout << "Encryption Time: " << encryptTime.count() << " seconds" << std::endl;
    std::cout << "Decryption Time: " << decryptTime.count() << " seconds" << std::endl;

    return 0;
}