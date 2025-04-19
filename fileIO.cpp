#include "fileIO.h"
#include <sstream>
#include <iostream>
#include <fstream>

void readFile(const string& fileName)
{
    ifstream rd(fileName);
    if(!rd.is_open()){
        cout << "δ�ҵ��ļ� " << fileName << "�����ӿ�ͨѶ¼��ʼ��" << endl;
        return;
    }

    string line;
    while(getline(rd,line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string name, category, number, company;
        if(getline(ss, name, '|') &&
           getline(ss, number, '|') &&
           getline(ss, company, '|') &&
           getline(ss, category, '|')){

            user* newUser = new user;
            newUser->name = name;
            newUser->number = number;
            newUser->company = company;
            newUser->category = category;

            if(head == nullptr)
                head = newUser;
            else{
                user* ptr = head;
                while(ptr -> next)
                    ptr = ptr -> next;

                ptr -> next = newUser;
                newUser -> prev = ptr;
            }
            len++;
           }
    }
    rd.close();
    cout << "��ϵ���Ѵ� " << fileName << " �м��ء�" << endl;
}
void saveFile(const string& fileName){
    ofstream wrt(fileName);
    if(!wrt.is_open()){
        cout << "�޷����ļ� " << fileName << " ���б��棬�����ļ�Ȩ�ޣ�" << endl;
        return;
    }

    user* ptr = head;
    while(ptr){
        wrt << ptr->name << '|'
                << ptr->number << '|'
                << ptr->company << '|'
                << ptr->category << '\n';
        ptr = ptr->next;
    }
    wrt.close();
    cout << "��ϵ�������ѱ��浽 " << fileName << "��" << endl;
}
