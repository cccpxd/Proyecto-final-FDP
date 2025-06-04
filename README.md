# Proyecto-final-FDP
# Documentación del Sistema FAP

## Descripción General
El Sistema FAP (Fondo de Ahorro y Préstamos) es una aplicación de consola desarrollada en C++ que permite gestionar usuarios, préstamos y pagos para una cooperativa o fondo de ahorros. El sistema distingue entre tres tipos de usuarios: administradores, socios y terceros, cada uno con diferentes permisos y funcionalidades.

## Autor
- **Nombre:** Cristian Camilo Colorado Posada
- **Correo:** cccoloradop@correo.usbcali.edu.co

## Características Principales
- Gestión de usuarios (creación y autenticación)
- Solicitud y aprobación de préstamos
- Sistema de pagos y cuotas
- Reportes financieros
- Manejo de ahorros para socios
- Sistema de codeudoría para préstamos

## Estructura del Código

### Archivos de Datos
El sistema utiliza los siguientes archivos para persistencia de datos:
- `usuarios.txt`: Almacena información de usuarios
- `prestamos.txt`: Almacena información de préstamos
- `pagos.txt`: Registro histórico de pagos
- `fondo.txt`: Almacena el fondo recuperado por pagos

### Estructuras de Datos
- Arreglos estáticos para almacenar:
  - Usuarios (máximo 100)
  - Préstamos (máximo 100)

### Funciones 

#### Funciones Auxiliares
- `cargarDatos()`: Carga datos desde archivos al iniciar
- `guardarDatos()`: Guarda datos en archivos al salir
- `registrarPago()`: Registra pagos en archivo

#### Funciones de Usuarios
- `login()`: Autentica usuarios
- `agregarUsuario()`: Crea nuevos usuarios

#### Funciones de Préstamos
- `solicitarPrestamoSocio()`: Solicitud para socios
- `solicitarPrestamoTercero()`: Solicitud para terceros
- `aprobarPrestamos()`: Aprobación por administrador
- `aceptarCodeudor()`: Aceptación por codeudor

#### Funciones de Pagos
- `realizarPago()`: Proceso de pago de cuotas
- `pagoAhorroSocio()`: Pago de ahorro mensual para socios

#### Reportes
- `mostrarEstadoCuenta()`: Estado individual
- `mostrarReporteAhorros()`: Reporte general de ahorros
- `mostrarGanancias()`: Reporte de ganancias

### Menús
- `menuSocio()`: Menú para usuarios tipo socio
- `menuTercero()`: Menú para usuarios tipo tercero
- `menuAdmin()`: Menú para administradores

## Requisitos del Sistema
- Compilador C++ compatible con C++11
- Sistema operativo: Windows/Linux/macOS
- Espacio en disco: mínimo 1MB

## Instrucciones de Compilación
1. Guardar el código en un archivo `sistema_fap.cpp`
2. Compilar con: `g++ sistema_fap.cpp -o sistema_fap`
3. Ejecutar: `./sistema_fap` (Linux/macOS) o `sistema_fap.exe` (Windows)

## Uso del Sistema
1. Iniciar sesión con credenciales válidas
2. Seguir las opciones del menú según el tipo de usuario
3. Los datos se guardan automáticamente al salir

## Consideraciones
- El sistema utiliza arreglos estáticos con límite de 100 registros
- Los archivos de datos se crean automáticamente en la primera ejecución
- Se recomienda hacer copias de seguridad periódicas de los archivos `.txt`

## Licencia
Este software se proporciona "tal cual" sin garantías de ningún tipo. El autor no se hace responsable por cualquier pérdida o daño causado por el uso de este sistema.
