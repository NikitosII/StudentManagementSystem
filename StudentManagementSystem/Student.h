#pragma once
#include <iostream>

class Student {
public:

    int group;
    std::string key;
    int data;
    int marks;
    Student* next;
    std::string other = "";

    // конструктор элемента хэш-таблицы 
    Student(int group, std::string key, int data, int marki, std::string others) {
        this->group = group;
        this->key = key;
        this->data = data;
        this->next = nullptr;
        this->other = others;
        this->marks = marki;
    }
};
