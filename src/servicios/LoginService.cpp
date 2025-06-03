#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // Para _getch en Windows

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "LoginService.h"
#include "menu/MenuUtils.h"

// inicializar variables estaticas
bool LoginService::sesionActiva = false;
const std::string LoginService::USUARIO = "admin";
const std::string LoginService::PASSWORD_ENCRIPTADA = encriptar("1234");

bool LoginService::iniciarSesion() {
    int intentos = 0;

    while (true) {
        MenuUtils::limpiarPantalla();
        MenuUtils::mostrarTitulo("SISTEMA DE GESTIÓN DENTAL", MenuUtils::AZUL, MenuUtils::BLANCO);
        MenuUtils::mostrarSubtitulo("INICIO DE SESIÓN", MenuUtils::CYAN);

        std::string usuario, contrasena;
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::AMARILLO);
        std::cout << "\nUsuario: ";
        MenuUtils::restaurarColor();
        std::getline(std::cin, usuario);

        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::AMARILLO);
        std::cout << "Contraseña: ";
        MenuUtils::restaurarColor();
        contrasena = leerContrasenaOculta();

        if (usuario == USUARIO && encriptar(contrasena) == PASSWORD_ENCRIPTADA) {
            MenuUtils::mostrarMensajeExito("Inicio de sesión exitoso.");
            sesionActiva = true;
            MenuUtils::pausar();
            return true;
        } else {
            MenuUtils::mostrarMensajeError("Credenciales incorrectas.");
            intentos++;
        }

        if (intentos == MAX_INTENTOS) {
            MenuUtils::mostrarMensajeAdvertencia("Demasiados intentos.");
            esperarConCuentaRegresiva(30);
            intentos = 0;
        } else {
            MenuUtils::pausar();
        }
    }
}

void LoginService::cerrarSesion() {
    sesionActiva = false;
    MenuUtils::limpiarPantalla();
    MenuUtils::mostrarMensajeExito("Sesión cerrada correctamente.");
    MenuUtils::pausar();
}

bool LoginService::esSesionActiva() {
    return sesionActiva;
}

std::string LoginService::leerContrasenaOculta() {
     std::string contrasena;
    char c;
    while ((c = _getch()) != '\r') { // Enter
        if (c == '\b') {
            if (!contrasena.empty()) {
                std::cout << "\b \b";
                contrasena.pop_back();
            }
        } else {
            contrasena.push_back(c);
            std::cout << '*';
        }
    }
    std::cout << '\n';
    return contrasena;
}

std::string LoginService::encriptar(const std::string& texto) {
    int clave = 3;
    std::string resultado = texto;
    for (char& c : resultado) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + clave) % 26 + base;
        }
    }
    return resultado;
}

void LoginService::esperarConCuentaRegresiva(int segundos) {
    for (int i = segundos; i > 0; --i) {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::ROJO_OSCURO);
        std::cout << "\rDemasiados intentos. Esperando " << i << "s..." << std::flush;
        MenuUtils::restaurarColor();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\r" << std::string(50, ' ') << "\r"; // Limpiar línea
    MenuUtils::mostrarMensajeAdvertencia("Puedes intentar nuevamente.");
}
