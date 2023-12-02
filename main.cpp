/*Bastian Guerra Valdes,Estructura de datos,Taller 2*/

#include <iostream>
#include <vector>
#include <limits> 
#include <climits>
#include <cstdlib>
#include <chrono>
#include "Arbol.cpp"
#include "Conecta4.cpp"


int main() {
    char jugador = 'X';
    char ia = 'O';
    Conecta4 juego(jugador, ia, Dificultad::FACIL);  

    std::cout << "Bienvenido" << std::endl;

    //Selección de dificultad
    std::cout << "Elige la dificultad:" << std::endl;
    std::cout << "1. Fácil" << std::endl;
    std::cout << "2. Intermedio" << std::endl;
    std::cout << "3. Difícil" << std::endl;
    std::cout << "4. Cargar Partida" << std::endl;

    int opcion;
    std::cin >> opcion;

    if (opcion == 2) {
        juego = Conecta4(jugador, ia, Dificultad::INTERMEDIO);
    } else if (opcion == 3) {
        juego = Conecta4(jugador, ia, Dificultad::DIFICIL);
    } else if (opcion == 4) {
        juego.cargarEstado("partida.csv", juego);
    }

    //Calculo de tiempo de ejecucion del Progama
    auto tiempoInicio = std::chrono::high_resolution_clock::now();

    //Funcionamiento del juego
    while (true) {

        juego.imprimirTablero();

        // Turno del jugador
        if (jugador == 'X') {
            int columna;
            std::cout << "Jugador " << jugador << ", elige una columna (0-6) - Guardar partida 7: ";
            std::cin >> columna;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el búfer

            if (columna == 7) {
                juego.guardarEstado("partida.csv");
                std::cout << "Partida guardada" << std::endl;
                break;
            } else if (columna < 0 || columna >= COLUMNAS || !juego.colocarFicha(columna, jugador)) {
                std::cout << "Columna no válida. Elige otra vez." << std::endl;
                continue;
    }
        } else {
            //Turno de la IA

            //Inicializar calculo de tiempo de la ejecucacion del algoritmo minimax
            auto tiempoInicio = std::chrono::high_resolution_clock::now();

            juego.moverIA(ia, static_cast<Dificultad>(opcion - 1));

            //Finalizar calculo tiempo y mostrarlo x pantalla
            auto tiempoFinal = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> iaTiempoRecorrido = tiempoFinal - tiempoInicio;
            std::cout << "Tiempo de ejecución de la funcion Minimax: " << iaTiempoRecorrido.count() << " segundos" << std::endl;
        }

        //Verificar el estado actual del tablero
        if (juego.hayGanador(jugador)) {
            juego.imprimirTablero();
            std::cout << "¡Jugador " << jugador << " ha ganado!" << std::endl;
            break;
        }

        //Empate
        if (juego.tableroLleno()) {
            juego.imprimirTablero();
            std::cout << "¡Empate!" << std::endl;
            break;
        }

        //Cambio de turno de jugador
        jugador = (jugador == 'X') ? 'O' : 'X';
    }

    //Tiempo total de ejecucion del progama una vez finalizado
    auto tiempoFinal = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoRecorrido = tiempoFinal - tiempoInicio;
    std::cout << "Tiempo total de ejecución: " << tiempoRecorrido.count() << " segundos" << std::endl;
    
    return 0;
}
