#define NOMINMAX 
#include <chrono>
#include <thread>
#include <iomanip>
#include <limits>

#include "menu/MenuUtils.h"
#include "menu/MainMenu.h"

// inicializacion de variables estaticas
HANDLE MenuUtils::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
WORD MenuUtils::colorOriginal = 0;

void MenuUtils::configurarConsola() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // obtener color original
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    colorOriginal = consoleInfo.wAttributes;
    
    // configurar el titulo de la ventana
    SetConsoleTitle("Sistema de Gestion Dental - Ratoncito Perez");
    
    // usar redimensionamiento para cambiar tamaño de la pantall
    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow) {
        // Obtener el tamaño de la pantalla
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        
        // redimensionar a un 80% de la pantalla
        int windowWidth = static_cast<int>(screenWidth * 0.8);
        int windowHeight = static_cast<int>(screenHeight * 0.8);
        int posX = (screenWidth - windowWidth) / 2;
        int posY = (screenHeight - windowHeight) / 2;
        
        SetWindowPos(consoleWindow, HWND_TOP, posX, posY, windowWidth, windowHeight, 
                    SWP_SHOWWINDOW | SWP_NOZORDER);
    }
    
    // configurar el buffer de la consola para mejor rendimiento
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    
    COORD newBufferSize;
    newBufferSize.X = 120; // Ancho del buffer
    newBufferSize.Y = 500; // Alto del buffer (permite scroll)
    
    SetConsoleScreenBufferSize(hConsole, newBufferSize);
    
    // configurar el modo de entrada para mejor responsividad
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD inputMode;
    GetConsoleMode(hInput, &inputMode);
    
    // // habilitar modo de entrada extendido, no permite seleccionar y copiar
    // inputMode |= ENABLE_EXTENDED_FLAGS;
    // inputMode &= ~ENABLE_QUICK_EDIT_MODE; // deshabilitar QuickEdit que puede causar cuelgues
    // inputMode |= ENABLE_INSERT_MODE;

    // habilitar modo de entrada extendido, no permite seleccionar y copiar
    inputMode |= ENABLE_EXTENDED_FLAGS;
    inputMode |= ENABLE_QUICK_EDIT_MODE; // deshabilitar QuickEdit que puede causar cuelgues
    inputMode |= ENABLE_INSERT_MODE;
    
    SetConsoleMode(hInput, inputMode);
}

void MenuUtils::cambiarColor(Color fondo, Color texto) {
    SetConsoleTextAttribute(hConsole, (fondo << 4) | texto);
}

void MenuUtils::restaurarColor() {
    SetConsoleTextAttribute(hConsole, colorOriginal);
}

void MenuUtils::limpiarPantalla() {
    // alternativa mas eficiente a system("cls")
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // Fallback al método original si falla
        system("cls");
        return;
    }
    
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    if (!FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten)) {
        system("cls");
        return;
    }
    
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        system("cls");
        return;
    }
    
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
        system("cls");
        return;
    }
    
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void MenuUtils::pausar() {
    std::cout << "\n";
    cambiarColor(NEGRO, AMARILLO);
    std::cout << "Presione cualquier tecla para continuar...";
    restaurarColor();
    
    // flush del buffer antes de esperar entrada
    std::cout.flush();
    _getch();
}

void MenuUtils::mostrarTitulo(const std::string& titulo, Color colorFondo, Color colorTexto) {
    cambiarColor(colorFondo, colorTexto);
    int longitud = titulo.length() + 8;
    
    std::cout << "\n" << std::string(longitud, '=') << std::endl;
    std::cout << "    " << titulo << "    " << std::endl;
    std::cout << std::string(longitud, '=') << std::endl;
    restaurarColor();
    std::cout.flush(); // asegurar que se muestre inmediatamente
}

void MenuUtils::mostrarSubtitulo(const std::string& subtitulo, Color colorTexto) {
    cambiarColor(NEGRO, colorTexto);
    std::cout << "\n>>> " << subtitulo << " <<<" << std::endl;
    restaurarColor();
    std::cout.flush();
}

void MenuUtils::mostrarSeparador(char caracter, int longitud, Color color) {
    cambiarColor(NEGRO, color);
    std::cout << std::string(longitud, caracter) << std::endl;
    restaurarColor();
    std::cout.flush();
}

void MenuUtils::mostrarOpcion(int numero, const std::string& texto, bool habilitada) {
    if (habilitada) {
        cambiarColor(NEGRO, BLANCO);
        std::cout << " ";
        cambiarColor(AZUL_OSCURO, AMARILLO);
        std::cout << " " << numero << " ";
        cambiarColor(NEGRO, BLANCO);
        std::cout << " " << texto << std::endl;
    } else {
        cambiarColor(NEGRO, GRIS);
        std::cout << " [" << numero << "] " << texto << " (No disponible)" << std::endl;
    }
    restaurarColor();
    std::cout.flush();
}

void MenuUtils::mostrarMensaje(const std::string& mensaje, Color color) {
    cambiarColor(NEGRO, color);
    std::cout << mensaje << std::endl;
    restaurarColor();
    std::cout.flush();
}

void MenuUtils::mostrarMensajeExito(const std::string& mensaje) {
    cambiarColor(VERDE_OSCURO, BLANCO);
    std::cout << " [OK] " << mensaje << " ";
    restaurarColor();
    std::cout << std::endl;
    std::cout.flush();
}

void MenuUtils::mostrarMensajeError(const std::string& mensaje) {
    cambiarColor(ROJO_OSCURO, BLANCO);
    std::cout << " [ERROR] " << mensaje << " ";
    restaurarColor();
    std::cout << std::endl;
    std::cout.flush();
}

void MenuUtils::mostrarMensajeAdvertencia(const std::string& mensaje) {
    cambiarColor(AMARILLO_OSCURO, NEGRO);
    std::cout << " [AVISO] " << mensaje << " ";
    restaurarColor();
    std::cout << std::endl;
    std::cout.flush();
}

void MenuUtils::centrarTexto(const std::string& texto, int ancho) {
    int espacios = (ancho - texto.length()) / 2;
    std::cout << std::string(espacios, ' ') << texto << std::endl;
    std::cout.flush();
}

void MenuUtils::mostrarCuadro(const std::vector<std::string>& lineas, Color colorBorde) {
    if (lineas.empty()) return;
    
    // encontrar la linea mas larga
    size_t maxLongitud = 0;
    for (const auto& linea : lineas) {
        if (linea.length() > maxLongitud) {
            maxLongitud = linea.length();
        }
    }
    
    cambiarColor(NEGRO, colorBorde);
    
    // linea superior
    std::cout << "+" << std::string(maxLongitud + 2, '=') << "+" << std::endl;
    
    // lineas de contenido
    for (const auto& linea : lineas) {
        std::cout << "| " << std::left << std::setw(maxLongitud) << linea << " |" << std::endl;
    }
    
    // linea inferior
    std::cout << "+" << std::string(maxLongitud + 2, '=') << "+" << std::endl;
    
    restaurarColor();
    std::cout.flush();
}

int MenuUtils::leerOpcion(int min, int max) {
    int opcion;
    while (true) {
        cambiarColor(NEGRO, AMARILLO);
        std::cout << "\n-> Seleccione una opcion (" << min << "-" << max << "): ";
        restaurarColor();
        std::cout.flush(); // importante: flush antes de leer
        
        if (std::cin >> opcion && opcion >= min && opcion <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        } else {
            mostrarMensajeError("Opcion no valida. Intente de nuevo.");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void MenuUtils::mostrarCargando(const std::string& mensaje, int duracion) {
    cambiarColor(NEGRO, CYAN);
    std::cout << mensaje;
    std::cout.flush(); // flush inicial
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << ".";
            std::cout.flush(); // flush cada punto
            std::this_thread::sleep_for(std::chrono::milliseconds(duracion / 9));
        }
        if (i < 2) {
            std::cout << "\b\b\b   \b\b\b";
            std::cout.flush(); // flush al limpiar
        }
    }
    
    restaurarColor();
    std::cout << std::endl;
    std::cout.flush(); // flush final
}