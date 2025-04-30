#pragma once
#include <iostream>
#include "Student.h"

class Hashmap {
private:
	int size;
	int count;
	Student** items;

public:
	Hashmap();
	~Hashmap();

	long hashFunc(std::string key); // хэш-функция
	void insertStudent(int group, std::string key, int data, int mark, std::string other); // добавление информации 
	void getST(std::string key); // поиск информации
	void deleteST(std::string key); // удаление информации
	void groupStudentsByS(std::string fileName); // сортировка по стипендии 
	void groupStudentsByM(double procent); // сортировка по оценкам 
};

