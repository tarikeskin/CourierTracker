#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <windows.h> 
#include <clocale>
#include <fstream>

using namespace std;

int main() {

    setlocale(LC_ALL, "Turkish");

    const int SIZE = 10;
    int matrix[SIZE][SIZE];
    const int CUSTOMER_COUNT = 5; 
    bool isCustomer[SIZE][SIZE] = { false }; 
    bool visited[SIZE][SIZE] = { false };   
    pair<int, int> customerLocations[CUSTOMER_COUNT]; 
    bool visitedCustomers[CUSTOMER_COUNT] = { false }; 

    int courierX = 0, courierY = 0; 
    int startX = courierX, startY = courierY;
    int totalPath = 0;

    srand(time(nullptr));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = rand() % 100; 
        }
    }

    for (int k = 0; k < CUSTOMER_COUNT; ++k) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (isCustomer[x][y] || (x == 0 && y == 0));

        isCustomer[x][y] = true;
        customerLocations[k] = { x, y };
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (true) {
        system("cls");

        SetConsoleTextAttribute(hConsole, 9);
        cout << "Müşteri Adresleri: \n";
        for (int k = 0; k < CUSTOMER_COUNT; ++k) {
            cout << "Müşteri " << k + 1 << ": (" << customerLocations[k].first
                << ", " << customerLocations[k].second << ")";
            if (visitedCustomers[k]) {
                SetConsoleTextAttribute(hConsole, 10);
                cout << " Kurye adrese ulaştı. Paket teslim edildi.";
            }
            SetConsoleTextAttribute(hConsole, 9); 
            cout << endl;
        }

        SetConsoleTextAttribute(hConsole, 7); 
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i == courierX && j == courierY) {
                    SetConsoleTextAttribute(hConsole, 12); 
                    cout << "K" << "\t";
                }
                else if (visited[i][j]) {
                    SetConsoleTextAttribute(hConsole, 10); 
                    cout << matrix[i][j] << "\t";
                }
                else if (isCustomer[i][j]) {
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << matrix[i][j] << "\t";
                }
                else {
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << matrix[i][j] << "\t";
                }
            }
            cout << "\n";
        }

        SetConsoleTextAttribute(hConsole, 7);
        cout << "\nGidilen Toplam Yol: " << totalPath << endl;

        char input = _getch(); 
        int newX = courierX, newY = courierY;

        if (input == 'w' && courierX > 0) newX--; 
        if (input == 's' && courierX < SIZE - 1) newX++;
        if (input == 'a' && courierY > 0) newY--;
        if (input == 'd' && courierY < SIZE - 1) newY++;

        if (newX != courierX || newY != courierY) {
            totalPath += matrix[newX][newY];
            visited[newX][newY] = true;

            for (int k = 0; k < CUSTOMER_COUNT; ++k) {
                if (customerLocations[k].first == newX && customerLocations[k].second == newY) {
                    visitedCustomers[k] = true; 
                    isCustomer[newX][newY] = false;
                }
            }
        }

        courierX = newX;
        courierY = newY;

        if (courierX == startX && courierY == startY && totalPath > 0) {
            cout << "\nKurye başlangıç noktasına geri döndü. Uygulama sonlanıyor...\n";
            break;
        }

        if (input == 'q') {
            cout << "\nUygulamadan çıkılıyor...\n";
            break;
        }
    }

    ofstream outFile("Cost.txt");
    if (outFile.is_open()) {
        outFile << "GÜN SONU RAPORU\nMüşteri Adresleri:\n";
        for (int k = 0; k < CUSTOMER_COUNT; ++k) {
            outFile << "Müşteri " << k + 1 << ": (" << customerLocations[k].first
                << ", " << customerLocations[k].second << ")";
            if (visitedCustomers[k]) {
                outFile << "Kurye müşteriye paketi teslim etti"; 
            }
            outFile << endl;
        }
        outFile << "\nToplam Yol Maliyeti: " << totalPath << endl;
        outFile.close();
        cout << "Müşteri bilgileri ve toplam yol maliyeti Cost.txt dosyasına kaydedildi.\n";
    }
    else {
        cout << "Dosya açılırken bir hata oluştu!\n";
    }

   

    SetConsoleTextAttribute(hConsole, 7);

    return 0;
}
