#include <iostream>
#include "Table.h"
#include <fstream>
#include <Windows.h>

Hashmap::Hashmap() {
    size = 100;
    count = 0;
    items = (Student**)calloc(size, sizeof(Student*));
}

Hashmap::~Hashmap() {
    for (int i = 0; i < size; ++i) {
        Student* current = items[i];
        while (current != nullptr) {
            Student* next = current->next;
            delete current;
            current = next;
        }
    }
    free(items);
    items = nullptr;
}

// хэш-функция
long Hashmap::hashFunc(std::string key) {
    long sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return (sum % 100);
}

// добавление информации о студенте
void Hashmap::insertStudent(int group, std::string key, int data, int mark, std::string other) {
    long index = hashFunc(key);
    Student* current = items[index];

    if (current == nullptr) {
        items[index] = new Student(group, key, data, mark, other);
        count++;
    }
    else if (current->key == key) {
        current->data = data;
        current->group = group;
        current->marks = mark;
        current->other = other;
        return;
    }
    else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Student(group, key, data, mark, other);
        count++;
        return;
    }
}

// вывод информации о студенте
void Hashmap::getST(std::string key) {
    long index = hashFunc(key);
    int hook = 0;
    Student* current = items[index];
    while (current != nullptr) {
        if (current->key == key) {
            int marks_ = current->marks, mark;
            std::cout << current->group << " " << current->key << " " << current->data << " ";
            for (int i = 0; i < 5; i++) {
                mark = marks_ % 10;
                if (i != 4)
                    std::cout << mark << "-";
                else std::cout << mark;
                marks_ /= 10;
            }
            std::cout << " " << current->other;
            std::cout << std::endl;
            hook = 1;
            break;
        }
        current = current->next;
    }
    if (hook == 0) {
        std::cout << "Не найдено" << std::endl;
    }

}

// удаление информации о студенте 
void Hashmap::deleteST(std::string key) {
    long index = hashFunc(key);

    Student* prev = nullptr;
    Student* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) { // Удаляемый элемент находится в начале
                items[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current; // Освобождаем память
            return;
        }
        prev = current;
        current = current->next;
    }
}

// сортировка студентов по размеру стипендии
void Hashmap::groupStudentsByS(std::string fileName) {
    const int MAX_Grants = 3000; // Максимальный размер стипендии
    const int MAX_STUDENTS = 100; // Максимальное количество студентов
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string** scholarshipGroups = new std::string * [MAX_Grants + 1];
    for (int i = 0; i <= MAX_Grants; i++) {
        scholarshipGroups[i] = new std::string[MAX_STUDENTS];
    } // Массив для группировки студентов по размеру стипендии

    for (int i = 0; i < size; i++) {
        Student* current = items[i];
        while (current != nullptr) {
            int scholarship = current->data;
            int index = 0;
            while (!scholarshipGroups[scholarship][index].empty()) {
                index++;
            }
            scholarshipGroups[scholarship][index] = current->key;
            current = current->next;
        }
    }

    for (int i = 0; i <= MAX_Grants; i++) {
        if (!scholarshipGroups[i][0].empty()) {
            std::cout << "Размер стипендии: " << i << std::endl;
            std::cout << "Студенты: ";
            int index = 0;
            while (!scholarshipGroups[i][index].empty()) {
                std::cout << scholarshipGroups[i][index] << ", ";
                index++;
            }
            std::cout << std::endl << std::endl;
        }
    }

    std::string choice;
    std::cout << "ВЫ хотите сохранить результат в файл? (да/нет): ";
    std::cin >> choice;

    if (choice == "Да" || choice == "да") {
        // Сохраняем отсортированные элементы в файл

        std::ofstream fout(fileName);

        if (fout.is_open()) {
            for (int i = 0; i <= MAX_Grants; i++) {
                if (!scholarshipGroups[i][0].empty()) {
                    fout << "Размер стипендии: " << i << std::endl;
                    fout << "Студенты: ";
                    int index = 0;
                    while (!scholarshipGroups[i][index].empty()) {
                        fout << scholarshipGroups[i][index] << ", ";
                        index++;
                    }
                    fout << std::endl << std::endl;
                }
            }
            fout.close();
            std::cout << "Данные успешно сохранены в sorted_data.txt\n";
        }
        else {
            std::cout << "Ошибка открытия файла\n";
        }

    }

    for (int i = 0; i <= MAX_Grants; i++) {
        delete[] scholarshipGroups[i];
    }
    delete[] scholarshipGroups;
}

// сортировка по проценту оценок "неуд/удовл" в группах
void Hashmap::groupStudentsByM(double procent) {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int MAX_GROUPS = 4000;

    // Выделение памяти для массива grades
    int** grades = new int* [MAX_GROUPS + 1];
    for (int i = 0; i <= MAX_GROUPS; i++) {
        grades[i] = new int[2] {0, 0}; // Инициализируем значения 0
    }

    // Заполнение массива кол-вом оценок // [номер_группы][0: количество троек/двоек, 1: общее количество]
    for (int i = 0; i < size; ++i) {
        Student* current = items[i];
        while (current != nullptr) {
            int group = current->group;
            int mark;
            int marks_ = current->marks;
            for (int i = 0; i < 5; i++) {
                mark = marks_ % 10;
                marks_ /= 10;

                if (mark == 2 || mark == 3) {
                    grades[group][0]++; // Увеличиваем количество троек/двоек
                }
            }
            grades[group][1] += 5; // Увеличиваем общее количество 
            current = current->next;
        }
    }

    // вывод групп с процентами 
    for (int i = 3000; i <= MAX_GROUPS; ++i) {
        if (grades[i][1] > 0) {
            double percentage = (double)grades[i][0] / grades[i][1] * 100;
            if (percentage > procent) {
                std::cout << "Группа " << i << ": " << percentage << "%" << std::endl;
            }
        }
    }

    for (int i = 0; i <= MAX_GROUPS; i++) {
        delete[] grades[i]; // Освобождение памяти для каждого столбца
    }
    delete[] grades; // Освобождение памяти для массива указателей


};