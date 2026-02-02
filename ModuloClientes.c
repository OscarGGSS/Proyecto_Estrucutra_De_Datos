/* ***
   Programa: ModuloClientes.c
   Autor: Islas Isis
   Fecha: 01-02-2026
   Objetivo:El sistema registrará los datos generales por cada cliente, se implementaran listas ligadas.
   Compilador: Dev-C++ 5.11
   Versión: 1.0
*** */

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipo

typedef char TsCadena[30];

typedef struct rCliente {
	
	TsCadena sNombre;
	TsCadena sTelefono;
	int eId;
	struct rCliente *pSiguiente;
	
} TrCliente;

typedef TrCliente *TpCliente;

//Prototipos
int ListaVacia(TpCliente);
int ListaLlena(TpCliente *);
void GenerarIdCliente(TpCliente, int *);
void PrepararNodo(TpCliente, int, TsCadena, TsCadena);
void AgregarEnListaVacia(TpCliente *, TpCliente *, TpCliente);
void AgregarDespuesDeUltimo (TpCliente *, TpCliente);
void AgregarCliente(TpCliente *, TpCliente *);
void DarBajaCliente(TpCliente *, TpCliente *);
void ModificarCliente(TpCliente);
void ConsultarCliente(TpCliente);
void GuardarArchivo(TpCliente);
void CargarArchivo(TpCliente *, TpCliente *);

//Programa principal
int main (){

	//Variables 
	TpCliente pPrimero = NULL, pUltimo = NULL;
	int eOpcion;

    do {

        printf("\n--- Men%c de clientes ---", 163);
        printf("\n 1. Agregar Cliente");
        printf("\n 2. Consultar Cliente (por ID)");
        printf("\n 3. Modificar Cliente");
        printf("\n 4. Dar de Baja Cliente");
        printf("\n 0. Guardar y Salir");

        printf("\n Seleccione una opcion: ");
        scanf("%d", &eOpcion);

        switch (eOpcion) {
        	
            case 1:
            	
                AgregarCliente(&pPrimero, &pUltimo);
                break;

            case 2:
            	
                ConsultarCliente(pPrimero);
                break;

            case 3:
            	
                ModificarCliente(pPrimero);
                break;

            case 4:
            	
                DarBajaCliente(&pPrimero, &pUltimo);
                break;

            case 0:
            	
                GuardarArchivo(pPrimero);
                printf("\n Saliendo del sistema...\n"); 
                break;

            default:
                printf("\nOpci%cn inv%clida", 162, 160);
                break;
        }

    } while (eOpcion != 0);

    return 0;
    
} //Main

int ListaVacia(TpCliente pPrimero){
	
	return (pPrimero == NULL);
	
} //ListaVacia

int ListaLlena(TpCliente *pNuevo){

	*pNuevo = (TpCliente)malloc(sizeof(TrCliente));
	
	return (*pNuevo == NULL);	
	
} //ListaLlena

void GenerarIdCliente(TpCliente pPrimero, int *pIdClienteNuevo) {
    
    //Variables
    int eMaxId;
    TpCliente pAuxiliar;
    
    eMaxId = 0;
    pAuxiliar = pPrimero;
    
    while (pAuxiliar != NULL) {
        
        if (pAuxiliar->eId > eMaxId) {
        	
            eMaxId = pAuxiliar->eId;
            
        }
        
        pAuxiliar = pAuxiliar->pSiguiente;
        
    }
    
    *pIdClienteNuevo = eMaxId + 1;
    
} //GenerarIdCliente

void PrepararNodo(TpCliente pNuevo, int eIdNuevo, TsCadena sNom, TsCadena sTel) {
    
    pNuevo->eId = eIdNuevo;
    
    strcpy(pNuevo->sNombre, sNom);
    strcpy(pNuevo->sTelefono, sTel);
    
    pNuevo->pSiguiente = NULL;
    
} //PrepararNodo


void AgregarEnListaVacia(TpCliente *pPrimero, TpCliente *pUltimo, TpCliente pNuevo){
	
	*pPrimero = pNuevo;
	*pUltimo = pNuevo;
	
} //AgregarEnListaVacia

void AgregarDespuesDeUltimo (TpCliente *pUltimo , TpCliente pNuevo){
	
	(*pUltimo)->pSiguiente = pNuevo;
	*pUltimo = pNuevo;
	
} //AgregarDespuesDeUltimo

void AgregarCliente(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
    TpCliente pNuevo;
    int eIdNuevo;
    TsCadena sNom, sTel;

    if (ListaLlena(&pNuevo)) {
    	
        printf("\n Error: No se pueden agregar m%cs clientes", 160);
        
    }

    GenerarIdCliente(*pPrimero, &eIdNuevo);

    printf("\n--- Registro de nuevo cliente con el ID: %d ---\n", eIdNuevo);
    printf("\nIngrese el nombre (1er nombre y 1er apellido): ");
    fflush(stdin);
    gets(sNom);
    
    printf("\nIngrese el n%cmero de telefono: ", 163);
    fflush(stdin);
    gets(sTel);

    PrepararNodo(pNuevo, eIdNuevo, sNom, sTel);

    if (ListaVacia(*pPrimero)) {
    	
        AgregarEnListaVacia(pPrimero, pUltimo, pNuevo);
        
    } else {
    	
        AgregarDespuesDeUltimo(pUltimo, pNuevo);
        
    }

    printf("\nEl registro se realiz%c con %cxito", 162, 130);
    
} //AgregarCliente

void DarBajaCliente(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
    int eIdBuscar;
    char cOpcion; 
    TpCliente pActual, pAnterior = NULL;

    if (ListaVacia(*pPrimero)) {
    	
        printf("\nNo hay clientes para dar de baja");
        
        return;
    }

    printf("\nIngrese el ID del cliente a dar de baja: ");
    scanf("%d", &eIdBuscar);
    fflush(stdin);

    pActual = *pPrimero;

    while (pActual != NULL && pActual->eId != eIdBuscar) {
    	
        pAnterior = pActual;
        pActual = pActual->pSiguiente;
        
    }

    if (pActual == NULL) {
    	
        printf("\nError: El ID (%d) no existe", eIdBuscar);
        
    } else {
    	
        printf("\n-- Datos del cliente --");
        printf("\nID: %d", pActual->eId);
        printf("\nNombre: %s", pActual->sNombre);
        printf("\nTelefono: %s\n", pActual->sTelefono);


        printf("\n¿Desea borrar este cliente? (S/N): ");
        scanf(" %c", &cOpcion); 
        fflush(stdin);

        if (cOpcion == 'S' || cOpcion == 's') {
        	
            if (pActual == *pPrimero) {
            	
                *pPrimero = (*pPrimero)->pSiguiente;
                
                if (*pPrimero == NULL) *pUltimo = NULL;
                
            } else {
            	
                pAnterior->pSiguiente = pActual->pSiguiente;
                
                if (pActual == *pUltimo) {
                	
                    *pUltimo = pAnterior;
                    
                }
                
            }
            
            free(pActual);
            
            printf("\nEl registro del cliente se borr%c de forma correcta", 162);
            
        } else {
        	
            printf("\nNo se realizara la funci%cn", 162);
            
        }
        
    }
    
} //DarBajaCliente

void ModificarCliente(TpCliente pPrimero) {
	
	//Variables
    int eIdBuscar;
    char cOpcion;
    TpCliente pAuxiliar;

    if (ListaVacia(pPrimero)) {
    	
        printf("\nNo hay clientes para modificar");
           
    }

    printf("\n Ingrese el ID del cliente a modificar: ");
    scanf("%d", &eIdBuscar);
    fflush(stdin);

    pAuxiliar = pPrimero;

    while (pAuxiliar != NULL && pAuxiliar->eId != eIdBuscar) {
    	
        pAuxiliar = pAuxiliar->pSiguiente;
        
    }

    if (pAuxiliar == NULL) {
    	
        printf("\nError: El ID (%d) no existe", eIdBuscar);
        
    } else {

        printf("\n-- Datos del cliente --");
        printf("\nID: %d", pAuxiliar->eId);
        printf("\nNombre: %s", pAuxiliar->sNombre);
        printf("\nTelefono: %s \n", pAuxiliar->sTelefono);

        printf("\n ¿Desea modificar a este cliente? (S/N): ");
        scanf(" %c", &cOpcion);
        fflush(stdin);

        if (cOpcion == 'S' || cOpcion == 's') {

            printf("\n---Modificando Cliente---");
            
            printf("\nIngrese el nuevo nombre: ");
            gets(pAuxiliar->sNombre);
            
            printf("\nIngrese nuevo telefono: ");
            gets(pAuxiliar->sTelefono);

            if (strlen(pAuxiliar->sNombre) > 0) {
            	
                printf("\nEl registro se modific%c de manera correcta", 162);
                
            } else {
            	
                printf("\nError al guardar los datos. Intente de nuevo\n");
            }

        } else if (cOpcion == 'N' || cOpcion == 'n') {
        	
            printf("\n No se realizara la funci%cn", 162);
            
        } else {
        	
            printf("\nNo se realizara la funci%cn", 162);
            
        }
        
    }
    
} //ModificarCliente

void ConsultarCliente(TpCliente pPrimero) {
	
    // Variables
    int eIdBuscar;
    TpCliente pAuxiliar;
    int lEncontrado = 0; 

    if (ListaVacia(pPrimero)) {
    	
        printf("\nNo hay clientes que consultar");
        return;
        
    }

    printf("\nIngrese el ID del cliente que desea consultar: ");
    scanf("%d", &eIdBuscar);
    fflush(stdin);

    pAuxiliar = pPrimero;

    while (pAuxiliar != NULL) {
        
        if (pAuxiliar->eId == eIdBuscar) {

            printf("\n-- Datos del cliente --");
            printf("\nID: %d", pAuxiliar->eId);
            printf("\nNombre: %s", pAuxiliar->sNombre);
            printf("\nTelefono: %s \n", pAuxiliar->sTelefono);
            
            lEncontrado = 1;
            break;
        }
        
        pAuxiliar = pAuxiliar->pSiguiente;
    }

    if (lEncontrado == 0) {
        printf("\n El cliente con ID %d no existe\n", eIdBuscar);
        
    }

} //ConsultarCliente

void GuardarArchivo(TpCliente pPrimero) {
	
    FILE *pFile;
    
    TpCliente pAuxiliar = pPrimero;

    pFile = fopen("clientes.dat", "wb"); 
    
    if (pFile == NULL) {
    	
        printf("\nError al abrir el archivo para guardar");
        
    }

    while (pAuxiliar != NULL) {

        fwrite(pAuxiliar, sizeof(TrCliente), 1, pFile);
        
        pAuxiliar = pAuxiliar->pSiguiente;
        
    }

    fclose(pFile);

    printf("\nDatos guardados en 'clientes.dat' correctamente");
    
} //GuardarArchivo

void CargarArchivo(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
    FILE *pFile;
    TrCliente rTemp;
    TpCliente pNuevo;

    pFile = fopen("clientes.dat", "rb");
    
    while (fread(&rTemp, sizeof(TrCliente), 1, pFile)) {
 
        if (!ListaLlena(&pNuevo)) {
        	

            pNuevo->eId = rTemp.eId;
            strcpy(pNuevo->sNombre, rTemp.sNombre);
            strcpy(pNuevo->sTelefono, rTemp.sTelefono);
            pNuevo->pSiguiente = NULL;

            if (ListaVacia(*pPrimero)) {
            	
                AgregarEnListaVacia(pPrimero, pUltimo, pNuevo);
                
            } else {
            	
                AgregarDespuesDeUltimo(pUltimo, pNuevo);
                
            }
            
        }
        
    }

    fclose(pFile);
    
    printf("\nDatos cargados exitosamente desde el archivo");
    
} //CargarArchivo
