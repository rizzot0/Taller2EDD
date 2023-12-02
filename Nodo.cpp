#include <iostream>
#include <vector>
#include <climits>

template <typename T>
class Nodo {
public:
    T valor;
    std::vector<Nodo<T>*> hijos;

    // Constructor
    Nodo(T val) : valor(val) {}

    // Destructor para liberar memoria
    ~Nodo() {
        for (Nodo<T>* hijo : hijos) {
            delete hijo;
        }
    }
};