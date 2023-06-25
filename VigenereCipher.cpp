#include <iostream>
#include <string>
#include <chrono>

std::string encryptVigenere(const std::string& plaintext, const std::string& key) {
    std::string ciphertext = "";
    int keyLength = key.length();

    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = (c - base + key[i % keyLength] - base) % 26 + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += c;
        }
    }

    return ciphertext;
}

std::string decryptVigenere(const std::string& ciphertext, const std::string& key) {
    std::string plaintext = "";
    int keyLength = key.length();

    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = (c - base - (key[i % keyLength] - base) + 26) % 26 + base;
            plaintext += decryptedChar;
        } else {
            plaintext += c;
        }
    }

    return plaintext;
}

int main() {
    std::string plaintext;
    std::string key;

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, plaintext);

    std::cout << "Enter the key: ";
    std::getline(std::cin, key);

    // Measure encryption time
    auto startEncrypt = std::chrono::steady_clock::now();
    std::string ciphertext = encryptVigenere(plaintext, key);
    auto endEncrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> encryptTime = endEncrypt - startEncrypt;

    // Measure decryption time
    auto startDecrypt = std::chrono::steady_clock::now();
    std::string decryptedText = decryptVigenere(ciphertext, key);
    auto endDecrypt = std::chrono::steady_clock::now();
    std::chrono::duration<double> decryptTime = endDecrypt - startDecrypt;

    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    // Print the measured times
    std::cout << "Encryption Time: " << encryptTime.count() << " seconds" << std::endl;
    std::cout << "Decryption Time: " << decryptTime.count() << " seconds" << std::endl;

    return 0;
}