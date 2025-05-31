#include <sstream>
#include <cctype> 
#include <ctime>
#include "utils/Validaciones.h"

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

bool Validaciones::estaVencido(const std::string& fechaVencimiento) {
    if (!validarFecha(fechaVencimiento)) return false;
    
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    
    int dia = now->tm_mday;
    int mes = now->tm_mon + 1;
    int anio = now->tm_year + 1900;
    
    int diaVen = std::stoi(fechaVencimiento.substr(0, 2));
    int mesVen = std::stoi(fechaVencimiento.substr(3, 2));
    int anioVen = std::stoi(fechaVencimiento.substr(6, 4));
    
    if (anioVen < anio) return true;
    if (anioVen == anio && mesVen < mes) return true;
    if (anioVen == anio && mesVen == mes && diaVen < dia) return true;
    
    return false;
}

int Validaciones::compararFechas(const std::string& fecha1, const std::string& fecha2) {
    // Convertir a AAAAMMDD para comparación
    auto convertir = [](const std::string& fecha) -> int {
        if (!validarFecha(fecha)) return 0;
        int dia = std::stoi(fecha.substr(0, 2));
        int mes = std::stoi(fecha.substr(3, 2));
        int anio = std::stoi(fecha.substr(6, 4));
        return anio * 10000 + mes * 100 + dia;
    };
    
    int f1 = convertir(fecha1);
    int f2 = convertir(fecha2);
    
    if (f1 < f2) return -1;
    if (f1 > f2) return 1;
    return 0;
}