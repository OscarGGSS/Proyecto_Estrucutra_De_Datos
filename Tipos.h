/* ***
   Programa: Tipos.h
   Fecha: 01-02-2026
   Objetivo: Crear una biblioteca que contenga todos los tipos y prototipos del sistema
   Compilador: Dev-C++ 5.11
   Versión: 1.0
*** */

#ifndef TIPOS_H
#define TIPOS_H

//Tipos de: ModuloClientes
typedef char TsCadena[30]; //Tipo Cadena

typedef struct rCliente {
	
	TsCadena sNombre;
	TsCadena sTelefono;
	int eId;
	struct rCliente *pSiguiente;
	
} TrCliente; //TrCliente (Registro de TrCliente)

typedef TrCliente *TpCliente; //TpCliente (Apuntador a rCliente)

////////////////////////////////////////////////////////////////////////////

//Tipos de: ModuloEntrenadores

typedef char TsCadenaEntrenador[50]; //Tipo Cadena 

typedef struct {
	
	int eDia; int eMes; int eAnio;
	
} TrFechaEntrenador; //Registro TrFechaEntrenador (Registro de fecha)

typedef struct {
	
	TsCadenaEntrenador sCalle; int eCP;
	TsCadenaEntrenador sColonia; TsCadenaEntrenador sMunicipio; TsCadenaEntrenador sEstado;
	
} TrDireccionEntrenador; //Registro TrDireccionEntrenador (Registro de dirección)

typedef struct {
	
	TsCadenaEntrenador sId; 
	TsCadenaEntrenador sNombre;
	TsCadenaEntrenador sApPaterno;
	TsCadenaEntrenador sApMaterno;
	TrFechaEntrenador rFechaNac;
	TrFechaEntrenador rFechaContrato;
	float fSueldoFijo;
	TsCadenaEntrenador sTelefono;
	TrDireccionEntrenador rDireccion;
	
} TrEntrenador; // Registro TrEntrenador (Registro de entrenador)

typedef struct rNodoEntrenador {
	
	TrEntrenador rDato;
	struct rNodoEntrenador *pSiguiente;
	
} TrNodoEntrenador; // Registro TrNodoEntrenador (Registro de nodo)

typedef TrNodoEntrenador *TpNodoEntrenador; // Apuntador a TrNodoEntrenador

////////////////////////////////////////////////////////////////////////////

//Tipos de: ModuloMembresia

typedef struct rRegistroFecha{
	
    int eDia;  
    int eMes;  
    int eAnio; 
    
} TrRegistroFecha; //TrFecha (Registro de fecha)

typedef struct TrMembresia{
	
    int eIDMembresia;            
    char cTipoMembresia[21];     
    float fCosto;                
    TrRegistroFecha rFechaInicio;  
    TrRegistroFecha rFechaVencimiento; 
    int eIDCliente;              
    char cEstatus[15]; 
	          
} rMembresia; //TrMembresia (Registro de membresia)

typedef struct rNodo {
	
    rMembresia datos;
    struct rNodo *pSiguiente;
    
} TrNodo; // Nodo (Registro de nodo)

typedef TrNodo *pPrimeroM; //Apuntador a rNodo

////////////////////////////////////////////////////////////////////////////

//Tipos de: ModuloSuplemento

typedef struct rSuplemento{
	
    int eIdProducto;        
    float fPrecio;          
    TrRegistroFecha eFechaCaducidad;    
    int eDisponibilidad;  
	 
} TrSuplemento; //TrSuplemento (Registro de suplemento)

typedef struct rNodoSuplemento {
	
    rSuplemento datos;      
    struct NodoS *pSiguiente;
    
} TrNodoSuplemento; //TrSuplemento (Registro de suplemento)

typedef TrNodoSuplemento *pInicioInv; // Apuntador a rNodoSuplemento

#endif
