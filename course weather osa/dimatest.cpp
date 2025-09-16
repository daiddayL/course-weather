#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>

using namespace std;

// Функция для получения нажатой клавиши
int getch() {
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

void loadingAnimation() {

    usleep(500000);
    // Реализация функции анимации загрузки
}

void writing(const string& region, const vector<string>& data, const string& mode) {
    // Реализация функции записи данных
}

void AdminMenu() {
    string login, password;
    cout << "Введите логин и пароль" << endl;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    if (login == "admin" && password == "12345678") {
        loadingAnimation();
        vector<string> adminmenu;
        adminmenu.push_back(" Внести изменение в прогноз погоды. ");
        adminmenu.push_back(" Продлить прогноз погоды. ");
        adminmenu.push_back(" Закончить сеанс и вернуться на панель входа.");
        int currentOption = 0;
        bool quit = false;

        while (!quit) {
            // Очистка консоли
            system("clear");

            // Вывод меню с подсветкой выбранного пункта
            for (int i = 0; i < adminmenu.size(); i++) {
                if (i == currentOption) {
                    cout << "\033[1;32m" << adminmenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                } else {
                    cout << adminmenu[i] << endl;
                }
            }

            // Получение нажатой клавиши
            int key = getch();

            // Обработка нажатой клавиши
            switch (key) {
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
                    if (currentOption == adminmenu.size() - 1) {
                        quit = true;
                        loadingAnimation();
                    } else {
                        loadingAnimation();
                        switch (currentOption) {
                            case 0: {
                                string region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/";
                                system("clear");
                                cout << "Введите дату (пример: '01.01.2024'): ";
                                string DateToChange;
                                cin >> DateToChange;
                                DateToChange += " ";
                                cout << "Введите максимальную температуру (пример: '31'): ";
                                string MaxTemp;
                                cin >> MaxTemp;
                                MaxTemp = " " + MaxTemp + "°C ";
                                cout << "Введите минимальную температуру (пример: '-1'): ";
                                string MinTemp;
                                cin >> MinTemp;
                                MinTemp = " " + MinTemp + "°C ";
                                cout << "Введите скорость ветра (пример: '11'): ";
                                string WindSpeed;
                                cin >> WindSpeed;
                                WindSpeed = " " + WindSpeed + " км/ч";
                                cout << "Введите влажность (пример: '65'): ";
                                string Humidity;
                                cin >> Humidity;
                                Humidity = " " + Humidity + "% ";
                                cout << "Введите файл (пример: 'minsk'): ";
                                string region1;
                                cin >> region1;
                                region += region1 + ".txt";

                                vector<string> changemenu;
                        changemenu.push_back(" Да. ");
                        changemenu.push_back(" Нет. ");
                                int currentOptionch = 0;
                                bool quitChange = false;

                                while (!quitChange) {
                                    // Очистка консоли
                                    system("clear");

                                    // Вывод меню с подсветкой выбранного пункта
                                    for (int i = 0; i < changemenu.size(); i++) {
                                        if (i == currentOptionch) {
                                            cout << "\033[1;32m" << changemenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                                        } else {
                                            cout << changemenu[i] << endl;
                                        }
                                    }

                                    // Получение нажатой клавиши
                                    int key = getch();

                                    // Обработка нажатой клавиши
                                    switch (key) {
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
                                            if (currentOptionch == changemenu.size() - 1) {
                                                quitChange = true;
                                            } else {
                                                loadingAnimation();
                                                vector<string> updatedData;
                                        updatedData.push_back(DateToChange);
                                        updatedData.push_back(MaxTemp);
                                        updatedData.push_back(MinTemp);
                                        updatedData.push_back(WindSpeed);
                                        updatedData.push_back(Humidity);
                                        writing(region, updatedData, DateToChange);
                                            }
                                            break;
                                    }
                                }
                                break;
                            }
                            case 1: {
                                cout << "Вы выбрали: Продлить прогноз погоды." << endl;
                                string region = "/Users/nikitaadamonis/Desktop/work&shit/osa/course/course weather/course weather osa/course weather osa/";
                                system("clear");
                                cout << "Введите максимальную температуру (пример: '31'): ";
                                string MaxTemp;
                                cin >> MaxTemp;
                                MaxTemp = " " + MaxTemp + "°C ";
                                cout << "Введите минимальную температуру (пример: '-1'): ";
                                string MinTemp;
                                cin >> MinTemp;
                                MinTemp = " " + MinTemp + "°C ";
                                cout << "Введите скорость ветра (пример: '11'): ";
                                string WindSpeed;
                                cin >> WindSpeed;
                                WindSpeed = " " + WindSpeed + " км/ч";
                                cout << "Введите влажность (пример: '65'): ";
                                string Humidity;
                                cin >> Humidity;
                                Humidity = " " + Humidity + "% ";
                                cout << "Введите файл (пример: 'minsk'): ";
                                string region1;
                                cin >> region1;
                                region += region1 + ".txt";

                                vector<string> changemenu;
                        changemenu.push_back(" Да. ");
                        changemenu.push_back(" Нет. ");
                                int currentOptionch = 0;
                                bool quitChange = false;

                                while (!quitChange) {
                                    // Очистка консоли
                                    system("clear");

                                    // Вывод меню с подсветкой выбранного пункта
                                    for (int i = 0; i < changemenu.size(); i++) {
                                        if (i == currentOptionch) {
                                            cout << "\033[1;32m" << changemenu[i] << "\033[0m" << endl; // Подсветка выбранного пункта зеленым цветом
                                        } else {
                                            cout << changemenu[i] << endl;
                                        }
                                    }

                                    // Получение нажатой клавиши
                                    int key = getch();

                                    // Обработка нажатой клавиши
                                    switch (key) {
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
                                            if (currentOptionch == changemenu.size() - 1) {
                                                quitChange = true;
                                            } else {
                                                loadingAnimation();
                                                vector<string> updatedData;
                                        // updatedData.push_back(DateToChange);
                                        updatedData.push_back(MaxTemp);
                                        updatedData.push_back(MinTemp);
                                        updatedData.push_back(WindSpeed);
                                        updatedData.push_back(Humidity);
                                                writing(region, updatedData, "new");
                                            }
                                            break;
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    break;
            }
        }
    }
}

int main() {
    AdminMenu();
    return 0;
}