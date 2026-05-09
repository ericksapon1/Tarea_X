#include "AVL.h"
#include <iostream>
#include <limits>

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    AVLTree tree;
    int option;

    do {
        std::cout << "\n--- Modulo de Ranking Academico ---\n";
        std::cout << "1. Insertar estudiante\n";
        std::cout << "2. Mostrar ranking academico\n";
        std::cout << "3. Buscar por skill_score\n";
        std::cout << "4. Mostrar estadisticas AVL\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione: ";
        
        if (!(std::cin >> option)) {
            clearBuffer();
            continue;
        }

        switch (option) {
            case 1: {
                Student s;
                std::cout << "ID: "; std::cin >> s.student_id;
                clearBuffer();
                std::cout << "Nombre: "; std::getline(std::cin, s.full_name);
                std::cout << "Carrera: "; std::getline(std::cin, s.career);
                std::cout << "Semestre: "; std::cin >> s.semester;
                std::cout << "GPA: "; std::cin >> s.gpa;
                std::cout << "Skill Score: "; std::cin >> s.skill_score;
                tree.insert(s);
                std::cout << "Insertado con exito.\n";
                break;
            }
            case 2:
                std::cout << "\n--- Ranking Academico ---\n";
                tree.displayRanking();
                break;
            case 3: {
                int score;
                std::cout << "Ingrese score exacto a buscar: ";
                std::cin >> score;
                tree.searchByScore(score);
                break;
            }
            case 4:
                tree.displayStats();
                break;
        }
    } while (option != 5);

    return 0;
}