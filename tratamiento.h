// Descripción: Clase orientada a objetos para la gestión de tratamientos

#ifndef TRATAMIENTO_H
#define TRATAMIENTO_H

#include "Registro.h"
#include <string>
#include <vector>

class Tratamiento : public Registro {
private:
    std::string duiPaciente;
    std::string medicamento;
    std::string dosis;
    std::string frecuencia;
    std::string duracion;
    std::string observaciones;
    std::string estado;

public:
    // Constructores
    Tratamiento() = default;
    Tratamiento(std::string dui, std::string med, std::string dos, std::string frec,
                std::string dur, std::string obs, std::string est);

    // Métodos heredados
    void registrar() override;
    void mostrar() const override;
    void editar() override;
    void eliminar() override;

    // Métodos de utilidad
    bool coincideCon(const std::string& dui, const std::string& med) const;

    // Métodos de acceso (getters)
    std::string getDUI() const;
    std::string getMedicamento() const;
    std::string getEstado() const;
    std::string getDosis() const;
    std::string getFrecuencia() const;
    std::string getDuracion() const;
    std::string getObservaciones() const;
};

// Funciones complementarias
std::vector<Tratamiento> cargarTratamientosDesdeArchivo();
void mostrarTratamientosPorDUI(const std::string& dui);
void editarTratamientoEnArchivo(const std::string& dui, const std::string& med);
void eliminarTratamientoEnArchivo(const std::string& dui, const std::string& med);

#endif