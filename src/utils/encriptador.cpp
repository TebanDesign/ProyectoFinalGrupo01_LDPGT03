// Descripción: Implementación de funciones de encriptamiento simple

#include "encriptador.h"

std::string encriptar(const std::string& texto, int clave) {
    std::string resultado = texto;
    for (char& c : resultado) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + clave) % 26 + base;
        }
    }
    return resultado;
}

std::string desencriptar(const std::string& texto, int clave) {
    return encriptar(texto, 26 - clave);
}