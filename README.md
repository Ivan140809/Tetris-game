# Portafolio de Proyectos de Programacion

Aca estan almacenados todos mis proyectos de final de semestre, voluntarios y relacionados con programacion para mi CV.

---

## Proyectos

### Tetris en C++

Un juego de Tetris funcional corriendo en la terminal, desarrollado en C++ sin librerias graficas externas.

**Caracteristicas:**

- Tablero de 30x30 celdas con bordes dibujados en consola
- 7 tipos de piezas clasicas del Tetris: Linea Recta, Cuadrado, S, Z, J, T y L
- Rotacion de piezas con hasta 4 orientaciones por figura
- Caida automatica con intervalo configurable
- Deteccion de colisiones con paredes, piso y piezas fijadas
- Eliminacion de filas completas
- Sistema de puntaje y conteo de lineas eliminadas
- Guardado automatico de estadisticas en archivo `Estadisticas.txt`
- Menu con modo juego, demo de rotaciones y visualizacion de estadisticas historicas

**Controles:**

| Tecla | Accion              |
|-------|---------------------|
| `A`   | Mover a la izquierda |
| `D`   | Mover a la derecha   |
| `W`   | Rotar figura         |
| `S`   | Acelerar caida       |

**Condicion de victoria:** eliminar 10 o mas lineas en una partida.

**Compilacion:**

Linux:
```bash
g++ Tetris.cpp -o tetris -lncurses && ./tetris
```

Windows (con [MSYS2](https://www.msys2.org/)):
```bash
pacman -S mingw-w64-x86_64-ncurses
g++ Tetris.cpp -o tetris.exe -lncurses && tetris.exe
```

**Archivos:**
- [Tetris.cpp](Tetris.cpp) — codigo fuente completo
