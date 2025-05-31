#include "servicios/CitaServicio.h"
#include "modelos/Cita.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

CitaServicio::CitaServicio(const std::string& archivo) : archivo(archivo) {}

std::vector<Cita> CitaServicio::cargarCitas() const {
    std::ifstream in(archivo);
    std::vector<Cita> citas;
    std::string linea;

    if (in.is_open()) {
        while (std::getline(in, linea)) {
            std::stringstream ss(linea);
            std::string segmento;
            std::vector<std::string> campos;
            while (std::getline(ss, segmento, '|')) {
                campos.push_back(segmento);
            }
            if (campos.size() == 7) { // Ahora esperamos 7 campos
                citas.emplace_back(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6]);
            } else {
                std::cerr << "Advertencia: Línea malformada en el archivo: " << linea << std::endl;
            }
        }
        in.close();
    }
    return citas;
}

bool CitaServicio::guardarCitas(const std::vector<Cita>& citas) const {
    std::ofstream out(archivo);
    if (out.is_open()) {
        for (const auto& cita : citas) {
            out << cita.toString() << "\n";
        }
        out.close();
        return true;
    }
    return false;
}

bool CitaServicio::agregarCita(const Cita& cita) {
    std::ofstream out(archivo, std::ios::app);
    if (!out.is_open()) return false;
    out << cita.toString() << "\n";
    out.close();
    return true;
}

std::vector<Cita> CitaServicio::obtenerTodasLasCitas() const {
    return cargarCitas();
}

bool CitaServicio::archivoTieneDatos() const {
    std::ifstream in(archivo);
    if (!in.is_open()) {
        return false;
    }
    bool tieneDatos = in.peek() != std::ifstream::traits_type::eof();
    in.close();
    return tieneDatos;
}

bool CitaServicio::editarCita(const std::string& duiOriginal, const std::string& fechaOriginal, const std::string& horaOriginal, const std::string& nuevoNombre, const std::string& nuevoTelefono, const std::string& nuevoTratamiento, const std::string& nuevaFecha, const std::string& nuevaHora, const std::string& nuevoMotivo) {
    std::vector<Cita> citas = cargarCitas();
    for (auto& cita : citas) {
        if (cita.getDuiPaciente() == duiOriginal && cita.getFecha() == fechaOriginal && cita.getHora() == horaOriginal) {
            cita.setNombrePaciente(nuevoNombre);
            cita.setTelefonoPaciente(nuevoTelefono);
            cita.setTratamiento(nuevoTratamiento);
            cita.setFecha(nuevaFecha);
            cita.setHora(nuevaHora);
            cita.setMotivo(nuevoMotivo);
            return guardarCitas(citas);
        }
    }
    return false; // No se encontró la cita
}

std::vector<Cita> CitaServicio::buscarCitasPorDui(const std::string& dui) const {
    std::vector<Cita> todasLasCitas = cargarCitas();
    std::vector<Cita> resultados;
    for (const auto& cita : todasLasCitas) {
        if (cita.getDuiPaciente() == dui) {
            resultados.push_back(cita);
        }
    }
    return resultados;
}