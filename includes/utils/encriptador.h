// Descripción: Declaración de funciones de encriptamiento simple

#ifndef ENCRIPTADOR_H
#define ENCRIPTADOR_H

#include <string>

std::string encriptar(const std::string& texto, int clave = 3);
std::string desencriptar(const std::string& texto, int clave = 3);

#endif