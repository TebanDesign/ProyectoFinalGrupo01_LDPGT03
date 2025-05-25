
#include <sstream>
#include <ctime>
#include <stdexcept>

#include "CalcularEdad.h"

std::string CalcularEdad::CalcularAsignarEdad(std::string fechaNacimiento){

    std::string edad;

    if (fechaNacimiento.empty()) {
        edad = "0";
        return edad;
    }

    // parsear la fecha de nacimiento (dd/MM/yyyy)
    std::istringstream ss(fechaNacimiento);
    std::string dia, mes, anio;
    std::getline(ss, dia, '/');
    std::getline(ss, mes, '/');
    std::getline(ss, anio);
    
    // validar que se pudieron extraer las tres partes
    if (dia.empty() || mes.empty() || anio.empty()) {
        edad = "0";
        return edad;
    }
    
    try {
        int diaNac = std::stoi(dia);
        int mesNac = std::stoi(mes);
        int anioNac = std::stoi(anio);
        
        // validar rangos de fecha
        if (mesNac < 1 || mesNac > 12 || diaNac < 1 || diaNac > 31) {
            edad = "0";
            return edad;
        }
        
        // obtener la fecha actual
        std::time_t tiempoActual = std::time(nullptr);
        std::tm* fechaActual = std::localtime(&tiempoActual);
        
        int diaActual = fechaActual->tm_mday;
        int mesActual = fechaActual->tm_mon + 1;  // tm_mon va de 0-11
        int anioActual = fechaActual->tm_year + 1900;  // tm_year es desde 1900
        
        // validar dias del mes considerando años bisiestos
        if (!esFechaValida(diaNac, mesNac, anioNac)) {
            edad = "0";
            return edad;
        }
        
        // calcular edad base
        int edadCalculada = anioActual - anioNac;
        
        // verificar si ya pasó el cumpleaños este año
        bool yaFueCumpleanos = false;
        
        if (mesActual > mesNac) {
            yaFueCumpleanos = true;
        } else if (mesActual == mesNac) {
            if (diaActual >= diaNac) {
                yaFueCumpleanos = true;
            }
        }
        
        // si no ha pasado el cumpleaños, restar un año
        if (!yaFueCumpleanos) {
            edadCalculada--;
        }
        
        // asegurar que la edad no sea negativa
        if (edadCalculada < 0) {
            edadCalculada = 0;
        }
        
        // convertir a string y asignar
        edad = std::to_string(edadCalculada);
        
    } catch (const std::exception& e) {
        // en caso de error en la conversión, asignar edad 0
        edad = "0";
    }

    return edad;
}

// funcio auxiliar para validar fechas considerando años bisiestos
bool CalcularEdad::esFechaValida(int dia, int mes, int anio) {
    // Días por mes (febrero se maneja especialmente)
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Verificar año bisiesto para febrero
    if (mes == 2 && esBisiesto(anio)) {
        diasPorMes[1] = 29;
    }
    
    return dia <= diasPorMes[mes - 1];
}

// funcio auxiliar para determinar años bisiestos
bool CalcularEdad::esBisiesto(int anio) {
    // un año es bisiesto si:
    // - es divisible por 4 Y no es divisible por 100
    // - o es divisible por 400
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
