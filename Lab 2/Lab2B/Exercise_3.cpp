#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;
const int BUFFER_SIZE = 1000;
const char* FILE_IN = "..\\Lab 2 - Data\\employee.txt";
const char* FILE_OUT = "sortedemponage.txt";

time_t t = time(0);
struct tm* now = localtime(&t);
const int CURRENT_YEAR = now->tm_year + 1900;

struct Data{
    int id;
    char* name;
    int age;
};

void readFile(const char* fileName, Data*& employee, int& sz){
    fstream fileIn(fileName, ios::in);
    if (!fileIn){
        cout << "Cannot open file " << fileName << endl;
        return;
    }
    char buffer[BUFFER_SIZE], col1[BUFFER_SIZE], col2[BUFFER_SIZE], col3[BUFFER_SIZE];
    fileIn.getline(buffer, BUFFER_SIZE);
    while(fileIn.getline(buffer, BUFFER_SIZE)){
        istringstream iss(buffer);
        employee = (Data*)realloc(employee, (sz + 1) * sizeof(Data));
        iss.getline(col1, BUFFER_SIZE, ',');
        iss.getline(col2, BUFFER_SIZE, ',');
        iss.getline(col3, BUFFER_SIZE);
        // cout << col1 << " " << col2 << " " << col3 << endl;

        employee[sz].id = atoi(col1);
        employee[sz].name = (char*)malloc(strlen(col2) + 1);
        strcpy(employee[sz].name, col2);
        int birthYear = atoi(col3);
        if (birthYear > CURRENT_YEAR)
            birthYear = 1900 + birthYear%100;
        
        employee[sz].age = CURRENT_YEAR - birthYear;
        // cout << employee[sz].id << " " << employee[sz].name << " " << employee[sz].age << endl;
        sz++;
    }
    fileIn.close();
}

void writeFile(const char* fileName, Data* employee, int sz){
    fstream fileOut(fileName, ios::out);
    if (!fileOut){
        cout << "Cannot open file " << fileName << endl;
        return;
    }
    fileOut << "ID, Name, Age" << endl;
    for (int i = 0; i < sz; i++){
        fileOut << employee[i].id << ", " << employee[i].name << ", " << employee[i].age << endl;
    }
    fileOut.close();
}

bool isLowerThan(Data* a, Data* b){
    if (a->age < b->age)
        return true;
    else if (a->age > b->age)
        return false;
    else
        return (strcmp(a->name, b->name) < 0);
}

void insertionSort(Data* employee, int sz){
    for (int i = 1; i < sz; i++){
        int j = i - 1;
        Data val = employee[i];
        while(j >= 0 && isLowerThan(&employee[j], &val)){
            employee[j + 1] = employee[j];
            j--;
        }
        employee[j + 1] = val;
    }
}

void selectionSort(Data* employee, int sz){
    for (int i = 0; i < sz - 1; i++){
        int ID = i;
        for (int j = i + 1; j < sz; j++){
            if (isLowerThan(&employee[ID], &employee[j]))
                ID = j;
        }
        if (ID != i){
            Data tmp = employee[i];
            employee[i] = employee[ID];
            employee[ID] = tmp;
        }
    }
}

void interchangeSort(Data* employee, int sz){
    for (int i = 0; i < sz - 1; i++){
        for (int j = i + 1; j < sz; j++){
            if (isLowerThan(&employee[i], &employee[j])){
                Data tmp = employee[i];
                employee[i] = employee[j];
                employee[j] = tmp;
            }
        }
    }
}

void menu(void){
    cout << "--------Instruction--------" << endl;
    cout << "1. Insertion sort" << endl;
    cout << "2. Selection sort" << endl;
    cout << "3. Interchange sort" << endl;
    cout << "----------------------------" << endl;
    cout << "Please choose a sorting algorithm: ";
}

void freeData(Data* &employee, int sz){
    for (int i = 0; i < sz; i++){
        free(employee[i].name);
    }
    free(employee);
}

int main(){
    Data* employee = nullptr;
    int sz = 0;
    readFile(FILE_IN, employee, sz);
    menu();    
    int choice;
    cin >> choice;
    if (choice == 1){
        insertionSort(employee, sz);
        cout << "Insertion sort successfully!" << endl;
    }
    else if (choice == 2){
        selectionSort(employee, sz);
        cout << "Selection sort successfully!" << endl;
    }
    else if (choice == 3){
        interchangeSort(employee, sz);
        cout << "Interchange sort successfully!" << endl;
    }
    else{
        cout << "Invalid choice!" << endl;
        return 0;
    }
    writeFile(FILE_OUT, employee, sz);
    freeData(employee, sz);
    return 0;
}