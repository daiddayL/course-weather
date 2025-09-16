#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;
string getAnsiColor(int position, int width, const vector<string> &colors)
{
    int index = (position * (colors.size() - 1)) / width;
    return colors[index];
}

// Функция для вывода ASCII-арта
void displayAsciiArtWithAnsiGradient(const vector<string> &art, const vector<string> &colors)
{
    system("clear");
    int width = art[0].length();
    for (const auto &line : art)
    {
        for (int i = 0; i < width; ++i)
        {
            cout << getAnsiColor(i, width, colors) << line[i] << "\033[0m"; // Применение цвета к каждому символу
        }
        cout << endl;
    }
    cout << "\033[0m"; // Сброс цвета
}

// Основная функция для отображения ASCII-арта
void displayGradientAsciiArt()
{

    // Изменение размеров терминала перед анимацией
    cout << "\e[8;7;80t";

    // Цветовые коды ANSI
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
    system("clear");

    // Изменение размеров окна терминала после анимации
    cout << "\e[8;12;60t";
}

vector<string> reading(const string &filename, int num, size_t n, const string &fields)
{
    vector<string> data;
    ifstream file(filename);
    if (file.is_open())
    {
        cout << "Согласно нашим данным о погоде: " << endl;
        string line;
        size_t lineCount = 0;
        while (getline(file, line))
        {
            lineCount++;
            if (lineCount >= static_cast<size_t>(num) && data.size() < n)
            {
                istringstream iss(line);
                string field;
                string output;
                size_t fieldIndex = 0;
                while (getline(iss, field, '/'))
                {
                    // Удаление начальных и конечных пробелов
                    field.erase(0, field.find_first_not_of(" \t"));
                    field.erase(field.find_last_not_of(" \t") + 1);

                    string colorCode;
                    if (fieldIndex == 1) // Максимальная температура
                    {
                        colorCode = "\033[31m"; // Красный
                    }
                    else if (fieldIndex == 2) // Минимальная температура
                    {
                        colorCode = "\033[34m"; // Синий
                    }
                    else if (fieldIndex == 3) // Скорость ветра
                    {
                        colorCode = "\033[32m"; // Зеленый
                    }
                    else if (fieldIndex == 4) // Влажность
                    {
                        colorCode = "\033[36m"; // Голубой
                    }
                    else
                    {
                        colorCode = "\033[0m"; // Сброс цвета
                    }

                    if (fieldIndex == static_cast<size_t>(stoi(fields)))
                    {
                        output = colorCode + field + "\033[0m";
                        break;
                    }
                    else if (fields.find(to_string(fieldIndex)) != string::npos)
                    {
                        output += colorCode + field + "\033[0m" + " ";
                    }
                    fieldIndex++;
                }
                data.push_back(output);
                cout << output << endl;
            }
            if (data.size() == n)
            {
                break;
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
        usleep(1000000);
    }

    return data;
}
int findLineNumberByDate(const string &filename, const string &date)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        int lineNumber = 0;
        while (getline(file, line))
        {
            lineNumber++;
            istringstream iss(line);
            string field;
            getline(iss, field, '/'); // Считываем дату

            // Удаление начальных и конечных пробелов
            field.erase(0, field.find_first_not_of(" \t"));
            field.erase(field.find_last_not_of(" \t") + 1);

            if (field == date)
            {
                file.close();
                return lineNumber;
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
        usleep(1000000);
    }

    return -1; // Возвращаем -1, если дата не найдена
}

string getNextDate(const string &lastDate)
{
    istringstream iss(lastDate);
    int day, month, year;
    char delimiter;
    iss >> day >> delimiter >> month >> delimiter >> year;

    tm date = {0};
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    date.tm_isdst = -1;

    time_t nextTime = mktime(&date) + 24 * 60 * 60;
    tm *nextDate = localtime(&nextTime);

    ostringstream oss;
    oss << setw(2) << setfill('0') << nextDate->tm_mday << "."
        << setw(2) << setfill('0') << nextDate->tm_mon + 1 << "."
        << nextDate->tm_year + 1900;

    return oss.str();
}

void writing(const string &filename, const vector<string> &data, const string &dateOrNew)
{
    ifstream file(filename);
    if (file.is_open())
    {
        vector<string> lines;
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        if (dateOrNew == "new")
        {
            // Получаем последнюю дату в файле
            string lastLine = lines.back();
            string lastDate = lastLine.substr(0, lastLine.find('/'));

            // Вычисляем следующую дату
            string nextDate = getNextDate(lastDate);

            ofstream outFile(filename, ios::app);
            if (outFile.is_open())
            {
                // Формирование новой строки с вычисленной датой
                string newLine = nextDate + " / ";
                for (size_t i = 0; i < data.size(); i++)
                {
                    newLine += data[i];
                    if (i != data.size() - 1)
                    {
                        newLine += " / ";
                    }
                }
                outFile << newLine << endl;
                outFile.close();
            }
            else
            {
                cout << "Unable to open file for writing" << endl;
                usleep(1000000);
            }
        }
        else
        {
            istringstream iss(dateOrNew);
            int day, month, year;
            char delimiter;
            iss >> day >> delimiter >> month >> delimiter >> year;
            if (iss.fail())
            {
                cout << "Invalid date format" << endl;
                usleep(1000000);
                return;
            }

            time_t t = time(nullptr);
            tm tm = *localtime(&t);
            int currentYear = tm.tm_year + 1900;
            if (year != currentYear)
            {
                cout << "Invalid year" << endl;
                usleep(1000000);
                return;
            }

            int startLine = 0;
            for (int m = 1; m < month; m++)
            {
                startLine += (m == 2) ? ((currentYear % 4 == 0 && currentYear % 100 != 0) || currentYear % 400 == 0) ? 29 : 28 : (m == 4 || m == 6 || m == 9 || m == 11) ? 30
                                                                                                                                                                         : 31;
            }
            startLine += day;

            if (startLine >= 1 && static_cast<size_t>(startLine) <= lines.size())
            {
                istringstream iss(lines[startLine - 1]);
                string field;
                size_t fieldIndex = 0;
                string newLine;
                while (getline(iss, field, '/'))
                {
                    if (fieldIndex < data.size())
                    {
                        newLine += data[fieldIndex] + " / ";
                    }
                    else
                    {
                        newLine += field + " / ";
                    }
                    fieldIndex++;
                }
                lines[startLine - 1] = newLine.substr(0, newLine.length() - 3);

                ofstream outFile(filename);
                if (outFile.is_open())
                {
                    for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
                    {
                        outFile << *it << endl;
                    }
                    outFile.close();
                }
                else
                {
                    cout << "Unable to open file for writing" << endl;
                    usleep(1000000);
                }
            }
            else
            {
                cout << "Invalid line number" << endl;
                usleep(1000000);
            }
        }
    }
    else
    {
        cout << "Unable to open file" << endl;
        usleep(1000000);
    }
}

void hideCursor()
{
    cout << "\033[?25l"; // Скрыть курсор
    fflush(stdout);
}

// Функция для получения нажатой клавиши без необходимости нажимать Enter
int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
void disableInputOutput()
{
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO); // Отключаем канонический режим и отображение ввода
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enableInputOutput()
{
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON | ECHO; // Включаем канонический режим и отображение ввода
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void loadingAnimation()
{
    const string loadingChars = "|/-\\";
    const int animationDuration = 700; // Длительность анимации в миллисекундах
    const int numChars = loadingChars.length();

    disableInputOutput(); // Отключаем ввод и вывод

    cout << " Загрузка";
    for (int i = 0; i < numChars; i++)
    {
        cout << "." << flush;
        this_thread::sleep_for(chrono::milliseconds(animationDuration / numChars));
    }
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < numChars; j++)
        {
            cout << "\r" << " " << loadingChars[j] << flush;
            this_thread::sleep_for(chrono::milliseconds(animationDuration / numChars));
        }
    }

    cout << "\r" << string(numChars + 1, ' ') << "\r" << flush;

    enableInputOutput(); // Включаем ввод и вывод
    system("clear");
}

void UserMenu()
{

    time_t t = time(nullptr);
    tm tm = *localtime(&t);
    int currentDay = tm.tm_mday;
    int currentMonth = tm.tm_mon + 1;
    int currentYear = tm.tm_year + 1900;
    int startLine = 0;
    for (int month = 1; month < currentMonth; month++)
    {
        startLine += (month == 2) ? ((currentYear % 4 == 0 && currentYear % 100 != 0) || currentYear % 400 == 0) ? 29 : 28 : (month == 4 || month == 6 || month == 9 || month == 11) ? 30
                                                                                                                                                                                     : 31;
    }
    startLine += currentDay;
    string region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/minsk.txt";
    vector<string> usermenu;
    usermenu.push_back(" Посмотреть детальную погоду на сегодня. ");
    usermenu.push_back(" Посмотреть краткую сводку погоды на неделю. ");
    usermenu.push_back(" Посмотреть детальную погоду на конкретное число. ");
    usermenu.push_back(" Сменить текущий регион. ");
    usermenu.push_back(" Перейти на главную. ");
    int currentOption = 0;
    bool quit = false;

    while (!quit)
    {

        // Очистка консоли
        system("clear");
        cout << "\033[90m" << "     Сегодняшнее число: " << put_time(&tm, "%d.%m.%Y") << "\033[0m" << '\n';
        // Вывод меню с подсветкой выбранного пункта
        for (int i = 0; i < usermenu.size(); i++)
        {
            if (i == currentOption)
            {
                cout << "\033[1;32m" << usermenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
            }
            else
            {
                cout << usermenu[i] << endl;
            }
        }

        // Получение нажатой клавиши
        int key = getch();

        // Обработка нажатой клавиши
        switch (key)
        {
        case 'w':
        case 'W':
        case 65: // Стрелка вверх
            currentOption = (currentOption - 1 + usermenu.size()) % usermenu.size();
            break;
        case 's':
        case 'S':
        case 66: // Стрелка вниз
            currentOption = (currentOption + 1) % usermenu.size();
            break;
        case 10: // Enter
            if (currentOption == usermenu.size() - 1)
            {
                quit = true;
                loadingAnimation();
                // Выход из программы при выборе "Exit"
            }
            else
            {
                loadingAnimation();
                switch (currentOption)
                {
                case 0:
                {
                    // Код для обработки Option 1
                    vector<string> lines = reading(region, startLine, 1, "012345");
                    getch();
                    break;
                }
                case 1:
                {
                    vector<string> lines = reading(region, startLine, 7, "012");
                    getch();
                    // Код для обработки Option 2
                    break;
                }
                case 2:
                {
                    cout << "Введите дату в формате ДД.ММ.ГГГГ: ";
                    string mmm;
                    cin >> mmm;
                    system("clear");
                    int lineNumberr = findLineNumberByDate(region, mmm);
                    if (lineNumberr != -1)
                    {
                        reading(region, lineNumberr, 1, "01234");
                    }
                    else
                    {
                        cout << " Возникла ошибка.";
                    }
                    getch();
                    getch();
                    break;
                }
                case 3:
                {
                    system("clear");
                    vector<string> regionmenu;
                    regionmenu.push_back(" Минская область. ");
                    regionmenu.push_back(" Гомельская область. ");
                    regionmenu.push_back(" Гродненская область. ");
                    regionmenu.push_back(" Брестская область. ");
                    regionmenu.push_back(" Могилевская область. ");
                    regionmenu.push_back(" Витебская область. ");
                    regionmenu.push_back(" Назад. ");
                    int currentOptionR = 0;
                    bool quitr = false;

                    while (!quitr)
                    {
                        // Очистка консоли
                        system("clear");

                        // Вывод меню с подсветкой выбранного пункта
                        for (int i = 0; i < regionmenu.size(); i++)
                        {
                            if (i == currentOptionR)
                            {
                                cout << "\033[1;32m" << regionmenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                            }
                            else
                            {
                                cout << regionmenu[i] << endl;
                            }
                        }

                        // Получение нажатой клавиши
                        int key = getch();

                        // Обработка нажатой клавиши
                        switch (key)
                        {
                        case 'w':
                        case 'W':
                        case 65: // Стрелка вверх
                            currentOptionR = (currentOptionR - 1 + regionmenu.size()) % regionmenu.size();
                            break;
                        case 's':
                        case 'S':
                        case 66: // Стрелка вниз
                            currentOptionR = (currentOptionR + 1) % regionmenu.size();
                            break;
                        case 10: // Enter
                            if (currentOptionR == regionmenu.size() - 1)
                            {
                                quitr = true; // Выход из программы при выборе "Назад."
                            }
                            else
                            {
                                loadingAnimation();
                                switch (currentOptionR)
                                {
                                case 0:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/minsk.txt";
                                    quitr = true;
                                    break;
                                case 1:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/gomel.txt";
                                    quitr = true;
                                    break;
                                case 2:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/grodno.txt";
                                    quitr = true;
                                    break;
                                case 3:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/brest.txt";
                                    quitr = true;
                                    break;
                                case 4:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/mogilev.txt";
                                    quitr = true;
                                    break;
                                case 5:
                                    region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/vitebsk.txt";
                                    quitr = true;
                                    break;
                                case 6:
                                {
                                    break;
                                }

                                default:
                                    cout << " Ошибка." << endl;
                                }
                            }
                        }
                    }
                    break;
                }
                case 4:
                {

                    break;
                    // Код для обработки Option 4
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
    }
}
void AdminMenu()
{
    string login = "admin";
    string password = "12345678";
    cout << "введите логин и пароль" << endl;
    cout << " логин: ";
    cin >> login;
    cout << " пароль: ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (login == "admin" && password == "12345678")
    {
        loadingAnimation();
        vector<string> adminmenu;
        adminmenu.push_back(" Внести изменение в прогноз погоды. ");
        adminmenu.push_back(" Продлить прогноз погоды. ");
        adminmenu.push_back(" Закончить сеанс и вернуться на панель входа.");
        int currentOption = 0;
        bool quit = false;

        while (!quit)
        {
            // Очистка консоли
            system("clear");

            // Вывод меню с подсветкой выбранного пункта
            for (int i = 0; i < adminmenu.size(); i++)
            {
                if (i == currentOption)
                {
                    cout << "\033[1;32m" << adminmenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                }
                else
                {
                    cout << adminmenu[i] << endl;
                }
            }

            // Получение нажатой клавиши
            int key = getch();

            // Обработка нажатой клавиши
            switch (key)
            {
            case 'w':
            case 'W':
            case 65: // Стрелка вверх
                currentOption = (currentOption - 1 + adminmenu.size()) % adminmenu.size();
                break;
            case 's':
            case 'S':
            case 66: // Стрелка вниз
                currentOption = (currentOption + 1) % adminmenu.size();
                break;
            case 10: // Enter
                if (currentOption == adminmenu.size() - 1)
                {
                    quit = true;
                    loadingAnimation();
                }
                else
                {
                    loadingAnimation();
                    switch (currentOption)
                    {
                    case 0:
                    {
                        string region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/";
                        system("clear");
                        cout << " Введите дату (пример:'01.01.2024'): ";
                        string DateToChange;
                        cin >> DateToChange;
                        DateToChange = DateToChange + " ";
                        cout << " Введите максимальную температуру (пример:'31'): ";
                        string MaxTemp;
                        cin >> MaxTemp;
                        MaxTemp = " " + MaxTemp + "°C ";
                        cout << " Введите минимальную температуру (пример:'-1'): ";
                        string MinTemp;
                        cin >> MinTemp;
                        MinTemp = " " + MinTemp + "°C ";
                        cout << " Введите скорость ветра (пример:'11 '): ";
                        string WindSpeed;
                        cin >> WindSpeed;
                        WindSpeed = " " + WindSpeed + " км\\ч";
                        cout << " Введите влажность (пример:'65'): ";
                        string Humidity;
                        cin >> Humidity;
                        Humidity = " " + Humidity + "% ";
                        cout << " Введите файл (пример: 'minsk'): ";
                        string region1;
                        cin >> region1;
                        region += region1;
                        region += ".txt";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        vector<string> changemenu;
                        changemenu.push_back(" Да. ");
                        changemenu.push_back(" Нет. ");
                        int currentOptionch = 0;
                        bool quitchange = false;

                        while (!quitchange)
                        {
                            // Очистка консоли
                            system("clear");
                            cout << " Продолжить?" << endl;
                            // Вывод меню с подсветкой выбранного пункта
                            for (int i = 0; i < changemenu.size(); i++)
                            {
                                if (i == currentOptionch)
                                {
                                    cout << "\033[1;32m" << changemenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                                }
                                else
                                {
                                    cout << changemenu[i] << endl;
                                }
                            }
                            // Получение нажатой клавиши
                            int key = getch();

                            // Обработка нажатой клавиши
                            switch (key)
                            {
                            case 'w':
                            case 'W':
                            case 65: // Стрелка вверх
                                currentOptionch = (currentOptionch - 1 + changemenu.size()) % changemenu.size();
                                break;
                            case 's':
                            case 'S':
                            case 66: // Стрелка вниз
                                currentOptionch = (currentOptionch + 1) % changemenu.size();
                                break;
                            case 10: // Enter
                                if (currentOptionch == changemenu.size() - 1)
                                {
                                    quitchange = true; // Выход из программы при выборе "Exit"
                                }
                                else
                                {
                                    loadingAnimation();
                                    switch (currentOptionch)
                                    {
                                    case 0:
                                    {
                                        vector<string> updatedData;
                                        updatedData.push_back(DateToChange);
                                        updatedData.push_back(MaxTemp);
                                        updatedData.push_back(MinTemp);
                                        updatedData.push_back(WindSpeed);
                                        updatedData.push_back(Humidity);
                                        writing(region, updatedData, DateToChange);
                                        quitchange = true;
                                        break;
                                    }
                                    case 1:
                                        quitchange = true;
                                        break;
                                    default:
                                        cout << " Ошибка." << endl;
                                    }
                                }
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    }
                    break;
                    case 1:
                    {
                        system("clear");
                        cout << " Вы выбрали: Продолжить прогноз погоды. " << endl;
                        string region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/";

                        cout << " Введите максимальную температуру (пример:'31'): ";
                        string MaxTemp;
                        cin >> MaxTemp;
                        MaxTemp = " " + MaxTemp + "°C ";
                        cout << " Введите минимальную температуру (пример:'-1'): ";
                        string MinTemp;
                        cin >> MinTemp;
                        MinTemp = " " + MinTemp + "°C ";
                        cout << " Введите скорость ветра (пример:'11 '): ";
                        string WindSpeed;
                        cin >> WindSpeed;
                        WindSpeed = " " + WindSpeed + " км\\ч";
                        cout << " Введите влажность (пример:'65'): ";
                        string Humidity;
                        cin >> Humidity;
                        Humidity = " " + Humidity + "% ";
                        cout << " Введите файл (пример: 'minsk'): ";
                        string region1;
                        cin >> region1;
                        region += region1;
                        region += ".txt";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        vector<string> changemenu;
                        changemenu.push_back(" Да. ");
                        changemenu.push_back(" Нет. ");
                        int currentOptionch = 0;
                        bool quitk = false;

                        while (!quitk)
                        {
                            // Очистка консоли
                            system("clear");
                            cout << " Продолжить?" << endl;

                            // Вывод меню с подсветкой выбранного пункта
                            for (int i = 0; i < changemenu.size(); i++)
                            {
                                if (i == currentOptionch)
                                {
                                    cout << "\033[1;32m" << changemenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                                }
                                else
                                {
                                    cout << changemenu[i] << endl;
                                }
                            }

                            // Получение нажатой клавиши
                            int key = getch();

                            // Обработка нажатой клавиши
                            switch (key)
                            {
                            case 'w':
                            case 'W':
                            case 65: // Стрелка вверх
                                currentOptionch = (currentOptionch - 1 + changemenu.size()) % changemenu.size();
                                break;
                            case 's':
                            case 'S':
                            case 66: // Стрелка вниз
                                currentOptionch = (currentOptionch + 1) % changemenu.size();
                                break;
                            case 10: // Enter
                                if (currentOptionch == changemenu.size() - 1)
                                {
                                    quitk = true; // Выход из программы при выборе "Exit"
                                }
                                else
                                {
                                    loadingAnimation();
                                    switch (currentOptionch)
                                    {
                                    case 0:
                                    {
                                        vector<string> updatedData;
                                        // updatedData.push_back(DateToChange);
                                        updatedData.push_back(MaxTemp);
                                        updatedData.push_back(MinTemp);
                                        updatedData.push_back(WindSpeed);
                                        updatedData.push_back(Humidity);
                                        writing(region, updatedData, "new");
                                        quitk = true;

                                        break;
                                    }
                                    case 1:
                                        quitk = true;
                                        break;
                                    default:
                                        cout << " Ошибка." << endl;
                                    }
                                }
                                break;
                            default:
                                break;
                            }
                        }

                        // Код для обработки Option 2
                        break;
                    }
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    else
    {
        cout << "Неверный логин или пароль!" << endl;
        usleep(1000000);
    }
}

void mainMenu()
{
    vector<string> menu;
    menu.push_back(" Вход в качестве пользователя. ");
    menu.push_back(" Вход в качестве администратора. ");
    menu.push_back(" Выйти. ");
    int currentOption = 0;
    bool quit = false;

    while (!quit)
    {
        // Очистка консоли
        system("clear");

        // Вывод меню с подсветкой выбранного пункта
        for (int i = 0; i < menu.size(); i++)
        {
            if (i == currentOption)
            {
                cout << "\033[1;32m" << menu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
            }
            else
            {
                cout << menu[i] << endl;
            }
        }

        // Получение нажатой клавиши
        int key = getch();

        // Обработка нажатой клавиши
        switch (key)
        {
        case 'w':
        case 'W':
        case 65: // Стрелка вверх
            currentOption = (currentOption - 1 + menu.size()) % menu.size();
            break;
        case 's':
        case 'S':
        case 66: // Стрелка вниз
            currentOption = (currentOption + 1) % menu.size();
            break;
        case 10: // Enter
            if (currentOption == menu.size() - 1)
            {
                quit = true; // Выход из программы при выборе "Exit"
            }
            else
            {
                loadingAnimation();
                switch (currentOption)
                {
                case 0:
                    UserMenu();
                    break;
                case 1:
                    AdminMenu();
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }
}
void setConsoleTitle(const std::string &title)
{
    std::cout << "\033]0;" << title << "\007";
}

int main()
{
    hideCursor();
    disableInputOutput();
    setConsoleTitle("weather");
    displayGradientAsciiArt();
    enableInputOutput();
    mainMenu();
    return 0;
}