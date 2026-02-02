/* ***
	Programa: PMembresias.c
	Autor: Jennifer García
	Fecha: 01/02/2026
	Objetivo: Gestionar las membresías de Vikingos Gym con paso de parámetros
	Compilador: Dev-C++ 5.11
	Versión: 0.2
*** */

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Tipos
typedef struct {
    int eDia;  
    int eMes;  
    int eAnio; 
} RegistroFecha;

typedef struct {
    int eIDMembresia;            
    char cTipoMembresia[21];     
    float fCosto;                
    RegistroFecha rFechaInicio;  
    RegistroFecha rFechaVencimiento; 
    int eIDCliente;              
    char cEstatus[15];           
} rMembresia;

typedef struct Nodo {
    rMembresia datos;
    struct Nodo *pSiguiente;
} TpNodoMembresia;

TpNodoMembresia *pPrimeroM = NULL; 

//Prototipos
float AplicarDescuentoEstudiantil(float fCosto, bool lEsEstudiante);
int GenerarIDMembresia(TpNodoMembresia *pLista);
bool verificarClienteExiste(int id);
void AltaMembresiaCliente();
void BajaMembresiaCliente(int eIDMembresia);
void ModificarMembresiaCliente(int eIDMembresia);
void ListadoMembresias(TpNodoMembresia *pLista);

//Programa principal
int main() {
    int op, idAux;
    do {
        printf("\nVIKINGOS GYM - GESTION DE MEMBRESIAS");
        printf("\n1 Alta\n2 Baja\n3 Modificar\n4 Listado\n5 Salir\nOpcion: ");
        scanf("%d", &op);
        
        switch (op) {
            case 1: 
                AltaMembresiaCliente(); 
                break;
            case 2: 
                printf("Ingrese ID de la membresia a eliminar: ");
                scanf("%d", &idAux);
                BajaMembresiaCliente(idAux); 
                break;
            case 3: 
                printf("Ingrese ID de la membresia a modificar: ");
                scanf("%d", &idAux);
                ModificarMembresiaCliente(idAux);
                break;
            case 4: 
                ListadoMembresias(pPrimeroM); 
                break;
        }
    } while (op != 5);
    return 0;
}

//AplicarDescuentoEstudiantil
float AplicarDescuentoEstudiantil(float fCosto, bool lEsEstudiante) {
    if (fCosto <= 0) return 0;
    if (lEsEstudiante) {
        fCosto = fCosto - (fCosto * 0.20); 
    }
    return fCosto; 
}

//GenerarIDMembresia
int GenerarIDMembresia(TpNodoMembresia *pLista) {
    if (pLista == NULL) return 10000;
    TpNodoMembresia *temp = pLista;
    int max = temp->datos.eIDMembresia;
    while (temp != NULL) {
        if (temp->datos.eIDMembresia > max) max = temp->datos.eIDMembresia;
        temp = temp->pSiguiente;
    }
    return max + 1;
}

//verificarClienteExiste
bool verificarClienteExiste(int id) {
    return (id >= 10000 && id <= 99999);
}

//AltaMembresiaCliente
void AltaMembresiaCliente() {
    int eIDCliente;
    char resp;
    
    printf("\nAlta Membresia Cliente\n");
    printf("Ingrese ID del Cliente: ");
    scanf("%d", &eIDCliente);

    if (!verificarClienteExiste(eIDCliente)) {
        printf("Error: El cliente no existe\n");
        return;
    }

    TpNodoMembresia *pNuevo = (TpNodoMembresia*)malloc(sizeof(TpNodoMembresia));
    if (pNuevo == NULL) return;

    pNuevo->datos.eIDCliente = eIDCliente;
    printf("Tipo de membresia: ");
    scanf("%s", pNuevo->datos.cTipoMembresia);
    printf("Costo: ");
    scanf("%f", &pNuevo->datos.fCosto);
    
    printf("¿Es estudiante? (S/N): ");
    scanf(" %c", &resp);
    pNuevo->datos.fCosto = AplicarDescuentoEstudiantil(pNuevo->datos.fCosto, (resp == 'S' || resp == 's'));

    printf("Fecha inicio (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaInicio.eDia, &pNuevo->datos.rFechaInicio.eMes, &pNuevo->datos.rFechaInicio.eAnio);
    printf("Fecha vencimiento (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaVencimiento.eDia, &pNuevo->datos.rFechaVencimiento.eMes, &pNuevo->datos.rFechaVencimiento.eAnio);

    pNuevo->datos.eIDMembresia = GenerarIDMembresia(pPrimeroM);
    strcpy(pNuevo->datos.cEstatus, "Activa");

    pNuevo->pSiguiente = pPrimeroM;
    pPrimeroM = pNuevo;

    printf("Registro exitoso. ID Membresia: %d\n", pNuevo->datos.eIDMembresia);
}

//BajaMembresiaCliente
void BajaMembresiaCliente(int eIDMembresia) {
    char cOpcion;
    TpNodoMembresia *pActual = pPrimeroM, *pAnterior = NULL;

    while (pActual != NULL && pActual->datos.eIDMembresia != eIDMembresia) {
        pAnterior = pActual;
        pActual = pActual->pSiguiente;
    }

    if (pActual == NULL) {
        printf("Error: La membresia no existe\n");
        return;
    }

    printf("¿Confirma eliminar membresia %d? (S/N): ", eIDMembresia);
    scanf(" %c", &cOpcion);

    if (cOpcion == 'S' || cOpcion == 's') {
        if (pAnterior == NULL) pPrimeroM = pActual->pSiguiente;
        else pAnterior->pSiguiente = pActual->pSiguiente;

        free(pActual);
        printf("Baja exitosa\n");
    }
}

//ModificarMembresiaCliente
void ModificarMembresiaCliente(int eIDMembresia) {
    TpNodoMembresia *temp = pPrimeroM;
    while (temp != NULL && temp->datos.eIDMembresia != eIDMembresia) temp = temp->pSiguiente;

    if (temp == NULL) {
        printf("Error: No existe\n");
        return;
    }

    printf("Nuevo Tipo: ");
    scanf("%s", temp->datos.cTipoMembresia);
    printf("Nuevo Costo: ");
    scanf("%f", &temp->datos.fCosto);
    printf("Modificacion correcta\n");
}

//ListadoMembresias
void ListadoMembresias(TpNodoMembresia *pLista) {
    if (pLista == NULL) {
        printf("Lista vacia\n");
        return;
    }
    printf("\nListado\n");
    TpNodoMembresia *actual = pLista;
    while (actual != NULL) {
        printf("ID: %d | Cliente: %d | Tipo: %s | Costo: %.2f\n", 
               actual->datos.eIDMembresia, actual->datos.eIDCliente, 
               actual->datos.cTipoMembresia, actual->datos.fCosto);
        actual = actual->pSiguiente;
    }
}
