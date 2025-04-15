#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

const string usename = "hakimi";
const string password = "777";
const int falseK = 5;

int len = 0;
typedef struct user {
    string name;      // 姓名
    string category;  // 关系
    string number;    // 电话号码
    string company;   // 公司名称
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
void fuzzySearch();
void show();
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
            case 6: fuzzySearch(); break;
            case 7: sum(); break;
            case 8: show(); break;
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
        if(attempts != falseK)cout << "剩余尝试次数：" << attempts << endl;

        cout << "请输入用户名：";
        string inputUsername;
        getline(cin, inputUsername);  // 读取用户名（可含空格）

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
    len++;
    user* newUser = new user;

    cout << "请输入联系人姓名（如：张三）：";
    getline(cin, newUser->name);

    cout << "请输入其电话号码（如：13800138000）：";
    getline(cin, newUser->number);

    cout << "请输入其公司名称（如：腾讯）：";
    getline(cin, newUser->company);

    cout << "请输入其类别（如：朋友/家人/同事）：";
    getline(cin, newUser->category);

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
    cout << "请输入要修改的联系人姓名（区分大小写）：";

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

    cout << "请输入要修改的信息类型（输入 C 表示公司，N 表示电话号码）：";
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
    cout << "请输入要删除的联系人姓名（区分大小写）：";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr->name != needName){
        ptr = ptr->next;
    }
    if(!ptr){
        cout << "查无此人!" << endl;
        cin.ignore();
        return;
    }
    len--;
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
    cout << "请输入要查找的姓名或姓：";
    string keyWord;
    cin >> keyWord;
    cin.ignore();

    bool found = false;
    user* ptr = head;
    while(ptr)
    {
        if(ptr -> name.find(keyWord) != string::npos)
        {
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr -> name << endl;
            cout << "关系: " << ptr -> category << endl;
            cout << "电话号码: " << ptr -> number << endl;
            cout << "公司: " << ptr -> company << endl << endl;
        }
        ptr = ptr -> next;
    }

    if(!found)
        cout << "\n未找到相关联系人!" << endl;
}
void classSearch(){
    cout << "请输入要查找的联系人类别（如：朋友/同事/家人）：";
    string keyWord;
    cin >> keyWord;
    cin.ignore();

    bool found = false;
    user* ptr = head;
    while(ptr)
    {
        if(ptr -> category.find(keyWord) != string::npos)
        {
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr -> name << endl;
            cout << "关系: " << ptr -> category << endl;
            cout << "电话号码: " << ptr -> number << endl;
            cout << "公司: " << ptr -> company << endl << endl;
        }
        ptr = ptr -> next;
    }

    if(!found)
        cout << "\n未找到相关联系人!" << endl;
}
void sum(){
    unordered_map<string,int> mp;
    user* ptr = head;
    while(ptr)
    {
        string cate = ptr -> category;
        mp[cate]++;
        ptr = ptr -> next;
    }

    cout << "------------- 数据统计 ------------" << endl;
    cout << "| " << left << setw(20) << "分类名称" << "| " << setw(10) << "人数" << "|" << endl;
    cout << "-----------------------------------" << endl;

    unordered_map<string, int>::const_iterator it;
    for (it = mp.begin(); it != mp.end(); ++it) {
        cout << "| " << left << setw(20) << it->first
             << "| " << setw(10) << it->second << "|" << endl;
    }

    cout << "-----------------------------------" << endl;
}

void fuzzySearch(){
    cout << "请输入要模糊搜索的关键词（可输入多个，使用英文加号 '+' 分隔，如：张+腾讯）：";
    string input;
    getline(cin, input);

    // 分割关键词
    vector<string> keywords;
    size_t pos = 0;
    while ((pos = input.find('+')) != string::npos) {
        string token = input.substr(0, pos);
        keywords.push_back(token);
        input.erase(0, pos + 1);
    }
    // 加入最后一个关键词
    if (!input.empty())
        keywords.push_back(input);

    bool found = false;
    user* ptr = head;

    while(ptr){
        // 将要搜索的内容整合成一个字符串，便于查找
        string content = ptr->name + ptr->number + ptr->company + ptr->category;
        bool match = true;

        for(const string& kw : keywords){
            if(content.find(kw) == string::npos){
                match = false;
                break;
            }
        }

        if(match){
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr->name << endl;
            cout << "关系: " << ptr->category << endl;
            cout << "电话号码: " << ptr->number << endl;
            cout << "公司: " << ptr->company << endl << endl;
        }

        ptr = ptr->next;
    }

    if(!found){
        cout << "\n未找到符合条件的联系人！" << endl;
    }
}
void show(){
    if (!head) {
        cout << "通讯录为空！" << endl;
        return;
    }

    cout << "*总共有" << len << "位联系人*\n" << endl;
    user* ptr = head;
    while(ptr){
        cout << "-----联系人-----" << endl;
        cout << "姓名: " << ptr->name << endl;
        cout << "关系: " << ptr->category << endl;
        cout << "电话号码: " << ptr->number << endl;
        cout << "公司: " << ptr->company << endl << endl;
        ptr = ptr -> next;
    }
}

