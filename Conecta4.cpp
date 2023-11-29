#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <algorithm>

const int FILAS = 6;
const int COLUMNAS = 7;
enum Dificultad { FACIL, INTERMEDIO, DIFICIL };

class Conecta4 {
public:
    char tablero[FILAS][COLUMNAS];
    char fichaJugador;  
    char fichaOponente;  
    int nodosExplorados = 0;
    Dificultad dificultad;
    void moverIADificil(char ficha, Dificultad nivel);
    
    Conecta4(char jugador, char oponente, Dificultad nivel) : fichaJugador(jugador), fichaOponente(oponente), dificultad(nivel) {
        // Inicializar el tablero vacío
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                tablero[i][j] = ' ';
            }
        }
    }


    // Imprimir el tablero
    void imprimirTablero() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                std::cout << "| " << tablero[i][j] << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
    }

    // Colocar una ficha en la columna elegida
    bool colocarFicha(int columna, char ficha) {
        for (int i = FILAS - 1; i >= 0; --i) {
            if (tablero[i][columna] == ' ') {
                tablero[i][columna] = ficha;
                return true; // Ficha colocada
            }
        }
        return false; // Columna llena
    }

    // Verificar si hay un ganador
    bool hayGanador(char ficha) {
    // Verificar en horizontal
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == ficha &&
                tablero[i][j + 1] == ficha &&
                tablero[i][j + 2] == ficha &&
                tablero[i][j + 3] == ficha) {
                return true;
            }
        }
    }

    // Verificar en vertical
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero[i][j] == ficha &&
                tablero[i + 1][j] == ficha &&
                tablero[i + 2][j] == ficha &&
                tablero[i + 3][j] == ficha) {
                return true;
            }
        }
    }

    // Verificar en diagonal (ascendente)
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == ficha &&
                tablero[i - 1][j + 1] == ficha &&
                tablero[i - 2][j + 2] == ficha &&
                tablero[i - 3][j + 3] == ficha) {
                return true;
            }
        }
    }

    // Verificar en diagonal (descendente)
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            if (tablero[i][j] == ficha &&
                tablero[i - 1][j - 1] == ficha &&
                tablero[i - 2][j - 2] == ficha &&
                tablero[i - 3][j - 3] == ficha) {
                return true;
            }
        }
    }

    return false;
}

    // Verificar si el tablero está lleno
    bool tableroLleno() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (tablero[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

//Mover la ficha en el turno de la IA
void moverIA(char ficha, Dificultad nivel) {
    int profundidad; //Tamaño de los estados a verificar del juego
    //Mayor profundidad mas dificultad de la ia

    switch (nivel) {
        case FACIL:
            profundidad = 3;
            break;
        case INTERMEDIO:
            profundidad = 5;
            break;
        case DIFICIL:
            profundidad = 8;
            break;
    }

    //Funcion Minimax sin Poda aplha-beta
    //int columna = minimax(profundidad, true).second;

    //Funcion Minimax con Poda aplha-beta
    int columna = minimaxAB(profundidad, true, INT_MIN, INT_MAX).second;
    colocarFicha(columna, ficha);
}

//Evaula el tablero para funcion Minimax
int evaluarTablero() {
    int evaluacion = 0;

    // Evaluar en horizontal y vertical
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS - 3; ++j) {
            evaluacion += evaluarVentana(tablero[i][j], tablero[i][j + 1], tablero[i][j + 2], tablero[i][j + 3]);
            evaluacion += evaluarVentana(tablero[j][i], tablero[j + 1][i], tablero[j + 2][i], tablero[j + 3][i]);
        }
    }

    // Evaluar en diagonal (ascendente)
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS - 3; ++j) {
            evaluacion += evaluarVentana(tablero[i][j], tablero[i - 1][j + 1], tablero[i - 2][j + 2], tablero[i - 3][j + 3]);
        }
    }

    // Evaluar en diagonal (descendente)
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            evaluacion += evaluarVentana(tablero[i][j], tablero[i - 1][j - 1], tablero[i - 2][j - 2], tablero[i - 3][j - 3]);
        }
    }

    return evaluacion;
}

//Asigna puntajes para determinar la mejor posicion en la funcion Minimax
int evaluarVentana(char c1, char c2, char c3, char c4) {
    int evaluacion = 0;
    int jugadorCount = 0;
    int oponenteCount = 0;

    const char ventana[4] = {c1, c2, c3, c4};

    for (int i = 0; i < 4; ++i) {
        if (ventana[i] == fichaJugador) {
            jugadorCount++;
        } else if (ventana[i] == fichaOponente) {
            oponenteCount++;
        }
    }

    // Asigna puntajes según las fichas en la ventana
    if (jugadorCount == 4) {
        evaluacion += 100;
    } else if (jugadorCount == 3 && oponenteCount == 0) {
        evaluacion += 5;
    } else if (jugadorCount == 2 && oponenteCount == 0) {
        evaluacion += 2;
    }

    if (oponenteCount == 4) {
        evaluacion -= 100;
    } else if (oponenteCount == 3 && jugadorCount == 0) {
        evaluacion -= 5;
    } else if (oponenteCount == 2 && jugadorCount == 0) {
        evaluacion -= 2;
    }

    return evaluacion;
}

//Funcion Minimax sin implementacion PODA alpha-beta

/*
std::pair<int, int> minimax(int profundidad, bool esMaximizador) {
    if (profundidad == 0 || hayGanador('X') || hayGanador('O') || tableroLleno()) {
        int evaluacion = evaluarTablero();
        return std::make_pair(evaluacion, -1);
    }

    std::vector<int> columnasDisponibles;
    for (int columna = 0; columna < COLUMNAS; ++columna) {
        if (tablero[0][columna] == ' ') {
            columnasDisponibles.push_back(columna);
        }
    }

    if (esMaximizador) {
        int maxEval = std::numeric_limits<int>::min();
        int mejorColumna = -1;

        for (int columna : columnasDisponibles) {
            Conecta4 nuevoEstado = *this;
            if (nuevoEstado.colocarFicha(columna, 'O')) {
                int evaluacion = nuevoEstado.minimax(profundidad - 1, false).first;

                // Introducir cierta variabilidad
                evaluacion += rand() % 10;

                if (evaluacion > maxEval) {
                    maxEval = evaluacion;
                    mejorColumna = columna;
                }
            }
        }
        return std::make_pair(maxEval, mejorColumna);
    } else {
        int minEval = std::numeric_limits<int>::max();
        int mejorColumna = -1;

        for (int columna : columnasDisponibles) {
            Conecta4 nuevoEstado = *this;
            if (nuevoEstado.colocarFicha(columna, 'X')) {
                int evaluacion = nuevoEstado.minimax(profundidad - 1, true).first;

                // Introducir cierta variabilidad
                evaluacion -= rand() % 10;

                if (evaluacion < minEval) {
                    minEval = evaluacion;
                    mejorColumna = columna;
                }
            }
        }
        nodosExplorados++;
        return std::make_pair(minEval, mejorColumna);
    }
}
*/

//Funcion Minimax con implementacion PODA alpha-beta

    std::pair<int, int> minimaxAB(int profundidad, bool esMaximizador, int alpha, int beta) {
    if (profundidad == 0 || hayGanador('X') || hayGanador('O') || tableroLleno()) {
        int evaluacion = evaluarTablero();
        return std::make_pair(evaluacion, -1);
    }

    int mejorColumna = -1;

    if (esMaximizador) {
        int maxEval = std::numeric_limits<int>::min();
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            Conecta4 nuevoEstado = *this;  // Crear una copia del estado actual
            if (nuevoEstado.colocarFicha(columna, 'O')) {
                int evaluacion = nuevoEstado.minimaxAB(profundidad - 1, false, alpha, beta).first;
                if (evaluacion > maxEval) {
                    maxEval = evaluacion;
                    mejorColumna = columna;
                }
                alpha = std::max(alpha, maxEval);
                if (beta <= alpha) break; // Poda alfa-beta
            }
        }
        return std::make_pair(maxEval, mejorColumna);
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            Conecta4 nuevoEstado = *this;  // Crear una copia del estado actual
            if (nuevoEstado.colocarFicha(columna, 'X')) {
                int evaluacion = nuevoEstado.minimaxAB(profundidad - 1, true, alpha, beta).first;
                if (evaluacion < minEval) {
                    minEval = evaluacion;
                    mejorColumna = columna;
                }
                beta = std::min(beta, minEval);
                if (beta <= alpha) break; // Poda alfa-beta
            }
        }
        nodosExplorados++;
        return std::make_pair(minEval, mejorColumna);
    }
}

    
};
