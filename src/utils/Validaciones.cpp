#include <sstream>
#include <cctype> 

#include "Validaciones.h"

bool Validaciones::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool Validaciones::validarFecha(const std::string& fechaStr) {
    // 1. Verificar el formato general
    if (fechaStr.length() != 10) {
        return false;
    }
    if (fechaStr[2] != '/' || fechaStr[5] != '/') {
        return false;
    }

    // 2. Extraer día, mes y año
    int dia, mes, anio;
    try {
        dia = std::stoi(fechaStr.substr(0, 2));
        mes = std::stoi(fechaStr.substr(3, 2));
        anio = std::stoi(fechaStr.substr(6, 4));
    } catch (const std::invalid_argument& e) {
        // La conversión a entero falló (caracteres no numéricos)
        return false;
    } catch (const std::out_of_range& e) {
        // El número es demasiado grande o pequeño para int
        return false;
    }

    // 3. Validar rangos básicos
    if (anio < 1) { // Ajusta este rango según tus necesidades (ej. anio < 1900)
        return false;
    }
    if (mes < 1 || mes > 12) {
        return false;
    }
    if (dia < 1 || dia > 31) { // 31 es el máximo posible antes de ajustar por mes
        return false;
    }

    // 4. Validar días por mes (y años bisiestos)
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Índice 0 no usado

    if (esBisiesto(anio)) {
        diasEnMes[2] = 29; // Febrero tiene 29 días en años bisiestos
    }

    if (dia > diasEnMes[mes]) {
        return false;
    }

    return true; // Si todo lo anterior pasó, la fecha es válida
}

bool Validaciones::esDigito(char c) {
    return std::isdigit(c);
}

bool Validaciones::validarDUI(const std::string& idStr) {
    // 1. Verificar la longitud y la posición del guion
    if (idStr.length() != 10) {
        return false;
    }
    if (idStr[8] != '-') {
        return false;
    }

    // 2. Verificar que los primeros 8 caracteres sean dígitos
    for (int i = 0; i < 8; ++i) {
        if (!esDigito(idStr[i])) {
            return false;
        }
    }

    // 3. Verificar que el último carácter (después del guion) sea un dígito
    if (!esDigito(idStr[9])) {
        return false;
    }

    return true; // Si todas las verificaciones pasan, el formato es válido
}
