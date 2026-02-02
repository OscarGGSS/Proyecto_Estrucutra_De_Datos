/* ***
	Programa: PSuplementos.c
	Autor: Jennifer García
	Fecha: 01/02/2026
	Objetivo: Crear un programa de gestión de suplementos para Vikingos Gym 
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

typedef struct rSuplemento {
    int eIdProducto;       
    float fPrecio;         
    TrRegistroFecha eFechaCaducidad; 
    int eDisponibilidad;  
} TrSuplemento; 

typedef struct rNodoSuplemento {
    TrSuplemento datos;      
    struct rNodoSuplemento *pSiguiente;
} TrNodoSuplemento; 

typedef TrNodoSuplemento *pInicioInv; 

pInicioInv pListaSup = NULL; 

//Prototipos
int GenerarIdSuplemento(pInicioInv pLista);
void AltaSuplemento();
void BajaSuplemento(int eIdProducto);
void ModificarProducto(int eIdProducto);
void Inventario(pInicioInv pLista);

//Programa principal
int main() {
    int op, idAux;
    do {
        printf("\nVIKINGOS GYM - SUPLEMENTOS\n1 Alta\n2 Baja\n3 Modificar\n4 Inventario\n5 Salir\nOpcion: ");
        scanf("%d", &op);
        switch(op) {
            case 1: AltaSuplemento(); break;
            case 2: printf("ID a eliminar: "); scanf("%d", &idAux); BajaSuplemento(idAux); break;
            case 3: printf("ID a modificar: "); scanf("%d", &idAux); ModificarProducto(idAux); break;
            case 4: Inventario(pListaSup); break;
        }
    } while (op != 5);
    return 0;
}

int GenerarIdSuplemento(pInicioInv pLista) {
    if (pLista == NULL) return 20001;
    TrNodoSuplemento *temp = pLista;
    int max = 0;
    while (temp != NULL) {
        if (temp->datos.eIdProducto > max) max = temp->datos.eIdProducto;
        temp = temp->pSiguiente;
    }
    return max + 1;
}

void AltaSuplemento() {
    TrNodoSuplemento *pNuevo = (TrNodoSuplemento *)malloc(sizeof(TrNodoSuplemento));
    if (pNuevo == NULL) return;
    pNuevo->datos.eIdProducto = GenerarIdSuplemento(pListaSup); 
    printf("Precio: "); scanf("%f", &pNuevo->datos.fPrecio); 
    printf("Fecha caducidad (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.eFechaCaducidad.eDia, &pNuevo->datos.eFechaCaducidad.eMes, &pNuevo->datos.eFechaCaducidad.eAnio); 
    printf("Disponibilidad: "); scanf("%d", &pNuevo->datos.eDisponibilidad); 

    pNuevo->pSiguiente = pListaSup;
    pListaSup = pNuevo;
    printf("Registro exitoso. ID: %d\n", pNuevo->datos.eIdProducto); 
}

void BajaSuplemento(int id) {
    char cOpcion;
    TrNodoSuplemento *pAct = pListaSup, *pAnt = NULL;
    while (pAct != NULL && pAct->datos.eIdProducto != id) {
        pAnt = pAct; pAct = pAct->pSiguiente;
    }
    if (pAct == NULL) { printf("No encontrado.\n"); return; }
    printf("¿Confirmar borrar? (S/N): ");
    scanf(" %c", &cOpcion);
    if (cOpcion == 'S' || cOpcion == 's') {
        if (pAnt == NULL) pListaSup = pAct->pSiguiente;
        else pAnt->pSiguiente = pAct->pSiguiente;
        free(pAct);
        printf("Borrado exitoso.\n");
    }
}

void ModificarProducto(int id) {
    TrNodoSuplemento *temp = pListaSup;
    while (temp != NULL && temp->datos.eIdProducto != id) temp = temp->pSiguiente;
    if (temp == NULL) { printf("No encontrado.\n"); return; }
    printf("Nueva Disponibilidad: "); scanf("%d", &temp->datos.eDisponibilidad);
    printf("Modificado correctamente.\n");
}

void Inventario(pInicioInv pLista) {
    if (pLista == NULL) { printf("Vacio.\n"); return; }
    while (pLista != NULL) {
        printf("ID: %d | Precio: %.2f | Stock: %d | Caducidad: %02d/%02d/%d\n", 
               pLista->datos.eIdProducto, pLista->datos.fPrecio, pLista->datos.eDisponibilidad,
               pLista->datos.eFechaCaducidad.eDia, pLista->datos.eFechaCaducidad.eMes, pLista->datos.eFechaCaducidad.eAnio);
        pLista = pLista->pSiguiente;
    }
}
