#pragma once
#include <iostream>

class CalcularEdad {
private:
    static bool esFechaValida(int dia, int mes, int anio);
    static bool esBisiesto(int anio);

public:

    /**
     * @brief Calcula la edad a partir de una fecha de nacimiento y la asigna al formato de texto.
     * @param fechaNacimiento La fecha de nacimiento en formato de cadena (ej. "DD/MM/YYYY").
     * @return Una cadena de texto que representa la edad calculada.
     */
    static std::string CalcularAsignarEdad(std::string fechaNacimiento);
};

