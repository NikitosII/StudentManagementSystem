
#include <iostream>
#include "Table.h"
#include <fstream> 
#include <sstream>
#include <Windows.h>

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Hashmap hm = Hashmap();
    int choice;
    std::string filename = std::string(argv[1]);
    do {
        std::cout << "1. Добавить информацию о студенте" << std::endl;
        std::cout << "2. Найти информацию о студенте" << std::endl;
        std::cout << "3. Удалить информацию о студенте" << std::endl;
        std::cout << "4. Процент неуспевающих по группам" << std::endl;
        std::cout << "5. Группировка студентов по стипендии" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Введите номер пункта: ";
        std::cin >> choice;
        switch (choice) {
        case 1: {
            int choice1;
            std::cout << "1.1. Из файла" << std::endl;
            std::cout << "2.1. Через консолль" << std::endl;
            std::cin >> choice1;
            switch (choice1) {
            case 1: {

                std::ifstream fin(filename);
                if (!fin.is_open()) {
                    std::cout << "Невозможно открыть файл для чтения." << std::endl;
                    return 1;
                }
                std::string line;
                std::cin.ignore();
                while (getline(fin, line)) {
                    std::istringstream istream(line);
                    std::string initials, word = "";
                    std::string other;
                    int group = 0, grants = 0, marks = 0;
                    int counter = 0;
                    while (istream >> word) {
                        switch (counter) {
                        case 0:
                            initials = word;
                            break;
                        case 1:
                            group = stoi(word);
                            break;
                        case 2:
                            marks = stoi(word);
                            break;
                        case 3:
                            grants = stoi(word);
                            break;
                        case 4:
                            other = word;
                            break;
                        }

                        counter++;
                    }
                    if (initials.length() > 50) {

                    }
                    else {
                        hm.insertStudent(group, initials, grants, marks, other);

                    }

                }
                fin.close();
                std::cout << std::endl;
                break;
            }
            case 2: {
                int group, grants, marks;
                std::string initials;
                std::string other_info;

                std::cout << "Добавить элемент (номер группы - инициалы - стипендия - оценки - другое):" << std::endl;
                std::cin >> group >> initials >> grants >> marks;
                std::cin.ignore(); // Очищаем буфер ввода

                std::getline(std::cin, other_info); // Считываем оставшуюся строку как дополнительную информацию

                if (initials.length() > 50) {
                    std::cout << "Превышает допустимое значение (50 символов)." << std::endl;
                }
                else {
                    hm.insertStudent(group, initials, grants, marks, other_info);
                    std::cout << std::endl;
                }

                break;
            }
            }
            break;
        }

        case 2: {
            std::string user_word;
            std::cin >> user_word;
            hm.getST(user_word);
            std::cout << std::endl;
            break;
        }

        case 3: {
            std::cout << "Введите инициалы для удаления: ";
            std::string user_word1;
            std::cin >> user_word1;
            hm.deleteST(user_word1);
            std::cout << std::endl;
            break;
        }
        case 4: {
            int thresholdPercentage;
            std::cout << "Введите порог процентного соотношения неуспевающих: ";
            std::cin >> thresholdPercentage;
            hm.groupStudentsByM(thresholdPercentage);
            std::cout << std::endl;
            break;
        }
        case 5:
            hm.groupStudentsByS("sorted_data.txt");
            std::cout << std::endl;
            break;
        case 0:
            choice = 0;
            break;

        default:
            std::cout << "Введите корректныый номер " << std::endl;
        }

    } while (choice != 0);

    return 0;
}
