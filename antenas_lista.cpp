//Problema 2: Cobertura de antenas con lista enlazada
//Estrategia GREEDY: cubrir la primera casa sin cobertura con una antena
//colocada lo mas a la derecha posible (en la posicion de la casa + R).

#include <iostream>
using namespace std;

class Casa { //representa una casa en la carretera
private:
    int posicion;
    Casa* next = NULL;

public:
    Casa(int p) { // constructor de la clase Casa
        posicion = p;
    }
    friend class Lista;
};

class Lista {
private:
    Casa* cabeza;

public:
    Lista() { // constructor de la clase Lista
        cabeza = NULL;
    }

    // La funcion insertarOrdenado mantiene la lista ordenada por posicion ascendente
    void insertarOrdenado(int p) {
        Casa* nueva = new Casa(p);

        // lista vacia o la nueva casa esta antes que la cabeza
        if (cabeza == NULL || p < cabeza->posicion) {
            nueva->next = cabeza;
            cabeza = nueva;
        } else {
            // avanzar mientras el siguiente tenga posicion menor o igual
            Casa* actual = cabeza;
            while (actual->next != NULL && actual->next->posicion <= p) {
                actual = actual->next;
            }
            nueva->next = actual->next;
            actual->next = nueva;
        }
    }

    // Muestra las posiciones de las casas ya ordenadas.
    void mostrar() {
        cout << "Casas ordenadas: ";
        Casa* actual = cabeza;
        while (actual != NULL) {
            cout << actual->posicion << " ";
            actual = actual->next;
        }
        cout << "\n";
    }

    // Recorre la lista colocando antenas y muestra el resultado.
    void colocarAntenas(int R) {
        int cantidad = 0;
        Casa* actual = cabeza;

        cout << "Antenas colocadas en:\n";
        while (actual != NULL) {
            int pos = actual->posicion + R;   // antena lo mas a la derecha posible
            cout << pos << "\n";
            cantidad++;

            // saltar las casas
            while (actual != NULL && actual->posicion <= pos + R) {
                actual = actual->next;
            }
        }
        cout << "Cantidad total: " << cantidad << "\n";
    }

    // destructor de la clase Lista.
    ~Lista() {
        while (cabeza != NULL) {
            Casa* borrar = cabeza;
            cabeza = cabeza->next;
            delete borrar;
        }
    }
};

int main() {
    int R; // rango de cobertura de cada antena
    int n; // cantidad de casas
    cout << "ingrese el rango de cobertura R ";
    cin >> R;
    cout << "ingrese cantidad de casas ";
    cin >> n;

    Lista milista;
    for (int i = 0; i < n; i++) {
        int p;
        cout << "Casa " << i+1 << " (posicion): ";
        cin >> p;
        milista.insertarOrdenado(p);
    }
    milista.mostrar();
    milista.colocarAntenas(R);
    return 0;
}
