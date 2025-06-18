#include <iostream>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <cstring>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

const int Filas = 30;
const int Columnas = 30;
const int Num_figuras = 7; // Línea Recta, Cuadrado, S, Z, J, T, L
const int Max_rotaciones = 4;
const int Tamaño_Figura = 4;

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
    int forma[Max_rotaciones][Tamaño_Figura][Tamaño_Figura];
};

void inicializar_figuras(Figura figuras[]) {
    // Figura 0: Línea Recta
    figuras[0].nombre = "Linea Recta";
    figuras[0].rotaciones = 2;
    figuras[0].rotacion_actual = 0;
    figuras[0].ancho = 4;
    figuras[0].alto = 1;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[0].forma[r][i][j] = 0;
            }
        }
    }

    figuras[0].forma[0][1][0] = 1;
    figuras[0].forma[0][1][1] = 1;
    figuras[0].forma[0][1][2] = 1;
    figuras[0].forma[0][1][3] = 1;

    figuras[0].forma[1][0][2] = 1;
    figuras[0].forma[1][1][2] = 1;
    figuras[0].forma[1][2][2] = 1;
    figuras[0].forma[1][3][2] = 1;

    // Figura 1: Cuadrado
    figuras[1].nombre = "Cuadrado";
    figuras[1].rotaciones = 1;
    figuras[1].rotacion_actual = 0;
    figuras[1].ancho = 2;
    figuras[1].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[1].forma[r][i][j] = 0;
            }
        }
    }

    figuras[1].forma[0][0][1] = 1;
    figuras[1].forma[0][0][2] = 1;
    figuras[1].forma[0][1][1] = 1;
    figuras[1].forma[0][1][2] = 1;

    // Figura 2: Figura S
    figuras[2].nombre = "Figura S";
    figuras[2].rotaciones = 2;
    figuras[2].rotacion_actual = 0;
    figuras[2].ancho = 3;
    figuras[2].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[2].forma[r][i][j] = 0;
            }
        }
    }

    figuras[2].forma[0][1][1] = 1;
    figuras[2].forma[0][1][2] = 1;
    figuras[2].forma[0][2][0] = 1;
    figuras[2].forma[0][2][1] = 1;

    figuras[2].forma[1][0][1] = 1;
    figuras[2].forma[1][1][1] = 1;
    figuras[2].forma[1][1][2] = 1;
    figuras[2].forma[1][2][2] = 1;

    // Figura 3: Figura Z
    figuras[3].nombre = "Figura Z";
    figuras[3].rotaciones = 2;
    figuras[3].rotacion_actual = 0;
    figuras[3].ancho = 3;
    figuras[3].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[3].forma[r][i][j] = 0;
            }
        }
    }

    figuras[3].forma[0][1][0] = 1;
    figuras[3].forma[0][1][1] = 1;
    figuras[3].forma[0][2][1] = 1;
    figuras[3].forma[0][2][2] = 1;

    figuras[3].forma[1][0][2] = 1;
    figuras[3].forma[1][1][1] = 1;
    figuras[3].forma[1][1][2] = 1;
    figuras[3].forma[1][2][1] = 1;

    // Figura 4: Figura J
    figuras[4].nombre = "Figura J";
    figuras[4].rotaciones = 4;
    figuras[4].rotacion_actual = 0;
    figuras[4].ancho = 3;
    figuras[4].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[4].forma[r][i][j] = 0;
            }
        }
    }

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

    // Figura 5: Figura T
    figuras[5].nombre = "Figura T";
    figuras[5].rotaciones = 4;
    figuras[5].rotacion_actual = 0;
    figuras[5].ancho = 3;
    figuras[5].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[5].forma[r][i][j] = 0;
            }
        }
    }

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

    // Figura 6: Figura L
    figuras[6].nombre = "Figura L";
    figuras[6].rotaciones = 4;
    figuras[6].rotacion_actual = 0;
    figuras[6].ancho = 3;
    figuras[6].alto = 2;

    for (int r = 0; r < Max_rotaciones; r++) {
        for (int i = 0; i < Tamaño_Figura; i++) {
            for (int j = 0; j < Tamaño_Figura; j++) {
                figuras[6].forma[r][i][j] = 0;
            }
        }
    }

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
    } else if (figura.nombre == "Figura S" || figura.nombre == "Figura Z" || figura.nombre == "Figura J" || figura.nombre == "Figura T" || figura.nombre == "Figura L") {
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
    cout << " " << figura.nombre << " (Rotacion " << figura.rotacion_actual << ") === ";
    cout << "Dimensiones: " << figura.ancho << "x" << figura.alto << "\n";

    for (int i = 0; i < Tamaño_Figura; i++) {
        for (int j = 0; j < Tamaño_Figura; j++) {
            if (figura.forma[figura.rotacion_actual][i][j] == 1) {
                cout << "#";
            } else {
                cout << "  ";
            }
        }
        cout << "\n";
    }
}

void inicializar_tablero(char tablero[Filas][Columnas]) {
    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Columnas; j++) {
            if (j == 0 || j == Columnas - 1) {
                tablero[i][j] = '|';
            } else if (i == Filas - 1) {
                tablero[i][j] = '-';
            } else {
                tablero[i][j] = ' ';
            }
        }
    }
}

void mostrartablerotetris(char tablero[Filas][Columnas]) {
    cout << "  Tablero de tetris  "<<endl;
    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Columnas; j++) {
            cout << tablero[i][j];
        }
        cout << "\n";
    }
}

int mostrarmenu() {
    int opcion;
    cout << " Ingresa una opcion para jugar al juego";
    cout << endl << endl << endl;
    cout << "1. Iniciar juego";
    cout << endl << endl;
    cout << "2. Demo de transposiciones";
    cout << endl << endl;
    cout << "3. Mirar estadisticas de partidas";
    cout << endl << endl;
    cout << "4. Salir";
    cout << endl << endl;
    cin >> opcion;
    return opcion;
}

void demo_transposiciones() {
    cout << "  Demo de trasposiciones (temporal)  ";
    cout << " Observar como cambian las figuras al rotar ";

    if (!figuras_inicializadas) {
        inicializar_figuras(figuras_globales);
        figuras_inicializadas = true;
    }

    Figura figura = estableceraleatoriofigura();
    char tecla;

    mostrar_figura(figura);

    while (true) {
        cout << "  Opciones: ";
        cout << "r = Rotar figura "<<endl;
        cout << "n = Nueva figura aleatoria "<<endl;
        cout << "a = Mostrar todas las rotaciones "<<endl;
        cout << "q = Salir "<<endl;
        cout << "Escoge opcion: "<<endl;
        cin >> tecla;

        if (tecla == 'q') {
            cout << "Saliendo del demo ";
            break;
        }

        if (tecla == 'r') {
            cout << "  Antes de rotar ";
            mostrar_figura(figura);

            transponer_figura(figura);
            calcular_dimensiones(figura);

            cout << "  Despues de rotar ";
            mostrar_figura(figura);
        }

        if (tecla == 'n') {
            figura = estableceraleatoriofigura();
            cout << "  Nueva figura: ";
            mostrar_figura(figura);
        }

        if (tecla == 'a') {
            cout << " Todas las rotaciones  :  " << figura.nombre << "  ";
            int rotacion_original = figura.rotacion_actual;

            for (int i = 0; i < figura.rotaciones; i++) {
                figura.rotacion_actual = i;
                calcular_dimensiones(figura);
                cout << " Rotacion " << i << " : ";
                mostrar_figura(figura);
            }

            figura.rotacion_actual = rotacion_original;
            calcular_dimensiones(figura);
        }
    }
}
bool hay_colision(char tablero[Filas][Columnas],Figura figura, int pos_x, int pos_y, int rotacion) {
    for (int i=0;i<Tamaño_Figura;i++) {
        for (int j=0;j<Tamaño_Figura;j++) {
            if (figura.forma[rotacion][i][j]==1) {
                int tablero_x =pos_x+j;
                int tablero_y=pos_y+i;
                if (tablero_x<0|| tablero_x >= Columnas || tablero_y>=Filas) {
                    return true;
                }
                if (tablero_y >=0 && tablero[tablero_y][tablero_x]!= ' ') {
                    return true;
                }
            }
        }
    }
    return false;
}
void fijarfigura(char tablero[Filas][Columnas], Figura figura, int pos_x, int pos_y) {
    for (int i=0;i< Tamaño_Figura;i++) {
        for (int j=0;j<Tamaño_Figura;j++) {
            if (figura.forma[figura.rotacion_actual][i][j]==1) {
                int tablero_x =pos_x+j;
                int tablero_y=pos_y+i;
                if (tablero_y >=0 && tablero_y < Filas && tablero_x >=0 && tablero_x < Columnas) {
                    tablero[tablero_y][tablero_x] = '#';
                }
            }
        }
    }
}
void mostrartableroconfig(char tablero[Filas][Columnas], Figura figura, int pos_x, int pos_y) {
    char temp[Filas][Columnas];
    memcpy(temp,tablero,sizeof(temp)); // Copiar el tablero
    for (int i=0;i<Tamaño_Figura;i++) {
        for (int j=0;j<Tamaño_Figura;j++) {
            if (figura.forma[figura.rotacion_actual][i][j]==1) {
                int tablero_x =pos_x+j;
                int tablero_y=pos_y+i;
                if (tablero_y >=0 && tablero_y <Filas && tablero_x >=0 && tablero_x < Columnas) {
                    temp[tablero_y][tablero_x] = '@';// figura actual
                }
            }
        }
    }
    cout <<" Tablero de tetris"<<endl;
    cout<<"  Presiona W para rotar la figura "<<endl;
    cout<<" Presiona D para llevar la figura a la derecha"<<endl;
    cout<<" Presiona A para llevar la figura a la izquierda"<<endl;
    cout<<" Presiona S para acelerar la figura hacia abajo"<<endl;
    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Columnas; j++) {
            cout << temp[i][j];
        }
        cout << endl;
    }
}
int eliminarfilascompletas(char tablero[Filas][Columnas]) {
    int lineaseliminadas=0;
    for (int i=0;i< Filas;i++) {
        bool fila_completa = true;
        for (int j=1;j<Columnas-1;j++) {
            if (tablero[i][j] == ' ') {
                fila_completa = false;
                break;
            }
        }
        if (fila_completa == true && i != Filas-1) {
            lineaseliminadas++;
            for (int k=i;k>0;k--) {
                for (int j=0;j<Columnas;j++) {
                    tablero[k][j] = tablero[k-1][j];
                }
            }
            for (int j=0;j < Columnas;j++) {
                if (j==0 || j== Columnas-1 ) {
                    tablero[0][j] = '|';
                }else {
                    tablero[0][j] = ' ';
                }
            }
        }
    }
    return lineaseliminadas;
}
void GuardarEstadisticas(EstadisticasPartida Estadisticas, string nombrearchivo) {
    ofstream archivo(nombrearchivo,ios::app);
    if (archivo.is_open()) {
        archivo<<Estadisticas.ganada<<"  "<< Estadisticas.tiempojugadosec<<"  " << Estadisticas.puntaje<<" "<<Estadisticas.lineaseliminadas<<endl;
        archivo.close();
    }else {
        cout << "Error al abrir el archivo"<<endl;
    }
}
//Funcion para mostrar estadisticas
void generarestadisticas(string nombrearchivo) {
    ifstream archivo(nombrearchivo,ios::in);
    if (archivo.is_open()) {
        int totaljugadas=0;
        int totalganadas=0;
        int totalTiempo=0;
        int totalPuntaje=0;
        int totalinease=0;
        EstadisticasPartida Estadisticas;

        while (archivo >> Estadisticas.ganada >> Estadisticas.tiempojugadosec >> Estadisticas.puntaje >> Estadisticas.lineaseliminadas) {
            totaljugadas++;
            if (Estadisticas.ganada) {
                totalganadas++;
            }
            totalTiempo+=Estadisticas.tiempojugadosec;
            totalPuntaje+=Estadisticas.puntaje;
            totalinease+=Estadisticas.lineaseliminadas;
        }
        archivo.close();
        double promedioTiempo;
        if (totaljugadas> 0) {
           promedioTiempo= static_cast<double>(totalTiempo)/static_cast<double>(totaljugadas);
        } else {
            promedioTiempo=0;
        }
        double promedioPuntaje;
        if (totalganadas > 0) {
            promedioTiempo=static_cast<double>(totalPuntaje)/static_cast<double>(totaljugadas);
        }else {
            promedioPuntaje=0;
        }
        if (totaljugadas==0) {
            cout<<" No hay estadisticas aun"<<endl;
        } else {
            cout<< "Total partidas jugadas "<<totaljugadas<<endl;
            cout<< "Total partidas Ganadas "<<totalganadas<<endl;
            cout<<" Tiempo promedio por partida: "<<promedioTiempo<<" segundos"<<endl;
            cout<<" Puntaje promedio por partida: "<<promedioPuntaje<<endl;
            cout<<" Lineas eliminadas total:<<"<<totalinease<<endl;
        }
    }else {
        cout<< "Error al abrir el archivo"<<endl;
    }
}
void jugartetriscentro(char tablero[Filas][Columnas]) {
    inicializar_tablero(tablero);
    Figura figura_actual= estableceraleatoriofigura();
    int pos_x = (Columnas-figura_actual.ancho)/2;
    int pos_y =0;
    int tiempocaida=0;
    int intervalocaida=50;
    int tiempo_inicio=time(nullptr);
    int lineaseliminadas=0;
    int puntaje=0;

    while (true) {
        system("cls");
        mostrartableroconfig(tablero,figura_actual,pos_x,pos_y);

        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'a': // Izquierda
                    if (!hay_colision(tablero, figura_actual, pos_x - 1, pos_y, figura_actual.rotacion_actual)) {
                        pos_x--;
                    }
                    break;
                case 'd': // Derecha
                    if (!hay_colision(tablero, figura_actual, pos_x + 1, pos_y, figura_actual.rotacion_actual)) {
                        pos_x++;
                    }
                    break;
                case 'w': { // Rotar
                    int nueva_rotacion = (figura_actual.rotacion_actual + 1) % figura_actual.rotaciones;
                    if (!hay_colision(tablero, figura_actual, pos_x, pos_y, nueva_rotacion)) {
                        figura_actual.rotacion_actual = nueva_rotacion;
                        calcular_dimensiones(figura_actual);
                    }
                    break;
                }
                case 's': // Acelerar caída
                    if (!hay_colision(tablero, figura_actual, pos_x, pos_y + 1, figura_actual.rotacion_actual)) {
                        pos_y++;
                    }
                    break;
            }
        }
        // caida automatica
        if (tiempocaida >= intervalocaida) {
            if (!hay_colision(tablero,figura_actual,pos_x,pos_y+1,figura_actual.rotacion_actual)) {
                pos_y++;
            } else {
                fijarfigura(tablero,figura_actual,pos_x,pos_y);
                eliminarfilascompletas(tablero);
                figura_actual=estableceraleatoriofigura();
                pos_x = (Columnas-figura_actual.ancho)/2;
                pos_y = 0;
                if (hay_colision(tablero,figura_actual,pos_x,pos_y,figura_actual.rotacion_actual)) {
                    cout<<"Juego terminado !!"<<endl;
                    int tiempojugado= time(nullptr)- tiempo_inicio;
                    bool ganada;
                    if (lineaseliminadas>=10) {
                        ganada=true;
                    }
                    EstadisticasPartida estadisticas= { ganada,tiempojugado,puntaje,lineaseliminadas};
                    GuardarEstadisticas(estadisticas,"Estadisticas.txt");
                    break;
                }
            }
            tiempocaida=0;
        }else {
            tiempocaida++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
int main() {
    srand(time(nullptr));

    cout << "Bienvenido a jugar tetris" << endl;
    cout << endl;

    int opcion = mostrarmenu();

    if (opcion == 4) {
        return 0;
    }

    char tablero[Filas][Columnas];
    inicializar_tablero(tablero);

    if (opcion == 1) {
        cout << "  MODO JUEGO   " << endl;
        jugartetriscentro(tablero);
    } else if (opcion == 2) {
        demo_transposiciones();

    } else if (opcion == 3) {
        cout << " Estadisticas: ";
        generarestadisticas("estadisticas.txt");
    }

    cout << "   Presiona Enter para salir  " ;
    cin.ignore();
    cin.get();

    return 0;
}
