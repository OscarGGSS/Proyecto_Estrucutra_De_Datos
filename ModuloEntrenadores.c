/******* *
	Programa: ModuloEntrenadores.c
	Autor: Oscar
	Fecha: 01-Feb-2026
	Objetivo: Crear modulo que pueda gestionar a los entrenadores
	Compilador: Dev-C++ 5.11
****** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Interfaz.h" 

//Prototipos
int ListaVaciaEntrenador(TpNodoEntrenador);
int ListaLlenaEntrenador(TpNodoEntrenador *);
TpNodoEntrenador BuscarEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void LiberarListaEntrenador(TpNodoEntrenador);
TrEntrenador LeerDatosEntrenador();
void AltaEntrenador(TpNodoEntrenador *, TrEntrenador);
void BajaEntrenador(TpNodoEntrenador *, TsCadenaEntrenador);
void ModificarEntrenador(TpNodoEntrenador *);
void ConsultarEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void ConsultarVentasEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void ListarEntrenadores(TpNodoEntrenador);
void GuardarArchivoEntrenador(TpNodoEntrenador);
void CargarArchivoEntrenador(TpNodoEntrenador *);

void PlantillaBase(char *);

//Programa Principal

int main(){
	
	//Variables
	TpNodoEntrenador pListaEntrenadores = NULL;
	int eOpcion;
	
	TsCadenaEntrenador sIdTemporal;
	TrEntrenador rEntrenadorTemporal;
	
	
	ConfigurarConsola(120, 30);
	Color(0, 11); 
	
	CargarArchivoEntrenador(&pListaEntrenadores);

	//Inicio
	do {
		PlantillaBase("VIKINGOS GYM: MODULO ENTRENADORES");
		
		GoToXY(45, 8);  printf("1. Alta de Entrenador");
		GoToXY(45, 10); printf("2. Baja de Entrenador");
		GoToXY(45, 12); printf("3. Modificar Entrenador");
		GoToXY(45, 14); printf("4. Consultar Informacion");
		GoToXY(45, 16); printf("5. Consultar Ventas");
		GoToXY(45, 18); printf("6. Listar Entrenadores");
		GoToXY(45, 20); printf("0. Salir (Guardar y Cerrar)");
		
		GoToXY(45, 24); printf("Selecciona: ");
		scanf("%d", &eOpcion);

		switch(eOpcion){
			case 1:
				rEntrenadorTemporal = LeerDatosEntrenador();
				AltaEntrenador(&pListaEntrenadores, rEntrenadorTemporal);
				system("pause"); break;
				
			case 2:
				PlantillaBase("BAJA DE ENTRENADOR");
				GoToXY(40, 10); printf("ID a eliminar: "); fflush(stdin); gets(sIdTemporal);
				BajaEntrenador(&pListaEntrenadores, sIdTemporal);
				system("pause"); break;
				
			case 3:
				ModificarEntrenador(&pListaEntrenadores);
				system("pause"); break;
				
			case 4:
				PlantillaBase("CONSULTAR INFORMACION");
				GoToXY(40, 10); printf("ID a consultar: "); fflush(stdin); gets(sIdTemporal);
				ConsultarEntrenador(pListaEntrenadores, sIdTemporal);
				system("pause"); break;
				
			case 5:
				PlantillaBase("CONSULTAR VENTAS");
				GoToXY(40, 10); printf("ID para ventas: "); fflush(stdin); gets(sIdTemporal);
				ConsultarVentasEntrenador(pListaEntrenadores, sIdTemporal);
				system("pause"); break;
				
			case 6:
				ListarEntrenadores(pListaEntrenadores);
				system("pause"); break;
				
			case 0: 
				GoToXY(40, 26); printf("Guardando cambios en archivo...");
				GuardarArchivoEntrenador(pListaEntrenadores);
				break;
				
			default: GoToXY(40, 26); printf("Opcion invalida"); system("pause");
		}
	} while(eOpcion != 0);

	LiberarListaEntrenador(pListaEntrenadores);
	return 0;
} // main

int ListaVaciaEntrenador(TpNodoEntrenador pPrimero){
	return (pPrimero == NULL);
} 

int ListaLlenaEntrenador(TpNodoEntrenador *pNuevo){
	*pNuevo = (TpNodoEntrenador) malloc(sizeof(TrNodoEntrenador));
	return (*pNuevo == NULL); 
} 

TpNodoEntrenador BuscarEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sIdBuscado){
	TpNodoEntrenador pActual = pPrimero;
	while(pActual != NULL){
		if(strcmp(pActual->rDato.sId, sIdBuscado) == 0) return pActual;
		pActual = pActual->pSiguiente;
	}
	return NULL;
} 

void LiberarListaEntrenador(TpNodoEntrenador pPrimero){
	TpNodoEntrenador pTemp;
	while(pPrimero != NULL){
		pTemp = pPrimero;
		pPrimero = pPrimero->pSiguiente;
		free(pTemp);
	}
} 

void AltaEntrenador(TpNodoEntrenador *pPrimero, TrEntrenador rEnt){
	TpNodoEntrenador pNuevo;


	if(BuscarEntrenador(*pPrimero, rEnt.sId) != NULL){
		GoToXY(40, 26); printf("El ID %s YA EXISTE.", rEnt.sId);
		return;
	}

	if(ListaLlenaEntrenador(&pNuevo)){
		GoToXY(40, 26); printf("Memoria Llena (RAM agotada).");
		return;
	}

	pNuevo->rDato = rEnt;
	pNuevo->pSiguiente = *pPrimero;
	*pPrimero = pNuevo;
	
	GoToXY(40, 26); printf("Entrenador %s registrado.", rEnt.sNombre);
} 

void BajaEntrenador(TpNodoEntrenador *pPrimero, TsCadenaEntrenador sIdBorrar){
	TpNodoEntrenador pActual = *pPrimero;
	TpNodoEntrenador pAnterior = NULL;

	if(ListaVaciaEntrenador(*pPrimero)){
		GoToXY(40, 12); printf("Lista vacia.");
		return;
	}

	while(pActual != NULL && strcmp(pActual->rDato.sId, sIdBorrar) != 0){
		pAnterior = pActual;
		pActual = pActual->pSiguiente;
	}

	if(pActual == NULL){
		GoToXY(40, 12); printf("No se encontro el ID: %s.", sIdBorrar);
	} else {
		if(pAnterior == NULL) *pPrimero = pActual->pSiguiente;
		else pAnterior->pSiguiente = pActual->pSiguiente;
		
		free(pActual);
		GoToXY(40, 12); printf("Entrenador eliminado.");
	}
} 

void ModificarEntrenador(TpNodoEntrenador *pPrimero){
	TsCadenaEntrenador sIdTemporal;
	TrEntrenador rEntrenadorTemporal;
	
	PlantillaBase("MODIFICAR ENTRENADOR");
	
	GoToXY(40, 10); printf("ID: "); fflush(stdin); gets(sIdTemporal);
	
	if(BuscarEntrenador(*pPrimero, sIdTemporal) == NULL){
		GoToXY(40, 12); printf("El ID no existe.");
	} else {
		BajaEntrenador(pPrimero, sIdTemporal);
		GoToXY(40, 12); printf("Ingrese NUEVOS datos:");

		Sleep(1000); 
		rEntrenadorTemporal = LeerDatosEntrenador();
		AltaEntrenador(pPrimero, rEntrenadorTemporal);
	}
} 

TrEntrenador LeerDatosEntrenador(){
	TrEntrenador rE;
	
	PlantillaBase("DATOS DEL ENTRENADOR");
	
	GoToXY(20, 6);  printf("ID: "); 
	GoToXY(20, 8);  printf("Nombre: "); 
	GoToXY(20, 10); printf("Ap. Paterno: "); 
	GoToXY(60, 10); printf("Ap. Materno: "); 
	
	GoToXY(20, 12); printf("Fecha Nac (dd mm aa): "); 
	GoToXY(60, 12); printf("Contrato (dd mm aa): "); 
	
	GoToXY(20, 14); printf("Sueldo: "); 
	GoToXY(60, 14); printf("Tel: "); 
	
	GoToXY(20, 16); printf("--- DIRECCION ---");
	GoToXY(20, 18); printf("Calle: "); 
	GoToXY(60, 18); printf("CP: "); 
	GoToXY(20, 20); printf("Colonia: "); 
	GoToXY(20, 22); printf("Municipio: "); 
	GoToXY(60, 22); printf("Estado: "); 

	fflush(stdin);
	GoToXY(24, 6);  gets(rE.sId);
	GoToXY(28, 8);  gets(rE.sNombre);
	GoToXY(33, 10); gets(rE.sApPaterno);
	GoToXY(73, 10); gets(rE.sApMaterno);
	
	GoToXY(40, 12); scanf("%d %d %d", &rE.rFechaNac.eDia, &rE.rFechaNac.eMes, &rE.rFechaNac.eAnio);
	GoToXY(78, 12); scanf("%d %d %d", &rE.rFechaContrato.eDia, &rE.rFechaContrato.eMes, &rE.rFechaContrato.eAnio);
	
	GoToXY(28, 14); scanf("%f", &rE.fSueldoFijo);
	fflush(stdin);
	GoToXY(65, 14); gets(rE.sTelefono);
	
	GoToXY(27, 18); gets(rE.rDireccion.sCalle);
	GoToXY(64, 18); scanf("%d", &rE.rDireccion.eCP);
	fflush(stdin);
	GoToXY(29, 20); gets(rE.rDireccion.sColonia);
	GoToXY(31, 22); gets(rE.rDireccion.sMunicipio);
	GoToXY(68, 22); gets(rE.rDireccion.sEstado);
	
	return rE;
} 

void ConsultarEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sId){
	TpNodoEntrenador p = BuscarEntrenador(pPrimero, sId);
	
	PlantillaBase("INFORMACION COMPLETA");
	
	if(p){
		GoToXY(30, 8);  printf("ID: %s", p->rDato.sId);
		GoToXY(30, 10); printf("Nombre: %s %s %s", p->rDato.sNombre, p->rDato.sApPaterno, p->rDato.sApMaterno);
		GoToXY(30, 12); printf("Fecha Nac: %02d/%02d/%d", p->rDato.rFechaNac.eDia, p->rDato.rFechaNac.eMes, p->rDato.rFechaNac.eAnio);
		GoToXY(70, 12); printf("Fecha Contrato: %02d/%02d/%d", p->rDato.rFechaContrato.eDia, p->rDato.rFechaContrato.eMes, p->rDato.rFechaContrato.eAnio);
		GoToXY(30, 14); printf("Sueldo: %.2f", p->rDato.fSueldoFijo);
		GoToXY(70, 14); printf("Telefono: %s", p->rDato.sTelefono);
		
		GoToXY(30, 16); printf("Direccion:");
		GoToXY(30, 17); printf("%s, Col. %s", p->rDato.rDireccion.sCalle, p->rDato.rDireccion.sColonia);
		GoToXY(30, 18); printf("CP %d, %s, %s", p->rDato.rDireccion.eCP, p->rDato.rDireccion.sMunicipio, p->rDato.rDireccion.sEstado);
		
	} else {
		GoToXY(40, 12); printf("No encontrado.");
	}
	GoToXY(40, 25); 
} 

void ListarEntrenadores(TpNodoEntrenador pPrimero){
	int y = 8; 
	
	PlantillaBase("LISTADO DE ENTRENADORES");
	
	GoToXY(10, 6); printf("%-10s %-20s %-20s", "ID", "NOMBRE", "AP. PATERNO");
	GoToXY(10, 7); printf("--------------------------------------------------");
	
	while(pPrimero != NULL){
		GoToXY(10, y); 
		printf("%-10s %-20s %-20s", pPrimero->rDato.sId, pPrimero->rDato.sNombre, pPrimero->rDato.sApPaterno);
		pPrimero = pPrimero->pSiguiente;
		y++;
		
		if(y > 25) { 
			GoToXY(80, 26); printf("Siguiente pagina...");
			getch();
			PlantillaBase("LISTADO DE ENTRENADORES (Cont.)");
			y = 8;
		}
	}
	GoToXY(40, 26);
} 

void ConsultarVentasEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sId){
	PlantillaBase("CONSULTAR VENTAS");
	
	if(BuscarEntrenador(pPrimero, sId)){
		GoToXY(40, 12); printf("[PENDIENTE DE INTEGRAR]");
	} else {
		GoToXY(40, 12); printf("No encontrado.");
	}
	GoToXY(40, 25);
} 

void GuardarArchivoEntrenador(TpNodoEntrenador pPrimero){
	FILE *pArchivo;
	pArchivo = fopen("Entrenadores.dat", "wb");
	
	if(pArchivo == NULL){
		printf("Error al abrir archivo.");
		return;
	}
	
	while(pPrimero != NULL){
		fwrite(&(pPrimero->rDato), sizeof(TrEntrenador), 1, pArchivo);
		pPrimero = pPrimero->pSiguiente;
	}
	fclose(pArchivo);
} 

void CargarArchivoEntrenador(TpNodoEntrenador *pPrimero){
	FILE *pArchivo;
	TrEntrenador rEnt;
	TpNodoEntrenador pNuevo;
	
	pArchivo = fopen("Entrenadores.dat", "rb");
	if(pArchivo == NULL) return; 
	
	while(fread(&rEnt, sizeof(TrEntrenador), 1, pArchivo)){
		if(ListaLlenaEntrenador(&pNuevo)) break;
		
		pNuevo->rDato = rEnt;
		pNuevo->pSiguiente = *pPrimero;
		*pPrimero = pNuevo;
	}
	fclose(pArchivo);
}

void PlantillaBase(char *titulo) {
	system("cls");
	DibujarMarco(2, 1, 117, 28);
	DibujarMarco(30, 2, 90, 4);
	CentrarTexto(3, titulo);
}

