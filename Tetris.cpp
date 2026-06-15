#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
using namespace std;

const int Filas = 30;
const int Columnas = 30;
const int Num_figuras = 7;
const int Max_rotaciones = 4;
const int Tamanio_Figura = 4;

struct EstadisticasPartida {
    bool ganada;
    int tiempojugadosec;
    int puntaje;
    int lineaseliminadas;
};

struct Figura {
    string nombre;
    int ancho;
    int alto;
    int rotaciones;
    int rotacion_actual;
    int forma[Max_rotaciones][Tamanio_Figura][Tamanio_Figura];
};

void inicializar_figuras(Figura figuras[]) {
    figuras[0].nombre = "Linea Recta";
    figuras[0].rotaciones = 2;
    figuras[0].rotacion_actual = 0;
    figuras[0].ancho = 4;
    figuras[0].alto = 1;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[0].forma[r][i][j] = 0;

    figuras[0].forma[0][1][0] = 1;
    figuras[0].forma[0][1][1] = 1;
    figuras[0].forma[0][1][2] = 1;
    figuras[0].forma[0][1][3] = 1;
    figuras[0].forma[1][0][2] = 1;
    figuras[0].forma[1][1][2] = 1;
    figuras[0].forma[1][2][2] = 1;
    figuras[0].forma[1][3][2] = 1;

    figuras[1].nombre = "Cuadrado";
    figuras[1].rotaciones = 1;
    figuras[1].rotacion_actual = 0;
    figuras[1].ancho = 2;
    figuras[1].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[1].forma[r][i][j] = 0;

    figuras[1].forma[0][0][1] = 1;
    figuras[1].forma[0][0][2] = 1;
    figuras[1].forma[0][1][1] = 1;
    figuras[1].forma[0][1][2] = 1;

    figuras[2].nombre = "Figura S";
    figuras[2].rotaciones = 2;
    figuras[2].rotacion_actual = 0;
    figuras[2].ancho = 3;
    figuras[2].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[2].forma[r][i][j] = 0;

    figuras[2].forma[0][1][1] = 1;
    figuras[2].forma[0][1][2] = 1;
    figuras[2].forma[0][2][0] = 1;
    figuras[2].forma[0][2][1] = 1;
    figuras[2].forma[1][0][1] = 1;
    figuras[2].forma[1][1][1] = 1;
    figuras[2].forma[1][1][2] = 1;
    figuras[2].forma[1][2][2] = 1;

    figuras[3].nombre = "Figura Z";
    figuras[3].rotaciones = 2;
    figuras[3].rotacion_actual = 0;
    figuras[3].ancho = 3;
    figuras[3].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[3].forma[r][i][j] = 0;

    figuras[3].forma[0][1][0] = 1;
    figuras[3].forma[0][1][1] = 1;
    figuras[3].forma[0][2][1] = 1;
    figuras[3].forma[0][2][2] = 1;
    figuras[3].forma[1][0][2] = 1;
    figuras[3].forma[1][1][1] = 1;
    figuras[3].forma[1][1][2] = 1;
    figuras[3].forma[1][2][1] = 1;

    figuras[4].nombre = "Figura J";
    figuras[4].rotaciones = 4;
    figuras[4].rotacion_actual = 0;
    figuras[4].ancho = 3;
    figuras[4].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[4].forma[r][i][j] = 0;

    figuras[4].forma[0][1][0] = 1;
    figuras[4].forma[0][1][1] = 1;
    figuras[4].forma[0][1][2] = 1;
    figuras[4].forma[0][2][0] = 1;
    figuras[4].forma[1][0][0] = 1;
    figuras[4].forma[1][1][0] = 1;
    figuras[4].forma[1][2][0] = 1;
    figuras[4].forma[1][2][1] = 1;
    figuras[4].forma[2][1][0] = 1;
    figuras[4].forma[2][1][1] = 1;
    figuras[4].forma[2][1][2] = 1;
    figuras[4].forma[2][2][2] = 1;
    figuras[4].forma[3][0][1] = 1;
    figuras[4].forma[3][0][2] = 1;
    figuras[4].forma[3][1][2] = 1;
    figuras[4].forma[3][2][2] = 1;

    figuras[5].nombre = "Figura T";
    figuras[5].rotaciones = 4;
    figuras[5].rotacion_actual = 0;
    figuras[5].ancho = 3;
    figuras[5].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[5].forma[r][i][j] = 0;

    figuras[5].forma[0][0][1] = 1;
    figuras[5].forma[0][1][0] = 1;
    figuras[5].forma[0][1][1] = 1;
    figuras[5].forma[0][1][2] = 1;
    figuras[5].forma[1][0][1] = 1;
    figuras[5].forma[1][1][1] = 1;
    figuras[5].forma[1][1][2] = 1;
    figuras[5].forma[1][2][1] = 1;
    figuras[5].forma[2][1][0] = 1;
    figuras[5].forma[2][1][1] = 1;
    figuras[5].forma[2][1][2] = 1;
    figuras[5].forma[2][2][1] = 1;
    figuras[5].forma[3][0][1] = 1;
    figuras[5].forma[3][1][0] = 1;
    figuras[5].forma[3][1][1] = 1;
    figuras[5].forma[3][2][1] = 1;

    figuras[6].nombre = "Figura L";
    figuras[6].rotaciones = 4;
    figuras[6].rotacion_actual = 0;
    figuras[6].ancho = 3;
    figuras[6].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++)
        for (int i = 0; i < Tamanio_Figura; i++)
            for (int j = 0; j < Tamanio_Figura; j++)
                figuras[6].forma[r][i][j] = 0;

    figuras[6].forma[0][1][0] = 1;
    figuras[6].forma[0][1][1] = 1;
    figuras[6].forma[0][1][2] = 1;
    figuras[6].forma[0][2][2] = 1;
    figuras[6].forma[1][0][2] = 1;
    figuras[6].forma[1][1][2] = 1;
    figuras[6].forma[1][2][1] = 1;
    figuras[6].forma[1][2][2] = 1;
    figuras[6].forma[2][1][0] = 1;
    figuras[6].forma[2][1][1] = 1;
    figuras[6].forma[2][1][2] = 1;
    figuras[6].forma[2][2][0] = 1;
    figuras[6].forma[3][0][0] = 1;
    figuras[6].forma[3][0][1] = 1;
    figuras[6].forma[3][1][0] = 1;
    figuras[6].forma[3][2][0] = 1;
}

Figura figuras_globales[Num_figuras];
bool figuras_inicializadas = false;

void transponer_figura(Figura& figura) {
    figura.rotacion_actual = (figura.rotacion_actual + 1) % figura.rotaciones;
}

void calcular_dimensiones(Figura& figura) {
    if (figura.nombre == "Linea Recta") {
        if (figura.rotacion_actual == 0) {
            figura.ancho = 4; figura.alto = 1;
        } else {
            figura.ancho = 1; figura.alto = 4;
        }
    } else if (figura.nombre == "Cuadrado") {
        figura.ancho = 2; figura.alto = 2;
    } else {
        if (figura.rotacion_actual == 0 || (figura.rotaciones == 4 && figura.rotacion_actual == 2)) {
            figura.ancho = 3; figura.alto = 2;
        } else {
            figura.ancho = 2; figura.alto = 3;
        }
    }
}

Figura estableceraleatoriofigura() {
    if (!figuras_inicializadas) {
        inicializar_figuras(figuras_globales);
        figuras_inicializadas = true;
    }
    int indice = rand() % Num_figuras;
    Figura nueva_figura = figuras_globales[indice];
    nueva_figura.rotacion_actual = 0;
    calcular_dimensiones(nueva_figura);
    return nueva_figura;
}

void mostrar_figura(Figura& figura) {
    printw(" %s (Rotacion %d)\n", figura.nombre.c_str(), figura.rotacion_actual);
    printw("Dimensiones %dx%d\n", figura.ancho, figura.alto);
    for (int i = 0; i < Tamanio_Figura; i++) {
        for (int j = 0; j < Tamanio_Figura; j++)
            addch(figura.forma[figura.rotacion_actual][i][j] == 1 ? '#' : ' ');
        addch('\n');
    }
    refresh();
}

void inicializar_tablero(char tablero[Filas][Columnas]) {
    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Columnas; j++) {
            if (j == 0 || j == Columnas - 1)
                tablero[i][j] = '|';
            else if (i == Filas - 1)
                tablero[i][j] = '-';
            else
                tablero[i][j] = ' ';
        }
    }
}

int mostrarmenu() {
    clear();
    printw(" Ingresa una opcion para jugar al juego\n\n\n");
    printw("1. Iniciar juego\n\n");
    printw("2. Demo de transposiciones\n\n");
    printw("3. Mirar estadisticas de partidas\n\n");
    printw("4. Salir\n\n");
    refresh();
    int opcion = getch() - '0';
    return opcion;
}

void demo_transposiciones() {
    clear();
    printw("  Demo de transposiciones para pruebas\n");
    printw(" Observar como cambian las figuras al rotar\n\n");

    Figura figura = estableceraleatoriofigura();
    mostrar_figura(figura);

    while (true) {
        printw("\n  Opciones:\n");
        printw("r: Rotar figura\n");
        printw("n: Nueva figura aleatoria\n");
        printw("a: Mostrar todas las rotaciones\n");
        printw("q: Salir\n");
        printw("Escoge opcion: ");
        refresh();

        char tecla = getch();

        if (tecla == 'q') {
            printw("Saliendo del demo\n");
            refresh();
            break;
        }
        if (tecla == 'r') {
            printw("  Antes de rotar\n");
            mostrar_figura(figura);
            transponer_figura(figura);
            calcular_dimensiones(figura);
            printw("  Despues de rotar\n");
            mostrar_figura(figura);
        }
        if (tecla == 'n') {
            figura = estableceraleatoriofigura();
            printw("  Nueva figura:\n");
            mostrar_figura(figura);
        }
        if (tecla == 'a') {
            printw(" Todas las rotaciones: %s\n", figura.nombre.c_str());
            int rotacion_original = figura.rotacion_actual;
            for (int i = 0; i < figura.rotaciones; i++) {
                figura.rotacion_actual = i;
                calcular_dimensiones(figura);
                printw(" Rotacion %d:\n", i);
                mostrar_figura(figura);
            }
            figura.rotacion_actual = rotacion_original;
            calcular_dimensiones(figura);
        }
    }
}

bool hay_colision(char tablero[Filas][Columnas], Figura figura, int pos_x, int pos_y, int rotacion) {
    for (int i = 0; i < Tamanio_Figura; i++) {
        for (int j = 0; j < Tamanio_Figura; j++) {
            if (figura.forma[rotacion][i][j] == 1) {
                int tablero_x = pos_x + j;
                int tablero_y = pos_y + i;
                if (tablero_x < 0 || tablero_x >= Columnas || tablero_y >= Filas)
                    return true;
                if (tablero_y >= 0 && tablero[tablero_y][tablero_x] != ' ')
                    return true;
            }
        }
    }
    return false;
}

void fijarfigura(char tablero[Filas][Columnas], Figura figura, int pos_x, int pos_y) {
    for (int i = 0; i < Tamanio_Figura; i++) {
        for (int j = 0; j < Tamanio_Figura; j++) {
            if (figura.forma[figura.rotacion_actual][i][j] == 1) {
                int tx = pos_x + j;
                int ty = pos_y + i;
                if (ty >= 0 && ty < Filas && tx >= 0 && tx < Columnas)
                    tablero[ty][tx] = '#';
            }
        }
    }
}

void mostrartableroconfig(char tablero[Filas][Columnas], Figura figura, int pos_x, int pos_y) {
    char temp[Filas][Columnas];
    memcpy(temp, tablero, sizeof(temp));
    for (int i = 0; i < Tamanio_Figura; i++) {
        for (int j = 0; j < Tamanio_Figura; j++) {
            if (figura.forma[figura.rotacion_actual][i][j] == 1) {
                int tx = pos_x + j;
                int ty = pos_y + i;
                if (ty >= 0 && ty < Filas && tx >= 0 && tx < Columnas)
                    temp[ty][tx] = '@';
            }
        }
    }
    clear();
    mvprintw(0, 0, " Tablero de tetris");
    mvprintw(1, 0, "  W: rotar  A: izquierda  D: derecha  S: bajar");
    for (int i = 0; i < Filas; i++) {
        move(3 + i, 0);
        for (int j = 0; j < Columnas; j++)
            addch(temp[i][j]);
    }
    refresh();
}

int eliminarfilascompletas(char tablero[Filas][Columnas]) {
    int lineaseliminadas = 0;
    for (int i = 0; i < Filas; i++) {
        bool fila_completa = true;
        for (int j = 1; j < Columnas - 1; j++) {
            if (tablero[i][j] == ' ') {
                fila_completa = false;
                break;
            }
        }
        if (fila_completa && i != Filas - 1) {
            lineaseliminadas++;
            for (int k = i; k > 0; k--)
                for (int j = 0; j < Columnas; j++)
                    tablero[k][j] = tablero[k - 1][j];
            for (int j = 0; j < Columnas; j++)
                tablero[0][j] = (j == 0 || j == Columnas - 1) ? '|' : ' ';
        }
    }
    return lineaseliminadas;
}

void GuardarEstadisticas(EstadisticasPartida estadisticas, string nombrearchivo) {
    ofstream archivo(nombrearchivo, ios::app);
    if (archivo.is_open()) {
        archivo << estadisticas.ganada << "  " << estadisticas.tiempojugadosec
                << "  " << estadisticas.puntaje << " " << estadisticas.lineaseliminadas << "\n";
        archivo.close();
    }
}

void generarestadisticas(string nombrearchivo) {
    ifstream archivo(nombrearchivo, ios::in);
    if (!archivo.is_open()) {
        printw(" Error al abrir el archivo\n");
        refresh();
        return;
    }

    int totaljugadas = 0, totalganadas = 0, totalTiempo = 0, totalPuntaje = 0, totalLineas = 0;
    EstadisticasPartida e;

    while (archivo >> e.ganada >> e.tiempojugadosec >> e.puntaje >> e.lineaseliminadas) {
        totaljugadas++;
        if (e.ganada) totalganadas++;
        totalTiempo += e.tiempojugadosec;
        totalPuntaje += e.puntaje;
        totalLineas += e.lineaseliminadas;
    }
    archivo.close();

    if (totaljugadas == 0) {
        printw(" No hay estadisticas aun\n");
    } else {
        double promedioTiempo = (double)totalTiempo / totaljugadas;
        double promedioPuntaje = (double)totalPuntaje / totaljugadas;
        printw("Total partidas jugadas: %d\n", totaljugadas);
        printw("Total partidas ganadas: %d\n", totalganadas);
        printw("Tiempo promedio por partida: %.1f segundos\n", promedioTiempo);
        printw("Puntaje promedio por partida: %.1f\n", promedioPuntaje);
        printw("Lineas eliminadas en total: %d\n", totalLineas);
    }
    refresh();
}

void jugartetriscentro(char tablero[Filas][Columnas]) {
    inicializar_tablero(tablero);
    Figura figura_actual = estableceraleatoriofigura();
    int pos_x = (Columnas - figura_actual.ancho) / 2;
    int pos_y = 0;
    int tiempocaida = 0;
    int intervalocaida = 50;
    int tiempo_inicio = time(nullptr);
    int lineaseliminadas = 0;
    int puntaje = 0;

    nodelay(stdscr, TRUE);

    while (true) {
        mostrartableroconfig(tablero, figura_actual, pos_x, pos_y);

        int tecla = getch();
        if (tecla != ERR) {
            switch (tecla) {
                case 'a':
                    if (!hay_colision(tablero, figura_actual, pos_x - 1, pos_y, figura_actual.rotacion_actual))
                        pos_x--;
                    break;
                case 'd':
                    if (!hay_colision(tablero, figura_actual, pos_x + 1, pos_y, figura_actual.rotacion_actual))
                        pos_x++;
                    break;
                case 'w': {
                    int nueva_rotacion = (figura_actual.rotacion_actual + 1) % figura_actual.rotaciones;
                    if (!hay_colision(tablero, figura_actual, pos_x, pos_y, nueva_rotacion)) {
                        figura_actual.rotacion_actual = nueva_rotacion;
                        calcular_dimensiones(figura_actual);
                    }
                    break;
                }
                case 's':
                    if (!hay_colision(tablero, figura_actual, pos_x, pos_y + 1, figura_actual.rotacion_actual))
                        pos_y++;
                    break;
            }
        }

        if (tiempocaida >= intervalocaida) {
            if (!hay_colision(tablero, figura_actual, pos_x, pos_y + 1, figura_actual.rotacion_actual)) {
                pos_y++;
            } else {
                fijarfigura(tablero, figura_actual, pos_x, pos_y);
                lineaseliminadas += eliminarfilascompletas(tablero);
                figura_actual = estableceraleatoriofigura();
                pos_x = (Columnas - figura_actual.ancho) / 2;
                pos_y = 0;
                if (hay_colision(tablero, figura_actual, pos_x, pos_y, figura_actual.rotacion_actual)) {
                    int tiempojugado = time(nullptr) - tiempo_inicio;
                    bool ganada = lineaseliminadas >= 10;
                    EstadisticasPartida estadisticas = {ganada, tiempojugado, puntaje, lineaseliminadas};
                    GuardarEstadisticas(estadisticas, "Estadisticas.txt");
                    nodelay(stdscr, FALSE);
                    clear();
                    printw("Juego terminado!!\n");
                    printw("Lineas eliminadas: %d\n", lineaseliminadas);
                    printw("\nPresiona cualquier tecla para continuar...\n");
                    refresh();
                    getch();
                    break;
                }
            }
            tiempocaida = 0;
        } else {
            tiempocaida++;
        }
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

int main() {
    srand(time(nullptr));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int opcion = mostrarmenu();

    if (opcion != 4) {
        char tablero[Filas][Columnas];
        inicializar_tablero(tablero);

        if (opcion == 1) {
            jugartetriscentro(tablero);
        } else if (opcion == 2) {
            demo_transposiciones();
        } else if (opcion == 3) {
            clear();
            generarestadisticas("Estadisticas.txt");
            nodelay(stdscr, FALSE);
            printw("\nPresiona cualquier tecla para salir...\n");
            refresh();
            getch();
        }
    }

    endwin();
    return 0;
}
