#ifndef CITA_H
#define CITA_H

#include <string>

class Cita {
private:
    std::string duiPaciente;
    std::string nombrePaciente; 
    std::string telefonoPaciente; 
    std::string tratamiento;
    std::string fecha;
    std::string hora;
    std::string motivo;

public:
    Cita();
    Cita(const std::string& duiPaciente, const std::string& nombrePaciente, const std::string& telefonoPaciente, const std::string& tratamiento, const std::string& fecha, const std::string& hora, const std::string& motivo);

    // Getters
    std::string getDuiPaciente() const;
    std::string getNombrePaciente() const; 
    std::string getTelefonoPaciente() const; 
    std::string getTratamiento() const;
    std::string getFecha() const;
    std::string getHora() const;
    std::string getMotivo() const;

    // Setters
    void setDuiPaciente(const std::string& dui);
    void setNombrePaciente(const std::string& nombre); 
    void setTelefonoPaciente(const std::string& telefono); 
    void setTratamiento(const std::string& trat);
    void setFecha(const std::string& fec);
    void setHora(const std::string& h);
    void setMotivo(const std::string& m);

    // Método para convertir a string
    std::string toString() const;
};

#endif