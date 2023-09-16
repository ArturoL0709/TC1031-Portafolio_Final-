

//File=Oreo.cpp
//Arturo López García A01276405
//date15/09/2023

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clase para representar una cadena de ADN
class DNAString {
public:
    string sequence;  // Secuencia de ADN
    int inversions;   // Número de inversiones en la secuencia

    // Constructor de la clase DNAString
    DNAString(const string& seq) : sequence(seq), inversions(0) {
        calculateInversions(); // Calcular el número de inversiones al crear el objeto
    }

    // Método para calcular el número de inversiones en la secuencia
    void calculateInversions() {
        int n = sequence.length();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (sequence[i] > sequence[j]) {
                    inversions++; // Incrementar el contador si encontramos una inversión
                }
            }
        }
    }
};

// Función para ordenar un vector de objetos DNAString manualmente
void customSort(vector<DNAString>& dnaStrings) {
    int n = dnaStrings.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dnaStrings[j].inversions > dnaStrings[j + 1].inversions) {
                // Intercambiar las cadenas si están en el orden incorrecto
                swap(dnaStrings[j], dnaStrings[j + 1]);
            }
        }
    }
}

int main() {
    // Solicitar al usuario ingresar la longitud de las cadenas de ADN (n) y el número de cadenas (m)
    cout << "Ingrese la longitud de las cadenas de ADN (n): ";
    int n;
    cin >> n;

    cout << "Ingrese el número de cadenas de ADN (m): ";
    int m;
    cin >> m;

    vector<DNAString> dnaStrings; // Vector para almacenar las cadenas de ADN

    // Solicitar al usuario ingresar las cadenas de ADN una por una
    cout << "Ingrese las " << m << " cadenas de ADN una por una:" << endl;
    for (int i = 0; i < m; i++) {
        string seq;
        cin >> seq;
        dnaStrings.push_back(DNAString(seq)); // Crear objetos DNAString y agregarlos al vector
    }

    // Ordenar las cadenas de ADN utilizando la función customSort
    customSort(dnaStrings);

    // Imprimir las cadenas de ADN ordenadas
    cout << "Cadenas de ADN ordenadas de 'más ordenadas' a 'menos ordenadas':" << endl;
    for (const DNAString& dna : dnaStrings) {
        cout << dna.sequence << endl;
    }

    return 0;
}
