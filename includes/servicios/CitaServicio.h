#ifndef CITASERVICIO_H
#define CITASERVICIO_H

#include <vector>
#include <string>
#include "modelos/Cita.h"

class CitaServicio {
private:
    std::string archivo;
    std::vector<Cita> cargarCitas() const;
    bool guardarCitas(const std::vector<Cita>& citas) const;

public:
    CitaServicio(const std::string& archivo);

    bool agregarCita(const Cita& cita);
    std::vector<Cita> obtenerTodasLasCitas() const;
    bool archivoTieneDatos() const;
    bool editarCita(const std::string& duiOriginal, const std::string& fechaOriginal, const std::string& horaOriginal, const std::string& nuevoNombre, const std::string& nuevoTelefono, const std::string& nuevoTratamiento, const std::string& nuevaFecha, const std::string& nuevaHora, const std::string& nuevoMotivo);
    std::vector<Cita> buscarCitasPorDui(const std::string& dui) const;
};

#endif