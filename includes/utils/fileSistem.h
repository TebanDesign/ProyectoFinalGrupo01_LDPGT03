
#pragma once
#include <string>

class FileSistem {
public:

    /**
     * @brief crea un archivo binario organizado en la estructura modelo/año/mes
     * 
     * @param modelo Obligatorio: Nombre del modelo (primero nivel de directorio) (eje. Pacientes)
     * @param nombreArchivo Obligatorio: Nombre del archivo a crear (eje. Pacientes.dat)
     * @param anio Opcional: Año (segundo nivel de directorio)
     * @param mes  Opcional: Mes (tercer nivel de directorio)
     * @return std::string Ruta del archivo creado
     * 
     * @note Si el año es igual a 0 (valor por defecto), se omite el nivel de directorio del año
     * @note Si el mes es una cadena vacia (valor por defecto), se omite el nivel de directorio del mes
     */
    static std::string escribirArchivoBinarioOrganizado(
            const std::string& nombreArchivo,
            const std::string& modelo,
            int anio = 0,
            const std::string& mes = ""
        );

};
