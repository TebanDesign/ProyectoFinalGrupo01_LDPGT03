#pragma once
#include <string> 

/**
 * @brief clase utilitaria para validar cadenas de texto como fechas en formato DD/MM/AAAA.
 */
class Validaciones {
public:
    /**
     * @brief valida si una cadena de texto representa una fecha válida en formato DD/MM/AAAA.
     * @param fechaStr La cadena de texto a validar.
     * @return true si la cadena es una fecha válida, false en caso contrario.
     */
    static bool validarFecha(const std::string& fechaStr);

    /**
     * @brief valida si una cadena de texto representa un DUI válido en formato "00000000-0".
     * Esta funcion valida el formato y que todos los caracteres esperados sean digitos.
     * @param idStr La cadena de texto a validar.
     * @return true si la cadena es un identificador válido, false en caso contrario.
     */
    static bool validarDUI(const std::string& idStr);


    /**
     * @brief Verifica si una fecha de vencimiento dada ha caducado.
     * @param fechaVencimiento La fecha de vencimiento en formato de cadena (ej. "DD/MM/YYYY").
     * @return `true` si la fecha de vencimiento ya paso, `false` en caso contrario.
     */
    static bool estaVencido(const std::string& fechaVencimiento);
    
    /**
     * @brief Compara dos fechas dadas en formato de cadena (DD/MM/AAAA).
     *
     * Esta función convierte ambas fechas a un formato numérico entero (AAAAMMDD)
     * para realizar una comparación directa y determinar su orden cronológico.
     *
     * @param fecha1 La primera fecha a comparar, en formato "DD/MM/AAAA".
     * @param fecha2 La segunda fecha a comparar, en formato "DD/MM/AAAA".
     * @return Un entero que indica la relación entre las dos fechas:
     * - **-1** si `fecha1` es cronologicamente anterior a `fecha2`.
     * - **0** si `fecha1` es igual a `fecha2`.
     * - **1** si `fecha1` es cronologicamente posterior a `fecha2`.
     */
    static int compararFechas(const std::string& fecha1, const std::string& fecha2);

private:
    /**
     * @brief funcion auxiliar para determinar si un año es bisiesto.
     * @param anio El año a verificar.
     * @return true si el año es bisiesto, false en caso contrario.
     */
    static bool esBisiesto(int anio);

    /**
     * @brief funcion auxiliar para verificar si un caracter es un digito.
     * @param c El caracter a verificar.
     * @return true si el caracter es un digito, false en caso contrario.
     */
    static bool esDigito(char c);
};
