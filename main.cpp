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
    //载入一下联系人数据
    readFile("contact.txt");
    if(!login()) return 0;
    menu();
    while(cin >> n && n) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除换行符

        switch(n) {
            case 1: input(); break;
            case 2: update(); break;
            case 3: delt(); break;
            case 4: nameSearch(); break;
            case 5: classSearch(); break;
            case 6: fuzzySearch(); break;
            case 7: sum(); break;
            case 8: show(); break;
            default: cout << "非法选择，请重试！" << endl; break;
        }
        cout << "按回车返回主菜单...";
        cin.get();  // 等待回车继续
        menu();
    }
    saveFile("contact.txt");
    return 0;
}

void menu() {
    system("cls");  // 清屏
    printf("\n\n\n");
    printf("\t\t\t|-------------------------------通讯录系统-------------------------------|\n");
    printf("\t\t\t| 0.退出                                                                 |\n");
    printf("\t\t\t| 1.登记                                                                 |\n");
    printf("\t\t\t| 2.更新                                                                 |\n");
    printf("\t\t\t| 3.删除                                                                 |\n");
    printf("\t\t\t| 4.名字查找                                                             |\n");
    printf("\t\t\t| 5.类查找                                                               |\n");
    printf("\t\t\t| 6.模糊查找                                                             |\n");
    printf("\t\t\t| 7.统计                                                                 |\n");
    printf("\t\t\t| 8.总览                                                                 |\n");
    printf("\t\t\t|------------------------------------------------------------------------|\n");
    printf("\t\t\t 请输入对应的功能编号（0-8）：");
}

bool login() {
    int attempts = falseK;  // 剩余尝试次数
    bool success = false;

    system("cls");
    while (attempts > 0) {
        if(attempts != falseK)
            cout << "剩余尝试次数：" << attempts << endl;

        cout << "请输入用户名：";
        string inputUsername;
        getline(cin, inputUsername);

        cout << "请输入密码：";
        string inputPassword;
        cin >> inputPassword;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (inputUsername == usename && inputPassword == password) {
            success = true;
            break;
        } else {
            cout << "\n用户名或密码错误！" << endl;
            attempts--;
            if (attempts > 0) {
                cout << "请点击回车重试..." << endl;
                cin.get();
            }
        }
        system("cls");
    }

    if (!success) {
        cout << "尝试次数已用完，登录失败！" << endl;
        return false;
    }
    return true;
}
