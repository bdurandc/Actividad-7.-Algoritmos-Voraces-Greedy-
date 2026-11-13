//Problema 1: Mochila Fraccional con lista enlazada
//Estrategia GREEDY: tomar primero los objetos con mayor valor/peso.
#include <iostream>
using namespace std;

class Mochila {   // nodo: representa un objeto
private:
    char objeto;  // es char porque solo es un caracter: A, B, C...
    int valor;
    int peso;
    Mochila* next = NULL;

public:
    Mochila(char o, int v, int p) { // constructor de la clase Mochila
        objeto = o;
        valor = v;
        peso = p;
    }
    friend class Lista;
};

class Lista { 
private:
    Mochila* cabeza;

public:
    Lista() { // constructor de la clase Lista
        cabeza = NULL;
    }

    // la funcio Inserta mantiene la lista ordenada por valor/peso descendente
    void insertarOrdenado(char o, int v, int p) {
        Mochila* nuevo = new Mochila(o, v, p);

        // lista vacia o el nuevo tiene mayor razon (valor/peso) que la cabeza
        if (cabeza == NULL || v * cabeza->peso > cabeza->valor * p) {
            nuevo->next = cabeza;
            cabeza = nuevo;
        } else {
            // avanzar mientras el siguiente tenga razon mayor o igual
            Mochila* actual = cabeza;
            while (actual->next != NULL &&
                   actual->next->valor * p >= v * actual->next->peso) {
                actual = actual->next;
            }
            nuevo->next = actual->next;
            actual->next = nuevo;
        }
    }

    // Muestra todos los objetos de la lista con su razon.
    void mostrar() {
        Mochila* actual = cabeza;
        while (actual != NULL) {
            cout << actual->objeto << " (valor " << actual->valor
                 << ", peso " << actual->peso << ")\n";
            actual = actual->next;
        }
    }

    // Recorre la lista llenando la mochila (paso greedy) y muestra el resultado.
    void llenarMochila(double capacidad) {
        double restante = capacidad;
        double total = 0;
        Mochila* actual = cabeza;

        cout << "Objetos seleccionados:\n";
        while (actual != NULL && restante > 0) {
            if (actual->peso <= restante) {          // cabe completo
                cout << actual->objeto << " completo\n";
                restante -= actual->peso;
                total += actual->valor;
            } else {                                 // solo cabe una parte
                cout << restante << "/" << actual->peso
                     << " Parte del objeto " << actual->objeto << "\n";
                total += actual->valor * restante / actual->peso;
                restante = 0;
            }
            actual = actual->next;
        }
        cout << "Valor total obtenido: " << total << "\n";
    }

    // destructor de la clase Lista.
    ~Lista() {
        while (cabeza != NULL) {
            Mochila* borrar = cabeza;
            cabeza = cabeza->next;
            delete borrar;
        }
    }
};

int main() {
    double capacidad; // cuanto peso puede aguantar la mochila 
    int n; // cantidad de elemntos que se quiera agregar a la mochila 
    cout << "ingrese la capacidad de la mochila ";
    cin >> capacidad;
    cout << "ingrese cantidad de valores ";
    cin >> n; 

    Lista milista;
    for (int i = 0; i < n; i++) {
        char o;
        int v; 
		int p;
		cout << "ingrese el valor " << i+1 <<endl;
        cin >> o >> v >> p;
        milista.insertarOrdenado(o, v, p);
    }
    milista.mostrar();
    milista.llenarMochila(capacidad);
    return 0;
}
