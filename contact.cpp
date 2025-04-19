#include "contact.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <limits>
using namespace std;

// 定义全局变量
user* head = nullptr;
int len = 0;

void input() {
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

    if (head == nullptr) {
        head = newUser;
    } else {
        user* p = head;
        while(p->next != nullptr) {
            p = p->next;
        }
        p->next = newUser;
        newUser->prev = p;
    }
    cout << "\n联系人登记成功！" << endl;
}

void update() {
    string needName;
    cout << "请输入要修改的联系人姓名（区分大小写）：";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr->name != needName) {
        ptr = ptr->next;
    }
    if(!ptr) {
        cout << "查无此人!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "请输入要修改的信息类型（输入 C 表示公司，N 表示电话号码）：";
    char op;
    cin >> op;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(op == 'C'){
        cout << "新公司为:";
        getline(cin, ptr->company);
    }
    else if(op == 'N'){
        cout << "新电话号码为:";
        getline(cin, ptr->number);
    }
    cout << "\n修改联系人信息成功！" << endl;
}

void delt() {
    string needName;
    cout << "请输入要删除的联系人姓名（区分大小写）：";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr->name != needName) {
        ptr = ptr->next;
    }
    if(!ptr) {
        cout << "查无此人!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    len--;
    // 删除头节点
    if(ptr == head) {
        head = ptr->next;
        if(head != nullptr) {
            head->prev = nullptr;
        }
    } else {
        // 更新前驱和后继指针
        ptr->prev->next = ptr->next;
        if(ptr->next != nullptr) {
            ptr->next->prev = ptr->prev;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    delete ptr;
    cout << "\n联系人删除成功！" << endl;
}

void nameSearch() {
    cout << "请输入要查找的姓名或姓：";
    string keyWord;
    cin >> keyWord;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    user* ptr = head;
    while(ptr) {
        if(ptr->name.find(keyWord) != string::npos) {
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr->name << endl;
            cout << "关系: " << ptr->category << endl;
            cout << "电话号码: " << ptr->number << endl;
            cout << "公司: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\n未找到相关联系人!" << endl;
}

void classSearch() {
    cout << "请输入要查找的联系人类别（如：朋友/同事/家人）：";
    string keyWord;
    cin >> keyWord;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    user* ptr = head;
    while(ptr) {
        if(ptr->category.find(keyWord) != string::npos) {
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr->name << endl;
            cout << "关系: " << ptr->category << endl;
            cout << "电话号码: " << ptr->number << endl;
            cout << "公司: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\n未找到相关联系人!" << endl;
}

void sum() {
    unordered_map<string,int> mp;
    user* ptr = head;
    while(ptr) {
        mp[ptr->category]++;
        ptr = ptr->next;
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

void fuzzySearch() {
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
    if(!input.empty())
        keywords.push_back(input);

    bool found = false;
    user* ptr = head;
    while(ptr) {
        // 整合联系人信息
        string content = ptr->name + ptr->number + ptr->company + ptr->category;
        bool match = true;
        for(const string& kw : keywords) {
            if(content.find(kw) == string::npos) {
                match = false;
                break;
            }
        }
        if(match) {
            found = true;
            cout << "-----联系人-----" << endl;
            cout << "姓名: " << ptr->name << endl;
            cout << "关系: " << ptr->category << endl;
            cout << "电话号码: " << ptr->number << endl;
            cout << "公司: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\n未找到符合条件的联系人！" << endl;
}

void show() {
    if (!head) {
        cout << "通讯录为空！" << endl;
        return;
    }
    cout << "*总共有" << len << "位联系人*\n" << endl;
    user* ptr = head;
    while(ptr) {
        cout << "-----联系人-----" << endl;
        cout << "姓名: " << ptr->name << endl;
        cout << "关系: " << ptr->category << endl;
        cout << "电话号码: " << ptr->number << endl;
        cout << "公司: " << ptr->company << endl << endl;
        ptr = ptr->next;
    }
}
