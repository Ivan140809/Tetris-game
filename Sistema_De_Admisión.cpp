#include <fstream>    // Biblioteca para trabajar con archivos (lectura y escritura)
#include <string>     // Biblioteca para manejar cadenas de texto (strings)
#include <cstdlib>    // Biblioteca para funciones generales como exit()
#include <cstring>    // Biblioteca para manipulación de cadenas estilo C (strcpy, strlen)
#include <ctime>      // Biblioteca para manejar tiempo (no se usa en este código)
#include <vector>     // Biblioteca para usar vectores dinámicos
#include <sstream>    // Biblioteca para trabajar con streams de strings
#include <iomanip>    // Biblioteca para manipuladores de formato como setw, setprecision
#include <cmath>      // Biblioteca para funciones matemáticas como sqrt, pow
#include <algorithm>  // Biblioteca para algoritmos como sort, minmax_element
#include <numeric>    // Biblioteca para funciones numéricas como accumulate
#include <iostream>   // Biblioteca para entrada/salida estándar (cin, cout)

using namespace std;

// Estructura para almacenar datos de estudiantes en formato binario (no se usa aqui, pero está definida)
struct Student {
    int serialNo;         // Número de serie del estudiante
    float greScore;       // Puntaje GRE
    float toeflScore;     // Puntaje TOEFL
    int universityRating; // Calificación de la universidad
    float sop;            // Calidad del Statement of Purpose
    float lor;            // Calidad de la carta de recomendación
    float cgpa;           // Promedio académico (GPA)
    int research;         // Indica si tiene experiencia en investigación (0 o 1)
    float chanceOfAdmit;  // Probabilidad de admisión
};

// Estructura para representar una matriz dinámica de datos CSV
struct CsvMatriz {
    char*** filas;           // Arreglo 3D: [fila][columna][caracteres de la cadena]
    int numeroFilas;         // Cantidad de filas actualmente ocupadas
    int numeroColumnas;      // Cantidad de columnas actualmente ocupadas
    int maximoFilas;         // Capacidad máxima de filas antes de redimensionar
    int maximoColumnas;      // Capacidad máxima de columnas antes de redimensionar
};

// Estructura para almacenar estadísticas de una columna numérica
struct EstadisticasColumna {
    string nombre;      // Nombre de la columna (tomado del encabezado del CSV)
    double media;       // Promedio aritmético de los valores
    double mediana;     // Valor central de los datos ordenados
    double desviacion;  // Desviacion estándar (dispersión de los datos)
    double minimo;      // Valor más pequeño de la columna
    double maximo;      // Valor más grande de la columna
    double rango;       // Diferencia entre máximo y mínimo
};

// Declaración de funciones (prototipos) para usarlas más adelante
CsvMatriz* crearMatriz(int filas, int columnas);
void redimensionarMatriz(CsvMatriz* matriz, int nuevasFilas, int nuevasColumnas);
void liberarMemoriaCsvMatriz(CsvMatriz* matriz);
CsvMatriz* leerCSV(const string& nombreArchivo);
bool esNumerico(const string& valor);
void mostrarMenu();
void mostrarInformacionGeneral(const CsvMatriz* matriz);
void mostrarCabecera(const CsvMatriz* matriz, int n = 5);
vector<EstadisticasColumna> generarEstadisticas(const CsvMatriz* matriz);
void enviarEstadisticasTxt(const vector<EstadisticasColumna>& estadisticas);
double calcularCorrelacion(const vector<double>& x, const vector<double>& y);
void mostrarCorrelaciones(const CsvMatriz* matriz);
void procesarYGuardarBinario(const CsvMatriz* matriz);

/**
 * Crea una matriz dinámica para almacenar datos CSV con una capacidad inicial dada
 * @param filasIniciales Número de filas iniciales a reservar
 * @param columnasIniciales Número de columnas iniciales a reservar
 * @return Puntero a la nueva matriz creada
 */
CsvMatriz* crearMatriz(int filasIniciales, int columnasIniciales) {
    CsvMatriz* matriz = new CsvMatriz; // Reserva memoria para la estructura CsvMatriz
    matriz->numeroFilas = 0;          // Inicializa el número de filas ocupadas en 0
    matriz->numeroColumnas = 0;       // Inicializa el número de columnas ocupadas en 0
    matriz->maximoFilas = filasIniciales;    // Establece la capacidad máxima inicial de filas
    matriz->maximoColumnas = columnasIniciales; // Establece la capacidad máxima inicial de columnas

    // Reserva memoria para un arreglo 3D: filas x columnas x punteros a cadenas
    matriz->filas = new char**[filasIniciales]; // Arreglo de punteros a filas
    for(int i = 0; i < filasIniciales; i++) {
        matriz->filas[i] = new char*[columnasIniciales]; // Arreglo de punteros a columnas por fila
        for(int j = 0; j < columnasIniciales; ++j) {
            matriz->filas[i][j] = nullptr; // Inicializa cada celda como vacía (sin datos)
        }
    }
    return matriz; // Devuelve el puntero a la matriz creada
}

/**
 * Redimensiona la matriz si se necesita más espacio para filas o columnas
 * @param matriz Puntero a la matriz que se va a redimensionar
 * @param nuevasFilas Nueva capacidad deseada de filas
 * @param nuevasColumnas Nueva capacidad deseada de columnas
 */
void redimensionarMatriz(CsvMatriz* matriz, int nuevasFilas, int nuevasColumnas) {
    // Si se necesitan más filas que la capacidad actual
    if(nuevasFilas > matriz->maximoFilas) {
        char*** nuevasFilasPtr = new char**[nuevasFilas]; // Nuevo arreglo para más filas
        for(int i = 0; i < nuevasFilas; i++) {
            nuevasFilasPtr[i] = new char*[matriz->maximoColumnas]; // Reserva columnas por fila
            if(i < matriz->maximoFilas) {
                // Copia datos existentes de las filas antiguas
                for(int j = 0; j < matriz->maximoColumnas; ++j) {
                    nuevasFilasPtr[i][j] = matriz->filas[i][j]; // Transfiere puntero a cadena de caracteres
                }
                delete[] matriz->filas[i]; // Libera memoria de la fila antigua
            } else {
                // Inicializa nuevas filas vacías
                for(int j = 0; j < matriz->maximoColumnas; j++) {
                    nuevasFilasPtr[i][j] = nullptr; // Nuevas celdas vacias
                }
            }
        }
        delete[] matriz->filas; // Libera el arreglo antiguo de punteros a filas
        matriz->filas = nuevasFilasPtr; // Actualiza el puntero a las nuevas filas
        matriz->maximoFilas = nuevasFilas; // Actualiza la capacidad maxima de filas
    }

    // Si se necesitan más columnas que la capacidad actual
    if(nuevasColumnas > matriz->maximoColumnas) {
        for(int i = 0; i < matriz->maximoFilas; i++) {
            char** nuevasColumnasPtr = new char*[nuevasColumnas]; // Nuevo arreglo para más columnas
            for(int j = 0; j < nuevasColumnas; ++j) {
                if(j < matriz->maximoColumnas) {
                    nuevasColumnasPtr[j] = matriz->filas[i][j]; // Copia datos existentes
                } else {
                    nuevasColumnasPtr[j] = nullptr; // Inicializa nuevas columnas como vacías
                }
            }
            delete[] matriz->filas[i]; // Libera memoria de la fila antigua
            matriz->filas[i] = nuevasColumnasPtr; // Actualiza el puntero a la nueva fila
        }
        matriz->maximoColumnas = nuevasColumnas; // Actualiza la capacidad máxima de columnas
    }
}

/**
 * Libera toda la memoria asignada dinámicamente para la matriz CSV
 * @param matriz Puntero a la matriz que se va a liberar
 */
void liberarMemoriaCsvMatriz(CsvMatriz* matriz) {
    if(!matriz)
        return; // Si el puntero es nulo, no hay nada que liberar

    // Libera memoria de cada celda, fila y la estructura completa
    for(int i = 0; i < matriz->maximoFilas; ++i) {
        for(int j = 0; j < matriz->maximoColumnas; ++j) {
            delete[] matriz->filas[i][j]; // Libera la cadena de caracteres en cada celda
        }
        delete[] matriz->filas[i]; // Libera el arreglo de punteros a columnas de la fila
    }
    delete[] matriz->filas; // Libera el arreglo de punteros a filas
    delete matriz; // Libera la estructura CsvMatriz
}

/**
 * Lee un archivo CSV y carga sus datos en una matriz dinámica
 * @param nombreArchivo Ruta del archivo CSV a leer
 * @return Puntero a la matriz con los datos cargados, o nullptr si hay error
 */
CsvMatriz* leerCSV(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura
    if(!archivo.is_open()) { // Verifica si se pudo abrir el archivo
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl; // Mensaje de error
        return nullptr; // Devuelve nullptr para indicar fallo
    }

    CsvMatriz* matriz = crearMatriz(100, 9); // Crea una matriz con capacidad inicial de 100 filas y 9 columnas
    string linea; // Variable para almacenar cada línea del archivo
    int numFila = 0; // Contador de filas procesadas

    // Lee el archivo línea por línea
    while(getline(archivo, linea)) {
        if(numFila >= matriz->maximoFilas) { // Si se excede la capacidad de filas
            redimensionarMatriz(matriz, matriz->maximoFilas * 2, matriz->maximoColumnas); // Duplica capacidad
        }

        stringstream ss(linea); // Convierte la linea en un stream para separar valores
        string valor; // Variable para cada valor separado por coma
        int numColumna = 0; // Contador de columnas procesadas en la fila actual

        // Separa la línea en valores usando la coma como delimitador
        while(getline(ss, valor, ',')) {
            if(numColumna >= matriz->maximoColumnas) { // Si se excede la capacidad de columnas
                redimensionarMatriz(matriz, matriz->maximoFilas, matriz->maximoColumnas * 2); // Duplica capacidad
            }

            // Reserva memoria para la cadena y copia el valor
            matriz->filas[numFila][numColumna] = new char[valor.size() + 1]; // +1 para el terminador nulo
            strcpy(matriz->filas[numFila][numColumna], valor.c_str()); // Copia la cadena
            ++numColumna; // Incrementa el contador de columnas
        }

        matriz->numeroColumnas = max(matriz->numeroColumnas, numColumna); // Actualiza el número de columnas si es mayor
        ++numFila; // Incrementa el contador de filas
    }

    matriz->numeroFilas = numFila; // Actualiza el número total de filas procesadas
    archivo.close(); // Cierra el archivo
    return matriz; // Devuelve el puntero a la matriz cargada
}

/**
 * Verifica si una cadena representa un valor numérico válido
 * @param valor Cadena a verificar
 * @return true si es numérico, false si no lo es
 */
bool esNumerico(const string& valor) {
    if(valor.empty())
        return false; // Si la cadena está vacia, no es numérica

    char* endPtr = nullptr; // Puntero para rastrear el final de la conversión
    strtod(valor.c_str(), &endPtr); // Intenta convertir la cadena a double
    return (*endPtr == '\0'); // True si toda la cadena se convirtió sin caracteres sobrantes
}

/**
 * Muestra el menú principal con las opciones disponibles para el usuario
 */
void mostrarMenu() {
    cout << " Menu de Análisis " << endl; // Título del menú
    cout << " 1. Mostrar información general" << endl; // Opcion 1
    cout << " 2. Mostrar primeras filas" << endl; // Opcion 2
    cout << " 3. Generar estadísticas descriptivas" << endl; // Opcion 3
    cout << " 4. Mostrar correlaciones" << endl; // Opción 4
    cout << " 0. Salir" << endl; // Opcion para salir
    cout << " Selección: "; // Solicita la entrada del usuario
}

/**
 * Muestra información general del dataset: filas, columnas y encabezados
 * @param matriz Puntero a la matriz con los datos
 */
void mostrarInformacionGeneral(const CsvMatriz* matriz) {
    cout << "  Información General " << endl; // Título de la sección
    cout << "Filas totales: " << matriz->numeroFilas - 1 << " (excluyendo encabezado)" << endl; // Muestra filas de datos
    cout << "Columnas totales: " << matriz->numeroColumnas << endl; // Muestra número de columnas
    cout << "Nombres de columnas:" << endl; // Subtítulo para los encabezados

    if(matriz->numeroFilas > 0) { // Verifica que haya al menos una fila (encabezado)
        for(int j = 0; j < matriz->numeroColumnas; ++j) {
            cout << " - " << matriz->filas[0][j] << endl; // Muestra cada nombre de columna
        }
    }
}

/**
 * Muestra las primeras n filas del dataset, incluyendo el encabezado, con formato alineado
 * @param matriz Puntero a la matriz con los datos
 * @param n Número de filas a mostrar (por defecto 5)
 */
void mostrarCabecera(const CsvMatriz* matriz, int n) {
    cout << "\n=== Primeras " << n << " filas ===" << endl; // Título con el número de filas a mostrar
    int limite = min(n + 1, matriz->numeroFilas); // Calcula cuántas filas mostrar (incluye encabezado)

    for(int i = 0; i < limite; ++i) { // Itera sobre las filas a mostrar
        for(int j = 0; j < matriz->numeroColumnas; ++j) { // Itera sobre las columnas
            // Usa setw(15) para establecer un ancho fijo de 15 caracteres por campo
            // Esto alinea la salida en columnas uniformes, facilitando la lectura
            cout << setw(15) << (matriz->filas[i][j] ? matriz->filas[i][j] : "NULL"); // Muestra dato o nullptr si está vacío
        }
        cout << endl; // Nueva línea después de cada fila
    }
}

/**
 * Calcula estadísticas descriptivas (media, mediana, etc.) para cada columna numérica
 * @param matriz Puntero a la matriz CSV con los datos
 * @return Vector con las estadísticas calculadas para cada columna numerica
 */
vector<EstadisticasColumna> generarEstadisticas(const CsvMatriz* matriz) {
    vector<EstadisticasColumna> estadisticas; // Vector para almacenar las estadísticas de cada columna

    // Itera sobre todas las columnas de la matriz
    for(int j = 0; j < matriz->numeroColumnas; ++j) {
        vector<double> valores; // Vector para almacenar los valores numericos de la columna
        bool esNumerica = true; // Bandera para verificar si toda la columna es numérica

        // Recolecta valores de la columna, excluyendo el encabezado (fila 0)
        for(int i = 1; i < matriz->numeroFilas; ++i) {
            if(!matriz->filas[i][j] || !esNumerico(matriz->filas[i][j])) { // Si el valor no es numérico o está vacío
                esNumerica = false; // Marca la columna como no numérica
                break; // Sale del bucle
            }
            valores.push_back(stod(matriz->filas[i][j])); // Convierte la cadena a double y la agrega al vector
        }

        if(esNumerica && !valores.empty()) { // Si la columna es numérica y tiene datos
            EstadisticasColumna stats; // Estructura para almacenar las estadísticas de esta columna
            stats.nombre = matriz->filas[0][j]; // Asigna el nombre de la columna desde el encabezado

            // Calcula la media: suma todos los valores y divide entre la cantidad
            // accumulate suma todos los elementos del vector desde el inicio hasta el final, comenzando en 0.0
            stats.media = accumulate(valores.begin(), valores.end(), 0.0) / valores.size();

            // Calcula la desviaciOn estándar
            double sumaCuadrados = 0.0; // Variable para acumular la suma de las diferencias al cuadrado
            for(double valor : valores) {
                sumaCuadrados += pow(valor - stats.media, 2); // Suma (valor - media)^2
            }
            stats.desviacion = sqrt(sumaCuadrados / valores.size()); // Raíz cuadrada de la varianza

            // Encuentra el mInimo y máximo usando minmax_element
            // minmax_element devuelve un par de iteradores al menor y mayor valor
            auto [minIter, maxIter] = minmax_element(valores.begin(), valores.end());
            stats.minimo = *minIter; // Obtiene el valor mínimo dereferenciando el iterador
            stats.maximo = *maxIter; // Obtiene el valor máximo dereferenciando el iterador
            stats.rango = stats.maximo - stats.minimo; // Calcula el rango como la diferencia entre max y min

            // Calcula la mediana: valor central de los datos ordenados
            vector<double> valoresOrdenados = valores; // Crea una copia para ordenarla
            sort(valoresOrdenados.begin(), valoresOrdenados.end()); // Ordena los valores de menor a mayor
            size_t n = valoresOrdenados.size(); // Tamaño del vector
            if(n % 2 == 0) { // Si hay un numero par de elementos
                stats.mediana = (valoresOrdenados[n/2 - 1] + valoresOrdenados[n/2]) / 2.0; // Promedia los dos centrales
            } else { // Si hay un número impar de elementos
                stats.mediana = valoresOrdenados[n/2]; // Toma el valor central
            }

            estadisticas.push_back(stats); // Agrega las estadísticas al vector
        }
    }

    return estadisticas; // Devuelve el vector con todas las estadísticas calculadas
}

/**
 * Escribe las estadísticas calculadas en un archivo de texto con formato
 * @param estadisticas Vector con las estadísticas de las columnas numéricas
 */
void enviarEstadisticasTxt(const vector<EstadisticasColumna>& estadisticas) {
    ofstream archivoEstadisticas("transformacion_resultados.txt"); // Abre el archivo para escritura (sobrescribe si existe)
    if(!archivoEstadisticas.is_open()) { // Verifica si se pudo abrir el archivo
        cerr << "Error: No se pudo abrir el archivo transformacion_resultados.txt" << endl; // Mensaje de error
        return; // Sale de la función
    }

    // Itera sobre cada conjunto de estadísticas
    for(const auto& stats : estadisticas) {
        archivoEstadisticas << "Columna: " << stats.nombre << endl; // Escribe el nombre de la columna

        // Usa fixed y setprecision(2) para formatear números con 2 decimales
        // fixed asegura que los números se muestren en notación decimal fija (no científica)
        // setprecision(2) limita la salida a 2 decimales, redondeando si es necesario
        archivoEstadisticas << "  Media: " << fixed << setprecision(2) << stats.media << endl;
        archivoEstadisticas << "  Mediana: " << stats.mediana << endl;
        archivoEstadisticas << "  Desv. Estándar: " << stats.desviacion << endl;
        archivoEstadisticas << "  Mínimo: " << stats.minimo << endl;
        archivoEstadisticas << "  Máximo: " << stats.maximo << endl;
        archivoEstadisticas << "  Rango: " << stats.rango << endl;
        archivoEstadisticas << endl; // Línea en blanco para separar las estadísticas de cada columna
    }

    archivoEstadisticas.close(); // Cierra el archivo
    cout << "\nEstadísticas exportadas a 'transformacion_resultados.txt'" << endl; // Confirma la operación
}

/**
 * Calcula el coeficiente de correlación de Pearson entre dos vectores de datos
 * @param x Primer vector de datos
 * @param y Segundo vector de datos
 * @return Coeficiente de correlación, o 0 si hay error
 */
double calcularCorrelacion(const vector<double>& x, const vector<double>& y) {
    if(x.size() != y.size() || x.empty()) return 0.0; // Verifica que los vectores tengan el mismo tamaño y no estén vacíos

    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0; // Variables para las sumas necesarias
    double sum_x2 = 0.0, sum_y2 = 0.0; // Sumas de cuadrados
    size_t n = x.size(); // Número de elementos

    // Calcula las sumas para la fórmula de Pearson
    for(size_t i = 0; i < n; ++i) {
        sum_x += x[i]; // Suma de valores de x
        sum_y += y[i]; // Suma de valores de y
        sum_xy += x[i] * y[i]; // Suma de productos x*y
        sum_x2 += x[i] * x[i]; // Suma de cuadrados de x
        sum_y2 += y[i] * y[i]; // Suma de cuadrados de y
    }

    // Formula de Pearson: (n * sum_xy - sum_x * sum_y) / sqrt((n * sum_x2 - sum_x^2) * (n * sum_y2 - sum_y^2))
    double numerador = n * sum_xy - sum_x * sum_y; // Numerador de la fórmula
    double denominador = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y)); // Denominador
    return denominador != 0.0 ? numerador / denominador : 0.0; // Devuelve la correlación o 0 si el denominador es 0
}

/**
 * Muestra una matriz de correlación para todas las columnas numéricas
 * @param matriz Puntero a la matriz con los datos
 */
void mostrarCorrelaciones(const CsvMatriz* matriz) {
    cout << "\n=== Matriz de Correlación ===" << endl; // Título de la sección

    vector<vector<double>> datosNumericos; // Vector para almacenar datos numéricos de cada columna
    vector<string> nombresColumnas; // Vector para almacenar nombres de columnas numéricas

    // Recolecta datos de columnas numéricas
    for(int j = 0; j < matriz->numeroColumnas; ++j) {
        vector<double> columna; // Vector para los valores de la columna actual
        bool esNumerica = true; // Bandera para verificar si la columna es numérica

        for(int i = 1; i < matriz->numeroFilas; ++i) { // Excluye el encabezado
            if(!matriz->filas[i][j] || !esNumerico(matriz->filas[i][j])) { // Si no es numérico
                esNumerica = false;
                break;
            }
            columna.push_back(stod(matriz->filas[i][j])); // Convierte a double y agrega
        }

        if(esNumerica) { // Si la columna es numérica
            datosNumericos.push_back(columna); // Agrega los datos al vector
            nombresColumnas.push_back(matriz->filas[0][j]); // Agrega el nombre de la columna
        }
    }

    const int ancho = 12; // Define un ancho fijo de 12 caracteres para alinear la salida
    cout << setw(ancho) << " "; // Espacio inicial para alinear los nombres de columnas
    for(const auto& nombre : nombresColumnas) {
        // Usa setw(ancho) para alinear cada nombre de columna en un campo de 12 caracteres
        // substr(0, ancho-2) trunca el nombre si es demasiado largo
        cout << setw(ancho) << nombre.substr(0, ancho-2);
    }
    cout << endl; // Nueva línea después de los encabezados

    // Muestra la matriz de correlación
    for(size_t i = 0; i < datosNumericos.size(); ++i) {
        // Muestra el nombre de la fila con setw(ancho) para alinearlo
        cout << setw(ancho) << nombresColumnas[i].substr(0, ancho-2);
        for(size_t j = 0; j < datosNumericos.size(); ++j) {
            double correlacion = calcularCorrelacion(datosNumericos[i], datosNumericos[j]); // Calcula la correlación
            // Usa setw(ancho) para alinear, fixed para notación decimal, y setprecision(3) para 3 decimales
            cout << setw(ancho) << fixed << setprecision(3) << correlacion;
        }
        cout << endl; // Nueva línea después de cada fila
    }
}

/**
 * Guarda los datos de la matriz en un archivo binario y valida la operación
 * @param matriz Puntero a la matriz con los datos
 */
void procesarYGuardarBinario(const CsvMatriz* matriz) {
    string archivoSalida = "data/Admission_Predict_new.bin"; // Ruta del archivo binario

    ofstream archivo(archivoSalida, ios::binary); // Abre el archivo en modo binario para escritura
    if(!archivo) { // Verifica si se pudo abrir
        cerr << "Error al crear archivo binario: " << archivoSalida << endl;
        return;
    }

    // Escribe las dimensiones de la matriz en el archivo
    archivo.write(reinterpret_cast<const char*>(&matriz->numeroFilas), sizeof(int)); // Número de filas
    archivo.write(reinterpret_cast<const char*>(&matriz->numeroColumnas), sizeof(int)); // Número de columnas

    // Escribe los datos de la matriz
    for(int i = 0; i < matriz->numeroFilas; i++) {
        for(int j = 0; j < matriz->numeroColumnas; j++) {
            if(matriz->filas[i][j]) { // Si la celda tiene datos
                size_t longitud = strlen(matriz->filas[i][j]); // Calcula la longitud de la cadena
                archivo.write(reinterpret_cast<const char*>(&longitud), sizeof(size_t)); // Escribe la longitud
                archivo.write(matriz->filas[i][j], longitud); // Escribe la cadena
            } else { // Si la celda está vacía
                size_t longitud = 0; // Longitud 0 para indicar celda vacía
                archivo.write(reinterpret_cast<const char*>(&longitud), sizeof(size_t)); // Escribe longitud 0
            }
        }
    }

    bool exitoEscritura = archivo.good(); // Verifica si la escritura fue exitosa
    archivo.close(); // Cierra el archivo

    if(exitoEscritura) { // Si la escritura fue exitosa
        cout << "\n=== Procesamiento Automático ===" << endl;
        cout << "Matriz guardada exitosamente en: " << archivoSalida << endl;
        cout << "Filas: " << matriz->numeroFilas << ", Columnas: " << matriz->numeroColumnas << endl;

        // Valida leyendo el archivo binario
        ifstream archivoLectura(archivoSalida, ios::binary); // Abre el archivo en modo binario para lectura
        if(!archivoLectura) {
            cerr << "Error al abrir archivo binario para validación" << endl;
            return;
        }

        int filasLeidas, columnasLeidas; // Variables para las dimensiones leídas
        archivoLectura.read(reinterpret_cast<char*>(&filasLeidas), sizeof(int)); // Lee número de filas
        archivoLectura.read(reinterpret_cast<char*>(&columnasLeidas), sizeof(int)); // Lee número de columnas

        cout << "\n=== Validación de Archivo Binario ===" << endl;
        cout << "Dimensiones leídas: " << filasLeidas << " filas, " << columnasLeidas << " columnas" << endl;

        if(filasLeidas == matriz->numeroFilas && columnasLeidas == matriz->numeroColumnas) { // Verifica dimensiones
            cout << "Validación exitosa: las dimensiones coinciden" << endl;

            // Muestra los primeros 5 registros
            cout << "\nPrimeros 5 registros:" << endl;

            vector<string> encabezados; // Vector para almacenar los encabezados
            for(int j = 0; j < columnasLeidas; j++) { // Lee los encabezados (primera fila)
                size_t longitud;
                archivoLectura.read(reinterpret_cast<char*>(&longitud), sizeof(size_t)); // Lee la longitud
                if(longitud > 0) { // Si hay datos
                    char* buffer = new char[longitud + 1]; // Reserva memoria para la cadena
                    archivoLectura.read(buffer, longitud); // Lee la cadena
                    buffer[longitud] = '\0'; // Agrega terminador nulo
                    encabezados.push_back(buffer); // Agrega al vector
                    delete[] buffer; // Libera memoria
                } else {
                    encabezados.push_back("NULL"); // Agrega "NULL" si está vacío
                }
            }

            cout << "Encabezados: "; // Muestra los encabezados
            for(const auto& header : encabezados) {
                cout << header << " | "; // Separa con barras
            }
            cout << endl;

            // Muestra 5 registros de datos
            for(int i = 1; i <= min(5, filasLeidas - 1); i++) {
                cout << "Registro " << i << ": ";
                for(int j = 0; j < columnasLeidas; j++) {
                    size_t longitud;
                    archivoLectura.read(reinterpret_cast<char*>(&longitud), sizeof(size_t)); // Lee longitud
                    if(longitud > 0) {
                        char* buffer = new char[longitud + 1]; // Reserva memoria
                        archivoLectura.read(buffer, longitud); // Lee la cadena
                        buffer[longitud] = '\0'; // Termina la cadena
                        cout << buffer << " | "; // Muestra el valor
                        delete[] buffer; // Libera memoria
                    } else {
                        cout << "NULL | "; // Muestra "NULL" si está vacío
                    }
                }
                cout << endl; // Nueva línea después de cada registro
            }
        } else {
            cout << "Error: las dimensiones no coinciden" << endl; // Mensaje si falla la validación
        }
        archivoLectura.close(); // Cierra el archivo de lectura
    } else {
        cerr << "Error al guardar la matriz en binario" << endl; // Mensaje si falla la escritura
    }
}

/**
 * Función principal: carga los datos, ofrece un menú interactivo y libera memoria
 */
int main() {
    string rutaArchivo = "C:\\Users\\ivans\\Downloads\\Admission_Predict.csv"; // Ruta del archivo CSV

    cout << "Cargando datos desde: " << rutaArchivo << endl; // Mensaje inicial
    CsvMatriz* matriz = leerCSV(rutaArchivo); // Carga los datos en una matriz

    if(!matriz) { // Verifica si la carga fue exitosa
        cerr << "Error al cargar el archivo CSV" << endl;
        return 1; // Sale con código de error
    }

    cout << "Datos cargados correctamente." << endl; // Confirma carga exitosa
    procesarYGuardarBinario(matriz); // Procesa y guarda en binario

    int opcion; // Variable para la selección del usuario
    do {
        mostrarMenu(); // Muestra el menú
        cin >> opcion; // Lee la opción del usuario

        switch(opcion) { // Evalúa la opcion seleccionada
            case 1:
                mostrarInformacionGeneral(matriz); // Muestra información general
                break;
            case 2:
                mostrarCabecera(matriz); // Muestra las primeras filas
                break;
            case 3: {
                vector<EstadisticasColumna> stats = generarEstadisticas(matriz); // Calcula estadísticas
                // Muestra las estadísticas en la consola
                for(const auto& s : stats) {
                    cout << "\nColumna: " << s.nombre << "\n";
                    // Usa fixed y setprecision(2) para mostrar con 2 decimales
                    cout << "  Media: " << fixed << setprecision(2) << s.media << "\n";
                    cout << "  Mediana: " << s.mediana << "\n";
                    cout << "  Desv. Estándar: " << s.desviacion << "\n";
                    cout << "  Minimo: " << s.minimo << "\n";
                    cout << "  Máximo: " << s.maximo << "\n";
                    cout << "  Rango: " << s.rango << endl;
                }
                enviarEstadisticasTxt(stats); // Exporta las estadísticas a un archivo
                break;
            }
            case 4:
                mostrarCorrelaciones(matriz); // Muestra la matriz de correlación
                break;
            case 0:
                break; // Sale del bucle
            default:
                cout << "Opcion invalida!" << endl; // Mensaje para opcion no válida
        }
    } while(opcion != 0); // Repite hasta que el usuario seleccione 0

    liberarMemoriaCsvMatriz(matriz); // Libera toda la memoria asignada
    return 0; // Termina el programa exitosamente
