#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#include "utils/fileSistem.h"

std::string  FileSistem::escribirArchivoBinarioOrganizado(
    const std::string& nombreArchivo,
    const std::string& modelo,
    int anio,
    const std::string& mes)
{
    try {

        if (modelo.empty() || nombreArchivo.empty()) {
                 throw("Error: El nombre del modleo y archivo son requeridos");
            }

        // Construir la ruta base con el modelo
        fs::path rutaCompleta = fs::current_path() / "Data_ClinicaDentalRP" / modelo;

        // Construir la ruta jeraquica

        // Se creara una carpeta con el año 
         if (anio > 0) {
            rutaCompleta = rutaCompleta / std::to_string(anio);
        }
        
        // Se creara una carpeta con el mes
        if (!mes.empty()) {
            rutaCompleta = rutaCompleta / mes;
        }
        
      // Crear los directorios si no existen
        if (!std::filesystem::exists(rutaCompleta)) {
            if (!std::filesystem::create_directories(rutaCompleta)) {
                throw("Error: No se pudo crear la ruta");
            }
        }

        // Agregar el nombre del archivo a la ruta
        rutaCompleta = rutaCompleta / nombreArchivo;
        
        // Crear el archivo binario
        std::ofstream archivo(rutaCompleta, std::ios::binary  | std::ios::app);
        if (!archivo.is_open()) {
            throw("Error: No se pudo crear el archivo en la ruta");
        }

        archivo.close();

        return rutaCompleta.string();

    } catch (const std::filesystem::filesystem_error& e) {

        std::string mensaje_completo = "Error del sistema de archivos: "  + std::string(e.what());
        throw(mensaje_completo);

    } catch (const std::exception& e) {
        
        std::string mensaje_completo = "Error: " + std::string(e.what());
        throw(mensaje_completo);

    }
}
