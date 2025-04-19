#include "contact.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <limits>
using namespace std;

// ����ȫ�ֱ���
user* head = nullptr;
int len = 0;

void input() {
    len++;
    user* newUser = new user;

    cout << "��������ϵ���������磺��������";
    getline(cin, newUser->name);

    cout << "��������绰���루�磺13800138000����";
    getline(cin, newUser->number);

    cout << "�������乫˾���ƣ��磺��Ѷ����";
    getline(cin, newUser->company);

    cout << "������������磺����/����/ͬ�£���";
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
    cout << "\n��ϵ�˵Ǽǳɹ���" << endl;
}

void update() {
    string needName;
    cout << "������Ҫ�޸ĵ���ϵ�����������ִ�Сд����";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr->name != needName) {
        ptr = ptr->next;
    }
    if(!ptr) {
        cout << "���޴���!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "������Ҫ�޸ĵ���Ϣ���ͣ����� C ��ʾ��˾��N ��ʾ�绰���룩��";
    char op;
    cin >> op;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(op == 'C'){
        cout << "�¹�˾Ϊ:";
        getline(cin, ptr->company);
    }
    else if(op == 'N'){
        cout << "�µ绰����Ϊ:";
        getline(cin, ptr->number);
    }
    cout << "\n�޸���ϵ����Ϣ�ɹ���" << endl;
}

void delt() {
    string needName;
    cout << "������Ҫɾ������ϵ�����������ִ�Сд����";
    cin >> needName;

    user* ptr = head;
    while(ptr && ptr->name != needName) {
        ptr = ptr->next;
    }
    if(!ptr) {
        cout << "���޴���!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    len--;
    // ɾ��ͷ�ڵ�
    if(ptr == head) {
        head = ptr->next;
        if(head != nullptr) {
            head->prev = nullptr;
        }
    } else {
        // ����ǰ���ͺ��ָ��
        ptr->prev->next = ptr->next;
        if(ptr->next != nullptr) {
            ptr->next->prev = ptr->prev;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    delete ptr;
    cout << "\n��ϵ��ɾ���ɹ���" << endl;
}

void nameSearch() {
    cout << "������Ҫ���ҵ��������գ�";
    string keyWord;
    cin >> keyWord;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    user* ptr = head;
    while(ptr) {
        if(ptr->name.find(keyWord) != string::npos) {
            found = true;
            cout << "-----��ϵ��-----" << endl;
            cout << "����: " << ptr->name << endl;
            cout << "��ϵ: " << ptr->category << endl;
            cout << "�绰����: " << ptr->number << endl;
            cout << "��˾: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\nδ�ҵ������ϵ��!" << endl;
}

void classSearch() {
    cout << "������Ҫ���ҵ���ϵ������磺����/ͬ��/���ˣ���";
    string keyWord;
    cin >> keyWord;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    user* ptr = head;
    while(ptr) {
        if(ptr->category.find(keyWord) != string::npos) {
            found = true;
            cout << "-----��ϵ��-----" << endl;
            cout << "����: " << ptr->name << endl;
            cout << "��ϵ: " << ptr->category << endl;
            cout << "�绰����: " << ptr->number << endl;
            cout << "��˾: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\nδ�ҵ������ϵ��!" << endl;
}

void sum() {
    unordered_map<string,int> mp;
    user* ptr = head;
    while(ptr) {
        mp[ptr->category]++;
        ptr = ptr->next;
    }

    cout << "------------- ����ͳ�� ------------" << endl;
    cout << "| " << left << setw(20) << "��������" << "| " << setw(10) << "����" << "|" << endl;
    cout << "-----------------------------------" << endl;

    unordered_map<string, int>::const_iterator it;
    for (it = mp.begin(); it != mp.end(); ++it) {
        cout << "| " << left << setw(20) << it->first
             << "| " << setw(10) << it->second << "|" << endl;
    }
    cout << "-----------------------------------" << endl;
}

void fuzzySearch() {
    cout << "������Ҫģ�������Ĺؼ��ʣ�����������ʹ��Ӣ�ļӺ� '+' �ָ����磺��+��Ѷ����";
    string input;
    getline(cin, input);

    // �ָ�ؼ���
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
        // ������ϵ����Ϣ
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
            cout << "-----��ϵ��-----" << endl;
            cout << "����: " << ptr->name << endl;
            cout << "��ϵ: " << ptr->category << endl;
            cout << "�绰����: " << ptr->number << endl;
            cout << "��˾: " << ptr->company << endl << endl;
        }
        ptr = ptr->next;
    }
    if(!found)
        cout << "\nδ�ҵ�������������ϵ�ˣ�" << endl;
}

void show() {
    if (!head) {
        cout << "ͨѶ¼Ϊ�գ�" << endl;
        return;
    }
    cout << "*�ܹ���" << len << "λ��ϵ��*\n" << endl;
    user* ptr = head;
    while(ptr) {
        cout << "-----��ϵ��-----" << endl;
        cout << "����: " << ptr->name << endl;
        cout << "��ϵ: " << ptr->category << endl;
        cout << "�绰����: " << ptr->number << endl;
        cout << "��˾: " << ptr->company << endl << endl;
        ptr = ptr->next;
    }
}
