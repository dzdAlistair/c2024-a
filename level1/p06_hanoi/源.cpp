#include <iostream>
#include <stack>
#include <utility>

// �ǵݹ麺ŵ��ʵ��
void hanoiNonRecursive(int n, char from, char to, char aux) {
    std::stack<std::pair<int, char>> stack; // ����ģ��ݹ����ջ
    stack.push({ n, from }); // ��ʼ״̬

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

        int num = current.first;
        char src = current.second;
        char dest = (src == from && num % 2 != 0) ? to : aux; // Ŀ������
        char temp = (src == from && num % 2 != 0) ? aux : to; // ��������

        if (num == 1) {
            std::cout << "������ 1 �� " << src << " �ƶ��� " << dest << std::endl;
        }
        else {
            // ģ��ݹ����
            stack.push({ num - 1, temp });
            stack.push({ 1, src });
            stack.push({ num - 1, src });
        }
    }
}

int main() {
    int n;

    // �������ӵ�����
    std::cout << "���������ӵ�����: ";
    std::cin >> n;

    // ���÷ǵݹ麺ŵ������
    hanoiNonRecursive(n, 'A', 'C', 'B');

    return 0;
}