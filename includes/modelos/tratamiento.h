#pragma once

#include <string>
#include <vector>

class Tratamiento {
private:
    std::string duiPaciente;
    std::string medicamento;
    std::string dosis;
    std::string frecuencia;
    std::string duracion;
    std::string observaciones;
    std::string estado;

public:
    Tratamiento(std::string dui = "", std::string med = "", std::string dos = "", std::string frec = "",
                std::string dur = "", std::string obs = "", std::string est = "");

    void registrar();
    void mostrar() const;
    void editar();
    void eliminar();

    bool coincideCon(const std::string& dui, const std::string& med) const;

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