#include "modelos/Cita.h"
#include <iostream>
#include <string>

// Constructor por defecto
Cita::Cita() : duiPaciente(""), nombrePaciente(""), telefonoPaciente(""), tratamiento(""), fecha(""), hora(""), motivo("") {}

// Constructor con todos los campos
Cita::Cita(const std::string& duiPaciente,
           const std::string& nombrePaciente,
           const std::string& telefonoPaciente,
           const std::string& tratamiento,
           const std::string& fecha,
           const std::string& hora,
           const std::string& motivo)
    : duiPaciente(duiPaciente),
      nombrePaciente(nombrePaciente),
      telefonoPaciente(telefonoPaciente),
      tratamiento(tratamiento),
      fecha(fecha),
      hora(hora),
      motivo(motivo) {}

// Getters
std::string Cita::getDuiPaciente() const { return duiPaciente; }
std::string Cita::getNombrePaciente() const { return nombrePaciente; }
std::string Cita::getTelefonoPaciente() const { return telefonoPaciente; }
std::string Cita::getTratamiento() const { return tratamiento; }
std::string Cita::getFecha() const { return fecha; }
std::string Cita::getHora() const { return hora; }
std::string Cita::getMotivo() const { return motivo; }

// Setters
void Cita::setDuiPaciente(const std::string& dui) { duiPaciente = dui; }
void Cita::setNombrePaciente(const std::string& nombre) { nombrePaciente = nombre; }
void Cita::setTelefonoPaciente(const std::string& telefono) { telefonoPaciente = telefono; }
void Cita::setTratamiento(const std::string& trat) { tratamiento = trat; }
void Cita::setFecha(const std::string& fec) { fecha = fec; }
void Cita::setHora(const std::string& h) { hora = h; }
void Cita::setMotivo(const std::string& m) { motivo = m; }

// Método para convertir la cita a una cadena (útil para guardar en el archivo)
std::string Cita::toString() const {
    return duiPaciente + "|" + nombrePaciente + "|" + telefonoPaciente + "|" + tratamiento + "|" + fecha + "|" + hora + "|" + motivo;
}