#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // Para _getch en Windows

#ifdef _WIN32
#include <windows.h> // Solo en sistemas Windows
#else
#include <unistd.h> // Alternativa para sistemas Unix (no utilizada en este código)
#endif

#include "LoginService.h"
#include "menu/MenuUtils.h"

// Inicialización de variables estáticas de la clase LoginService
bool LoginService::sesionActiva = false;
const std::string LoginService::USUARIO = "admin";
const std::string LoginService::PASSWORD_ENCRIPTADA = encriptar("1234"); // Se guarda la contraseña encriptada

// Método para iniciar sesión
bool LoginService::iniciarSesion() {
    int intentos = 0; // Contador de intentos fallidos

    while (true) {
        // Limpia pantalla y muestra encabezados
        MenuUtils::limpiarPantalla();
        MenuUtils::mostrarTitulo("SISTEMA DE GESTIÓN DENTAL", MenuUtils::AZUL, MenuUtils::BLANCO);
        MenuUtils::mostrarSubtitulo("INICIO DE SESIÓN", MenuUtils::CYAN);

        std::string usuario, contrasena;

        // Solicita nombre de usuario
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::AMARILLO);
        std::cout << "\nUsuario: ";
        MenuUtils::restaurarColor();
        std::getline(std::cin, usuario);

        // Solicita contraseña (oculta al escribir)
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::AMARILLO);
        std::cout << "Contraseña: ";
        MenuUtils::restaurarColor();
        contrasena = leerContrasenaOculta();

        // Verifica credenciales
        if (usuario == USUARIO && encriptar(contrasena) == PASSWORD_ENCRIPTADA) {
            MenuUtils::mostrarMensajeExito("Inicio de sesión exitoso.");
            sesionActiva = true; // Marca la sesión como activa
            MenuUtils::pausar();
            return true;
        } else {
            MenuUtils::mostrarMensajeError("Credenciales incorrectas.");
            intentos++; // Incrementa el contador de intentos fallidos
        }

        // Si se excede el número máximo de intentos, espera antes de permitir más intentos
        if (intentos == MAX_INTENTOS) {
            MenuUtils::mostrarMensajeAdvertencia("Demasiados intentos.");
            esperarConCuentaRegresiva(30); // Espera 30 segundos
            intentos = 0; // Reinicia contador de intentos
        } else {
            MenuUtils::pausar(); // Espera una tecla antes de volver a intentar
        }
    }
}

// Método para cerrar sesión
void LoginService::cerrarSesion() {
    sesionActiva = false; // Marca la sesión como inactiva
    MenuUtils::limpiarPantalla();
    MenuUtils::mostrarMensajeExito("Sesión cerrada correctamente.");
    MenuUtils::pausar();
}

// Verifica si hay una sesión activa
bool LoginService::esSesionActiva() {
    return sesionActiva;
}

// Método para leer contraseña oculta (con asteriscos)
std::string LoginService::leerContrasenaOculta() {
    std::string contrasena;
    char c;
    while ((c = _getch()) != '\r') { // Termina con Enter (carácter '\r')
        if (c == '\b') { // Retroceso
            if (!contrasena.empty()) {
                std::cout << "\b \b"; // Borra un carácter en pantalla
                contrasena.pop_back(); // Elimina el último carácter de la contraseña
            }
        } else {
            contrasena.push_back(c); // Agrega el carácter a la contraseña
            std::cout << '*'; // Muestra asterisco en vez del carácter real
        }
    }
    std::cout << '\n';
    return contrasena;
}

// Método de encriptación tipo César (desplazamiento de 3 posiciones)
std::string LoginService::encriptar(const std::string& texto) {
    int clave = 3;
    std::string resultado = texto;
    for (char& c : resultado) {
        if (isalpha(c)) { // Solo encripta letras
            char base = islower(c) ? 'a' : 'A'; // Determina base según mayúscula/minúscula
            c = (c - base + clave) % 26 + base; // Aplica desplazamiento
        }
    }
    return resultado;
}

// Espera con cuenta regresiva visible (segundos)
void LoginService::esperarConCuentaRegresiva(int segundos) {
    for (int i = segundos; i > 0; --i) {
        MenuUtils::cambiarColor(MenuUtils::NEGRO, MenuUtils::ROJO_OSCURO);
        std::cout << "\rDemasiados intentos. Esperando " << i << "s..." << std::flush;
        MenuUtils::restaurarColor();
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo
    }
    std::cout << "\r" << std::string(50, ' ') << "\r"; // Limpia la línea anterior
    MenuUtils::mostrarMensajeAdvertencia("Puedes intentar nuevamente.");
}
