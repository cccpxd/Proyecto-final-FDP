//Cristian Camilo Colorado Posada
//cccoloradop@correo.usbcali.edu.co

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // para setprecision
using namespace std;

// arreglos para usuarios
string nombresUsuarios[100];
string contrasenasUsuarios[100];
string tiposUsuarios[100];
float ahorrosUsuarios[100];
int totalUsuarios = 0;

// arreglos para préstamos
string solicitantesPrestamos[100];
float montosPrestamos[100];
int cuotasPrestamos[100];
float interesesPrestamos[100];
string codeudoresPrestamos[100];
int cuotasPagadasPrestamos[100];
string estadoPrestamos[100];
int totalPrestamos = 0;

// Variable global para fondo recuperado por pagos de cuotas
float fondoRecuperado = 0;

// FUNCIONES AUXILIARES
// Esta funcion lee los datos de usuarios y préstamos desde archivos
void cargarDatos() {
    ifstream archivoUsuarios("usuarios.txt");
    if (archivoUsuarios.is_open()) {
        while (archivoUsuarios >> nombresUsuarios[totalUsuarios] // usuario
            >> contrasenasUsuarios[totalUsuarios] // contraseña
            >> tiposUsuarios[totalUsuarios] // tipo de usuario
            >> ahorrosUsuarios[totalUsuarios]) { // ahorro de usuario
            totalUsuarios++; // esto cuenta los usuarios
            if (totalUsuarios >= 100){
                break;// esto limita a 100 usuarios
            }
            else {} 
        }
        archivoUsuarios.close();
    }
    else {}

    ifstream archivoPrestamos("prestamos.txt");
    if (archivoPrestamos.is_open()) {
        while (archivoPrestamos >> solicitantesPrestamos[totalPrestamos] // usuario solicitante
          >> montosPrestamos[totalPrestamos] // monto del préstamo
          >> cuotasPrestamos[totalPrestamos] // número de cuotas
          >> interesesPrestamos[totalPrestamos] // interés del préstamo
          >> codeudoresPrestamos[totalPrestamos] // coudeudor del préstamo
          >> cuotasPagadasPrestamos[totalPrestamos] // cuotas pagadas del préstamo
          >> estadoPrestamos[totalPrestamos]) { // estado del préstamo
            totalPrestamos++;
            if (totalPrestamos >= 100){ 
                break; // esto limita a 100 prestamos
            } else{}
        }
        archivoPrestamos.close();
    }
    else {}

    // Leer fondo recuperado de archivo 
    /*
    fondo recuperado es el dinero que se ha recuperado por pagos de cuotas
    */
    ifstream archivoFondo("fondo.txt");
    if (archivoFondo.is_open()) {
        archivoFondo >> fondoRecuperado;
        archivoFondo.close();
    }
    else {}
}
// Esta función guarda los datos de usuarios y préstamos en archivos
// y el fondo recuperado

void guardarDatos() {
    ofstream archivoUsuarios("usuarios.txt");
    for (int i = 0; i < totalUsuarios; i++) {
        archivoUsuarios << nombresUsuarios[i] << " " // guardar nombre de usuario
                       << contrasenasUsuarios[i] << " " // guardar contraseña de usuario
                       << tiposUsuarios[i] << " " // guardar tipo de usuario
                       << ahorrosUsuarios[i] << "\n"; // guardar ahorro de usuario
    }
    archivoUsuarios.close();

    ofstream archivoPrestamos("prestamos.txt");
    for (int i = 0; i < totalPrestamos; i++) {
        archivoPrestamos << solicitantesPrestamos[i] << " " // usuario solicitante
     << montosPrestamos[i] << " " // monto del préstamo
     << cuotasPrestamos[i] << " " // número de cuotas
     << interesesPrestamos[i] << " " // interés del préstamo
     << codeudoresPrestamos[i] << " " // codeudor del préstamo
     << cuotasPagadasPrestamos[i] << " " // cuotas pagadas del préstamo
     << estadoPrestamos[i] << "\n"; // estado del préstamo
    }
    archivoPrestamos.close();

    // Guardar fondo recuperado
    ofstream archivoFondo("fondo.txt");
    archivoFondo << fondoRecuperado << endl;
    archivoFondo.close();
}
// Esta función registra un pago en el archivo pagos.txt
void registrarPago(string usuario, int idPrestamo, float monto) {
    ofstream archivoPagos("pagos.txt", ios::app);
    if (!archivoPagos.is_open()) {
        cout << "No se pudo abrir pagos.txt\n";
        return;
    }
    else {}
    archivoPagos << usuario << " " << idPrestamo << " " << monto << "\n";
    archivoPagos.close();
}

//FUNCIONES DE LOGIN Y USUARIOS 
string login() {
    string usuario, contrasena, tipoElegido;
    cout << "\nInicio de sesion\n";
    cout << "Seleccione tipo de usuario:\n";
    cout << "1. Admin\n";
    cout << "2. Socio\n";
    cout << "3. Tercero\n";
    cout << "Opcion: ";
    int opcionTipo;
    cin >> opcionTipo;
    // Validar la opción ingresada
    switch (opcionTipo) {
        case 1: tipoElegido = "admin"; break;
        case 2: tipoElegido = "socio"; break;
        case 3: tipoElegido = "tercero"; break;
        default:
            cout << "Opcion no valida\n";
            return "fallo";
    }

    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> contrasena;
     // validar que el usuario y contraseña existan y esten bien
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == usuario && 
            contrasenasUsuarios[i] == contrasena &&
            tiposUsuarios[i] == tipoElegido) {
            return tiposUsuarios[i] + ":" + usuario;
        }
        else {}
    }
    return "fallo";
}
// Aca se agrega un nuevo usuario al sistema
void agregarUsuario() {
    if (totalUsuarios >= 100) {
        cout << "Limite de usuarios alcanzado\n";
        return;
    }
    else {}
    string nombre, contrasena, tipo;
    cout << "\nAgregar Usuario\n";
    cout << "Nombre: ";
    cin >> nombre;
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == nombre) {
            cout << "El usuario ya existe\n";
            return;
        }
        else {}
    }
    cout << "Contrasena: ";
    cin >> contrasena;
    cout << "Tipo (socio/tercero/admin): ";
    cin >> tipo;
    // Validar tipo de usuario
    if (tipo != "socio" && tipo != "tercero" && tipo != "admin") {
        cout << "Tipo de usuario no valido\n";
        return;
    }
    else {}
    // agrega los valores a los arreglos
    nombresUsuarios[totalUsuarios] = nombre;
    contrasenasUsuarios[totalUsuarios] = contrasena;
    tiposUsuarios[totalUsuarios] = tipo;
    // Si es socio, asigna un ahorro inicial de $25000
    ahorrosUsuarios[totalUsuarios] = (tipo == "socio") ? 25000 : 0;
    totalUsuarios++;
    cout << "Usuario agregado exitosamente\n";
}

// FUNCIONES DE PRÉSTAMOS Y PAGOS 

// Muestra el estado de cuenta del usuario
void mostrarEstadoCuenta(string usuario) {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\nEstado de Cuenta \n";
    // Valida el usuario y muestra sus ahorros
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == usuario) {
            cout << "Ahorros: $" << ahorrosUsuarios[i] << "\n";
            break;
        }
        else {}
    }
    cout << "Prestamos:\n";
    bool tienePrestamos = false;
    // Recorre los préstamos y muestra los que pertenecen al usuario
    for (int i = 0; i < totalPrestamos; i++) {
        if (solicitantesPrestamos[i] == usuario && estadoPrestamos[i] == "aprobado") {
            tienePrestamos = true;
            float valorCuota = montosPrestamos[i] * (1 + interesesPrestamos[i]/100) / cuotasPrestamos[i];// Calcula el valor de la cuota
            cout << "- Monto: $" << montosPrestamos[i] 
                 << "\n  Cuotas: " << cuotasPagadasPrestamos[i] << "/" << cuotasPrestamos[i] // muestra las cuotas pagadas y totales
                 << "\n  Valor cuota: $" << valorCuota
                 << "\n  Interes: " << interesesPrestamos[i] << "%";
                 // Si tiene codeudor, lo muestra
            if (codeudoresPrestamos[i] != "NINGUNO") {
                cout << "\n  Codeudor: " << codeudoresPrestamos[i];
            }
            else {}
            cout << "\n";
        }
        else {}
    }
    if (!tienePrestamos) {
        cout << "No tiene prestamos activos\n";
    }
    else {}
}
// Préstamos para socios
void solicitarPrestamoSocio(string usuario) {
    cout << "\n Solicitar Prestamo \n";
    int indiceUsuario = -1; // Buscar el índice del usuario
    // Buscar el índice del usuario en el arreglo
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == usuario) {
            indiceUsuario = i;
            break;
        }
        else {}
    }
    float monto;
    int cuotas;
    // Validar que el monto no sea negativo o cero
    do {
        cout << "Monto a solicitar: $";
        cin >> monto;
        if (monto <= 0) {
            cout << "El monto debe ser mayor que cero.\n";
        }
    } while (monto <= 0);
    cout << "Numero de cuotas: ";
    cin >> cuotas;

    // Recorre los usuarios y valida que el usuario sea socio
    // luego suma todos los ahorros
    float totalAhorros = 0;
    for (int i = 0; i < totalUsuarios; i++) {
        if (tiposUsuarios[i] == "socio") {
            totalAhorros += ahorrosUsuarios[i];
        }
        else {}
    }
    // Valida que todas las cuotas esten pagas
    // si no estan pagas, suma el monto de los prestamos activos
    float totalPrestamosActivos = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (estadoPrestamos[i] == "aprobado" && cuotasPagadasPrestamos[i] < cuotasPrestamos[i]) {
            totalPrestamosActivos += montosPrestamos[i];
        }
        else {}
    }
    // Validar que el monto solicitado no exceda los fondos disponibles
        // Calcular intereses ganados
    float totalInteresesPagados = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        float interesPorCuota = montosPrestamos[i] * (interesesPrestamos[i]/100);
        totalInteresesPagados += interesPorCuota * cuotasPagadasPrestamos[i];
    }
    float disponible = totalAhorros + totalInteresesPagados - totalPrestamosActivos;
    if (monto > disponible) {
        cout << "Fondos insuficientes en el sistema. Prestamo rechazado.\n";
        return;
    }
    else {}
    string codeudor = "NINGUNO";
    // Si el monto solicitado es mayor al 150% de los ahorros del usuario, solicitar codeudor
    if (monto > ahorrosUsuarios[indiceUsuario] * 1.5) {
        cout << "\nNecesita un codeudor (socio) para montos mayores al 150% de su ahorro\n";
        cout << "Ingrese nombre del codeudor: ";
        cin >> codeudor;
        bool codeudorValido = false;
        // valida si el codeudor es un socio 
        for (int i = 0; i < totalUsuarios; i++) {
            if (nombresUsuarios[i] == codeudor && tiposUsuarios[i] == "socio") {
                codeudorValido = true;
                break;
            }
            else {}
        }
        if (!codeudorValido) {
            cout << "Codeudor no valido. Prestamo rechazado.\n";
            return;
        }
        else {}
    }
    else {}
    // Arreglos para almacenar los datos del préstamo
    solicitantesPrestamos[totalPrestamos] = usuario;
    montosPrestamos[totalPrestamos] = monto;
    cuotasPrestamos[totalPrestamos] = cuotas;
    interesesPrestamos[totalPrestamos] = 1.0;
    codeudoresPrestamos[totalPrestamos] = codeudor;
    cuotasPagadasPrestamos[totalPrestamos] = 0;
    estadoPrestamos[totalPrestamos] = "pendiente_admin";
    totalPrestamos++;
    guardarDatos(); // Guardar inmediatamente la solicitud
    cout << "\nSolicitud enviada al administrador para aprobación.\n";
}
// Préstamos para terceros
void solicitarPrestamoTercero(string usuario) {
    cout << "\n Solicitar Prestamo \n";
    float monto;
    int cuotas;
    float interes;
    // Validar que el monto no sea negativo o cero
    do {
        cout << "Monto a solicitar: $";
        cin >> monto;
        if (monto <= 0) {
            cout << "El monto debe ser mayor que cero.\n";
        }
    } while (monto <= 0);
    cout << "Numero de cuotas: ";
    cin >> cuotas;
    // Validar que el monto no sea mayor a $500000
    if (monto > 500000) {
        interes = 2.5;
    }
    else {
        interes = 2.0;
    }
    cout << "Se le aplicara un interes del " << interes << "% mensual\n";
    float totalAhorros = 0;
    // Calcular el total de ahorros de los socios
    for (int i = 0; i < totalUsuarios; i++) {
        if (tiposUsuarios[i] == "socio") {
            totalAhorros += ahorrosUsuarios[i];
        }
        else {}
    }
    // Restar préstamos activos
    float totalPrestamosActivos = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (estadoPrestamos[i] == "aprobado" && cuotasPagadasPrestamos[i] < cuotasPrestamos[i]) {
            totalPrestamosActivos += montosPrestamos[i];
        }
        else {}
    }
    
// Validar que el monto solicitado no exceda los fondos disponibles
        // Calcular intereses ganados
    float totalInteresesPagados = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        float interesPorCuota = montosPrestamos[i] * (interesesPrestamos[i]/100);
        totalInteresesPagados += interesPorCuota * cuotasPagadasPrestamos[i];
    }
    
    float disponible = totalAhorros + totalInteresesPagados - totalPrestamosActivos;
    // Validar que el monto solicitado no exceda los fondos disponibles
    if (monto > disponible) {
        cout << "Fondos insuficientes en el sistema. Prestamo rechazado.\n";
        return;
    }
    else {}
    // Solicitar codeudor obligatorio
    string codeudor;
    cout << "Ingrese nombre del codeudor:  ";
    cin >> codeudor;
    bool codeudorValido = false;
    // Validar que el codeudor sea un socio existente
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == codeudor && tiposUsuarios[i] == "socio") {
            codeudorValido = true;
            break;
        }
        else {}
    }
    if (!codeudorValido) {
        cout << "Codeudor no valido. Prestamo rechazado.\n";
        return;
    }
    else {}
    // Arreglos para almacenar los datos del préstamo
    solicitantesPrestamos[totalPrestamos] = usuario;
    montosPrestamos[totalPrestamos] = monto;
    cuotasPrestamos[totalPrestamos] = cuotas;
    interesesPrestamos[totalPrestamos] = interes;
    codeudoresPrestamos[totalPrestamos] = codeudor;
    cuotasPagadasPrestamos[totalPrestamos] = 0;
    estadoPrestamos[totalPrestamos] = "pendiente_admin";// Estado inicial de la solicitud
    totalPrestamos++;
    guardarDatos(); // Guardar inmediatamente la solicitud
    cout << "\nSolicitud enviada al administrador para aprobación.\n";
}

void aceptarCodeudor(string usuario) {
    cout << "\n=== Solicitudes para ser Codeudor ===\n";
    bool tieneSolicitudes = false;
    // Buscar solicitudes pendientes de codeudor
    // Recorre los préstamos y muestra los que necesitan codeudor
    // y que el usuario sea codeudor
    for (int i = 0; i < totalPrestamos; i++) {
        if (codeudoresPrestamos[i] == usuario && cuotasPagadasPrestamos[i] == 0 && estadoPrestamos[i] == "pendiente_codeudor") {
            tieneSolicitudes = true;
            cout << "Solicitante: " << solicitantesPrestamos[i] 
                 << ", Monto: $" << montosPrestamos[i] 
                 << ", Cuotas: " << cuotasPrestamos[i] << "\n";
            cout << "Aceptar ser codeudor? (s/n): ";
            char opcion;
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                estadoPrestamos[i] = "aprobado";
                guardarDatos(); // Guardar cambio de estado
                cout << "Has aceptado ser codeudor. Préstamo activado.\n";
            }
            else {
                // Eliminar el préstamo rechazado por el codeudor
                for (int j = i; j < totalPrestamos - 1; j++) {
                    solicitantesPrestamos[j] = solicitantesPrestamos[j + 1];
                    montosPrestamos[j] = montosPrestamos[j + 1];
                    cuotasPrestamos[j] = cuotasPrestamos[j + 1];
                    interesesPrestamos[j] = interesesPrestamos[j + 1];
                    codeudoresPrestamos[j] = codeudoresPrestamos[j + 1];
                    cuotasPagadasPrestamos[j] = cuotasPagadasPrestamos[j + 1];
                    estadoPrestamos[j] = estadoPrestamos[j + 1];
                }
                totalPrestamos--; // indicar que hay un préstamo menos
                guardarDatos(); // Guardar eliminación
                cout << "Has rechazado ser codeudor. Préstamo eliminado.\n";
                i--;
            }
        }
        else {}
    }
    if (!tieneSolicitudes) {
        cout << "No tienes solicitudes para ser codeudor\n";
    }
    else {}
}
// Pagos de prestamos
void realizarPago(string usuario) {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\n Realizar Pago \n";
    bool tienePrestamos = false;
    // Buscar préstamos activos del usuario
    for (int i = 0; i < totalPrestamos; i++) { 
        if (solicitantesPrestamos[i] == usuario && estadoPrestamos[i] == "aprobado" && cuotasPagadasPrestamos[i] < cuotasPrestamos[i])
        // Validar que el usuario tenga préstamos aprobados y no pagados
        {
            // Calcular el valor de la cuota
            tienePrestamos = true;
            float interesTotal = montosPrestamos[i] * (interesesPrestamos[i]/100) * cuotasPrestamos[i];
            float montoTotal = montosPrestamos[i] + interesTotal;
            float valorCuota = montoTotal / cuotasPrestamos[i];
            cout << i+1 << ". Monto: $" << montosPrestamos[i]
                 << ", Cuotas pagadas: " << cuotasPagadasPrestamos[i]
                 << "/" << cuotasPrestamos[i]
                 << ", Valor cuota: $" << valorCuota << "\n";
        }
        else {}
    }
    if (!tienePrestamos) {
        cout << "No tienes préstamos activos para pagar.\n";
        return;
    }
    else {}
    // Seleccionar el préstamo a pagar
    cout << "Seleccione el número de préstamo a pagar: ";
    int opcion;
    cin >> opcion;
    opcion--; // Ajustar índice
    // Validar la opción seleccionada
    if (opcion < 0 || opcion >= totalPrestamos ||
        solicitantesPrestamos[opcion] != usuario ||
        estadoPrestamos[opcion] != "aprobado" ||
        cuotasPagadasPrestamos[opcion] >= cuotasPrestamos[opcion]) {
        cout << "Opción inválida.\n";
        return;
    }
    else {}
    // Calcular el valor de la cuota a pagar
    float interesTotal = montosPrestamos[opcion] * (interesesPrestamos[opcion]/100) * cuotasPrestamos[opcion];
    float montoTotal = montosPrestamos[opcion] + interesTotal;
    float valorCuota = montoTotal / cuotasPrestamos[opcion];
    cuotasPagadasPrestamos[opcion]++;
    registrarPago(usuario, opcion, valorCuota);// registrar el pago en pagos.txt

    // Sumar el pago de la cuota al fondo recuperado
    fondoRecuperado += valorCuota;

    cout << "Pago registrado correctamente.\n";
    guardarDatos();

    // Generacion de ticket de pago
    stringstream ticket;
    ticket << fixed << setprecision(0); // Mostrar dinero sin notación científica en ticket
    ticket << "\n========== COMPROBANTE DE PAGO DE CUOTA ==========\n";
    ticket << "Usuario: " << usuario << "\n";
    ticket << "Préstamo #: " << (opcion + 1) << "\n";
    ticket << "Monto pagado: $" << valorCuota << "\n";
    ticket << "Cuotas pagadas: " << cuotasPagadasPrestamos[opcion] << "/" << cuotasPrestamos[opcion] << "\n";
    ticket << "===============================================\n";
    cout << ticket.str();
    cout << "Pago guardado en un archivo correctamente.\n";
    // Guardar ticket en un archivo 
    stringstream nombreArchivo;
    nombreArchivo << "ticket_pago_" << usuario << "_" << (opcion + 1) << "_" << cuotasPagadasPrestamos[opcion] << ".txt";
    ofstream archivoTicket(nombreArchivo.str()); // crea un archivo con el nombre del usuario y el número de préstamo
    if (archivoTicket.is_open()) {
        archivoTicket << ticket.str(); // escribe el ticket en el archivo
        archivoTicket.close();
    } else {
        cout << "No se pudo guardar el ticket en archivo.\n";
    }
}
// Pago de ahorro mensual para socios
void pagoAhorroSocio(string usuario) {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\n Pago de Ahorro Mensual \n";
    float monto;
    cout << "Ingrese el monto a ahorrar este mes (mínimo $25000): $";
    cin >> monto;
    if (monto < 25000) {
        cout << "El monto mínimo es $25000. Operación cancelada.\n";
        return;
    }
    else {}
    // Buscar el índice del usuario
    int indice = -1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (nombresUsuarios[i] == usuario) {
            indice = i;
            break;
        }
        else {}
    }
    if (indice == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }
    else {}
    // sumar el monto al ahorro del usuario
    ahorrosUsuarios[indice] += monto;

    // Registrar el pago en pagos.txt (tipo: ahorro)
    ofstream archivoPagos("pagos.txt", ios::app);
    if (!archivoPagos.is_open()) {
        cout << "No se pudo abrir pagos.txt\n";
        return;
    }
    else {}
    // Guardar el pago de ahorro
    archivoPagos << usuario << " ahorro " << monto << "\n";
    archivoPagos.close();

    cout << "Pago de ahorro registrado correctamente. Nuevo saldo de ahorros: $" << ahorrosUsuarios[indice] << "\n";

    // Generación de ticket de pago de ahorro
    stringstream ticket;
    ticket << fixed << setprecision(0); // Mostrar dinero sin notación científica en ticket
    ticket << "\n========== COMPROBANTE DE AHORRO ==========\n";
    ticket << "Usuario: " << usuario << "\n";
    ticket << "Monto ahorrado: $" << monto << "\n";
    ticket << "Nuevo saldo de ahorros: $" << ahorrosUsuarios[indice] << "\n";
    ticket << "===========================================\n";
    cout << ticket.str();

    guardarDatos();
}

//  MENÚS 
// menu para socios 
void menuSocio(string usuario) {
    while (true) {
        cout << "\n Menu Socio (" << usuario << ") ";
        cout << "\n1. Solicitar prestamo";
        cout << "\n2. Ver estado de cuenta";
        cout << "\n3. Aceptar ser codeudor";
        cout << "\n4. Realizar pago";
        cout << "\n5. Hacer pago de ahorro mensual";
        cout << "\n6. Salir";
        cout << "\nOpcion: ";
        int opcion;
        cin >> opcion;
        // Validar la opción ingresada
        // Dependiendo de la opción, se llama a la función correspondiente
        switch(opcion) {
            case 1:
                solicitarPrestamoSocio(usuario);
                break;
            case 2:
                mostrarEstadoCuenta(usuario);
                break;
            case 3:
                aceptarCodeudor(usuario);
                break;
            case 4:
                realizarPago(usuario);
                break;
            case 5:
                pagoAhorroSocio(usuario);
                break;
            case 6:
                return;
            default:
                cout << "Opcion no valida\n";
        }
    }
}
// menu para terceros
void menuTercero(string usuario) {
    while (true) {
        cout << "\n Menu Tercero (" << usuario << ") ";
        cout << "\n1. Solicitar prestamo";
        cout << "\n2. Ver estado de prestamos";
        cout << "\n3. Realizar pago";
        cout << "\n4. Salir";
        cout << "\nOpcion: ";
        int opcion;
        cin >> opcion;
        // Validar la opción ingresada
        // Dependiendo de la opción, se llama a la función correspondiente
        switch(opcion) {
            case 1:
                solicitarPrestamoTercero(usuario);
                break;
            case 2:
                mostrarEstadoCuenta(usuario);
                break;
            case 3:
                realizarPago(usuario);
                break;
            case 4:
                return;
            default:
                cout << "Opcion no valida\n";
        }
    }
}
// Muestra el reporte de ahorros de los socios  
void mostrarReporteAhorros() {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\n--- Reporte de Ahorros ---\n";
    float totalAhorros = 0;
    // Mostrar ahorros de cada socio
    for (int i = 0; i < totalUsuarios; i++) {
        if (tiposUsuarios[i] == "socio") {
            cout << nombresUsuarios[i] << ": $" << ahorrosUsuarios[i] << "\n";
            totalAhorros += ahorrosUsuarios[i];// Suma los ahorros de los socios
        }
        else {}
    }
    // Calcular total de préstamos activos
    float totalPrestamosActivos = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (estadoPrestamos[i] == "aprobado" && cuotasPagadasPrestamos[i] < cuotasPrestamos[i]) {
            totalPrestamosActivos += montosPrestamos[i];
        }
        else {}
    }
    // calcular el total de intereses pagados
    float totalInteresesPagados = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        float interesPorCuota = montosPrestamos[i] * (interesesPrestamos[i]/100);
        totalInteresesPagados += interesPorCuota * cuotasPagadasPrestamos[i];
    }
    cout << "\nTotal ahorrado: $" << totalAhorros << "\n";
    cout << "Total recuperado por pagos de cuotas: $" << fondoRecuperado << "\n";
    cout << "Total de intereses pagados: $" << totalInteresesPagados << "\n";
    cout << "Total en préstamos activos: $" << totalPrestamosActivos << "\n";
    cout << "Total disponible en el sistema: $" << (totalAhorros + totalInteresesPagados - totalPrestamosActivos) << "\n";
}

void mostrarGanancias() {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\n=== Reporte de Ganancias ===\n";
    float gananciasActuales = 0;
    float gananciasProyectadas = 0;
    // Calcular ganancias actuales y proyectadas
    // Recorre los préstamos y calcula las ganancias
    for (int i = 0; i < totalPrestamos; i++) {
        float interesMensual = montosPrestamos[i] * (interesesPrestamos[i]/100);
        gananciasActuales += interesMensual * cuotasPagadasPrestamos[i];
        gananciasProyectadas += interesMensual * (cuotasPrestamos[i] - cuotasPagadasPrestamos[i]);
    }
    cout << "Ganancias actuales: $" << gananciasActuales << "\n";
    cout << "Ganancias proyectadas: $" << gananciasProyectadas << "\n";
    cout << "Total ganancias: $" << (gananciasActuales + gananciasProyectadas) << "\n";
}
// Aprobar préstamos pendientes de los socios
void aprobarPrestamos() {
    cout << fixed << setprecision(0); // Mostrar dinero sin notación científica
    cout << "\n=== Solicitudes de Préstamo Pendientes ===\n";
    bool hayPendientes = false;
    // valida los préstamos pendientes de aprobación
    // Recorre los préstamos y muestra los que están pendientes de aprobación
    for (int i = 0; i < totalPrestamos; i++) {
        if (estadoPrestamos[i] == "pendiente_admin") {
            hayPendientes = true;
            cout << i+1 << ". Usuario: " << solicitantesPrestamos[i]
                 << ", Monto: $" << montosPrestamos[i]
                 << ", Cuotas: " << cuotasPrestamos[i]
                 << ", Interes: " << interesesPrestamos[i]
                 << ", Codeudor: " << codeudoresPrestamos[i] << "\n";
            cout << "Aprobar este prestamo? (s/n): ";
            char opcion;
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                if (codeudoresPrestamos[i] != "NINGUNO") {
                    estadoPrestamos[i] = "pendiente_codeudor";
                    guardarDatos(); // Guardar cambio de estado
                    cout << "Aprobado por admin. Falta aceptación del codeudor.\n";
                }
                else {
                    estadoPrestamos[i] = "aprobado";
                    guardarDatos(); // Guardar cambio de estado
                    cout << "Préstamo aprobado y activado.\n";
                }
            }
            else {
                estadoPrestamos[i] = "rechazado";
                guardarDatos(); // Guardar cambio de estado
                cout << "Préstamo rechazado.\n";
            }
        }
        else {}
    }
    if (!hayPendientes) {
        cout << "No hay solicitudes pendientes.\n";
    }
    else {}
}

// Menu para el administrador
void menuAdmin() {
    while (true) {
        cout << "\n=== Menu Administrador ===";
        cout << "\n1. Ver reporte de ahorros";
        cout << "\n2. Ver ganancias";
        cout << "\n3. Agregar usuario";
        cout << "\n4. Aprobar préstamos";
        cout << "\n5. Salir";
        cout << "\nOpcion: ";
        int opcion;
        cin >> opcion;
        switch(opcion) {
            case 1:
                mostrarReporteAhorros();
                break;
            case 2:
                mostrarGanancias();
                break;
            case 3:
                agregarUsuario();
                break;
            case 4:
                aprobarPrestamos();
                break;
            case 5:
                return;
            default:
                cout << "Opcion no valida\n";
        }
    }
}

// MAIN
int main() {

    cout << "==============================================\n";
    cout << "         Bienvenido al Sistema FAP   \n";
    cout << "==============================================\n";
    cout << "   Por      Cristian Camilo Colorado P.       \n";
    cout << "----------------------------------------------\n";
    cout << "  Gestiona tus ahorros, préstamos y pagos aqui\n";
    cout << "==============================================\n\n";
    
    cargarDatos();
    while (true) {
        string resultado = login();
        if (resultado == "fallo") {
            cout << "Usuario o contrasena incorrectos\n";
            continue;
        }
        else {}
        size_t pos = resultado.find(":");
        string tipo = resultado.substr(0, pos);
        string usuario = resultado.substr(pos + 1);
        if (tipo == "socio") {
            menuSocio(usuario);
        }
        else if (tipo == "tercero") {
            menuTercero(usuario);
        }
        else if (tipo == "admin") {
            menuAdmin();
        }
        else {}
        guardarDatos();
    }
    return 0;
}
