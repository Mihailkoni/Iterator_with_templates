#include <iostream>
#include <cmath>
#include <string>
#include <variant>

using namespace std;

struct List_of_students {
    variant<int, string, double> student_ID;
    string student_surname;
    string student_name;
    string student_patronymic;

    List_of_students(variant<int, string, double> id, const string& surname, const string& name, const string& patronymic)
        : student_ID(id), student_surname(surname), student_name(name), student_patronymic(patronymic) {}
};

template<typename T>
struct Node {
    Node* next;
    T data;
    Node(T info) : data(info), next(nullptr) {}
};

template<typename T>
class Iterator {
private:
    Node<T>* slider;

    bool Digits_Even(int num) {
        if (num % 2 != 0) {
            return false;
        }
        while (num != 0) {
            int digit = abs(num % 10);
            if (digit % 2 != 0) {
                return false;
            }
            num /= 10;
        }
        return true;
    }

    void move_to_next() {
        while (slider != nullptr) {
            if (auto id = get_if<int>(&slider->data.student_ID)) {
                if (Digits_Even(*id)) {
                    break;
                }
            }
            slider = slider->next;
        }
    }

public:
    Iterator(Node<T>* start) : slider(start) {//конструктор для того чтобы итератор начинал свою работу с чётного числа 
        move_to_next();
    }

    Iterator& operator++() {// перегрузка++ к следующему чётному числу
        if (slider != nullptr) {
            slider = slider->next;
            move_to_next();
        }
        return *this;
    }

    T operator*() {//перегрузка * к получению data
        return slider->data;
    }

    bool operator==(const Iterator& it) {//проверка на равенство
        return slider == it.slider;
    }

    bool operator!=(const Iterator& it) {//проверка на неравенство 
        return !(*this == it);
    }
};

template<typename T>
class Single_Linked_List {
private:
    Node<T>* head;
public:
    Single_Linked_List() : head(nullptr) {}//конструктор

    void add(T data) { // добавление
        Node<T>* NewNode = new Node<T>(data);
        if (head == nullptr) {
            head = NewNode;
            return;
        }
        Node<T>* slider = head;
        while (slider->next != nullptr) {
            slider = slider->next;
        }
        slider->next = NewNode;
    }


    ~Single_Linked_List() { //деструктор
        Node<T>* slider = head;
        while (slider != nullptr) {
            Node<T>* next = slider->next;
            delete slider;
            slider = next;
        }
        head = nullptr;
    }

    void printList() {// вывод
        Node<T>* slider = head;
        while (slider != nullptr) {
            cout << "Student ID: ";
            if (auto id = get_if<int>(&slider->data.student_ID)) {
                cout << *id;
            }
            else if (auto id = get_if<string>(&slider->data.student_ID)) {
                cout << *id;
            }
            else if (auto id = get_if<double>(&slider->data.student_ID)) {
                cout << *id;
            }
            cout << ", Full name: " << slider->data.student_surname << " " << slider->data.student_name << " " << slider->data.student_patronymic << endl;
            slider = slider->next;
        }
        cout << "\n";
    }

    Iterator<T> begin() { return Iterator<T>(head); }

    Iterator<T> end() { return Iterator<T>(nullptr); }
};