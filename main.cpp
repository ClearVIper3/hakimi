#include "contact.h"
#include "fileIO.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

const string usename = "hakimi";
const string password = "777";
const int falseK = 5;

bool login();
void menu();

int main() {
    int n;
    //����һ����ϵ������
    readFile("contact.txt");
    if(!login()) return 0;
    menu();
    while(cin >> n && n) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������з�

        switch(n) {
            case 1: input(); break;
            case 2: update(); break;
            case 3: delt(); break;
            case 4: nameSearch(); break;
            case 5: classSearch(); break;
            case 6: fuzzySearch(); break;
            case 7: sum(); break;
            case 8: show(); break;
            default: cout << "�Ƿ�ѡ�������ԣ�" << endl; break;
        }
        cout << "���س��������˵�...";
        cin.get();  // �ȴ��س�����
        menu();
    }
    saveFile("contact.txt");
    return 0;
}

void menu() {
    system("cls");  // ����
    printf("\n\n\n");
    printf("\t\t\t|-------------------------------ͨѶ¼ϵͳ-------------------------------|\n");
    printf("\t\t\t| 0.�˳�                                                                 |\n");
    printf("\t\t\t| 1.�Ǽ�                                                                 |\n");
    printf("\t\t\t| 2.����                                                                 |\n");
    printf("\t\t\t| 3.ɾ��                                                                 |\n");
    printf("\t\t\t| 4.���ֲ���                                                             |\n");
    printf("\t\t\t| 5.�����                                                               |\n");
    printf("\t\t\t| 6.ģ������                                                             |\n");
    printf("\t\t\t| 7.ͳ��                                                                 |\n");
    printf("\t\t\t| 8.����                                                                 |\n");
    printf("\t\t\t|------------------------------------------------------------------------|\n");
    printf("\t\t\t �������Ӧ�Ĺ��ܱ�ţ�0-8����");
}

bool login() {
    int attempts = falseK;  // ʣ�ೢ�Դ���
    bool success = false;

    system("cls");
    while (attempts > 0) {
        if(attempts != falseK)
            cout << "ʣ�ೢ�Դ�����" << attempts << endl;

        cout << "�������û�����";
        string inputUsername;
        getline(cin, inputUsername);

        cout << "���������룺";
        string inputPassword;
        cin >> inputPassword;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (inputUsername == usename && inputPassword == password) {
            success = true;
            break;
        } else {
            cout << "\n�û������������" << endl;
            attempts--;
            if (attempts > 0) {
                cout << "�����س�����..." << endl;
                cin.get();
            }
        }
        system("cls");
    }

    if (!success) {
        cout << "���Դ��������꣬��¼ʧ�ܣ�" << endl;
        return false;
    }
    return true;
}
