#include <iostream>
#include <regex>
#include <fstream>

#ifdef _WIN32
#include <winows.h>
#endif

using namespace std;

int main(int argc, char *argv[]){
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

        #ifdef __linux__
            string str;
            cout << "press any key to continue";
            getline(cin, str);
        #elif _WIN32
            system("PAUSE");
        #endif

        return 0;
    }
    string str = "g++ " + (string)argv[idx] + " -o a";
    system(str.c_str());

    bool analysis = false;

    ifstream test1_in("test1.in");
    ifstream test1_out("test1.out");
    if(test1_in.good() && test1_out.good()){

        #ifdef __linux__
            system("./a < test1.in > test1.in.out");
        #elif _WIN32
            system("a.exe < test1.in >> test1.in.out");
        #endif

        ifstream test1_in_out("test1.in.out");
        
        string line0, line1, line2;

        bool all_right = true;
        for(;getline(test1_in, line0) && getline(test1_in_out, line1) && getline(test1_out, line2);){
            if(line1 != line2)
                all_right = false;
            // cout << "[Wrong answer in test1]" << endl;
            // cout << "      input: " << line0 << endl;
            #ifdef __linux__
                cout << "your answer: " << line1 << endl;
                cout << "real answer: " << line2 << endl;
                cout << endl;
            #elif _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if(line1 == line2){
                    cout << "your answer: ";
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << line1 << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "real answer: ";
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << line2 << endl;
                    cout << endl;
                }else{
                    cout << "your answer: ";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << line1 << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "real answer: ";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << line2 << endl;
                    cout << endl;
                }
                SetConsoleTextAttribute(hConsole, 7);
            #endif
            
        }
        #ifdef __linux__
            if(all_right == true)
                cout << "========= PASS test1 =========" << endl << endl;
            else
                cout << "========= test1 NOT passed =========" << endl << endl;
        #elif _WIN32
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
        #endif

        test1_in_out.close();

        #ifdef __linux__
            system("rm test1.in.out");
        #elif _WIN32
            system("del test1.in.out");
        #endif

        analysis = true;
    }
    test1_in.close();
    test1_out.close();


    ifstream test2_in("test2.in");
    ifstream test2_out("test2.out");
    if(test2_in.good() && test2_out.good()){

        #ifdef __linux__
            system("./a < test2.in > test2.in.out");
        #elif _WIN32
            system("a.exe < test2.in >> test2.in.out");
        #endif

        ifstream test2_in_out("test2.in.out");
        
        string line0, line1, line2;

        bool all_right = true;
        for(;getline(test2_in, line0) && getline(test2_in_out, line1) && getline(test2_out, line2);){
            if(line1 != line2)
                all_right = false;
            // cout << "[Wrong answer in test2]" << endl;
            // cout << "      input: " << line0 << endl;
            #ifdef __linux__
                cout << "your answer: " << line1 << endl;
                cout << "real answer: " << line2 << endl;
                cout << endl;
            #elif _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if(line1 == line2){
                    cout << "your answer: ";
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << line1 << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "real answer: ";
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << line2 << endl;
                    cout << endl;
                }else{
                    cout << "your answer: ";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << line1 << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "real answer: ";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << line2 << endl;
                    cout << endl;
                }
                SetConsoleTextAttribute(hConsole, 7);
            #endif
        }
        #ifdef __linux__
            if(all_right == true)
                cout << "========= PASS test2 =========" << endl << endl;
            else
                cout << "========= test2 NOT passed =========" << endl << endl;
        #elif _WIN32
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
        #endif

        test2_in_out.close();

        #ifdef __linux__
            system("rm test2.in.out");
        #elif _WIN32
            system("del test2.in.out");
        #endif
        
        analysis = true;
    }
    test2_in.close();
    test2_out.close();


    string remove;
    if(analysis){
        cout << "remove execution file?(y/n): ";
        getline(cin, remove);
        if(remove == "y" || remove == "Y" || remove == ""){
            #ifdef __linux__
                system("rm a");
            #elif _WIN32
                system("del a.exe");
            #endif
        }
    }
}