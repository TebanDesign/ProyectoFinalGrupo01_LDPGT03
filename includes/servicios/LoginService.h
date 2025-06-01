#pragma oncee
#include <string>

class LoginService {
private:
    static bool sesionActiva;
    static const std::string USUARIO;
    static const std::string PASSWORD_ENCRIPTADA;
    static const int MAX_INTENTOS = 3;
    
    static std::string leerContrasenaOculta();
    static std::string encriptar(const std::string& texto);
    static void esperarConCuentaRegresiva(int segundos);
    
public:
    static bool iniciarSesion();
    static void cerrarSesion();
    static bool esSesionActiva();
};
