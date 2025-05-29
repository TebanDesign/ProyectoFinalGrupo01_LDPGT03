#include <iostream>
#include <iomanip>
#include <sstream>

#include "Paciente.h"
#include "utils/CalcularEdad.h"


// Constructor por defecto
Paciente::Paciente() : nombre(""), dui(""), genero(""), fechaNacimiento(""), edad(""), comentariosSalud("") {}

// constructor con parametros
Paciente::Paciente( std::string& nombre,
                    std::string& dui,
                    std::string& genero,
                    std::string& fechaNacimiento,
                    std::string& comentariosSalud) :
                    nombre(move(nombre)),
                    dui(move(dui)),
                    genero(move(genero)),
                    fechaNacimiento(move(fechaNacimiento)),
                    comentariosSalud(move(comentariosSalud))
                    {
                        this->edad = CalcularEdad::CalcularAsignarEdad(this->fechaNacimiento);
                    }

// getters
std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getDui() const { return dui; }
std::string Paciente::getGenero() const { return genero; }
std::string Paciente::getFechaNacimiento() const { return fechaNacimiento; }
std::string Paciente::getEdad() const { return edad; }
std::string Paciente::getComentariosSalud() const { return comentariosSalud; }

// getters
void Paciente::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Paciente::setDui(const std::string& dui) { this->dui = dui; }
void Paciente::setGenero(const std::string& genero) { this-> genero = genero; }
void Paciente::setFechaNacimiento(const std::string& fecha) { this->fechaNacimiento = fecha; }
// void Paciente::setEdad(const std::string& edad) { this->edad = CalcularEdad::CalcularAsignarEdad(this->fechaNacimiento); }
void Paciente::setComentariosSalud(const std::string& comentarios) { this->comentariosSalud = comentarios; }
