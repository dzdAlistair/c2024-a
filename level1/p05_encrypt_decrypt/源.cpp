#include <iostream>
#include <string>

// ���ܺ���
std::string encrypt(const std::string& text, int shift) {
    std::string result = "";

    for (char ch : text) {
        // �����д��ĸ
        if (isupper(ch)) {
            result += char((ch + shift - 'A') % 26 + 'A');
        }
        // ����Сд��ĸ
        else if (islower(ch)) {
            result += char((ch + shift - 'a') % 26 + 'a');
        }
        // ����ĸ�ַ����ֲ���
        else {
            result += ch;
        }
    }

    return result;
}

// ���ܺ���
std::string decrypt(const std::string& text, int shift) {
    // �����Ǽ��ܵ�����̣��ƶ�λ��ȡ��
    return encrypt(text, 26 - shift);
}

int main() {
    std::string input;
    int shift;

    // �����ַ������ƶ�λ��
    std::cout << "������Ҫ���ܵ��ַ���: ";
    std::getline(std::cin, input);
    std::cout << "�������ƶ�λ������Կ��: ";
    std::cin >> shift;

    // ����
    std::string encrypted = encrypt(input, shift);
    std::cout << "���ܺ���ַ���: " << encrypted << std::endl;

    // ����
    std::string decrypted = decrypt(encrypted, shift);
    std::cout << "���ܺ���ַ���: " << decrypted << std::endl;

    return 0;
}