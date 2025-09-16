#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

// Функция для получения цветового градиента
string getAnsiColor(int position, int width, const vector<string>& colors) {
    int index = (position * (colors.size() - 1)) / width;
    return colors[index];
}

// Функция для вывода ASCII-арта с цветовым градиентом
void displayAsciiArtWithAnsiGradient(const vector<string>& art, const vector<string>& colors) {
    int width = art[0].length();
    for (const auto& line : art) {
        for (int i = 0; i < width; ++i) {
            cout << getAnsiColor(i, width, colors) << line[i] << "\033[0m"; // Применение цвета к каждому символу
        }
        cout << endl;
    }
    cout << "\033[0m"; // Сброс цвета
}

// Основная функция для отображения ASCII-арта с градиентом
void displayGradientAsciiArt() {
    // Изменение размеров окна терминала перед анимацией
    cout << "\e[8;12;80t";

    // Цветовые коды ANSI без зеленого
    vector<string> colors;
    colors.push_back("\033[34m");   // Синий
    colors.push_back("\033[36m");   // Голубой
    colors.push_back("\033[36;1m"); // Ярко-голубой
    colors.push_back("\033[33m");   // Желтый
    colors.push_back("\033[33;1m"); // Ярко-желтый
    colors.push_back("\033[31;1m"); // Ярко-красный
    colors.push_back("\033[31m");   // Красный
    colors.push_back("\033[35m");   // Магента
    colors.push_back("\033[35;1m"); // Ярко-магента
    colors.push_back("\033[34;1m"); // Ярко-синий

    // ASCII-арт
    vector<string> asciiArt;
    asciiArt.push_back(" -*=. :*+.  :*: .=*=::-+-     -=   :+--+*--+= .*#-   -%+. .=#+::-+=  -#*:-+=   ");
    asciiArt.push_back("   %*   %#   =-   #%    ..    -%%   -  .%*  .: .@+    +@.   #%     .  =@:  =@-  ");
    asciiArt.push_back("   *%  =*@  =:   :@+::+      =:-@:     +@:     *@=---=@+   :@*--+     @%--=*-   ");
    asciiArt.push_back("   =@.+.-@:=:    #%..--     *=--@+    .@*     .@+    *@.   #%  .-    +@:.@+     ");
    asciiArt.push_back("   .@#. .@#:    -@-    .:  +.   *%    +@.     *%    .@+   -@-    .: .@+  -@-    ");
    asciiArt.push_back("    #:   #:    :#%-::-+# :#-   .+%= .-%#.    -#*.  .*#-  .*#-::-+* .+#-   =*:   ");

    // Вывод ASCII-арта с цветовым градиентом
    displayAsciiArtWithAnsiGradient(asciiArt, colors);

    // Задержка на 3 секунды
    this_thread::sleep_for(chrono::seconds(3));

    // Очистка экрана
    cout << "\033[2J\033[H";

    // Изменение размеров окна терминала после анимации
    cout << "\e[8;12;60t";
}

int main() {
    displayGradientAsciiArt();
    return 0;
}