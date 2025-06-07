#pragma oncee
#include <string>

class LoginService {
private:
    /**
     * @brief Indica si la sesion del usuario esta actualmente activa.
     *
     * Se utiliza para controlar el acceso a funcionalidades que requieren autenticacion.
     */
    static bool sesionActiva;
    static const std::string USUARIO;
    static const std::string PASSWORD_ENCRIPTADA;
    static const int MAX_INTENTOS = 3;
    
    /**
     * @brief Lee una contraseña ingresada por el usuario de forma oculta (sin mostrar los caracteres).
     * @return La contraseña ingresada por el usuario como una cadena de texto.
     */
    static std::string leerContrasenaOculta();

    /**
     * @brief Encripta una cadena de texto dada.
     * @param texto La cadena de texto a encriptar.
     * @return La cadena de texto encriptada.
     *
     * Se utiliza para proteger la contraseña.
     */
    static std::string encriptar(const std::string& texto);

    /**
     * @brief Detiene la ejecución del programa por un numero de segundos, mostrando una cuenta regresiva.
     * @param segundos El numero de segundos que el programa esperara.
     *
     * Proporciona un feedback visual al usuario durante una espera forzada.
     */
    static void esperarConCuentaRegresiva(int segundos);
    
public:
    /**
     * @brief Intenta iniciar sesion en el sistema.
     * @return true si el inicio de sesión fue exitoso, false en caso contrario.
     *
     * Solicita credenciales al usuario y las valida contra las predefinidas.
    */ 
    static bool iniciarSesion();

    /**
     * @brief Cierra la sesion activa del usuario.
     *
     * Restablece el estado de la sesion, invalidando el acceso a funcionalidades protegidas.
     */
    static void cerrarSesion();

    /**
     * @brief Verifica si hay una sesion de usuario activa.
     * @return true si hay una sesion activa, false en caso contrario.
     *
     * Permite a otras partes del programa determinar si el usuario esta autenticado.
     */
    static bool esSesionActiva();
};
