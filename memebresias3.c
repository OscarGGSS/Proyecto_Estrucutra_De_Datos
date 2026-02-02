#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- ESTRUCTURAS BASADAS EN EL DICCIONARIO DE DATOS ---

// Estructura para fechas (rFechaInicio, rFechaVencimiento) 
typedef struct {
    int eDia;  
    int eMes;  
    int eAnio; 
} RegistroFecha;

// Registro principal de Membresía (rMembresia) [cite: 378, 450]
typedef struct {
    int eIDMembresia;            // Entero de 5 dígitos 
    char cTipoMembresia[21];     // Cadena de 20 caracteres 
    float fCosto;                // Flotante con dos decimales 
    RegistroFecha rFechaInicio;  
    RegistroFecha rFechaVencimiento; 
    int eIDCliente;               
    char cEstatus[15];            
} rMembresia;

// Nodo para la Lista Ligada (Basado en ejemplo A18) 
typedef struct Nodo {
    rMembresia datos;
    struct Nodo *pSiguiente;
} TpNodoMembresia;

TpNodoMembresia *pPrimero = NULL; // Puntero al inicio de la lista 

// --- SUBPROCESOS ---

// Subproceso: AplicarDescuentoEstudiantil 
float AplicarDescuentoEstudiantil(float fCosto, bool lEsEstudiante) {
    // Verificar que fCosto > 0 
    if (fCosto <= 0) {
        printf("Error: Costo invalido.\n");
        return 0;
    }
    // Comprobar si es estudiante [cite: 477]
    if (lEsEstudiante) {
        fCosto = fCosto - (fCosto * 0.20); // Descuento del 20% 
    }
    return fCosto; // Regresar fCosto actualizado 
}

// Generador de ID automático 
int GenerarIDMembresia() {
    if (pPrimero == NULL) return 10000;
    TpNodoMembresia *temp = pPrimero;
    int max = temp->datos.eIDMembresia;
    while (temp != NULL) {
        if (temp->datos.eIDMembresia > max) max = temp->datos.eIDMembresia;
        temp = temp->pSiguiente;
    }
    return max + 1;
}

// Simulación de verificación de cliente en el sistema 
bool verificarClienteExiste(int id) {
    // En un sistema completo, buscaría en la lista de clientes
    return (id >= 10000 && id <= 99999);
}

// --- MÓDULOS PRINCIPALES ---

// 1. AltaMembresiaCliente 
void AltaMembresiaCliente() {
    int eIDCliente;
    char resp;
    
    printf("\n--- Alta Membresia Cliente ---\n");
    // Solicitar el ID del cliente 
    printf("Ingrese ID del Cliente (5 digitos): ");
    scanf("%d", &eIDCliente);

    // Verificar si el cliente está registrado 
    if (!verificarClienteExiste(eIDCliente)) {
        printf("Error: El cliente no existe en el sistema.\n"); 
        return;
    }

    TpNodoMembresia *pNuevo = (TpNodoMembresia*)malloc(sizeof(TpNodoMembresia));
    if (pNuevo == NULL) return;

    pNuevo->datos.eIDCliente = eIDCliente;
    
    // Solicitar datos de la membresía 
    printf("Tipo de membresia (20 letras): ");
    scanf("%s", pNuevo->datos.cTipoMembresia);
    printf("Costo: ");
    scanf("%f", &pNuevo->datos.fCosto);
    
    // Integración del subproceso de descuento 
    printf("¿El cliente es estudiante? (S/N): ");
    scanf(" %c", &resp);
    pNuevo->datos.fCosto = AplicarDescuentoEstudiantil(pNuevo->datos.fCosto, (resp == 'S' || resp == 's'));

    printf("Fecha Inicio (dia mes anio): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaInicio.eDia, &pNuevo->datos.rFechaInicio.eMes, &pNuevo->datos.rFechaInicio.eAnio);
    printf("Fecha Vencimiento (dia mes anio): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaVencimiento.eDia, &pNuevo->datos.rFechaVencimiento.eMes, &pNuevo->datos.rFechaVencimiento.eAnio);

    // Generar automáticamente el ID 
    pNuevo->datos.eIDMembresia = GenerarIDMembresia();
    strcpy(pNuevo->datos.cEstatus, "Activa");

    // Guardar en la lista dinámica
    pNuevo->pSiguiente = pPrimero;
    pPrimero = pNuevo;

    printf("El registro se realizo con exito. ID Membresia: %d\n", pNuevo->datos.eIDMembresia);
}

// 2. BajaMembresiaCliente 
void BajaMembresiaCliente() {
    int id;
    char cOpcion;
    
    printf("\n--- Baja Membresia Cliente ---\n");
    // Solicitar eIDMembresia 
    printf("Ingrese ID de la membresia a eliminar: ");
    scanf("%d", &id);

    TpNodoMembresia *pActual = pPrimero, *pAnterior = NULL;

    // Verificar si la membresía existe 
    while (pActual != NULL && pActual->datos.eIDMembresia != id) {
        pAnterior = pActual;
        pActual = pActual->pSiguiente;
    }

    if (pActual == NULL) {
        printf("Error: La membresia no existe.\n"); 
        return;
    }

    // Solicitar confirmación 
    printf("¿Esta seguro de eliminar la membresia %d? (S/N): ", id);
    scanf(" %c", &cOpcion);

    if (cOpcion == 'S' || cOpcion == 's') {
        if (pAnterior == NULL) pPrimero = pActual->pSiguiente;
        else pAnterior->pSiguiente = pActual->pSiguiente;

        free(pActual); // Eliminar registro 
        printf("Baja de membresia exitosa.\n"); 
    } else {
        printf("No se realizara la baja.\n"); 
    }
}

// 3. ModificarMembresiaCliente 
void ModificarMembresiaCliente() {
    int id, campo;
    printf("\n--- Modificar Membresia Cliente ---\n");
    printf("Ingrese ID de membresia: ");
    scanf("%d", &id);

    // Verificar si existe 
    TpNodoMembresia *temp = pPrimero;
    while (temp != NULL && temp->datos.eIDMembresia != id) temp = temp->pSiguiente;

    if (temp == NULL) {
        printf("Error: La membresia no existe.\n"); 
        return;
    }

    // Mostrar datos actuales 
    printf("Datos Actuales - Tipo: %s, Costo: %.2f\n", temp->datos.cTipoMembresia, temp->datos.fCosto);

    // Solicitar campo a modificar 
    printf("¿Que desea modificar? 1.Tipo 2.Costo 3.Fecha Inicio 4.Fecha Vencimiento: ");
    scanf("%d", &campo);

    switch(campo) {
        case 1: printf("Nuevo Tipo: "); scanf("%s", temp->datos.cTipoMembresia); break; // 
        case 2: printf("Nuevo Costo: "); scanf("%f", &temp->datos.fCosto); break; // 
        case 3: printf("Nueva Fecha Inicio (d m a): "); 
                scanf("%d %d %d", &temp->datos.rFechaInicio.eDia, &temp->datos.rFechaInicio.eMes, &temp->datos.rFechaInicio.eAnio); break; 
        case 4: printf("Nueva Fecha Vencimiento (d m a): ");
                scanf("%d %d %d", &temp->datos.rFechaVencimiento.eDia, &temp->datos.rFechaVencimiento.eMes, &temp->datos.rFechaVencimiento.eAnio); break; 
    }

    printf("Modificacion exitosa.\n");
}

// 4. ListadoMembresias 
void ListadoMembresias() {
    if (pPrimero == NULL) {
        printf("Error: No hay ninguna membresia.\n"); 
        return;
    }

    printf("\n--- Listado de Membresias ---\n");
    TpNodoMembresia *actual = pPrimero;
    while (actual != NULL) {
        // En un caso real, se compararía rFechaVencimiento con la fecha actual del sistema 
        // Para el ejemplo, se muestra el estatus guardado.
        printf("ID: %d | Cliente: %d | Tipo: %s | Costo: %.2f | Estatus: %s\n", 
               actual->datos.eIDMembresia, actual->datos.eIDCliente, 
               actual->datos.cTipoMembresia, actual->datos.fCosto, actual->datos.cEstatus);
        actual = actual->pSiguiente;
    }
}

int main() {
    int op;
    do {
        printf("\nVIKINGOS GYM - GESTION DE MEMBRESIAS\n");
        printf("1. Alta\n2. Baja\n3. Modificar\n4. Listado\n5. Salir\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) AltaMembresiaCliente();
        if (op == 2) BajaMembresiaCliente();
        if (op == 3) ModificarMembresiaCliente();
        if (op == 4) ListadoMembresias();
    } while (op != 5);
    return 0;
}
