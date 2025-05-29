#include "utils/login.h"
#include "utils/encriptador.h"
#include "menu/MenuUtils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // Para _getch en Windows

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

const std::string USUARIO = "admin";
const std::string PASSWORD_ENCRIPTADA = encriptar("1234"); // puedes cambiar la contraseña

std::string leerContrasenaOculta() {
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

void esperarConCuentaRegresiva(int segundos) {
    for (int i = segundos; i > 0; --i) {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::ROJO_OSCURO);
        std::cout << "\rDemasiados intentos. Esperando " << i << "s..." << std::flush;
        MenuUtils::restaurarColor();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\r" << std::string(50, ' ') << "\r"; // Limpiar línea
    MenuUtils::mostrarMensajeAdvertencia("Puedes intentar nuevamente.");
}

bool iniciarSesion() {
    const int MAX_INTENTOS = 3;
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
