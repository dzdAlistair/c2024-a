#include <iostream>
#include <vector>
#include <chrono> // ���ڼ���ʱ��

// ������˹����ɸ��
void sieveOfEratosthenes(int n) {
    std::vector<bool> isPrime(n + 1, true); // ��ʼ��������Ϊ����
    isPrime[0] = isPrime[1] = false;        // 0 �� 1 ������

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            // ��� p �ı���Ϊ������
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // ��ӡ��������
    for (int p = 2; p <= n; ++p) {
        if (isPrime[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n = 1000; // ����
    std::cout << "2 �� 1000 ���ڵ���������Ϊ��" << std::endl;

    // ��¼��ʼʱ��
    auto start = std::chrono::high_resolution_clock::now();

    // ����ɸ������
    sieveOfEratosthenes(n);

    // ��¼����ʱ��
    auto end = std::chrono::high_resolution_clock::now();

    // ���㲢��ӡ��ʱ��
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "�ܼ���ʱ��: " << duration.count() << " ΢��" << std::endl;

    return 0;
}