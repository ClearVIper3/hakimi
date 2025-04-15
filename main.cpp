#include <cstdio>
#include <iostream>
#include <string>
#include <limits>
using namespace std;

const string usename = "hakimi";
const int password = 777;
const int falseK = 5;

typedef struct user {
    string number;    // 电话号码
    string company;   // 公司名称
    string name;      // 姓名
    struct user* next;
    struct user* prev;
} user;

// 全局指针，指向通讯录链表头部
user* head = nullptr;

bool login();

void input();
void update();
void delt();
void nameSearch();
void classSearch();
void sum();
void approSearch();
void menu();

int main()
{
    int n;
    if(!login()) return 0;
    menu();
    while(cin >> n && n)
    {
        // 清除换行符
        cin.ignore();

        switch(n)
        {
            case 1: input(); break;
            case 2: update(); break;
            case 3: delt(); break;
            case 4: nameSearch(); break;
            case 5: classSearch(); break;
            case 6: sum(); break;
            case 7: approSearch(); break;
            default: cout << "非法选择，请重试！" << endl; break;
        }
        cout << "按回车返回主菜单...";
        cin.get();  // 等待回车继续
        menu();
    }
    return 0;
}

void menu()
{
    // 清屏，不同平台可能需要调整
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t|-------------------------------通讯录系统-------------------------------|\n");
    printf("\t\t\t| 0.退出                                                                 |\n");
    printf("\t\t\t| 1.登记                                                                 |\n");
    printf("\t\t\t| 2.更新                                                                 |\n");
    printf("\t\t\t| 3.删除                                                                 |\n");
    printf("\t\t\t| 4.名字查找                                                             |\n");
    printf("\t\t\t| 5.类查找                                                               |\n");
    printf("\t\t\t| 6.人数                                                                 |\n");
    printf("\t\t\t| 7.模糊查找                                                             |\n");
    printf("\t\t\t|------------------------------------------------------------------------|\n");
    printf("\t\t\t\tchoose the number:");
}

bool login() {
    int attempts = falseK;  // 剩余尝试次数
    bool success = false;

    system("cls");
    while (attempts > 0) {
        if(attempts != falseK)cout << "剩余尝试次数：" << attempts << endl;

        cout << "请输入用户名：";
        string inputUsername;
        getline(cin, inputUsername);  // 读取用户名（可含空格）

        cout << "请输入密码：";
        int inputPassword;
        cin >> inputPassword;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (inputUsername == usename && inputPassword == password) {
            success = true;
            break;
        } else {
            cout << "用户名或密码错误！" << endl;
            attempts--;
            if (attempts > 0)
                cout << "请点击回车重试..." << endl;
                cin.get();
        }
        system("cls");
    }

    if (!success) {
        cout << "尝试次数已用完，登录失败！" << endl;
        return false;
    }
    return true;
}

void input()
{
    user* newUser = new user;

    cout << "请输入联系人姓名: ";
    getline(cin, newUser->name);

    cout << "请输入电话号码: ";
    getline(cin, newUser->number);

    cout << "请输入公司名称: ";
    getline(cin, newUser->company);

    newUser->next = nullptr;
    newUser->prev = nullptr;

    if(head == nullptr){
        head = newUser;
    }
    else{
        user* p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = newUser;
        newUser->prev = p;
    }

    cout << "\n联系人登记成功！" << endl;
}

void update(){
    string needName;
    cout << "想要修改谁的信息？";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr -> name != needName){
        ptr = ptr -> next;
    }
    if(!ptr){
        cout << "查无此人!" << endl;
        cin.ignore();
        return;
    }

    cout << "更改公司请输入 'C' || 更改电话号码请输入 'N': ";
    char op;
    cin >> op;
    cin.ignore();
    if(op == 'C'){
        cout << "新公司为:";
        getline(cin,ptr -> company);
    }
    else if(op == 'N'){
        cout << "新电话号码为:";
        getline(cin,ptr -> number);
    }
    cout << "\n修改联系人信息成功！" << endl;
}
void delt() {
    string needName;
    cout << "想要删除谁的信息？";
    cin >> needName;

    user* ptr = head;
    // 查找要删除的节点
    while(ptr && ptr->name != needName){
        ptr = ptr->next;
    }
    if(!ptr){
        cout << "查无此人!" << endl;
        cin.ignore();
        return;
    }

    // 删除的是头节点
    if(ptr == head){
        head = ptr->next;
        if(head != nullptr) {
            head->prev = nullptr;
        }
    } else {
        // 如果有前驱，将前驱的next指针指向当前节点的next
        ptr->prev->next = ptr->next;
        // 如果当前节点不是尾节点，则更新它后继节点的prev指针
        if(ptr->next != nullptr) {
            ptr->next->prev = ptr->prev;
        }
    }
    cin.ignore();
    delete ptr;
    cout << "\n联系人删除成功！" << endl;
}
void nameSearch(){
}
void classSearch(){
}
void sum(){
}
void approSearch(){
}
