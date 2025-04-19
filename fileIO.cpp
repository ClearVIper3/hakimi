#include "fileIO.h"
#include <sstream>
#include <iostream>
#include <fstream>

void readFile(const string& fileName)
{
    ifstream rd(fileName);
    if(!rd.is_open()){
        cout << "未找到文件 " << fileName << "，将从空通讯录开始。" << endl;
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
    cout << "联系人已从 " << fileName << " 中加载。" << endl;
}
void saveFile(const string& fileName){
    ofstream wrt(fileName);
    if(!wrt.is_open()){
        cout << "无法打开文件 " << fileName << " 进行保存，请检查文件权限！" << endl;
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
    cout << "联系人数据已保存到 " << fileName << "！" << endl;
}
