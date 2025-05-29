#pragma once
#include <iostream>

class CalcularEdad {
private:
    static bool esFechaValida(int dia, int mes, int anio);
    static bool esBisiesto(int anio);

public:
    static std::string CalcularAsignarEdad(std::string fechaNacimiento);
};

