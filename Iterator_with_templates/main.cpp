#include <iostream>
#include <string>
#include "Iterator_Templates.h"

using namespace std;

int main() {
    Single_Linked_List < List_of_students> students_list;

    // Добавление студентов
    students_list.add(List_of_students(1, "Korikov", "Mihail", "Evgenevich"));
    students_list.add(List_of_students(24, "Ivanova", "Anna", "Petrovna")); 
    students_list.add(List_of_students(3.14, "Sidorov", "Pavel", "Alexandrovich")); 
    students_list.add(List_of_students(46, "Smirnova", "Maria", "Sergeevna")); 
    students_list.add(List_of_students("string_id", "Popov", "Dmitry", "Vladimirovich")); 
    students_list.add(List_of_students(60, "Mikhailov", "Svetlana", "Ivanovna")); 
    students_list.add(List_of_students(7, "Fedorov", "Andrey", "Nikolaevich")); 
    students_list.add(List_of_students(8, "Petrova", "Olga", "Dmitrievna")); 

    // Вывод списка студентов
    cout << "List of students:\n";
    students_list.printList();

    // Пример использования итератора для обхода списка студентов с четными ID
    cout << "Students with even IDs:\n";
    for (Iterator<List_of_students> it = students_list.begin(); it != students_list.end(); ++it) {
        cout << "Student ID: " << get<int>((*it).student_ID) << ", Full name: " << (*it).student_surname << " " << (*it).student_name << " " << (*it).student_patronymic << endl;
    }
    return 0;
}
