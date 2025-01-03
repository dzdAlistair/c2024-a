#include <iostream>

// ��������ڵ�ṹ
struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

// ����������ӡ�ڵ��ֵ
void traverseList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// ��������
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next; // ������һ���ڵ�
        current->next = prev; // ��ת��ǰ�ڵ��ָ��
        prev = current;       // �ƶ� prev �� current
        current = next;
    }

    return prev; // �����µ�ͷ�ڵ�
}

// ���ҵ�һ��ֵΪ target �Ľڵ㣬���ؽڵ���ţ���0��ʼ��
int findFirstValue(Node* head, int target) {
    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->value == target) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // δ�ҵ�
}

// ������һ��ֵΪ target �Ľڵ㣬���ؽڵ���ţ���0��ʼ��
int findNextValue(Node* head, int target, int startIndex) {
    Node* current = head;
    int index = 0;

    // �ƶ��� startIndex ��λ��
    while (current != nullptr && index < startIndex) {
        current = current->next;
        index++;
    }

    // �� startIndex ��ʼ����
    while (current != nullptr) {
        if (current->value == target) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // δ�ҵ�
}

int main() {
    // ������������
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(5);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(5);

    // ����������ӡ�ڵ��ֵ
    std::cout << "����ڵ�ֵ: ";
    traverseList(head);

    // ��������
    head = reverseList(head);
    std::cout << "����������ڵ�ֵ: ";
    traverseList(head);

    // ���ҵ�һ��ֵΪ 5 �Ľڵ�
    int firstIndex = findFirstValue(head, 5);
    if (firstIndex != -1) {
        std::cout << "��һ��ֵΪ 5 �Ľڵ����: " << firstIndex << std::endl;
    }
    else {
        std::cout << "δ�ҵ�ֵΪ 5 �Ľڵ�" << std::endl;
    }

    // ������һ��ֵΪ 5 �Ľڵ�
    int nextIndex = findNextValue(head, 5, firstIndex + 1);
    if (nextIndex != -1) {
        std::cout << "��һ��ֵΪ 5 �Ľڵ����: " << nextIndex << std::endl;
    }
    else {
        std::cout << "δ�ҵ���һ��ֵΪ 5 �Ľڵ�" << std::endl;
    }

    // �ͷ������ڴ�
    Node* current = head;
    Node* nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}