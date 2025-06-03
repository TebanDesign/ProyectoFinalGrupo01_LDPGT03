#include "servicios/CitaServicio.h" 
#include "modelos/Cita.h"            
#include <fstream>                   
#include <sstream>                   
#include <iostream>                  
#include <vector>                    
#include <stdexcept>                 
#include "utils/fileSistem.h"        

// Constructor: Ahora utiliza FileSistem para obtener la ruta completa del archivo
CitaServicio::CitaServicio(const std::string& nombreArchivoBase) {
    try {
        
        this->rutaArchivo = FileSistem::escribirArchivoBinarioOrganizado(
            nombreArchivoBase, "Citas", 0, ""
        );
        std::ofstream archivo(rutaArchivo, std::ios::app);
        archivo.close();
    } catch (const std::exception& e) {
        std::cerr << "Error al inicializar CitaServicio: " << e.what() << std::endl;
        throw; // Re-lanzar la excepción para que sea manejada en un nivel superior
    }
}

// Carga todas las citas desde el archivo de texto delimitado
std::vector<Cita> CitaServicio::cargarCitas() const { // <-- Const aquí
    std::ifstream in(rutaArchivo); // Usar rutaArchivo
    std::vector<Cita> citas;
    std::string linea;

    if (!in.is_open()) {
        return citas;
    }

    while (std::getline(in, linea)) {
        std::stringstream ss(linea);
        std::string segmento;
        std::vector<std::string> campos;

        while (std::getline(ss, segmento, '|')) {
            campos.push_back(segmento);
        }
        // Se espera 7 campos (DUI, Nombre, Teléfono, Tratamiento, Fecha, Hora, Motivo)
        if (campos.size() == 7) {
            citas.emplace_back(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6]);
        } else {
            std::cerr << "Advertencia: Línea malformada en el archivo de citas: " << linea << std::endl;
        }
    }
    in.close();
    return citas;
}

// Guarda un vector de objetos Cita en el archivo de texto, sobrescribiendo el contenido
bool CitaServicio::guardarCitas(const std::vector<Cita>& citas) const { 
    std::ofstream out(rutaArchivo, std::ios::trunc); // Usar rutaArchivo, sobrescribir (trunc)
    if (!out.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar citas: " << rutaArchivo << std::endl;
        return false;
    }

    for (const auto& cita : citas) {
        out << cita.toString() << "\n";
    }
    out.close();
    return true;
}

// Agrega una única cita al final del archivo
bool CitaServicio::agregarCita(const Cita& cita) {
    try {
        // Verificar si la cita ya existe (DUI, Fecha, Hora) antes de agregar
        std::vector<Cita> citasExistentes = cargarCitas(); 
        for (const auto& c : citasExistentes) {
            if (c.getDuiPaciente() == cita.getDuiPaciente() &&
                c.getFecha() == cita.getFecha() &&
                c.getHora() == cita.getHora()) {
                return false; // La cita ya existe, no agregar
            }
        }

        std::ofstream out(rutaArchivo, std::ios::app); // Usar rutaArchivo, modo append
        if (!out.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo para agregar cita: " + rutaArchivo);
        }
        out << cita.toString() << "\n";
        out.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error al agregar cita: " << e.what() << std::endl;
        return false; // Retornar false en caso de error
    }
}

// Retorna todas las citas cargadas desde el archivo.
std::vector<Cita> CitaServicio::obtenerTodasLasCitas() const {
    try {
        return cargarCitas(); 
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener todas las citas: " << e.what() << std::endl;
        return {};
    }
}

// Verifica si el archivo de citas contiene datos.
bool CitaServicio::archivoTieneDatos() const {
    std::ifstream in(rutaArchivo); // Usar rutaArchivo
    if (!in.is_open()) {
        return false;
    }
    bool tieneDatos = in.peek() != std::ifstream::traits_type::eof();
    in.close();
    return tieneDatos;
}

// Edita una cita específica.
bool CitaServicio::editarCita(const std::string& duiOriginal, const std::string& fechaOriginal, const std::string& horaOriginal,
                              const Cita& citaActualizada) { 
    try {
        std::vector<Cita> citas = cargarCitas(); // Carga todas las citas existentes.
        bool encontrada = false;

        for (auto& cita : citas) {
            if (cita.getDuiPaciente() == duiOriginal && cita.getFecha() == fechaOriginal && cita.getHora() == horaOriginal) {
                // Validación para evitar duplicados al cambiar DUI/Fecha/Hora
                // Solo se verifica si los identificadores de la cita actualizada son diferentes a los originales.
                if ((citaActualizada.getDuiPaciente() != duiOriginal ||
                     citaActualizada.getFecha() != fechaOriginal ||
                     citaActualizada.getHora() != horaOriginal) &&
                    buscarCita(citaActualizada.getDuiPaciente(), citaActualizada.getFecha(), citaActualizada.getHora()).getDuiPaciente() != "")
                {
                    // La nueva combinación de DUI/Fecha/Hora ya existe para otra cita.
                    std::cerr << "Error de edición: La nueva combinación DUI/Fecha/Hora ya existe para otra cita." << std::endl;
                    return false;
                }

                // Actualiza todos los campos de la cita con los nuevos valores.
                cita.setNombrePaciente(citaActualizada.getNombrePaciente());
                cita.setTelefonoPaciente(citaActualizada.getTelefonoPaciente());
                cita.setTratamiento(citaActualizada.getTratamiento());
                cita.setFecha(citaActualizada.getFecha());
                cita.setHora(citaActualizada.getHora());
                cita.setMotivo(citaActualizada.getMotivo());
                encontrada = true;
                break;
            }
        }

        if (encontrada) {
            return guardarCitas(citas); // Guarda el vector de citas actualizado y retorna el resultado.
        }
        return false; // Retorna false si no se encontró ninguna cita que coincida con los criterios originales.
    } catch (const std::exception& e) {
        std::cerr << "Error al editar cita: " << e.what() << std::endl;
        return false;
    }
}

// Busca y retorna un objeto Cita por sus identificadores (DUI, fecha, hora).
// Retorna un objeto Cita vacío si no se encuentra.
Cita CitaServicio::buscarCita(const std::string& dui, const std::string& fecha, const std::string& hora) const { // <-- Firma corregida y 'const'
    try {
        std::vector<Cita> todasLasCitas = cargarCitas();
        for (const auto& cita : todasLasCitas) {
            if (cita.getDuiPaciente() == dui && cita.getFecha() == fecha && cita.getHora() == hora) {
                return cita;
            }
        }
        return Cita(); // Retorna una Cita vacía si no se encuentra
    } catch (const std::exception& e) {
        std::cerr << "Error al buscar cita por clave: " << e.what() << std::endl;
        return Cita(); // Retorna una Cita vacía en caso de error
    }
}


// Busca citas por el DUI del paciente.
std::vector<Cita> CitaServicio::buscarCitasPorDui(const std::string& dui) const {
    std::vector<Cita> resultados;
    try {
        std::vector<Cita> todasLasCitas = cargarCitas(); 
        for (const auto& cita : todasLasCitas) {
            if (cita.getDuiPaciente() == dui) {
                resultados.push_back(cita);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al buscar citas por DUI: " << e.what() << std::endl;
    }
    return resultados;
}