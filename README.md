# Taller2EDD
Taller 2 realizado en la asignatura de Estructura de datos 2023_2

--Dificultades--
Las dificultades estan establecidas con el siguiente nivel de profundidad
Facil: Profundidad = 3
Mediana: Profundidad = 5
Dificil: Profunidad = 8
Estos valores se pueden modificar a voluntad antes de iniciar el progama.

--Algoritmo Minimax--

En la seleccion de la ficha por parte de la ia, se coloco un contador de tiempo para determinar
el tiempo en la demora del algoritmo minimax(TiempoInicio y tiempoFinal en la clase Main)}

Las funciones minimax estan al final de la clase Conecta4, en este caso el codigo se ejecuta con el algoritmo minimax sin poda.
Para seleccionar con que algoritmo ejecutar el progama, se debe realizar una pequeña modoficacion en el codigo:
-Al final de la clase Conecta4, comentar y descomentar la funcion que quiere utilizar, luego en el metodo moverIA comentar o descomentar la funcion que quiere realizar

En este parte del codigo en el metodo moverIA:
    /*--Funciones minimax*/

    //Funcion Minimax sin Poda aplha-beta
    int columna = minimax(profundidad, true).second;

    //Funcion Minimax con Poda aplha-beta
    //int columna = minimaxAB(profundidad, true, INT_MIN, INT_MAX).second;

--Ejecucion minimax sin poda alpha beta--

1-Dificultad facil:

Tiempo promedio de ejecucion de la ia: 0.00007184788 (s)

2-Dificultad media:

Tiempo promedio de ejecucion de la ia: 0.0800955429 (s)

3-Dificultad dificil:

Tiempo promedio de ejecucion de la ia: 7.727345 (s)

--Ejecucion minimax poda alpha beta--

1-Dificultad facil:

Tiempo promedio de ejecucion de la ia: 0.000826964429 (s)

2-Dificultad media:

Tiempo promedio de ejecucion de la ia: 0.00819596167 (s)

3-Dificultad dificil:

Tiempo promedio de ejecucion de la ia: 0.179038267 (s)







