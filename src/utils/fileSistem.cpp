#include <fstream>
#include <iostream>
#include <filesystem>
#include <windows.h> // Solo en Windows

namespace fs = std::filesystem;

#include "utils/fileSistem.h"

std::string FileSistem::escribirArchivoBinarioOrganizado(
    const std::string& nombreArchivo,
    const std::string& modelo,
    int anio,
    const std::string& mes)
{
    try {
        if (modelo.empty() || nombreArchivo.empty()) {
            throw("Error: El nombre del modelo y archivo son requeridos");
        }

        // Obtener la ruta del ejecutable
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        fs::path exePath = fs::path(buffer).parent_path();

        // Subir un nivel desde /bin a raíz del proyecto
        fs::path projectRoot = exePath.parent_path();

        // Construir la ruta completa
        fs::path rutaCompleta = projectRoot / "Data_ClinicaDentalRP" / modelo;

        if (anio > 0) {
            rutaCompleta /= std::to_string(anio);
        }

        if (!mes.empty()) {
            rutaCompleta /= mes;
        }

        // Crear directorios si no existen
        if (!fs::exists(rutaCompleta)) {
            if (!fs::create_directories(rutaCompleta)) {
                throw("Error: No se pudo crear la ruta");
            }
        }

        // Agregar el nombre del archivo
        rutaCompleta /= nombreArchivo;

        // Crear el archivo si no existe
        std::ofstream archivo(rutaCompleta, std::ios::binary | std::ios::app);
        if (!archivo.is_open()) {
            throw("Error: No se pudo crear el archivo en la ruta");
        }

        archivo.close();
        return rutaCompleta.string();

    } catch (const std::filesystem::filesystem_error& e) {
        throw std::string("Error del sistema de archivos: ") + e.what();
    } catch (const std::exception& e) {
        throw std::string("Error: ") + e.what();
    }
}
