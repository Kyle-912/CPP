#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Function to clean the text: remove non-letter characters and convert to lowercase
std::string cleanText(const std::string &text)
{
    std::string cleaned;
    for (char c : text)
    {
        if (std::isalpha(c))
        {
            cleaned += std::tolower(c);
        }
    }
    return cleaned;
}

// Function to encrypt using the Vigenère cipher
std::string vigenereEncrypt(const std::string &plaintext, const std::string &key)
{
    std::string cleanedText = cleanText(plaintext);
    std::string ciphertext;
    int keyLength = key.length();
    int textLength = cleanedText.length();

    for (int i = 0; i < textLength; ++i)
    {
        int shift = key[i % keyLength] - 'a';
        char encryptedChar = (cleanedText[i] - 'a' + shift) % 26 + 'a';
        ciphertext += encryptedChar;
    }

    return ciphertext;
}

// Function to format the ciphertext into groups of 8 characters, with 8 groups per line
std::string formatCiphertext(const std::string &ciphertext)
{
    std::string formatted;
    int length = ciphertext.length();

    for (int i = 0; i < length; ++i)
    {
        if (i > 0 && i % 8 == 0)
        {
            formatted += ' ';
            if (i % 64 == 0)
            {
                formatted += '\n';
            }
        }
        formatted += ciphertext[i];
    }

    return formatted;
}

int main()
{
    std::string key = "mykey";

    std::string plaintext1 = "[Insert first piece of English prose of at least 2000 characters here]";
    std::string plaintext2 = "[Insert second piece of English prose of at least 2000 characters here]";

    std::string ciphertext1 = vigenereEncrypt(plaintext1, key);
    std::string ciphertext2 = vigenereEncrypt(plaintext2, key);

    std::string formattedCiphertext1 = formatCiphertext(ciphertext1);
    std::string formattedCiphertext2 = formatCiphertext(ciphertext2);

    std::cout << "Ciphertext 1:\n"
              << formattedCiphertext1 << "\n";
    std::cout << "Ciphertext 2:\n"
              << formattedCiphertext2 << "\n";

    return 0;
}
