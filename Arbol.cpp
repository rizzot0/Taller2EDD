#include <iostream>
#include <vector>
#include <climits>
#include <limits> 
#include "Nodo.cpp"

template <typename T>
class Arbol {
public:
    Nodo<T>* raiz;

    // Constructor
    Arbol(T val) : raiz(new Nodo<T>(val)) {}

    // Destructor para liberar memoria
    ~Arbol() {
        delete raiz;
    }

    // Función para agregar un hijo a un nodo dado
    void agregarHijo(Nodo<T>* padre, T val) {
        Nodo<T>* nuevoNodo = new Nodo<T>(val);
        padre->hijos.push_back(nuevoNodo);
    }

    // Función para imprimir el árbol de manera recursiva
    void imprimirArbol(Nodo<T>* nodo, int nivel = 0) {
        if (nodo) {
            for (int i = 0; i < nivel; ++i) {
                std::cout << "  ";  // Espacios para la indentación
            }
            std::cout << nodo->valor << std::endl;

            for (Nodo<T>* hijo : nodo->hijos) {
                imprimirArbol(hijo, nivel + 1);
            }
        }
    }
};