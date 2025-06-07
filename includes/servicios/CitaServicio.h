#ifndef CITASERVICIO_H
#define CITASERVICIO_H

#include <vector>
#include <string>
#include <fstream> 
#include "modelos/Cita.h" 

// Declaración de la clase CitaServicio.
// Esta clase proporciona servicios para gestionar operaciones de citas, como cargar, guardar,
// agregar, obtener, editar y buscar citas desde y hacia un archivo.
class CitaServicio {
private:
    std::string rutaArchivo; // Ruta completa al archivo de citas (gestionada por FileSistem)

    // Método privado para cargar citas desde el archivo.
    std::vector<Cita> cargarCitas() const; // <-- Mantenemos 'const' aquí si la implementación lo es
    // Método privado para guardar una lista de citas en el archivo.
    bool guardarCitas(const std::vector<Cita>& citas) const; // <-- Mantenemos 'const' aquí si la implementación lo es

public:
    // Constructor que inicializa el nombre del archivo de datos.
    // Recibe el nombre base del archivo ("citas.dat").
    CitaServicio(const std::string& nombreArchivoBase);

    // Agrega una nueva cita al archivo.
    bool agregarCita(const Cita& cita);
    // Obtiene todas las citas registradas en el archivo.
    std::vector<Cita> obtenerTodasLasCitas() const;
    // Verifica si el archivo de citas contiene algún dato.
    bool archivoTieneDatos() const;

    // Edita una cita existente identificada por su DUI, fecha y hora originales,
    // actualizando sus campos con los valores de un objeto Cita actualizado.
    bool editarCita(const std::string& duiOriginal, const std::string& fechaOriginal, const std::string& horaOriginal,
                    const Cita& citaActualizada); 

    // Busca y retorna un objeto Cita por sus identificadores (DUI, fecha, hora).
    // Retorna un objeto Cita vacío si no se encuentra.
    Cita buscarCita(const std::string& dui, const std::string& fecha, const std::string& hora) const; // <-- Nueva firma

    // Busca y retorna todas las citas asociadas a un DUI de paciente específico.
    std::vector<Cita> buscarCitasPorDui(const std::string& dui) const;
};

#endif 