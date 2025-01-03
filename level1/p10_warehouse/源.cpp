#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// �������ṹ
struct Product {
    std::string model; // �����ͺ�
    int quantity;      // ��������
};

// ȫ�ֱ���������б�
std::vector<Product> inventory;

// ��ʾ����б�
void displayInventory() {
    if (inventory.empty()) {
        std::cout << "���Ϊ�գ�" << std::endl;
        return;
    }

    std::cout << "����б�" << std::endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << "�ͺ�: " << inventory[i].model << ", ����: " << inventory[i].quantity << std::endl;
    }
}

// ���
void addStock() {
    std::string model;
    int quantity;

    std::cout << "����������ͺ�: ";
    std::cin >> model;
    std::cout << "�������������: ";
    std::cin >> quantity;

    // �����Ƿ��Ѵ��ڸ��ͺ�
    for (auto& product : inventory) {
        if (product.model == model) {
            product.quantity += quantity;
            std::cout << "���ɹ���" << std::endl;
            return;
        }
    }

    // ��������ڣ�����»���
    inventory.push_back({ model, quantity });
    std::cout << "�»������ɹ���" << std::endl;
}

// ����
void removeStock() {
    std::string model;
    int quantity;

    std::cout << "����������ͺ�: ";
    std::cin >> model;
    std::cout << "�������������: ";
    std::cin >> quantity;

    // ���һ���
    for (auto& product : inventory) {
        if (product.model == model) {
            if (product.quantity >= quantity) {
                product.quantity -= quantity;
                std::cout << "����ɹ���" << std::endl;
            }
            else {
                std::cout << "��治�㣬�޷����⣡" << std::endl;
            }
            return;
        }
    }

    std::cout << "δ�ҵ��û��" << std::endl;
}

// ���ļ����ؿ������
void loadInventory() {
    std::ifstream file("inventory.txt");
    if (!file.is_open()) {
        std::cout << "δ�ҵ�����ļ������������ļ���" << std::endl;
        return;
    }

    inventory.clear();
    std::string model;
    int quantity;
    while (file >> model >> quantity) {
        inventory.push_back({ model, quantity });
    }

    file.close();
    std::cout << "������ݼ��سɹ���" << std::endl;
}

// ���������ݵ��ļ�
void saveInventory() {
    std::ofstream file("inventory.txt");
    if (!file.is_open()) {
        std::cerr << "�޷����������ݣ�" << std::endl;
        return;
    }

    for (const auto& product : inventory) {
        file << product.model << " " << product.quantity << std::endl;
    }

    file.close();
    std::cout << "������ݱ���ɹ���" << std::endl;
}

// ��ʾ�˵�
void showMenu() {
    std::cout << "===== ���������ϵͳ =====" << std::endl;
    std::cout << "1. ��ʾ����б�" << std::endl;
    std::cout << "2. ���" << std::endl;
    std::cout << "3. ����" << std::endl;
    std::cout << "4. �˳�����" << std::endl;
    std::cout << "��ѡ����: ";
}

int main() {
    // ����ʱ���ؿ������
    loadInventory();

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayInventory();
            break;
        case 2:
            addStock();
            break;
        case 3:
            removeStock();
            break;
        case 4:
            // �˳�ʱ����������
            saveInventory();
            std::cout << "�������˳���" << std::endl;
            return 0;
        default:
            std::cout << "��Чѡ�����������룡" << std::endl;
            break;
        }
    }

    return 0;
}