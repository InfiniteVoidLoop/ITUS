#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

bool compareFile(char* file1, char* file2){
    fstream f1(file1, ios::in);
    fstream f2(file2, ios::in);
    if (!f1.is_open()){
        cout << "Can't open file " << file1 << endl;
        return false;
    }
    if (!f2.is_open()){
        cout << "Can't open file " << file2 << endl;
        return false;
    }
    string buffer;
    string buffer2;
    while(!f1.eof() && !f2.eof()){
        getline(f1, buffer);
        getline(f2, buffer2);
        if (buffer != buffer2){
            return false;
        }
    }
    if (f1.eof() && f2.eof()){
        return true;
    }
}

int main(int argc, char* argv[]){
    if (compareFile(argv[1], argv[2])){
        cout << "Files are the same !!!" << endl;
    } else {
        cout << "Files are different !!!" << endl;
    }
    return 0;

}