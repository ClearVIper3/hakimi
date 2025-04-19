#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;

typedef struct user {
    string name;      // 姓名
    string category;  // 关系
    string number;    // 电话号码
    string company;   // 公司名称
    struct user* next = nullptr;
    struct user* prev = nullptr;
} user;

// 全局变量声明
extern user* head;
extern int len;     // 联系人数量

void input();
void update();
void delt();
void nameSearch();
void classSearch();
void sum();
void fuzzySearch();
void show();

#endif
