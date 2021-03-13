#include <iostream>
#include <regex>
#include <fstream>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[]){

    // delete the previous remain execution file if exist
    ifstream f("a.exe");
    if(f.good()){
        f.close();
        system("del a.exe");
    }

    // to check if it is c/cpp file
    regex reg_cpp(".+\\.cpp");
    regex reg_c(".+\\.c");
    int count = 0, idx = -1;

    for(int i=0; i<argc; i++){
        if(regex_match(argv[i], reg_c) || regex_match(argv[i], reg_cpp)){
            idx = i;
            count++;
        }
    }
    if(count != 1){
        if(count >= 2)
            cout << "[Error]: more than 1 *.c or *.cpp" << endl;
        if(count == 0)
            cout << "[Error]: no *.c or *.cpp file" << endl;

        system("PAUSE");
        return 0;
    }

    // compile and check compilation success or not
    string str;
    str = "g++ " + (string)argv[idx] + " -o a -g";
    system(str.c_str());

    ifstream exe_file("a.exe");
    if(!exe_file.good()){
        cout << "compile failed!" << endl;
        system("PAUSE");
        return 0;
    }else
        exe_file.close();

    bool analysis = false;
    ifstream test1_in("test1.in");
    ifstream test1_out("test1.out");

    if(test1_in.good() && test1_out.good()){

        system("a.exe < test1.in >> test1.in.out");

        ifstream test1_in_out("test1.in.out");
        string line1, line2;
        bool all_right = true;

        while(getline(test1_out, line2)){
            getline(test1_in_out, line1);
            if(line1 != line2)
                all_right = false;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if(line1 == line2){
                cout << "your answer: ";
                SetConsoleTextAttribute(hConsole, 10);
                cout << line1 << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cout << "real answer: ";
                SetConsoleTextAttribute(hConsole, 10);
                cout << line2 << endl << endl;
            }else{
                cout << "your answer: ";
                SetConsoleTextAttribute(hConsole, 12);
                cout << line1 << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cout << "real answer: ";
                SetConsoleTextAttribute(hConsole, 12);
                cout << line2 << endl << endl;
            }
            SetConsoleTextAttribute(hConsole, 7);
            line1 = line2 = "";
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(all_right == true){
            SetConsoleTextAttribute(hConsole, 47);
            cout << "========= PASS test1 =========";
            SetConsoleTextAttribute(hConsole, 7);
            cout << endl << endl;
        }else{
            SetConsoleTextAttribute(hConsole, 79);
            cout << "========= test1 NOT passed =========";
            SetConsoleTextAttribute(hConsole, 7);
            cout << endl << endl;
        }

        test1_in_out.close();

        system("del test1.in.out");

        analysis = true;
    }
    test1_in.close();
    test1_out.close();


    ifstream test2_in("test2.in");
    ifstream test2_out("test2.out");
    if(test2_in.good() && test2_out.good()){

        system("a.exe < test2.in >> test2.in.out");

        ifstream test2_in_out("test2.in.out");
        string line1, line2;
        bool all_right = true;
        
        while(getline(test2_out, line2)){
            getline(test2_in_out, line1);
            if(line1 != line2)
                all_right = false;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if(line1 == line2){
                cout << "your answer: ";
                SetConsoleTextAttribute(hConsole, 10);
                cout << line1 << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cout << "real answer: ";
                SetConsoleTextAttribute(hConsole, 10);
                cout << line2 << endl << endl;
            }else{
                cout << "your answer: ";
                SetConsoleTextAttribute(hConsole, 12);
                cout << line1 << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cout << "real answer: ";
                SetConsoleTextAttribute(hConsole, 12);
                cout << line2 << endl << endl;
            }
            SetConsoleTextAttribute(hConsole, 7);
            line1 = line2 = "";
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(all_right == true){
            SetConsoleTextAttribute(hConsole, 47);
            cout << "========= PASS test2 =========";
            SetConsoleTextAttribute(hConsole, 7);
            cout << endl << endl;
        }else{
            SetConsoleTextAttribute(hConsole, 79);
            cout << "========= test2 NOT passed =========";
            SetConsoleTextAttribute(hConsole, 7);
            cout << endl << endl;
        }

        test2_in_out.close();

        system("del test2.in.out");
        
        analysis = true;
    }
    test2_in.close();
    test2_out.close();

    string keep = "";
    if(analysis){
        cout << "keep execution file?(y): ";
        getline(cin, keep);
        if(keep != "y" && keep != "Y")
            system("del a.exe");
    }
}