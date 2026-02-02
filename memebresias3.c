/* ***
	Programa: PMembresias.c
	Autor: Jennifer García
	Fecha: 01/02/2026
	Objetivo: Gestionar las membresías de Vikingos Gym
	Compilador: Dev-C++ 5.11
	Versión: 0.2
*** */

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Tipos

typedef struct rRegistroFecha {
    int eDia;  
    int eMes;  
    int eAnio; 
} TrRegistroFecha; 

typedef struct TrMembresia {
    int eIDMembresia;            
    char cTipoMembresia[21];     
    float fCosto;                
    TrRegistroFecha rFechaInicio;  
    TrRegistroFecha rFechaVencimiento; 
    int eIDCliente;              
    char cEstatus[15];           
} rMembresia; 

typedef struct rNodo {
    rMembresia datos;
    struct rNodo *pSiguiente;
} TrNodo; 

typedef TrNodo *pPrimeroM; 

pPrimeroM pInicioMem = NULL; 

//Prototipos
int GenerarIDMembresia(pPrimeroM pLista);
bool verificarClienteExiste(int id);
void AltaMembresiaCliente();
void BajaMembresiaCliente(int eIDMembresia);
void ModificarMembresiaCliente(int eIDMembresia);
void ListadoMembresias(pPrimeroM pLista);

//Programa principal
int main() {
    int op, idAux;
    do {
        printf("\nVIKINGOS GYM - MEMBRESIAS\n1 Alta\n2 Baja\n3 Modificar\n4 Listado\n5 Salir\nOpcion: ");
        scanf("%d", &op);
        switch (op) {
            case 1: AltaMembresiaCliente(); break;
            case 2: printf("ID a eliminar: "); scanf("%d", &idAux); BajaMembresiaCliente(idAux); break;
            case 3: printf("ID a modificar: "); scanf("%d", &idAux); ModificarMembresiaCliente(idAux); break;
            case 4: ListadoMembresias(pInicioMem); break;
        }
    } while (op != 5);
    return 0;
}

int GenerarIDMembresia(pPrimeroM pLista) {
    if (pLista == NULL) return 10001;
    int max = 0;
    TrNodo *temp = pLista;
    while (temp != NULL) {
        if (temp->datos.eIDMembresia > max) max = temp->datos.eIDMembresia;
        temp = temp->pSiguiente;
    }
    return max + 1;
}

bool verificarClienteExiste(int id) {
    return (id >= 10000 && id <= 99999);
}

void AltaMembresiaCliente() {
    TrNodo *pNuevo = (TrNodo*)malloc(sizeof(TrNodo));
    if (pNuevo == NULL) return;
    printf("ID Cliente: "); scanf("%d", &pNuevo->datos.eIDCliente);
    if (!verificarClienteExiste(pNuevo->datos.eIDCliente)) {
        printf("Error: Cliente no existe.\n");
        free(pNuevo);
        return;
    }
    printf("Tipo Membresia: "); scanf("%s", pNuevo->datos.cTipoMembresia);
    printf("Costo: "); scanf("%f", &pNuevo->datos.fCosto);
    printf("Fecha Inicio (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaInicio.eDia, &pNuevo->datos.rFechaInicio.eMes, &pNuevo->datos.rFechaInicio.eAnio);
    printf("Fecha Vencimiento (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaVencimiento.eDia, &pNuevo->datos.rFechaVencimiento.eMes, &pNuevo->datos.rFechaVencimiento.eAnio);
    
    pNuevo->datos.eIDMembresia = GenerarIDMembresia(pInicioMem);
    strcpy(pNuevo->datos.cEstatus, "Activa");
    pNuevo->pSiguiente = pInicioMem;
    pInicioMem = pNuevo;
    printf("Registro exitoso. ID: %d\n", pNuevo->datos.eIDMembresia);
}

void BajaMembresiaCliente(int id) {
    TrNodo *pAct = pInicioMem, *pAnt = NULL;
    while (pAct != NULL && pAct->datos.eIDMembresia != id) {
        pAnt = pAct; pAct = pAct->pSiguiente;
    }
    if (pAct == NULL) { printf("No encontrado.\n"); return; }
    if (pAnt == NULL) pInicioMem = pAct->pSiguiente;
    else pAnt->pSiguiente = pAct->pSiguiente;
    free(pAct);
    printf("Baja exitosa.\n");
}

void ModificarMembresiaCliente(int id) {
    TrNodo *temp = pInicioMem;
    while (temp != NULL && temp->datos.eIDMembresia != id) temp = temp->pSiguiente;
    if (temp == NULL) { printf("No existe.\n"); return; }
    printf("Nuevo Costo: "); scanf("%f", &temp->datos.fCosto);
    printf("Modificado.\n");
}

void ListadoMembresias(pPrimeroM pLista) {
    if (pLista == NULL) { printf("Vacio.\n"); return; }
    while (pLista != NULL) {
        printf("ID: %d | Cliente: %d | Costo: %.2f\n", 
               pLista->datos.eIDMembresia, pLista->datos.eIDCliente, pLista->datos.fCosto);
        pLista = pLista->pSiguiente;
    }
}
