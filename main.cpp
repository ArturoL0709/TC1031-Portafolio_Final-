// =================================================================
//
// File: main.cpp
// Author:Arturo Lopez Garcia - A01276405
// Date: 22/11/2023
//
// =================================================================

// Librerias
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

// =================================================================
// Definición de estructuras y funciones
// =================================================================

struct Concursante {
    int equipo;
    int problemas_resueltos;
    int tiempo_penalizado;
    map<int, int> intentos_incorrectos;
    set<int> conjunto_problemas_resueltos;
};

int main() {
    vector<Concursante> concursantes(101);

    string linea;
    
    // Leer datos de los equipos y calcular resultados
    while (getline(cin, linea)) {
        istringstream ss(linea);
        int equipo, problema, tiempo;
        char resultado;
        ss >> equipo >> problema >> tiempo >> resultado;

        concursantes[equipo].equipo = equipo;
        if (resultado == 'C' || resultado == 'I') {
            if (resultado == 'C' && concursantes[equipo].conjunto_problemas_resueltos.find(problema) == concursantes[equipo].conjunto_problemas_resueltos.end()) {
                concursantes[equipo].problemas_resueltos++;
                concursantes[equipo].tiempo_penalizado += tiempo + (20 * concursantes[equipo].intentos_incorrectos[problema]);
                concursantes[equipo].conjunto_problemas_resueltos.insert(problema);
            } else if (resultado == 'I') {
                concursantes[equipo].intentos_incorrectos[problema]++;
            }
        }
    } //(Complejidad: O(1))

    vector<Concursante> concursantes_validos;

    for (int i = 1; i < 101; i++) {
        if (concursantes[i].problemas_resueltos > 0 || concursantes[i].tiempo_penalizado > 0) {
            concursantes_validos.push_back(concursantes[i]);
        }
    }

    // Agregar equipos que se registraron pero no tienen puntuación ni tiempo
    for (int i = 1; i < 101; i++) {
        if (concursantes[i].equipo == i && concursantes[i].problemas_resueltos == 0 && concursantes[i].tiempo_penalizado == 0) {
            concursantes_validos.push_back(concursantes[i]);
        }
    } //(Complejidad: O(1))

    // Ordenar los concursantes según los criterios
    sort(concursantes_validos.begin(), concursantes_validos.end(),
        [](const Concursante& a, const Concursante& b) {
            if (a.problemas_resueltos == b.problemas_resueltos) {
                if (a.tiempo_penalizado == b.tiempo_penalizado) {
                    return a.equipo < b.equipo;
                }
                return a.tiempo_penalizado < b.tiempo_penalizado;
            }
            return a.problemas_resueltos > b.problemas_resueltos;
        }
    ); // Complejidad: O(N log N)

    // Imprimir la salida ordenada
    for (const Concursante& concursante : concursantes_validos) {
        cout << concursante.equipo << " " << concursante.problemas_resueltos << " " << concursante.tiempo_penalizado << endl;
    } // Complejidad total del programa: O(N log N)

    return 0;
}
