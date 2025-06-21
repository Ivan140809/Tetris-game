include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

struct usuario {
    string nombre;
    string apellido;
    string genero;
    string correo;
    int cumpleanos;
    bool infopublica;
    string contrasena;
    char rol;
    bool visible;
    bool activo;
};

struct pelicula {
    int codigo;
    string nombre;
    string genero;
    string resumen;
};


int contarUsuariosRegistrados() {
    int contador = 0;
    string linea;
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            contador++;
        }
        archivo.close();
    }
    return contador;
}

bool esMayorEdad(int cumpleanos) {
    int anioActual = 2024;
    int anioNacimiento = cumpleanos / 10000;
    int edad = anioActual - anioNacimiento;

    int mesDiaActual = 202411;
    int mesDiaNacimiento = cumpleanos % 10000;
    if (mesDiaActual < mesDiaNacimiento) {
        edad--;
    }
    return edad >= 18;
}

bool correoExiste(string correo) {
    ifstream archivo("usuarios.txt");
    string linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream linestream(linea);
            string nombre, apellido, genero, correoExistente;
            getline(linestream, nombre, ',');
            getline(linestream, apellido, ',');
            getline(linestream, genero, ',');
            getline(linestream, correoExistente, ',');
            if (correoExistente == correo) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
    }
    return false;
}

void mostrarPreMenu() {
    cout << "Bienvenido a instafilm!" << endl;
    cout << "Seleccione una opcion:" << endl;
    cout << " 1. Registrarse" << endl;
    cout << " 2. Iniciar sesion" << endl;
    cout << " 3. Salir del sistema" << endl;
}

void mostrarMenuPrincipal() {
    cout << "Hola Panita, Bienvenido a instafilm!" << endl;
    cout << "Seleccione una opcion:" << endl;
    cout << " 1. Opciones de Panita mayor (administrador)" << endl;
    cout << " 2. Opciones de perfil" << endl;
    cout << " 3. Opciones de Panitas amigos" << endl;
    cout << " 4. Peliculas" << endl;
    cout << " 0. Cerrar sesion y volver a registro panita" << endl;
}


void mostrarMenuAsignarAdministradores() {
    cout << "***Asignar Panitas mayores (Administradores)*** ."<<endl;
    cout << "Bueno Panita mayor tienes 3 opciones para asignar panitas mayores"<<endl;
    cout << "1. Buscar por correo"<<endl;
    cout << "2. Asignar administradores"<<endl;
    cout << "3. Quitar asignacion de administrador"<<endl;
    cout << "0. Volver al menu administrador"<<endl;
}

void mostrarMenuAdministrarPeliculas() {
    cout << "***Administrar peliculas de instafilm!!!*** ."<<endl;
    cout << "Para administrar las peliculas panita mayor tienes 3 opciones:"<<endl;
    cout << "1. Crea una pelicula(Recuerda que cada pelicula tiene su codigo, nombre, resumen y genero)"<<endl;
    cout << "2. Modifica un aspecto de una pelicula!"<<endl;
    cout << "3. Elimina una pelicula (con su codigo)"<<endl;
}

void registrarUsuario() {
    if (contarUsuariosRegistrados() >= 50) {
        cout << "No se pueden registrar más de 50 usuarios. Registro fallido."<<endl;
    }

    usuario nuevoUsuario;
    cout << " *** Registro de Panita *** "<<endl;
    cout << "Ingrese su nombre(Primera letra mayuscula porfavor): "<<endl;
    cin >> nuevoUsuario.nombre;
    cout << "Ingrese su apellido(Primera letra mayuscula porfavor): "<<endl;
    cin >> nuevoUsuario.apellido;
    cout << "Ingrese su genero (M/F): "<<endl;
    cin >> nuevoUsuario.genero;
    cout << "Ingrese su correo: "<<endl;
    cin >> nuevoUsuario.correo;
    if (correoExiste(nuevoUsuario.correo)) {
        cout << " El correo ingresado ya esta registrado. Intente con otro correo."<<endl;
    }
    cout << "Ingrese su cumpleanos (YYYYMMDD): "<<endl;
    cin >> nuevoUsuario.cumpleanos;
    if (!esMayorEdad(nuevoUsuario.cumpleanos)) {
        cout << "Lo sentimos, solo los mayores de 18 años pueden registrarse."<<endl;
    }
    cout << "Desea que su informacion sea publica? (1: Si, 0: No): "<<endl;
    cin >> nuevoUsuario.infopublica;
    cout << "Ingrese su contrasena: "<<endl;
    cin >> nuevoUsuario.contrasena;

    if (contarUsuariosRegistrados() == 0 || contarUsuariosRegistrados() == 4) {// es un 4 para hacer pruebas con el usuario 4 pero el original es el 0
        nuevoUsuario.rol = 'A';
    } else {
        nuevoUsuario.rol = 'U';
    }

    cout << "Desea que su perfil sea visible para otros usuarios? (1: Si, 0: No): "<<endl;
    cin >> nuevoUsuario.visible;

    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevoUsuario.nombre << "," << nuevoUsuario.apellido << ","
                << nuevoUsuario.genero << "," << nuevoUsuario.correo << ","
                << nuevoUsuario.cumpleanos << "," << nuevoUsuario.infopublica << ","
                << nuevoUsuario.contrasena << "," << nuevoUsuario.rol << ","
                << nuevoUsuario.visible << endl;
        archivo.close();
        cout << "Registro exitoso, Panita!"<<endl;
    } else {
        cout << "Error al registrar al Panita."<<endl;
    }
}

void buscarUsuarioPorCorreo(string correo) {
    usuario usuarioArchivo;
    ifstream archivo("usuarios.txt");
    string linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream linestream(linea);
            getline(linestream, usuarioArchivo.nombre, ',');
            getline(linestream, usuarioArchivo.apellido, ',');
            getline(linestream, usuarioArchivo.genero, ',');
            getline(linestream, usuarioArchivo.correo, ',');
            linestream >> usuarioArchivo.cumpleanos;
            linestream.ignore();
            linestream >> usuarioArchivo.infopublica;
            linestream.ignore();
            getline(linestream, usuarioArchivo.contrasena, ',');
            linestream >> usuarioArchivo.rol;
            linestream.ignore();
            linestream >> usuarioArchivo.visible;

            if(usuarioArchivo.correo == correo) {
                cout << "Nombre: " << usuarioArchivo.nombre << endl;
                cout << "Apellido: " << usuarioArchivo.apellido << endl;
                cout << "Genero: " << usuarioArchivo.genero << endl;
                cout << "Cumpleanos: " << usuarioArchivo.cumpleanos << endl;
                cout << "Correo: " << usuarioArchivo.correo << endl;
                cout << "Rol: " << usuarioArchivo.rol << endl;
                break;
            }
        }
        archivo.close();
    }
}

void mostrarUsuariosOrdenados() {
    ifstream archivo("usuarios.txt");
    string usuarios[50];
    int numUsuarios = 0;

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea) && numUsuarios < 50) {
            usuarios[numUsuarios++] = linea;
        }
        archivo.close();
    }

    for(int i = 0; i < numUsuarios; i++) {
        for(int j = 0; j < numUsuarios-i-1; j++) {
            stringstream linestream1(usuarios[j]);
            stringstream linestream2(usuarios[j + 1]);
            string apellido1, apellido2;
            getline(linestream1, apellido1, ',');
            getline(linestream1, apellido1, ',');
            getline(linestream2, apellido2, ',');
            getline(linestream2, apellido2, ',');

            if(apellido1 > apellido2) {
                string temp = usuarios[j];
                usuarios[j] = usuarios[j + 1];
                usuarios[j + 1] = temp;
            }
        }
    }

    cout << "*** Lista de panitas registrados por apellido!!! "<<endl;
    for(int i = 0; i < numUsuarios; i++) {
        stringstream linestream(usuarios[i]);
        string nombre, apellido;
        getline(linestream, nombre, ',');
        getline(linestream, apellido, ',');
        cout << "Apellido: " << apellido << endl;
    }
}

void crearPelicula() {
    pelicula peliculas[100];
    pelicula nuevaPelicula;
    bool codigoExiste = false;
    string resumenTemp;
    int numPeliculas = 0;

    ifstream contarPeliculas("peliculas.txt");
    if (contarPeliculas.is_open()) {
        string linea;
        while (getline(contarPeliculas, linea)) {
            numPeliculas++;
        }
        contarPeliculas.close();
    }

    if (numPeliculas >= 100) {
        cout << "Lo siento panita, ya llegamos al limite de 100 peliculas!"<<endl;
    }

    cout << "Ingresa el codigo de la pelicula (numero entero de dos digitos 00-99): "<<endl;
    cin >> nuevaPelicula.codigo;

    ifstream verificarCodigo("peliculas.txt");
    string linea;
    if (verificarCodigo.is_open()) {
        while (getline(verificarCodigo, linea)) {
            stringstream linestream(linea);
            pelicula peliculaTemp;
            string codigoTemp;
            getline(linestream, codigoTemp, ',');
            peliculaTemp.codigo = atoi(codigoTemp.c_str());
            if (peliculaTemp.codigo == nuevaPelicula.codigo) {
                codigoExiste = true;
                break;
            }
        }
        verificarCodigo.close();
    }

    if (codigoExiste) {
        cout << "Este codigo ya existe panita, intenta con otro "<<endl;
    }

    cout << "Ingresa el nombre de la pelicula: "<<endl;
    string temp;
    nuevaPelicula.nombre = "";
    cin >> temp;
    nuevaPelicula.nombre = temp;
    while(cin >> temp) {
        nuevaPelicula.nombre += " " + temp;
        if(cin.get() == '\n')
            break;
    }
    cout << "Ingresa el genero de la pelicula: "<<endl;
    cin >>nuevaPelicula.genero;

    cout << "Ingresa el resumen de la pelicula (maximo 100 caracteres): "<<endl;
    cin >> temp;
    nuevaPelicula.resumen = temp;
    while(cin >> temp) {
        nuevaPelicula.resumen += " " + temp;
        if(nuevaPelicula.resumen.length() > 100) {
            cout << "El resumen es muy largo panita! Debe ser menor a 100 caracteres "<<endl;
            nuevaPelicula.resumen = "";
            break;
        }
        if(cin.get() == '\n')
            break;
    }

    ifstream leerPeliculas("peliculas.txt");
    if (leerPeliculas.is_open()) {
        int i = 0;
        while (getline(leerPeliculas, linea)) {
            stringstream linestream(linea);
            string codigoTemp;
            getline(linestream, codigoTemp, ',');
            peliculas[i].codigo = atoi(codigoTemp.c_str());
            getline(linestream, peliculas[i].nombre, ',');
            getline(linestream, peliculas[i].genero, ',');
            getline(linestream, peliculas[i].resumen);
            i++;
        }
        leerPeliculas.close();
        peliculas[numPeliculas] = nuevaPelicula;
        numPeliculas++;
    }

    ofstream archivosalida("peliculas.txt");
    if (archivosalida.is_open()) {
        for(int i = 0; i < numPeliculas; i++) {
            archivosalida << peliculas[i].codigo << ","
                       << peliculas[i].nombre << ","
                       << peliculas[i].genero << ","
                       << peliculas[i].resumen << endl;
        }
        archivosalida.close();
        cout << " Pelicula guardada exitosamente, panita!"<<endl;
    } else {
        cout << "Error al guardar la pelicula, panita "<<endl;
    }
}
void modificarPelicula() {
 pelicula peliculas[100];
 int numPeliculas = 0;
 int codigoBuscar;
 bool peliculaEncontrada = false;

 cout << " *** Peliculas disponibles *** "<<endl;
 ifstream archivoPeliculas("peliculas.txt");
 if (archivoPeliculas.is_open()) {
     string linea;
     while (getline(archivoPeliculas, linea)) {
         stringstream linestream(linea);
         string codigoTemp;
         getline(linestream, codigoTemp, ',');
         peliculas[numPeliculas].codigo = atoi(codigoTemp.c_str());
         getline(linestream, peliculas[numPeliculas].nombre, ',');
         getline(linestream, peliculas[numPeliculas].genero, ',');
         getline(linestream, peliculas[numPeliculas].resumen);

         cout << "Codigo: " << peliculas[numPeliculas].codigo
              << " - Pelicula: " << peliculas[numPeliculas].nombre << endl;
         numPeliculas++;
     }
     archivoPeliculas.close();
 }

 cout << " Ingresa el codigo de la pelicula que deseas modificar: "<<endl;
 cin >> codigoBuscar;

 for(int i = 0; i < numPeliculas; i++) {
     if(peliculas[i].codigo == codigoBuscar) {
         peliculaEncontrada = true;
         cout << " Pelicula encontrada!"<<endl;
         cout << "Que deseas modificar panita?"<<endl;
         cout << "1. Nombre "<<endl;
         cout << "2. Genero "<<endl;
         cout << "3. Resumen "<<endl;

         int opcionModificar;
         cin >> opcionModificar;

         switch(opcionModificar) {
             case 1: {
                 cout << "Ingresa el nuevo nombre: "<<endl;
                 string temp;
                 cin >> temp;
                 peliculas[i].nombre = temp;
                 while(cin >> temp) {
                     peliculas[i].nombre += " " + temp;
                     if(cin.get() == '\n')
                         break;
                 }
                 break;
             }
             case 2: {
                 cout << "Ingresa el nuevo genero: " << endl;
                 cin >> peliculas[i].genero;
                 break;
             }
             case 3: {
                 cout << "Ingresa el nuevo resumen (maximo 100 caracteres): "<<endl;
                 string temp;
                 cin >> temp;
                 peliculas[i].resumen = temp;
                 while(cin >> temp) {
                     peliculas[i].resumen += " " + temp;
                     if(peliculas[i].resumen.length() > 100) {
                         cout << "El resumen es muy largo panita! Debe ser menor a 100 caracteres "<<endl;
                         peliculas[i].resumen = "";
                         break;
                     }
                     if(cin.get() == '\n')
                         break;
                 }
                 break;
             }
             default:
                 cout << "Opcion invalida panita "<<endl;
                 break;
         }

         ofstream archivoSalida("peliculas.txt");
         if (archivoSalida.is_open()) {
             for(int j = 0; j < numPeliculas; j++) {
                 archivoSalida << peliculas[j].codigo << ","
                            << peliculas[j].nombre << ","
                            << peliculas[j].genero << ","
                            << peliculas[j].resumen << endl;
             }
             archivoSalida.close();
             cout << " Pelicula modificada exitosamente, panita "<<endl;
         } else {
             cout << "Error al guardar los cambios, panita "<<endl;
         }
         break;
     }
 }
 if (!peliculaEncontrada) {
     cout << "No se encontro ninguna pelicula con ese codigo, panita"<<endl;
 }
}
    void eliminarPelicula() {
        pelicula peliculas[100];
        int numPeliculas = 0;
        int codigoBuscar;
        bool peliculaEncontrada = false;

        cout << "Peliculas disponibles: "<<endl;
        ifstream archivoPeliculas("peliculas.txt");
        if (archivoPeliculas.is_open()) {
            string linea;
            while (getline(archivoPeliculas, linea)) {
                stringstream linestream(linea);
                string codigoTemp;
                getline(linestream, codigoTemp, ',');
                peliculas[numPeliculas].codigo = atoi(codigoTemp.c_str());
                getline(linestream, peliculas[numPeliculas].nombre, ',');
                getline(linestream, peliculas[numPeliculas].genero, ',');
                getline(linestream, peliculas[numPeliculas].resumen);
                numPeliculas++;
            }
            archivoPeliculas.close();
        }

        cout << " Ingresa el codigo de la pelicula que deseas eliminar: "<<endl;
        cin >> codigoBuscar;

        ofstream archivoSalida("peliculas.txt");
        if (archivoSalida.is_open()) {
            for(int i = 0; i < numPeliculas; i++) {
                if(peliculas[i].codigo != codigoBuscar) {
                    archivoSalida << peliculas[i].codigo << ","
                               << peliculas[i].nombre << ","
                               << peliculas[i].genero << ","
                               << peliculas[i].resumen << endl;
                } else {
                    peliculaEncontrada = true;
                    cout << "La pelicula " << peliculas[i].nombre << " ha sido eliminada, panita!";
                }
            }
            archivoSalida.close();

            if (!peliculaEncontrada) {
                cout << "No se encontro ninguna pelicula con ese codigo, panita"<<endl;
            }
        } else {
            cout << "Error al actualizar el archivo, panita"<<endl;
        }
    }
void asignarAdministrador(string correo) {
    ifstream archivoLectura("usuarios.txt");
    string usuarios[50];
    int numUsuarios = 0;
    bool usuarioEncontrado = false;

    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            if (numUsuarios < 50) {
                usuarios[numUsuarios] = linea;
                numUsuarios++;
            }
        }
        archivoLectura.close();
    }

    ofstream archivoEscritura("usuarios.txt");
    if (archivoEscritura.is_open()) {
        for(int i = 0; i < numUsuarios; i++) {
            stringstream linestream(usuarios[i]);
            usuario usuarioTemp;
            string cumpleanosTemp, infopublicaTemp, visibleTemp;

            getline(linestream, usuarioTemp.nombre, ',');
            getline(linestream, usuarioTemp.apellido, ',');
            getline(linestream, usuarioTemp.genero, ',');
            getline(linestream, usuarioTemp.correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarioTemp.contrasena, ',');
            linestream >> usuarioTemp.rol;
            getline(linestream, visibleTemp);

            usuarioTemp.cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarioTemp.infopublica = atoi(infopublicaTemp.c_str());
            usuarioTemp.visible = atoi(visibleTemp.c_str());

            if(usuarioTemp.correo == correo) {
                usuarioTemp.rol = 'A';
                usuarioEncontrado = true;
                cout << " El panita " << usuarioTemp.nombre << " ahora es administrador "<<endl;
            }

            archivoEscritura << usuarioTemp.nombre << ","
                            << usuarioTemp.apellido << ","
                            << usuarioTemp.genero << ","
                            << usuarioTemp.correo << ","
                            << usuarioTemp.cumpleanos << ","
                            << usuarioTemp.infopublica << ","
                            << usuarioTemp.contrasena << ","
                            << usuarioTemp.rol << ","
                            << usuarioTemp.visible << endl;
        }
        archivoEscritura.close();

        if (!usuarioEncontrado) {
            cout << "No se encontró ningún panita con ese correo "<<endl;
        }
    }
}

void quitarAdministrador(string correo) {
    ifstream archivoLectura("usuarios.txt");
    string usuarios[50];
    int numUsuarios = 0;
    bool usuarioEncontrado = false;
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            if (numUsuarios < 50) {
                usuarios[numUsuarios] = linea;
                numUsuarios++;
            }
        }
        archivoLectura.close();
    }

    ofstream archivoEscritura("usuarios.txt");
    if (archivoEscritura.is_open()) {
        for(int i = 0; i < numUsuarios; i++) {
            stringstream linestream(usuarios[i]);
            usuario usuarioTemp;
            string cumpleanosTemp, infopublicaTemp, visibleTemp;

            getline(linestream, usuarioTemp.nombre, ',');
            getline(linestream, usuarioTemp.apellido, ',');
            getline(linestream, usuarioTemp.genero, ',');
            getline(linestream, usuarioTemp.correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarioTemp.contrasena, ',');
            linestream >> usuarioTemp.rol;
            getline(linestream, visibleTemp);

            usuarioTemp.cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarioTemp.infopublica = atoi(infopublicaTemp.c_str());
            usuarioTemp.visible = atoi(visibleTemp.c_str());

            if(usuarioTemp.correo == correo && usuarioTemp.rol == 'A') {
                usuarioTemp.rol = 'U';
                usuarioEncontrado = true;
                cout << "El panita " << usuarioTemp.nombre << " ya no es administrador "<<endl;
            }

            archivoEscritura << usuarioTemp.nombre << ","
                            << usuarioTemp.apellido << ","
                            << usuarioTemp.genero << ","
                            << usuarioTemp.correo << ","
                            << usuarioTemp.cumpleanos << ","
                            << usuarioTemp.infopublica << ","
                            << usuarioTemp.contrasena << ","
                            << usuarioTemp.rol << ","
                            << usuarioTemp.visible << endl;
        }
        archivoEscritura.close();

        if (!usuarioEncontrado) {
            cout << "No se encontró ningún panita administrador con ese correo "<<endl;
        }
    }
}
void grabarArchivo() {
    cout << " *** Grabando informacion de InstaFilm ***"<<endl;;
    ifstream archivoUsuarios("usuarios.txt");
    ofstream backupUsuarios("backup_usuarios.txt");
    if (archivoUsuarios.is_open() && backupUsuarios.is_open()) {
        string linea;
        while (getline(archivoUsuarios, linea)) {
            backupUsuarios << linea << endl;
        }
        archivoUsuarios.close();
        backupUsuarios.close();
        cout << "Usuarios guardados exitosamente "<<endl;
    } else {
        cout << "Error al guardar usuarios "<<endl;
    }

    ifstream archivoPeliculas("peliculas.txt");
    ofstream backupPeliculas("backup_peliculas.txt");

    if (archivoPeliculas.is_open() && backupPeliculas.is_open()) {
        string linea;
        while (getline(archivoPeliculas, linea)) {
            backupPeliculas << linea << endl;
        }
        archivoPeliculas.close();
        backupPeliculas.close();
        cout << "Peliculas guardadas exitosamente! "<<endl;
    } else {
        cout << "Error al guardar peliculas "<<endl;
    }
}
void cargarInformacion() {
    cout << "*** Cargando informacion de InstaFilm ***"<<endl;
    ifstream backupUsuarios("backup_usuarios.txt");
    ofstream archivoUsuarios("usuarios.txt");
    if (backupUsuarios.is_open() && archivoUsuarios.is_open()) {
        string linea;
        while (getline(backupUsuarios, linea)) {
            archivoUsuarios << linea << endl;
        }
        backupUsuarios.close();
        archivoUsuarios.close();
        cout << "Usuarios cargados exitosamente!"<<endl;
    } else {
        cout << "Error al cargar usuarios "<<endl;
    }
    ifstream backupPeliculas("backup_peliculas.txt");
    ofstream archivoPeliculas("peliculas.txt");

    if (backupPeliculas.is_open() && archivoPeliculas.is_open()) {
        string linea;
        while (getline(backupPeliculas, linea)) {
            archivoPeliculas << linea << endl;
        }
        backupPeliculas.close();
        archivoPeliculas.close();
        cout << "Peliculas cargadas exitosamente! "<<endl;
    } else {
        cout << "Error al cargar peliculas "<<endl;
    }
}

void menuAdministrador() {
    int opcionAdmin;
    do {
        cout << "Ingreso como panita admin exitoso: que desea hacer?" << endl;
        cout << " 1. Asigna Panitas mayores (Administradores)" << endl;
        cout << " 2. Ver los Panitas registrados" << endl;
        cout << " 3. Administra peliculas" << endl;
        cout << " 4. Grabar informacion de Instafilm" << endl;
        cout << " 5. Cargar informacion de Instafilm" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cin >> opcionAdmin;

        switch (opcionAdmin) {
            case 1: {
                mostrarMenuAsignarAdministradores();
                int opcionasignar;
                cin >> opcionasignar;
                string correo;

                switch(opcionasignar) {
                    case 1:
                        cout << "Ingresa el correo del pana que deseas buscar "<<endl;
                    cin >> correo;
                    buscarUsuarioPorCorreo(correo);
                    break;
                    case 2:
                        cout << "Ingresa el correo del pana mayor que deseas asignar "<<endl;
                    cin >> correo;
                    asignarAdministrador(correo);
                    break;
                    case 3:
                        cout << "Ingresa el correo del pana mayor que deseas eliminar "<<endl;
                    cin >> correo;
                    quitarAdministrador(correo);
                    break;
                    default:
                        cout << "Error no se pudo leer tu opcion panita"<<endl;
                }
                break;
            }
            case 2:
                cout << "***Ver los Panitas registrados*** "<<endl;
            mostrarUsuariosOrdenados();
            break;
            case 3: {
                mostrarMenuAdministrarPeliculas();
                int opcionpelicula;
                cin >> opcionpelicula;

                switch(opcionpelicula) {
                    case 1:
                        crearPelicula();
                    break;
                    case 2:
                        cout << "Modifica algun dato de una pelicula"<<endl;
                    modificarPelicula();
                    break;
                    case 3:
                        cout << "Elimina una pelicula"<<endl;
                    eliminarPelicula();
                    break;
                    default: cout<<"Opcion invalida panita"<<endl;
                }
                break;
            }
            case 4:
                cout << "Grabar información de Instafilm ."<<endl;
            grabarArchivo();
            break;
            case 5:
                cout << "Cargar información de Instafilm ."<<endl;
            cargarInformacion();
                break;
            case 0:
                cout << "Volviendo al menu principal..."<<endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente. "<<endl;
        }
    } while (opcionAdmin != 0);
}
void Modificarperfil(string CorreoActual) {
    usuario usuarios[50];
    int numUsuarios=0;
    bool usuarioEncontrado;
    ifstream archivoLectura("usuarios.txt");
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            stringstream linestream(linea);
            string cumpleanosTemp, infopublicaTemp, visibleTemp;

            getline(linestream, usuarios[numUsuarios].nombre, ',');
            getline(linestream, usuarios[numUsuarios].apellido, ',');
            getline(linestream, usuarios[numUsuarios].genero, ',');
            getline(linestream, usuarios[numUsuarios].correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarios[numUsuarios].contrasena, ',');
            linestream >> usuarios[numUsuarios].rol;
            getline(linestream, visibleTemp);

            usuarios[numUsuarios].cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarios[numUsuarios].infopublica = atoi(infopublicaTemp.c_str());
            usuarios[numUsuarios].visible = atoi(visibleTemp.c_str());

            numUsuarios++;
        }
        archivoLectura.close();
    }
    for(int i = 0; i < numUsuarios; i++) {
        if(usuarios[i].correo == CorreoActual) {
            usuarioEncontrado = true;
            int opcion;
            cout << " Que deseas modificar panita? "<<endl;
            cout<<"1. Nombre"<<endl;
            cout<<"2. Apellido"<<endl;
            cout<<"3. Genero"<<endl;
            cout<<"4. Contrasena"<<endl;
            cout<<"5. Informacion publica"<<endl;
            cout<<"6. Perfil visible"<<endl;
            cout<<"0. Volver al menu perfil"<<endl;
            cin >> opcion;

            switch(opcion) {
                case 1:
                    cout << "Ingresa tu nuevo nombre: "<<endl;
                cin >> usuarios[i].nombre;
                break;
                case 2:
                    cout << "Ingresa tu nuevo apellido: "<<endl;
                cin >> usuarios[i].apellido;
                break;
                case 3:
                    cout << "Ingresa tu genero (M/F): "<<endl;
                cin >> usuarios[i].genero;
                break;
                case 4:
                    cout << "Ingresa tu nueva contrasena: "<<endl;
                cin >> usuarios[i].contrasena;
                break;
                case 5:
                    cout << "Deseas que tu informacion sea publica? (1:Si, 0:No): "<<endl;
                cin >> usuarios[i].infopublica;
                break;
                case 6:
                    cout << "Deseas que tu perfil sea visible? (1:Si, 0:No): "<<endl;
                cin >> usuarios[i].visible;
                break;
                case 0:
                    cout << "Volviendo al menu anterior "<<endl;
                return;
                default:
                    cout << "Opcion invalida panita "<<endl;
                return;
            }
            ofstream archivoSalida("usuarios.txt");
            if (archivoSalida.is_open()) {
                for(int j = 0; j < numUsuarios; j++) {
                    archivoSalida << usuarios[j].nombre << ","
                                << usuarios[j].apellido << ","
                                << usuarios[j].genero << ","
                                << usuarios[j].correo << ","
                                << usuarios[j].cumpleanos << ","
                                << usuarios[j].infopublica << ","
                                << usuarios[j].contrasena << ","
                                << usuarios[j].rol << ","
                                << usuarios[j].visible << endl;
                }
                archivoSalida.close();
                cout << " Perfil modificado exitosamente, panita"<<endl;
            } else {
                cout << "Error al guardar los cambios, panita";
            }
            break;
        }
    }

    if (!usuarioEncontrado) {
        cout << "Error: No se encontro tu perfil, panita";
    }
}
void Inactivarperfil(string correoUsuario) {
    usuario usuarios[50];
    int numUsuarios = 0;
    bool usuarioEncontrado = false;

    ifstream archivoLectura("usuarios.txt");
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            stringstream linestream(linea);
            string cumpleanosTemp, infopublicaTemp, visibleTemp, activoTemp;

            getline(linestream, usuarios[numUsuarios].nombre, ',');
            getline(linestream, usuarios[numUsuarios].apellido, ',');
            getline(linestream, usuarios[numUsuarios].genero, ',');
            getline(linestream, usuarios[numUsuarios].correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarios[numUsuarios].contrasena, ',');
            linestream >> usuarios[numUsuarios].rol;
            getline(linestream, visibleTemp, ',');
            getline(linestream, activoTemp);

            usuarios[numUsuarios].cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarios[numUsuarios].infopublica = atoi(infopublicaTemp.c_str());
            usuarios[numUsuarios].visible = atoi(visibleTemp.c_str());
            usuarios[numUsuarios].activo = atoi(activoTemp.c_str());

            numUsuarios++;
        }
        archivoLectura.close();
    }
    for(int i = 0; i < numUsuarios; i++) {
        if(usuarios[i].correo == correoUsuario) {
            usuarioEncontrado = true;

            char confirmar;
            cout << " Estas seguro de inactivar tu perfil panita? (S/N): ";
            cin >> confirmar;

            if(confirmar == 'S' ) {
                usuarios[i].activo = false;
                cout << " Tu perfil ha sido inactivado panita";

                ofstream archivoSalida("usuarios.txt");
                if (archivoSalida.is_open()) {
                    for(int j = 0; j < numUsuarios; j++) {
                        archivoSalida << usuarios[j].nombre << ","
                                    << usuarios[j].apellido << ","
                                    << usuarios[j].genero << ","
                                    << usuarios[j].correo << ","
                                    << usuarios[j].cumpleanos << ","
                                    << usuarios[j].infopublica << ","
                                    << usuarios[j].contrasena << ","
                                    << usuarios[j].rol << ","
                                    << usuarios[j].visible << ","
                                    << usuarios[j].activo << endl;
                    }
                    archivoSalida.close();
                }
            } else {
                cout << "\nOperacion cancelada panita\n";
            }
            break;
        }
    }
    if (!usuarioEncontrado) {
        cout << "Error: No se encontro tu perfil, panita\n";
    }
}
void inactivarPerfil(string correoUsuario) {
    usuario usuarios[50];
    int numUsuarios = 0;
    bool usuarioEncontrado = false;

    ifstream archivoLectura("usuarios.txt");
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            stringstream linestream(linea);
            string cumpleanosTemp, infopublicaTemp, visibleTemp, activoTemp;

            getline(linestream, usuarios[numUsuarios].nombre, ',');
            getline(linestream, usuarios[numUsuarios].apellido, ',');
            getline(linestream, usuarios[numUsuarios].genero, ',');
            getline(linestream, usuarios[numUsuarios].correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarios[numUsuarios].contrasena, ',');
            linestream >> usuarios[numUsuarios].rol;
            getline(linestream, visibleTemp, ',');
            getline(linestream, activoTemp);

            usuarios[numUsuarios].cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarios[numUsuarios].infopublica = atoi(infopublicaTemp.c_str());
            usuarios[numUsuarios].visible = atoi(visibleTemp.c_str());
            usuarios[numUsuarios].activo = atoi(activoTemp.c_str());

            numUsuarios++;
        }
        archivoLectura.close();
    }

    for(int i = 0; i < numUsuarios; i++) {
        if(usuarios[i].correo == correoUsuario) {
            usuarioEncontrado = true;

            char confirmar;
            cout << "\n¿Estas seguro de inactivar tu perfil panita? (S/N): ";
            cin >> confirmar;

            if(confirmar == 'S' || confirmar == 's') {
                usuarios[i].activo = false;
                cout << "\nTu perfil ha sido inactivado panita\n";

                ofstream archivoSalida("usuarios.txt");
                if (archivoSalida.is_open()) {
                    for(int j = 0; j < numUsuarios; j++) {
                        archivoSalida << usuarios[j].nombre << ","
                                    << usuarios[j].apellido << ","
                                    << usuarios[j].genero << ","
                                    << usuarios[j].correo << ","
                                    << usuarios[j].cumpleanos << ","
                                    << usuarios[j].infopublica << ","
                                    << usuarios[j].contrasena << ","
                                    << usuarios[j].rol << ","
                                    << usuarios[j].visible << ","
                                    << usuarios[j].activo << endl;
                    }
                    archivoSalida.close();
                }
            } else {
                cout << "\nOperacion cancelada panita\n";
            }
            break;
        }
    }

    if (!usuarioEncontrado) {
        cout << "Error: No se encontro tu perfil, panita\n";
    }
}

void eliminarPerfil(string correoUsuario) {
    usuario usuarios[50];
    int numUsuarios = 0;
    bool usuarioEncontrado = false;
    bool puedeEliminar = false;

    ifstream archivoLectura("usuarios.txt");
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            stringstream linestream(linea);
            string cumpleanosTemp, infopublicaTemp, visibleTemp, activoTemp;

            getline(linestream, usuarios[numUsuarios].nombre, ',');
            getline(linestream, usuarios[numUsuarios].apellido, ',');
            getline(linestream, usuarios[numUsuarios].genero, ',');
            getline(linestream, usuarios[numUsuarios].correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarios[numUsuarios].contrasena, ',');
            linestream >> usuarios[numUsuarios].rol;
            getline(linestream, visibleTemp, ',');
            getline(linestream, activoTemp);

            usuarios[numUsuarios].cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarios[numUsuarios].infopublica = atoi(infopublicaTemp.c_str());
            usuarios[numUsuarios].visible = atoi(visibleTemp.c_str());
            usuarios[numUsuarios].activo = atoi(activoTemp.c_str());

            if(usuarios[numUsuarios].correo == correoUsuario) {
                usuarioEncontrado = true;
                if(usuarios[numUsuarios].activo==false) {
                    puedeEliminar = true;
                }
            }
            numUsuarios++;
        }
        archivoLectura.close();
    }

    if (!usuarioEncontrado) {
        cout << " No se encontro tu perfil panita ";
        return;
    }

    if (!puedeEliminar) {
        cout << " Solo puedes eliminar tu perfil si esta inactivo panita ";
        return;
    }

    char confirmar;
    cout << " Estas seguro de eliminar tu perfil? Esta accion no se puede deshacer (S/N): ";
    cin >> confirmar;

    if(confirmar == 'S' ) {
        ofstream archivoSalida("usuarios.txt");
        if (archivoSalida.is_open()) {
            for(int i = 0; i < numUsuarios; i++) {
                if(usuarios[i].correo != correoUsuario) {
                    archivoSalida << usuarios[i].nombre << ","
                                << usuarios[i].apellido << ","
                                << usuarios[i].genero << ","
                                << usuarios[i].correo << ","
                                << usuarios[i].cumpleanos << ","
                                << usuarios[i].infopublica << ","
                                << usuarios[i].contrasena << ","
                                << usuarios[i].rol << ","
                                << usuarios[i].visible << ","
                                << usuarios[i].activo << endl;
                }
            }
            archivoSalida.close();
            cout << " Tu perfil ha sido eliminado panita."<<endl;
        }
    } else {
        cout << "Operacion cancelada panita";
    }
}
void mostrarMenuPerfil(string correoUsuario) {
    cout << "Que cambios deseas hacer en tu perfil Panita?" << endl;
    cout << " 1. Modificar perfil" << endl;
    cout << " 2. Inactivar perfil" << endl;
    cout << " 3. Eliminar informacion de tu perfil" << endl;
    int opcionmenuperfil;
    cin>>opcionmenuperfil;
    switch(opcionmenuperfil) {
        case 1: cout<<"Modificar tu perfil:  "<<endl;
        Modificarperfil(correoUsuario);
        break;
        case 2: cout<<"Inactivar perfil: "<<endl;
        Inactivarperfil(correoUsuario);
        break;
        case 3: cout<<"Eliminar informacion de tu perfil definitivamente"<<endl;
        eliminarPerfil(correoUsuario);
        break;
        default: cout<<"Opcion invalida panita"<<endl;
    }
}
void buscarAmigo() {
    string busqueda;
    bool encontrado = false;

    cout << " *** Buscar Panitas *** "<<endl;
    cout << "Ingresa el nombre o apellido del panita que buscas: "<<endl;
    cin >> busqueda;

    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream linestream(linea);
            string nombre, apellido, genero, correo;
            int cumpleanos, infopublica, visible, activo;
            getline(linestream, nombre, ',');
            getline(linestream, apellido, ',');
            getline(linestream, genero, ',');
            getline(linestream, correo, ',');
            linestream >> cumpleanos;
            linestream.ignore();
            linestream >> infopublica;
            linestream.ignore();
            linestream >> visible;
            linestream.ignore();
            linestream >> activo;

            if(nombre == busqueda || apellido == busqueda) {
                encontrado = true;
                cout << "Panita encontrado:\n";
                cout << "Nombre: " << nombre << endl;
                cout << "Apellido: " << apellido << endl;
                cout << "Correo: " << correo << endl;

                if(infopublica == 1) {
                    cout << "Genero: " << genero << endl;
                    cout << "Cumpleanos: " << cumpleanos << endl;
                }
            }
        }
        archivo.close();
    }
    if(!encontrado) {
        cout << " No se encontraron panitas con ese nombre o apellido :( ";
    }
}
void enviarSolicitudAmistad(string correoUsuario) {
   string correoDestino;
   bool usuarioExiste = false;
   bool solicitudExiste = false;
   bool yaEsAmigo = false;

   cout << " *** Enviar Solicitud de Amistad ***"<<endl;
   cout << "Ingresa el correo del panita al que quieres enviar la solicitud: "<<endl;
   cin >> correoDestino;

   if(correoDestino == correoUsuario) {
       cout << "No puedes enviarte una solicitud a ti mismo panita";
   }

   ifstream archivoUsuarios("usuarios.txt");
   if (archivoUsuarios.is_open()) {
       string linea;
       while (getline(archivoUsuarios, linea)) {
           stringstream linestream(linea);
           string nombre, apellido, genero, correo;
           getline(linestream, nombre, ',');
           getline(linestream, apellido, ',');
           getline(linestream, genero, ',');
           getline(linestream, correo, ',');

           if (correo == correoDestino) {
               usuarioExiste = true;
               break;
           }
       }
       archivoUsuarios.close();
   }

   if (!usuarioExiste) {
       cout << "No existe ningun panita con ese correo ";
   }

   ifstream archivoSolicitudes("solicitudes.txt");
   if (archivoSolicitudes.is_open()) {
       string linea;
       while (getline(archivoSolicitudes, linea)) {
           stringstream linestream(linea);
           string remitente, destinatario;
           getline(linestream, remitente, ',');
           getline(linestream, destinatario);

           if (remitente == correoUsuario && destinatario == correoDestino) {
               solicitudExiste = true;
               break;
           }
       }
       archivoSolicitudes.close();
   }

   if (solicitudExiste) {
       cout << "Ya le enviaste una solicitud a este panita ";
   }

   ifstream archivoAmigos("amigos.txt");
   if (archivoAmigos.is_open()) {
       string linea;
       while (getline(archivoAmigos, linea)) {
           stringstream linestream(linea);
           string amigo1, amigo2;
           getline(linestream, amigo1, ',');
           getline(linestream, amigo2);

           if ((amigo1 == correoUsuario && amigo2 == correoDestino) ||
               (amigo1 == correoDestino && amigo2 == correoUsuario)) {
               yaEsAmigo = true;
               break;
           }
       }
       archivoAmigos.close();
   }

   if (yaEsAmigo) {
       cout << "Este panita ya es tu amigo! ";
       return;
   }

   ofstream archivoSalida("solicitudes.txt", ios::app);
   if (archivoSalida.is_open()) {
       archivoSalida << correoUsuario << "," << correoDestino << endl;
       archivoSalida.close();
       cout << " Solicitud de amistad enviada exitosamente! ";
   } else {
       cout << "Error al enviar la solicitud de amistad ";
   }
}

void verSolicitudesPendientes(string correoUsuario) {
    bool haySolicitudes = false;
    cout << "  Solicitudes de Amistad Pendientes  ";

    ifstream archivoSolicitudes("solicitudes.txt");
    if (archivoSolicitudes.is_open()) {
        string linea;
        while (getline(archivoSolicitudes, linea)) {
            stringstream linestream(linea);
            string correoRemitente, correoDestino;
            getline(linestream, correoRemitente, ',');
            getline(linestream, correoDestino);

            if (correoDestino == correoUsuario) {
                haySolicitudes = true;

                ifstream archivoUsuarios("usuarios.txt");
                string lineaUsuario;
                while (getline(archivoUsuarios, lineaUsuario)) {
                    stringstream streamUsuario(lineaUsuario);
                    string nombre, apellido, genero, correo;
                    getline(streamUsuario, nombre, ',');
                    getline(streamUsuario, apellido, ',');
                    getline(streamUsuario, genero, ',');
                    getline(streamUsuario, correo, ',');

                    if (correo == correoRemitente) {

                        cout << "Tienes una solicitud de: ";
                        cout << "Nombre: " << nombre << endl;
                        cout << "Apellido: " << apellido << endl;

                        break;
                    }
                }
                archivoUsuarios.close();
            }
        }
        archivoSolicitudes.close();
    }
    if (!haySolicitudes) {
        cout << "No tienes solicitudes de amistad pendientes, panita\n";
    }
}
void aceptarSolicitud(string correoUsuario) {
   bool haySolicitudes = false;
   int numSolicitudes = 0;
   string solicitudes[50][2];

   cout << " *** Aceptar Solicitudes de Amistad *** ";

   ifstream archivoSolicitudes("solicitudes.txt");
   if (archivoSolicitudes.is_open()) {
       string linea;
       while (getline(archivoSolicitudes, linea)) {
           stringstream linestream(linea);
           string correoRemitente, correoDestino;
           getline(linestream, correoRemitente, ',');
           getline(linestream, correoDestino);

           if (correoDestino == correoUsuario) {
               haySolicitudes = true;
               solicitudes[numSolicitudes][0] = correoRemitente;
               solicitudes[numSolicitudes][1] = correoDestino;

               ifstream archivoUsuarios("usuarios.txt");
               string lineaUsuario;
               while (getline(archivoUsuarios, lineaUsuario)) {
                   stringstream streamUsuario(lineaUsuario);
                   string nombre, apellido, genero, correo;
                   getline(streamUsuario, nombre, ',');
                   getline(streamUsuario, apellido, ',');
                   getline(streamUsuario, genero, ',');
                   getline(streamUsuario, correo, ',');

                   if (correo == correoRemitente) {
                       cout << numSolicitudes + 1 << ". ";
                       cout << "Solicitud de " << nombre << " " << apellido << endl;
                       break;
                   }
               }
               archivoUsuarios.close();
               numSolicitudes++;
           }
       }
       archivoSolicitudes.close();
   }

   if (!haySolicitudes) {
       cout << "No tienes solicitudes de amistad pendientes, panita ";
   }

   int opcion;
   cout << " Ingresa el numero de la solicitud que deseas aceptar (0 para cancelar): "<<endl;
   cin >> opcion;

   if (opcion == 0) {
       cout << "Operacion cancelada";
       return;
   }

   if (opcion < 1 || opcion > numSolicitudes) {
       cout << "Opcion invalida panita"<<endl;
       return;
   }

   ofstream archivoAmigos("amigos.txt", ios::app);
   if (archivoAmigos.is_open()) {
       archivoAmigos << solicitudes[opcion-1][0] << "," << solicitudes[opcion-1][1] << endl;
       archivoAmigos.close();
   }

   ifstream archivoLeerSolicitudes("solicitudes.txt");
   ofstream archivoActualizado("solicitudes.txt");
   if (archivoLeerSolicitudes.is_open() && archivoActualizado.is_open()) {
       string linea;
       while (getline(archivoLeerSolicitudes, linea)) {
           stringstream linestream(linea);
           string remitente, destino;
           getline(linestream, remitente, ',');
           getline(linestream, destino);

           if (!(remitente == solicitudes[opcion-1][0] && destino == solicitudes[opcion-1][1])) {
               archivoActualizado << linea << endl;
           }
       }
       archivoLeerSolicitudes.close();
       archivoActualizado.close();

       cout << " Solicitud aceptada exitosamente! Ahora son panitas "<<endl;
   }
}
void verAmigos(string correoUsuario) {
    cout << " *** Lista de tus Panitas *** ";
    bool tieneAmigos = false;

    ifstream archivoAmigos("amigos.txt");
    if (archivoAmigos.is_open()) {
        string linea;
        while (getline(archivoAmigos, linea)) {
            stringstream linestream(linea);
            string correoAmigo1, correoAmigo2;
            getline(linestream, correoAmigo1, ',');
            getline(linestream, correoAmigo2);

            string correoAmigo;
            if (correoAmigo1 == correoUsuario) {
                correoAmigo = correoAmigo2;
            } else if (correoAmigo2 == correoUsuario) {
                correoAmigo = correoAmigo1;
            } else {
                continue;
            }

            ifstream archivoUsuarios("usuarios.txt");
            string lineaUsuario;
            while (getline(archivoUsuarios, lineaUsuario)) {
                stringstream streamUsuario(lineaUsuario);
                string nombre, apellido, genero, correo, cumpleanos;
                getline(streamUsuario, nombre, ',');
                getline(streamUsuario, apellido, ',');
                getline(streamUsuario, genero, ',');
                getline(streamUsuario, correo, ',');
                getline(streamUsuario, cumpleanos, ',');

                if (correo == correoAmigo) {
                    tieneAmigos = true;
                    cout << "Nombre: " << nombre << endl;
                    cout << "Apellido: " << apellido << endl;
                    cout << "Correo: " << correo << endl;
                    cout << "Cumpleanos: " << cumpleanos << endl;
                    break;
                }
            }
            archivoUsuarios.close();
        }
        archivoAmigos.close();
    }

    if (!tieneAmigos) {
        cout << "Aun no tienes panitas :( ";
    }
}
void verInformacionAmigo(string correoUsuario) {
   string correoAmigo;
   bool esAmigo = false;
   cout << "\n*** Ver Informacion de un Panita ***\n";
   cout << "Ingresa el correo del panita: ";
   cin >> correoAmigo;

   ifstream archivoAmigos("amigos.txt");
   if (archivoAmigos.is_open()) {
       string linea;
       while (getline(archivoAmigos, linea)) {
           stringstream linestream(linea);
           string correoAmigo1, correoAmigo2;
           getline(linestream, correoAmigo1, ',');
           getline(linestream, correoAmigo2);

           if ((correoAmigo1 == correoUsuario && correoAmigo2 == correoAmigo) ||
               (correoAmigo2 == correoUsuario && correoAmigo1 == correoAmigo)) {
               esAmigo = true;
               break;
           }
       }
       archivoAmigos.close();
   }

   if (!esAmigo) {
       cout << "Este panita no esta en tu lista de amigos!\n";
       return;
   }

   ifstream archivoUsuarios("usuarios.txt");
   if (archivoUsuarios.is_open()) {
       string linea;
       while (getline(archivoUsuarios, linea)) {
           stringstream linestream(linea);
           string nombre, apellido, genero, correo, cumpleanosTemp, infopublicaTemp;
           string contrasena, rol, visibleTemp, activoTemp;

           getline(linestream, nombre, ',');
           getline(linestream, apellido, ',');
           getline(linestream, genero, ',');
           getline(linestream, correo, ',');
           getline(linestream, cumpleanosTemp, ',');
           getline(linestream, infopublicaTemp, ',');
           getline(linestream, contrasena, ',');
           getline(linestream, rol, ',');
           getline(linestream, visibleTemp, ',');
           getline(linestream, activoTemp);

           if (correo == correoAmigo) {

               cout << "Nombre: " << nombre << endl;
               cout << "Apellido: " << apellido << endl;
               cout << "Genero: " << genero << endl;
               cout << "Correo: " << correo << endl;
               cout << "Cumpleanos: " << cumpleanosTemp << endl;
               cout << " --- Peliculas que le gustan --- ";

               ifstream archivoPeliculasGustan("peliculasgustan.txt");
               if (archivoPeliculasGustan.is_open()) {
                   string lineaPelicula;
                   bool tienePeliculas = false;

                   while (getline(archivoPeliculasGustan, lineaPelicula)) {
                       stringstream streamPelicula(lineaPelicula);
                       string correoUsuarioPelicula, codigoPelicula;
                       getline(streamPelicula, correoUsuarioPelicula, ',');
                       getline(streamPelicula, codigoPelicula);

                       if (correoUsuarioPelicula == correoAmigo) {
                           ifstream archivoPeliculas("peliculas.txt");
                           string lineaPeliculaInfo;

                           while (getline(archivoPeliculas, lineaPeliculaInfo)) {
                               stringstream streamPeliculaInfo(lineaPeliculaInfo);
                               string codigoTemp, nombre, genero, resumen;
                               getline(streamPeliculaInfo, codigoTemp, ',');

                               if (codigoTemp == codigoPelicula) {
                                   getline(streamPeliculaInfo, nombre, ',');
                                   getline(streamPeliculaInfo, genero, ',');
                                   getline(streamPeliculaInfo, resumen);


                                   cout << "Nombre: " << nombre << endl;
                                   cout << "Genero: " << genero << endl;
                                   cout << "Resumen: " << resumen << endl;
                                   tienePeliculas = true;
                                   break;
                               }
                           }
                           archivoPeliculas.close();
                       }
                   }

                   if (!tienePeliculas) {
                       cout << "Este panita aun no tiene peliculas favoritas\n";
                   }
                   archivoPeliculasGustan.close();
               }
               break;
           }
       }
       archivoUsuarios.close();
   }
}
void verPeliculasComun(string correoUsuario) {
   string correoAmigo;
   bool esAmigo = false;
   cout << " *** Ver Peliculas en Comun con un Panita ***";
   cout << "Ingresa el correo del panita: ";
   cin >> correoAmigo;

   ifstream archivoAmigos("amigos.txt");
   if (archivoAmigos.is_open()) {
       string linea;
       while (getline(archivoAmigos, linea)) {
           stringstream linestream(linea);
           string correoAmigo1, correoAmigo2;
           getline(linestream, correoAmigo1, ',');
           getline(linestream, correoAmigo2);

           if ((correoAmigo1 == correoUsuario && correoAmigo2 == correoAmigo) ||
               (correoAmigo2 == correoUsuario && correoAmigo1 == correoAmigo)) {
               esAmigo = true;
               break;
           }
       }
       archivoAmigos.close();
   }

   if (!esAmigo) {
       cout << "Este panita no esta en tu lista de amigos ";
   }

   string peliculasUsuario[50];
   string peliculasAmigo[50];
   int numPeliculasUsuario = 0;
   int numPeliculasAmigo = 0;

   ifstream archivoPeliculasGustan("peliculasgustan.txt");
   if (archivoPeliculasGustan.is_open()) {
       string linea;
       while (getline(archivoPeliculasGustan, linea)) {
           stringstream linestream(linea);
           string correo, codigoPelicula;
           getline(linestream, correo, ',');
           getline(linestream, codigoPelicula);

           if (correo == correoUsuario) {
               peliculasUsuario[numPeliculasUsuario] = codigoPelicula;
               numPeliculasUsuario++;
           }
           if (correo == correoAmigo) {
               peliculasAmigo[numPeliculasAmigo] = codigoPelicula;
               numPeliculasAmigo++;
           }
       }
       archivoPeliculasGustan.close();
   }
   cout << " Tabla de Peliculas ";
   cout << "Guia: [X] En comun, [ ] No en comun ";
   cout << "Codigo | Nombre | Tu | Panita | En Comun\n";

   ifstream archivoPeliculas("peliculas.txt");
   if (archivoPeliculas.is_open()) {
       string linea;
       while (getline(archivoPeliculas, linea)) {
           stringstream linestream(linea);
           string codigo, nombre, genero, resumen;
           getline(linestream, codigo, ',');
           getline(linestream, nombre, ',');
           getline(linestream, genero, ',');
           getline(linestream, resumen);

           bool tienePeliculaUsuario = false;
           bool tienePeliculaAmigo = false;

           for(int i = 0; i < numPeliculasUsuario; i++) {
               if(peliculasUsuario[i] == codigo) {
                   tienePeliculaUsuario = true;
                   break;
               }
           }

           for(int i = 0; i < numPeliculasAmigo; i++) {
               if(peliculasAmigo[i] == codigo) {
                   tienePeliculaAmigo = true;
                   break;
               }
           }

           cout << codigo << " | " << nombre << " | ";
           if(tienePeliculaUsuario) {
               cout << "X";
           } else {
               cout << " ";
           }
           cout << " | ";
           if(tienePeliculaAmigo) {
               cout << "X";
           } else {
               cout << " ";
           }
           cout << "   | ";
           if(tienePeliculaUsuario && tienePeliculaAmigo) {
               cout << "  [X]";
           } else {
               cout << "  [ ]";
           }
           cout << endl;
       }
       archivoPeliculas.close();
   }
}
void deshacerAmistad(string correoUsuario) {
    string correoAmigo;
    bool esAmigo = false;
    cout << " *** Deshacer Amistad *** ";
    cout << "Ingresa el correo del panita que quieres eliminar: ";
    cin >> correoAmigo;

    string amigos[50][2];
    int numAmigos = 0;

    ifstream archivoLectura("amigos.txt");
    if (archivoLectura.is_open()) {
        string linea;
        while (getline(archivoLectura, linea)) {
            stringstream linestream(linea);
            string correoAmigo1, correoAmigo2;
            getline(linestream, correoAmigo1, ',');
            getline(linestream, correoAmigo2);

            if ((correoAmigo1 == correoUsuario && correoAmigo2 == correoAmigo) ||
                (correoAmigo2 == correoUsuario && correoAmigo1 == correoAmigo)) {
                esAmigo = true;
                }

            amigos[numAmigos][0] = correoAmigo1;
            amigos[numAmigos][1] = correoAmigo2;
            numAmigos++;
        }
        archivoLectura.close();
    }

    if (!esAmigo) {
        cout << "Este panita no esta en tu lista de amigos ";
        return;
    }

    ofstream archivoEscritura("amigos.txt");
    if (archivoEscritura.is_open()) {
        for (int i = 0; i < numAmigos; i++) {
            if (!((amigos[i][0] == correoUsuario && amigos[i][1] == correoAmigo) ||
                  (amigos[i][1] == correoUsuario && amigos[i][0] == correoAmigo))) {
                archivoEscritura << amigos[i][0] << "," << amigos[i][1] << endl;
                  }
        }
        archivoEscritura.close();
        cout << "Has dejado de ser panita de este usuario ";
    }
}
void mostrarMenuAmigos(string correoUsuario) {
    int opcionamigos;
    cout << " Edita info de la lista de tus Panitas" << endl;
    cout << "1. Busca Panitas" << endl;
    cout << "2. Haz solicitud de amistad" << endl;
    cout << "3. Ver solicitudes pendientes" << endl;
    cout << "4. Acepta solicitudes :)" << endl;
    cout << "5. Ver Panitas" << endl;
    cout << "6. Ver informacion de un Panita" << endl;
    cout << "7. Ver peliculas en comun" << endl;
    cout << "8. Deshacer amistad" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "\nIngresa tu opcion panita: ";
    cin >> opcionamigos;

    switch (opcionamigos) {
        case 1:
            cout << "Busca la info publica de algun panita" << endl;
        buscarAmigo();
        break;
        case 2:
            cout << "Hazle solicitud a algun panita" << endl;
        enviarSolicitudAmistad(correoUsuario);
        break;
        case 3:
            cout << "Mira tus solicitudes de amistad de panitas pendientes" << endl;
        verSolicitudesPendientes(correoUsuario);
        break;
        case 4:
            cout << "Acepta solicitudes de amistad de otros panitas" << endl;
        aceptarSolicitud(correoUsuario);
        break;
        case 5:
            cout << "Ver a tus panitas amigos!" << endl;
        verAmigos(correoUsuario);
        break;
        case 6:
            cout << "Ver la informacion de tus amigos" << endl;
        verInformacionAmigo(correoUsuario);
        break;
        case 7:
            cout << "Ver peliculas en comun con panitas" << endl;
        verPeliculasComun(correoUsuario);
        break;
        case 8:
            cout << "Deshacer amistad o panita" << endl;
        deshacerAmistad(correoUsuario);
        break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
        break;
        default:
            cout << "Opcion invalida panita" << endl;
    }
}
void agregarPeliculasMeGusta(string correoUsuario) {
   pelicula peliculas[100];
   int numPeliculas = 0;
   string peliculasGustan[100];
   int numPeliculasGustan = 0;

   cout << " *** Agregar Peliculas a Me Gusta ***";

   ifstream archivoPeliculas("peliculas.txt");
   if (archivoPeliculas.is_open()) {
       string linea;
       while (getline(archivoPeliculas, linea)) {
           stringstream linestream(linea);
           string codigoTemp;
           getline(linestream, codigoTemp, ',');
           peliculas[numPeliculas].codigo = atoi(codigoTemp.c_str());
           getline(linestream, peliculas[numPeliculas].nombre, ',');
           getline(linestream, peliculas[numPeliculas].genero, ',');
           getline(linestream, peliculas[numPeliculas].resumen);
           numPeliculas++;
       }
       archivoPeliculas.close();
   }

   ifstream archivoMeGusta("peliculasgustan.txt");
   if (archivoMeGusta.is_open()) {
       string linea;
       while (getline(archivoMeGusta, linea)) {
           stringstream linestream(linea);
           string correo, codigoPelicula;
           getline(linestream, correo, ',');
           if(correo == correoUsuario) {
               getline(linestream, codigoPelicula);
               peliculasGustan[numPeliculasGustan] = codigoPelicula;
               numPeliculasGustan++;
           }
       }
       archivoMeGusta.close();
   }

   cout << " Peliculas disponibles: ";

   for(int i = 0; i < numPeliculas; i++) {
       cout << peliculas[i].codigo << ". " << peliculas[i].nombre
            << "  Genero: " << peliculas[i].genero << endl;
   }

   int codigoElegido;
   cout << " Ingresa el codigo de la pelicula que te gusta (0 para cancelar): ";
   cin >> codigoElegido;

   if(codigoElegido == 0) {
       cout << "Operacion cancelada ";
       return;
   }

   for(int i = 0; i < numPeliculasGustan; i++) {
       if(atoi(peliculasGustan[i].c_str()) == codigoElegido) {
           cout << "Esta pelicula ya esta en tus me gusta panita! ";
           return;
       }
   }

   bool peliculaExiste = false;
   for(int i = 0; i < numPeliculas; i++) {
       if(peliculas[i].codigo == codigoElegido) {
           peliculaExiste = true;
           break;
       }
   }

   if(!peliculaExiste) {
       cout << "El codigo ingresado no existe panita! ";
       return;
   }

   ofstream archivoAgregar("peliculasgustan.txt", ios::app);
   if(archivoAgregar.is_open()) {
       archivoAgregar << correoUsuario << "," << codigoElegido << endl;
       archivoAgregar.close();
       cout << "  Pelicula agregada a tus me gusta exitosamente! ";
   }
}
void quitarPeliculasMeGusta(string correoUsuario) {
   string peliculasGustan[50][2];
   int numPeliculasGustan = 0;
   bool tienePeliculas = false;

   cout << "  *** Quitar Peliculas de Me Gusta ***  ";

   ifstream archivoMeGusta("peliculasgustan.txt");
   if (archivoMeGusta.is_open()) {
       string linea;
       while (getline(archivoMeGusta, linea)) {
           stringstream linestream(linea);
           getline(linestream, peliculasGustan[numPeliculasGustan][0], ',');
           getline(linestream, peliculasGustan[numPeliculasGustan][1]);
           numPeliculasGustan++;
       }
       archivoMeGusta.close();
   }

   cout << "  Tus peliculas favoritas: ";
   for(int i = 0; i < numPeliculasGustan; i++) {
       if(peliculasGustan[i][0] == correoUsuario) {
           tienePeliculas = true;
           string codigoPelicula = peliculasGustan[i][1];

           ifstream archivoPeliculas("peliculas.txt");
           string linea;
           while(getline(archivoPeliculas, linea)) {
               stringstream linestream(linea);
               string codigo, nombre;
               getline(linestream, codigo, ',');
               getline(linestream, nombre, ',');

               if(codigo == codigoPelicula) {
                   cout << codigo << ". " << nombre << endl;
                   break;
               }
           }
           archivoPeliculas.close();
       }
   }

   if(!tienePeliculas) {
       cout << "No tienes peliculas en me gusta panita! ";
       return;
   }

   int codigoEliminar;
   cout << "\nIngresa el codigo de la pelicula que quieres quitar (0 para cancelar): ";
   cin >> codigoEliminar;

   if(codigoEliminar == 0) {
       cout << "Operacion cancelada  ";
       return;
   }

   ofstream archivoActualizado("peliculasgustan.txt");
   if(archivoActualizado.is_open()) {
       bool peliculaEncontrada = false;
       for(int i = 0; i < numPeliculasGustan; i++) {
           if(!(peliculasGustan[i][0] == correoUsuario &&
                atoi(peliculasGustan[i][1].c_str()) == codigoEliminar)) {
               archivoActualizado << peliculasGustan[i][0] << ","
                                << peliculasGustan[i][1] << endl;
           } else {
               peliculaEncontrada = true;
           }
       }
       archivoActualizado.close();

       if(peliculaEncontrada) {
           cout << " Pelicula quitada de tus me gusta exitosamente!  ";
       } else {
           cout << "No tienes una pelicula con ese codigo en tus me gusta\n";
       }
   }
}
void verPeliculasMeGusta(string correoUsuario) {
    bool tienePeliculas = false;

    cout << " *** Tus Peliculas Favoritas ***  ";
    ifstream archivoMeGusta("peliculasgustan.txt");
    if (archivoMeGusta.is_open()) {
        string linea;
        while (getline(archivoMeGusta, linea)) {
            stringstream linestream(linea);
            string correo, codigoPelicula;
            getline(linestream, correo, ',');
            getline(linestream, codigoPelicula);

            if(correo == correoUsuario) {
                ifstream archivoPeliculas("peliculas.txt");
                string lineaPelicula;
                while(getline(archivoPeliculas, lineaPelicula)) {
                    stringstream streamPelicula(lineaPelicula);
                    string codigo, nombre, genero, resumen;
                    getline(streamPelicula, codigo, ',');

                    if(codigo == codigoPelicula) {
                        getline(streamPelicula, nombre, ',');
                        getline(streamPelicula, genero, ',');
                        getline(streamPelicula, resumen);

                        tienePeliculas = true;
                        cout << " Codigo: " << codigo << endl;
                        cout << "Nombre: " << nombre << endl;
                        cout << "Genero: " << genero << endl;
                        cout << "Resumen: " << resumen << endl;
                    }
                }
                archivoPeliculas.close();
            }
        }
        archivoMeGusta.close();
    }

    if(!tienePeliculas) {
        cout << "No tienes peliculas en me gusta panita!";
    }
}
void mostrarMenuPeliculas(string correoUsuario) {
    cout << "Que deseas hacer con las peliculas panita" << endl;
    cout << " 1. Peliculas en me gusta" << endl;
    cout << " 2. Quita peliculas en me gusta" << endl;
    cout << " 3. Ver peliculas en me gusta" << endl;
    int opcionpeli;
    cin>> opcionpeli;
    switch(opcionpeli) {
        case 1: cout<<"Pon peliculas en me gusta panita" << endl;
        agregarPeliculasMeGusta(correoUsuario);
        break;
        case 2: cout<< "Quita peliculas de me gusta panita" << endl;
        quitarPeliculasMeGusta(correoUsuario);
        break;
        case 3: cout<< "Mira las peliculas que te gustan panita!" << endl;
        verPeliculasMeGusta(correoUsuario);
        break;
        default: cout<<"Opcion invalida panita!"<<endl;
    }
}
bool iniciarSesion() {
    string linea, correo, contrasena;
    usuario usuarioArchivo;
    cout << "*** Inicio de Sesion ***"<<endl;
    cout << "Ingrese su correo: "<<endl;
    cin >> correo;
    cout << "Ingrese su contrasena: "<<endl;;
    cin >> contrasena;

    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream linestream(linea);
            string cumpleanosTemp, infopublicaTemp, visibleTemp;
            getline(linestream, usuarioArchivo.nombre, ',');
            getline(linestream, usuarioArchivo.apellido, ',');
            getline(linestream, usuarioArchivo.genero, ',');
            getline(linestream, usuarioArchivo.correo, ',');
            getline(linestream, cumpleanosTemp, ',');
            getline(linestream, infopublicaTemp, ',');
            getline(linestream, usuarioArchivo.contrasena, ',');
            linestream >> usuarioArchivo.rol;
            getline(linestream, visibleTemp);

            usuarioArchivo.cumpleanos = atoi(cumpleanosTemp.c_str());
            usuarioArchivo.infopublica = atoi(infopublicaTemp.c_str());
            usuarioArchivo.visible = atoi(visibleTemp.c_str());

            if (usuarioArchivo.correo == correo && usuarioArchivo.contrasena == contrasena) {
                archivo.close();
                cout << "Inicio de sesion exitoso, Panita! "<<endl;

                int opcionMenu;
                do {
                    mostrarMenuPrincipal();
                    cin >> opcionMenu;
                    switch (opcionMenu) {
                        case 1:
                            if (usuarioArchivo.rol == 'A') {
                                menuAdministrador();
                            } else {
                                cout << "No tienes permisos para acceder a las opciones de administrador."<<endl;
                            }
                            break;
                        case 2:
                            mostrarMenuPerfil(usuarioArchivo.correo);
                            break;
                        case 3:
                            mostrarMenuAmigos(usuarioArchivo.correo);
                            break;
                        case 4:
                            mostrarMenuPeliculas(usuarioArchivo.correo);
                            break;
                        case 0:
                            cout << "Cerrando sesion..."<<endl;
                            break;
                        default:
                            cout << "Opcion invalida. Intente nuevamente."<<endl;;
                    }
                } while (opcionMenu != 0);
                return true;
            }
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    cout << "Nombre de usuario o contrasena incorrectos.\n";
    return false;
}

int main() {
    int opcionPreMenu;

    while (true) {
        mostrarPreMenu();
        cin >> opcionPreMenu;

        switch (opcionPreMenu) {
            case 1:
                registrarUsuario();
                break;
            case 2:
                iniciarSesion();
                break;
            case 3:
                cout << "Saliendo del sistema... Adios Panita!" << endl;
                return 0;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
    }
}
// Uso de la IA claude.ai para organizacion y implementacion de cout repetidamente del codigo/uso en la implementacion repetida de abrir y cerrar archivos
// Cuenta de administrador= Correo: Juan1234@gmail.com, Contraseña: 123
