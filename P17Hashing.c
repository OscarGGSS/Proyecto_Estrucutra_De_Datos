/******* *
	Programa: P17Hashing.c
	Autor: Oscar
	Fecha: 20-oct-2025
	Objetivo: Programa que muestra el uso de hashing con residuo de la división
	Compilador: Dev-C++ 5.11
****** */


//Bibliotecas

#include "P18ListaLigadaConPrimero.c"

//Constantes

#define DIVISOR 97

//Tipos

typedef TpNodo TaTablaHash [DIVISOR];

//Prototipos

int ConvertirCadenaAEntero(TsCadena );

int HashPorResiduo (int);

TrNodo LeerDatosEmpleado();

void InsertarHashing(TaTablaHash, TrNodo);

void EliminarHashing(TaTablaHash, TsCadena);

void RecorrerHashing(TaTablaHash);

void InicializarTabla(TaTablaHash);

void LiberarHashing(TaTablaHash);

void ConsultarHashing(TaTablaHash, TsCadena);





//Programa Principal

int main(){
	
	//Variables
	
	TaTablaHash aTablaHash;
	
	int eOpcion;
	
	TrNodo rNodo;
	
	TsCadena sNombre;
	
	InicializarTabla(aTablaHash);
	
	do{
		printf("Hashing de empleados\n\n");
		
		printf("1. Agregar Empleado\n");
		
		printf("2. Borrar Empleado\n");
		
		printf("3. Consultar Empleado\n");
		
		printf("4. Listar Todos Los Empleados\n");
		
		printf("0. Salir\n\n");
		
		printf("Selecciona una opci%cn: ", 162);
		scanf("%d", &eOpcion);
		
		switch(eOpcion){
			
			case 1:
				
				rNodo = LeerDatosEmpleado();
				
				InsertarHashing(aTablaHash, rNodo);
				
				break;			
				
			case 2:
				
				printf("Ingrese el nombre del empleado a borrar: ");
				
				fflush(stdin);
				gets(sNombre);
				
				EliminarHashing(aTablaHash, sNombre);
				
				break;
				
			case 3: 
			
				printf("Ingrese el nombre del empleado a consultar: ");
				
				fflush(stdin);
				gets(sNombre);
				
				ConsultarHashing(aTablaHash, sNombre);
				
				break; 
				
			case 4:
				
				RecorrerHashing(aTablaHash);
				
				break;
				
			case 0:
			
				printf("Adi%cs", 162);
				
				break;
							
			default:
				
				printf("Opci%cn inv%clida", 162, 160);
		}
		
		
		getchar();
	} while (eOpcion != 0);
	
	LiberarHashing(aTablaHash);
	
	return 0;
	
}


int ConvertirCadenaAEntero(TsCadena sNombre){
	//Variables
	
	int eSuma = 0;
	int eCaracter;
	
	//Inicio
	
	for(eCaracter = 0; eCaracter < strlen(sNombre); eCaracter++){
		
		eSuma += sNombre[eCaracter];
		
	}
	
	return eSuma;
} //ConvertirCadenaAEntero

int HashPorResiduo (int eClave){
	
	return eClave % DIVISOR;
} // HashPorResiduo


TrNodo LeerDatosEmpleado(){
	
	//Variables
	
	TrNodo rNodo;
	
	//Inicio
	
	printf("Ingrese los siguientes datos del empleado: \n\n");
	
	printf("Nombre: ");
	fflush(stdin);
	gets(rNodo.sNombre);
	
	printf("Sueldo: ");
	scanf("%f", &rNodo.fSueldo);
	
	printf("Departamento: ");
	fflush(stdin);
	gets(rNodo.sDepartamento);
	
	return rNodo;
} //LeerDatosEmpleado


void InsertarHashing(TaTablaHash aTablaHash, TrNodo rNodo){
	
	//Variables
	
	int ePos;
	
	//Inicio
	
	ePos = HashPorResiduo(ConvertirCadenaAEntero(rNodo.sNombre));
	
	if(Buscar(aTablaHash[ePos], rNodo.sNombre) != NULL){
		
		printf("Ya existe el empleado con el nombre: %s ", rNodo.sNombre);
			
	} else {
		
		Agregar(&aTablaHash[ePos], rNodo);
		
		printf("Empleado %s Agregado correctamente", rNodo.sNombre);
	}
	
}// InsertarHashing


void EliminarHashing(TaTablaHash aTablaHash, TsCadena sNombre){

	//Variables
	
	int ePos;
	
	//Inicio
	
	ePos = HashPorResiduo(ConvertirCadenaAEntero(sNombre));
	
	if(Buscar(aTablaHash[ePos], sNombre) == NULL){
		
		printf("No se encontr%c el empleado con el nombre: %s", 162, sNombre);
		
	} else {
		
		Eliminar(&aTablaHash[ePos], sNombre);
		
		printf("El empleado: %s Fue borrado Correctamente", sNombre);
	}
}

void RecorrerHashing(TaTablaHash aTablaHash){
	
	//Variables
	
	int ePos;
	
	//inicio
	
	printf("%-25s %-7s %-15s", "Nombre", "Sueldo", "Departamento");
	
	for(ePos = 0; ePos < DIVISOR; ePos++ ){
		
		RecorrerDePrimeroAUltimo(aTablaHash[ePos]);
	}
} // RecorrerHashing


void InicializarTabla(TaTablaHash aTablaHash){
	
	int eContador;
	
	for(eContador = 0; eContador < DIVISOR; eContador++){
		
		aTablaHash[eContador] = NULL;
		
	}
	
	
}


void LiberarHashing(TaTablaHash aTablaHash){
	
	//Variables
	
	int ePos;
	
	//Inicio
	
	for(ePos = 0; ePos < DIVISOR; ePos++){
		
		LiberarListaRecursiva(aTablaHash[ePos]);
	}
	
} //LiberarHashing


void ConsultarHashing(TaTablaHash aTablaHash, TsCadena sNombre){

	//Variables
	
	int ePos;
	TpNodo pNodo;
	
	//Inicio
	
	ePos = HashPorResiduo(ConvertirCadenaAEntero(sNombre))	;
	
	pNodo = Buscar(aTablaHash[ePos], sNombre);
	
	if(pNodo == NULL){
		
		printf("No se encontr%c el empleado con el nombre: %s", 162, sNombre);
		
	} else {
		
		printf("Los datos del empleado son : %s", sNombre);
		
		printf("\n\nNombre: %s", pNodo->sNombre);
		printf("\nSueldo: %7.2f", pNodo->fSueldo);
		printf("\nDepartamento: %s", pNodo->sDepartamento);
		
	}
} //ConsultarHashing


