
// =================================================================
//Nombre:Arturo Lopez Garcia
//A01276405
// @Complejidad	O(V Log (E))
// =================================================================


// Incluye bibliotecas
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> conexiones;
vector<bool> visitado;

// =================================================================

// @Complejidad	O(V Log (E))
// =================================================================
void recorridoProfundidad(int inicio) {
    visitado[inicio] = true;
    for (int vecino : conexiones[inicio]) {
        if (!visitado[vecino]) {
            recorridoProfundidad(vecino);
        }
    }
}

// =================================================================
// Función para contar árboles y bellotas en un grafo
//
// @param aristas vector de cadenas, cadena de letras individuales
// @return pair<int, int> número de árboles y bellotas
// @Complejidad	O(n^2)
// =================================================================
pair<int, int> contarArbolesBellotas(const vector<string>& aristas, const string& letras) {
    int numArboles = 0;
    int numBellotas = 0;

    set<int> nodosGrafo;
    set<char> todosNodos;

    set<int> vertices;
    for (const string& arista : aristas) {
        char u = arista[1];
        char v = arista[3];
        vertices.insert(u - 'A');
        vertices.insert(v - 'A');
    }

    int n = 26; // Suponemos que hay 26 vértices (A..Z)
    conexiones.resize(n);
    visitado.resize(n, false);

    for (int i = 0; i < n; i++) {
        conexiones[i].clear();
    }

    // Construir el grafo a partir de las aristas proporcionadas
    for (const string& arista : aristas) {
        char u = arista[1];
        char v = arista[3];
        int uIndice = u - 'A';
        int vIndice = v - 'A';
        nodosGrafo.insert(uIndice);
        nodosGrafo.insert(vIndice);
        conexiones[uIndice].push_back(vIndice);
        conexiones[vIndice].push_back(uIndice);
    }

    // Dividir la cadena en tokens usando comas como delimitador
    istringstream iss(letras);
    string token;

    while (getline(iss, token, ',')) {
        for (char c : token) {
            if (isalpha(c)) {
                todosNodos.insert(c);
            }
        }
    }

    // Encontrar componentes conectados en el grafo igual al conteo de los árboles
    for (int u : vertices) {
        if (!visitado[u]) {
            recorridoProfundidad(u);
            numArboles++;
        }
    }

    // Iterar a través del alfabeto y contar los vértices que no están en 'nodosGrafo' pero están en 'todosNodos' igual al conteo de bellotas
    for (char c = 'A'; c <= 'Z'; c++) {
        int indiceNodo = c - 'A';
        if (nodosGrafo.find(indiceNodo) == nodosGrafo.end() && todosNodos.find(c) != todosNodos.end()) {
            numBellotas++;
        }
    }

    return make_pair(numArboles, numBellotas);
}

int main() {
    string linea;
    vector<string> aristas;
    
    while (getline(cin, linea)) {
        if (linea == "****") {
            // Fin de la lista de aristas
            break;
        }
        aristas.push_back(linea);
    }

    getline(cin, linea); // Leer la línea después de los asteriscos, lista de puntos de los árboles

    pair<int, int> resultados = contarArbolesBellotas(aristas, linea); // Complejidad O(n^2)

    cout << "There are " << resultados.first << " tree(s) and " << resultados.second << " acorn(s)." << endl;

    return 0;
}
