#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

class MenuUtils {
public:
    // colores para la consola
    enum Color {
        NEGRO = 0,
        AZUL_OSCURO = 1,
        VERDE_OSCURO = 2,
        CYAN_OSCURO = 3,
        ROJO_OSCURO = 4,
        MAGENTA_OSCURO = 5,
        AMARILLO_OSCURO = 6,
        BLANCO_OSCURO = 7,
        GRIS = 8,
        AZUL = 9,
        VERDE = 10,
        CYAN = 11,
        ROJO = 12,
        MAGENTA = 13,
        AMARILLO = 14,
        BLANCO = 15
    };

    static void configurarConsola();
    static void cambiarColor(Color fondo, Color texto);
    static void restaurarColor();
    static void limpiarPantalla();
    static void pausar();
    static void mostrarTitulo(const std::string& titulo, Color colorFondo = AZUL, Color colorTexto = BLANCO);
    static void mostrarSubtitulo(const std::string& subtitulo, Color colorTexto = CYAN);
    static void mostrarSeparador(char caracter = '=', int longitud = 50, Color color = AMARILLO);
    static void mostrarOpcion(int numero, const std::string& texto, bool habilitada = true);
    static void mostrarMensaje(const std::string& mensaje, Color color = BLANCO);
    static void mostrarMensajeExito(const std::string& mensaje);
    static void mostrarMensajeError(const std::string& mensaje);
    static void mostrarMensajeAdvertencia(const std::string& mensaje);
    static void centrarTexto(const std::string& texto, int ancho = 80);
    static void mostrarCuadro(const std::vector<std::string>& lineas, Color colorBorde = CYAN);
    static int leerOpcion(int min, int max);
    static void mostrarCargando(const std::string& mensaje = "Procesando", int duracion = 2000);

private:
    static HANDLE hConsole;
    static WORD colorOriginal;
};
