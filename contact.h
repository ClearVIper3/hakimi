#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;

typedef struct user {
    string name;      // ����
    string category;  // ��ϵ
    string number;    // �绰����
    string company;   // ��˾����
    struct user* next = nullptr;
    struct user* prev = nullptr;
} user;

// ȫ�ֱ�������
extern user* head;
extern int len;     // ��ϵ������

void input();
void update();
void delt();
void nameSearch();
void classSearch();
void sum();
void fuzzySearch();
void show();

#endif
