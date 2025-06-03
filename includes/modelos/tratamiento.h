#pragma once

#include <string>
#include <vector> // Necesario para las funciones auxiliares

// Clase que representa un tratamiento asignado a un paciente
class Tratamiento {
private:
    std::string duiPaciente;
    std::string medicamento;
    std::string dosis;
    std::string frecuencia;
    std::string duracion;
    std::string observaciones;
    std::string estado; // Ej: Activo, Finalizado, Eliminado

public:
    // Constructor
    Tratamiento(std::string dui = "", std::string med = "", std::string dos = "", std::string frec = "",
                std::string dur = "", std::string obs = "", std::string est = "");

    // Métodos de operación
    void registrar();           // Permite ingresar un nuevo tratamiento
    void mostrar() const;       // Muestra los detalles de un tratamiento
    void editar();              // Permite modificar los campos de un tratamiento
    void eliminar();            // Marca el tratamiento como eliminado (estado)

    // Utilidad
    bool coincideCon(const std::string& dui, const std::string& med) const;

    // Getters
    std::string getDUI() const;
    std::string getMedicamento() const;
    std::string getDosis() const;
    std::string getFrecuencia() const;
    std::string getDuracion() const;
    std::string getObservaciones() const;
    std::string getEstado() const;
};

// Funciones auxiliares
void editarTratamientoEnArchivo(const std::string& dui, const std::string& med);
void eliminarTratamientoEnArchivo(const std::string& dui, const std::string& med);
std::vector<Tratamiento> cargarTratamientosDesdeArchivo();
void mostrarTratamientosPorDUI(const std::string& dui);