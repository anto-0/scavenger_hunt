#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 5, HEIGHT = 5; // Dimensiunea harta

// Structura player
struct Player {
    int x = 0, y = 0; 
    int score = 0;

    void move(char direction) {
        switch (direction) {
            case 'w': if (y > 0) y--; break; // Sus
            case 's': if (y < HEIGHT - 1) y++; break; // Jos
            case 'a': if (x > 0) x--; break; // Stanga
            case 'd': if (x < WIDTH - 1) x++; break; // Dreapta
            default:cout << "Comandă invalidă!\n";
        }
    }
};

// Intrebari
struct Question {
   string text;
   string correctAnswer;

    bool askQuestion() {
        string answer;
        cout << text << " ";
        cin >> answer;
        return answer == correctAnswer;
    }
};

// Afisare harta
void displayMap(Player player, int map[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == player.y && j == player.x)
               cout << "P "; // Pozitia
            else if (map[i][j] == 2)
                cout << "N "; // NPC / Intrebare
            else if (map[i][j] == 3)
                cout << "F "; // Finish
            else
                cout << ". ";
        }
        cout << "\n";
    }
}

int main() {
    Player player;
    int map[HEIGHT][WIDTH] = {
        {0, 0, 0, 0, 0},
        {0, 2, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 0, 2, 0},
        {0, 0, 0, 3, 0} 
    };

    // Intrebari
    vector<Question> questions = {
        {"1+1? ", "2"},
        {"2+2?", "4"},
        {"3+3?", "6"},
        {"4+4", "8"}
    };

    int timeRemaining = 30; // Timpul in s
    bool gameRunning = true;

    cout << "Bine ai venit in Scavenger Game!\n";
    cout << "Comenzi: w (sus), a (stanga), s (jos), d (dreapta). Scopul: Ajungi la 'F'!\n";

    while (gameRunning) {
        displayMap(player, map);
        cout << "Scor: " << player.score << " | Timp ramas: " << timeRemaining << " secunde\n";
        cout << "Introdu o comanda: ";

        char command;
        cin >> command;

        player.move(command);
        timeRemaining--;

        //  a ajuns la un NPC
        if (map[player.y][player.x] == 2) {
            cout << "Raspunde la intrebare pentru a primi puncte.\n";
            int qIndex = rand() % questions.size();
            if (questions[qIndex].askQuestion()) {
                cout << "Raspuns corect! +10 puncte.\n";
                player.score += 10;
            } else {
               cout << "Raspuns gresit! Nu primesti puncte.\n";
            }
            map[player.y][player.x] = 0; // Elimină NPC-ul
        }

        // Verificare condiție de evadare
        if (map[player.y][player.x] == 3) {
            cout << "Felicitari! Ai ajuns la finalul jocului.\n";
            cout << "Scor final: " << player.score << "\n";
            gameRunning = false;
        }

        // Verificare timp
        if (timeRemaining <= 0) {
            cout << "Timpul a expirat! Joc terminat.\n";
            cout << "Scor final: " << player.score << "\n";
            gameRunning = false;
        }
    }

    return 0;
}
