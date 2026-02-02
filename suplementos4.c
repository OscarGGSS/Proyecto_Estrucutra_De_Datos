#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- ESTRUCTURAS ---

// Registro de Suplemento (rSuplemento)
typedef struct {
    int eIdProducto;       // ID del producto 
    float fPrecio;         // Precio con centavos 
    int eFechaCaducidad;   // Fecha de caducidad 
    int eDisponibilidad;   // Unidades en inventario 
} rSuplemento;

// Nodo para la Lista Ligada Dinámica 
typedef struct NodoS {
    rSuplemento datos;      // Se corrigió eliminando la referencia a rMembresia
    struct NodoS *pSiguiente;
} TpNodoSuplemento;

// Puntero global al inicio del inventario
TpNodoSuplemento *pInicioInv = NULL;

// --- SUBPROCESOS DE APOYO ---

// GenerarIdSuplemento: Asigna ID único (último + 1) 
int GenerarIdSuplemento() {
    if (pInicioInv == NULL) return 10000; 
    TpNodoSuplemento *temp = pInicioInv;
    int maxID = temp->datos.eIdProducto;
    while (temp != NULL) {
        if (temp->datos.eIdProducto > maxID) {
            maxID = temp->datos.eIdProducto;
        }
        temp = temp->pSiguiente;
    }
    return maxID + 1; 
}

// --- MÓDULOS PRINCIPALES ---

// 1. Módulo: AltaSuplemento 
void AltaSuplemento() {
    TpNodoSuplemento *pNuevo = (TpNodoSuplemento *)malloc(sizeof(TpNodoSuplemento));
    if (pNuevo == NULL) {
        printf("Error: No hay memoria suficiente.\n");
        return;
    }

    // Proceso de captura según el análisis 
    pNuevo->datos.eIdProducto = GenerarIdSuplemento(); 
    
    printf("Ingrese precio del suplemento: ");
    scanf("%f", &pNuevo->datos.fPrecio); 
    
    printf("Ingrese fecha de caducidad: ");
    scanf("%d", &pNuevo->datos.eFechaCaducidad); 
    
    printf("Ingrese disponibilidad: ");
    scanf("%d", &pNuevo->datos.eDisponibilidad); 

    // Almacenar en lista dinámica (Agregar al inicio)
    pNuevo->pSiguiente = pInicioInv;
    pInicioInv = pNuevo;
    
    printf("El registro se realizo con exito. ID: %d\n", pNuevo->datos.eIdProducto); 
}

// 2. Módulo: BajaSuplemento 
void BajaSuplemento() {
    int idBusca;
    char cOpcion; 
    
    if (pInicioInv == NULL) {
        printf("El inventario esta vacio.\n");
        return;
    }

    printf("Ingrese ID del producto a dar de baja: ");
    scanf("%d", &idBusca); 

    TpNodoSuplemento *pActual = pInicioInv, *pAnterior = NULL;

    // Buscar eIdProducto 
    while (pActual != NULL && pActual->datos.eIdProducto != idBusca) {
        pAnterior = pActual;
        pActual = pActual->pSiguiente;
    }

    if (pActual == NULL) {
        printf("Error: ID no existente\n"); 
        return;
    }

    // Mostrar datos actuales y solicitar confirmación 
    printf("Datos: ID %d, Precio %.2f, Stock %d\n", pActual->datos.eIdProducto, pActual->datos.fPrecio, pActual->datos.eDisponibilidad);
    printf("¿Desea borrar este producto? (S/N): ");
    scanf(" %c", &cOpcion);

    if (cOpcion == 'S' || cOpcion == 's') { 
        if (pAnterior == NULL) pInicioInv = pActual->pSiguiente;
        else pAnterior->pSiguiente = pActual->pSiguiente;
        
        free(pActual); // Liberar memoria 
        printf("El registro del producto se borro correctamente\n"); 
    } else {
        printf("No se realizara la funcion\n"); 
    }
}

// 3. Módulo: ModificarProducto 
void ModificarProducto() {
    int idBusca;
    char cOpcion;
    
    if (pInicioInv == NULL) {
        printf("El inventario esta vacio.\n");
        return;
    }

    printf("Ingrese ID del producto a modificar: ");
    scanf("%d", &idBusca);

    TpNodoSuplemento *temp = pInicioInv;
    while (temp != NULL && temp->datos.eIdProducto != idBusca) temp = temp->pSiguiente;

    if (temp == NULL) {
        printf("Error: El ID no existe\n");
        return;
    }

    // Mostrar actuales y confirmar [cite: 549-550]
    printf("Datos actuales: Precio %.2f, Caducidad %d, Stock %d\n", temp->datos.fPrecio, temp->datos.eFechaCaducidad, temp->datos.eDisponibilidad);
    printf("¿Desea modificar los datos de este producto? (S/N): ");
    scanf(" %c", &cOpcion);

    if (cOpcion == 'S' || cOpcion == 's') { 
        // Solicitar nuevos datos (rProductoNuevo) 
        printf("Nuevo precio: ");
        scanf("%f", &temp->datos.fPrecio);
        printf("Nueva fecha de caducidad: ");
        scanf("%d", &temp->datos.eFechaCaducidad);
        printf("Nueva disponibilidad: ");
        scanf("%d", &temp->datos.eDisponibilidad);
        printf("El registro se modifico de manera correcta\n"); 
    } else {
        printf("No se realizara la funcion.\n"); 
    }
}

// 4. Módulo: Inventario 
void Inventario() {
    if (pInicioInv == NULL) {
        printf("El inventario esta vacio\n"); 
        return;
    }

    printf("\n--- Inventario de Suplementos ---\n"); 
    TpNodoSuplemento *pPos = pInicioInv;
    while (pPos != NULL) { // [cite: 577]
        printf("ID del Producto: %d\n", pPos->datos.eIdProducto); 
        printf("  Precio: %.2f\n", pPos->datos.fPrecio); 
        printf("  Fecha de Caducidad: %d\n", pPos->datos.eFechaCaducidad); 
        printf("  Disponibilidad: %d\n", pPos->datos.eDisponibilidad);
        printf("--------------------------\n");
        pPos = pPos->pSiguiente;
    }
}

// --- FUNCIÓN PRINCIPAL ---
int main() {
    int op;
    do {
        printf("\nVIKINGOS GYM - GESTION DE SUPLEMENTOS");
        printf("\n1. Alta Suplemento\n2. Baja Suplemento\n3. Modificar Producto\n4. Revisar Inventario\n5. Salir\nOpcion: ");
        scanf("%d", &op);
        switch(op) {
            case 1: AltaSuplemento(); break;
            case 2: BajaSuplemento(); break;
            case 3: ModificarProducto(); break;
            case 4: Inventario(); break;
            case 5: printf("Saliendo del modulo de suplementos...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (op != 5);
    
    return 0;
}
