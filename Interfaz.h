#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdarg.h>

void ConfigurarConsola(int ancho, int alto);
void GoToXY(int x, int y);
void OcultarCursor();
void Color(int fondo, int texto);
void DibujarMarco(int x1, int y1, int x2, int y2);
void CentrarTexto(int y, char *texto);
void EscribirXY(int x, int y, const char *formato, ...);
void LineaHorizontal(int x, int y, int longitud);

void ConfigurarConsola(int ancho, int alto) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, 1, 1};
    COORD tamBuffer = {ancho, alto};
    
    SetConsoleWindowInfo(hConsola, TRUE, &rect);
    SetConsoleScreenBufferSize(hConsola, tamBuffer);
    
    rect.Right = ancho - 1;
    rect.Bottom = alto - 1;
    SetConsoleWindowInfo(hConsola, TRUE, &rect);
    
    OcultarCursor();
}

void GoToXY(int x, int y) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X = x;
    posicion.Y = y;
    SetConsoleCursorPosition(hConsola, posicion);
}

void OcultarCursor() {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsola, &cursorInfo);
}

void Color(int fondo, int texto) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsola, (fondo << 4) | texto);
}

void DibujarMarco(int x1, int y1, int x2, int y2) {
    int i;
    
    GoToXY(x1, y1); printf("%c", 201);
    GoToXY(x2, y1); printf("%c", 187);
    GoToXY(x1, y2); printf("%c", 200);
    GoToXY(x2, y2); printf("%c", 188);
    
    for(i = x1 + 1; i < x2; i++) {
        GoToXY(i, y1); printf("%c", 205);
        GoToXY(i, y2); printf("%c", 205);
    }
    
    for(i = y1 + 1; i < y2; i++) {
        GoToXY(x1, i); printf("%c", 186);
        GoToXY(x2, i); printf("%c", 186);
    }
}

void CentrarTexto(int y, char *texto) {
    int x;
    x = (120 - strlen(texto)) / 2;
    GoToXY(x, y);
    printf("%s", texto);
}

void EscribirXY(int x, int y, const char *formato, ...) {
    GoToXY(x, y);
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
}

void LineaHorizontal(int x, int y, int longitud) {
    int i;
    GoToXY(x, y);
    for(i = 0; i < longitud; i++) {
        printf("%c", 196);
    }
}

#endif
