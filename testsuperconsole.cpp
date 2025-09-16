
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


char getch() {//на мак функции getch, как и библиотеки conio.h попросту не существует, поэтому я сделал так.
    char buf = 0;
    struct termios old;
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
void hideCursor() {
    std::cout << "\033[?25l"; // Скрыть курсор
    fflush(stdout);
}

void showCursor() {
    std::cout << "\033[?25h"; // Показать курсор
    fflush(stdout);
}



using namespace std;
int main()
{
//hideCursor();
setlocale(0, "");
char ch;
while (true)
{
ch = getch();
if (ch == -32) ch = getch(); // Отлавливаем стрелочки
switch (ch)
{
case 27:
exit(0);
case 72:
cout<<"up"<<(int)ch<<endl;
break;
case 80:
cout<<"down"<<(int)ch<<endl;
break;



}
}
}