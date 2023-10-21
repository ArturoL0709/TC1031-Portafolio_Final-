
// =========================================================
// File: s3.cpp
// Author:Arturo Lopez Garcia- A001276405
// Date: 20/10/2023
// =========================================================
// Complejidad de la función josephus: O(n^2)
// Esta función resuelve el problema de Josephus utilizando una lista enlazada
// y un bucle while, donde la complejidad está dominada por la suma de los 
// primeros n números naturales.



#include <iostream>
#include <list>
using namespace std;

int josephus(int n, int k) {
    // Creamos una lista enlazada para representar el círculo de personas.
    list<int> circle;
    for (int i = 1; i <= n; ++i) {
        circle.push_back(i);
    }

    list<int>::iterator current = circle.begin();
    while (n > 1) {
        // Simulamos el proceso de contar y eliminar personas en cada ronda.
        for (int count = 1; count < k; ++count) {
            ++current;
            if (current == circle.end()) {
                current = circle.begin();
            }
        }
        
        list<int>::iterator next = ++current;
        if (next == circle.end()) {
            next = circle.begin();
        }
        --current;
        
        // Imprimimos el número eliminado en esta ronda.
        cout << "Eliminado: " << *next << endl;
        
        // Eliminamos la persona y ajustamos el iterador.
        circle.erase(next);
        ++current;
        if (current == circle.end()) {
            current = circle.begin();
        }
        --n;
    }

    // Devolvemos la posición segura (sobreviviente).
    return *circle.begin();
}

int main() {
    int n, k;
    cout << "Ingrese el número de personas (n): ";
    cin >> n;
    cout << "Ingrese el valor de k: ";
    cin >> k;

    int posicion_segura = josephus(n, k);

    cout << "La posición segura para comenzar el conteo es: " << posicion_segura << endl;
    
    return 0;
}
