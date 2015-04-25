#ifndef MICRAGENETIC_H
#define MICRAGENETIC_H

#include <stdlib.h>//Para numeros aleatorios
#include <ctime>//Para iniciar la semilla con el tiempo
#include <functional>//Para acceso a greater
#include <algorithm>//Para SORT
#include "OperadoresSeleccion.h"//Para metodos de seleccion alternativos al predeterminado (ruleta)

//Descripcion: 	Implementacion de un algoritmo genetico basico basado en plantillas. Se confia en que los objetos implementen IIndividuo.
//Detalles: Seleccion de reproductores por ruleta (predeterminado)/torneo/aleatorio puro
//			Probabilidad de solicitar la mutacion de los nuevos individuos configurable
//			Reemplazo por seleccion de los N mejores
//Autor: Nicolas C ;; -#VERSION: 3.0
enum TiposSeleccion{SelRuleta, SelTorneo, SelAleatorioPuro};

template <class T> class MicraGENETIC{
	public:
		//Constructor-> Se requiere el numero de individuos total, cuantos de ellos son reproductores y el vector que los contiene
		MicraGENETIC(int nIndividuos, int nReproductores, double probabilidadMutacion,
			   TiposSeleccion opSelector=SelRuleta, int tTorneo=4);
		T optimizarPorCiclos(int nCiclos);//El proceso de optimizacion no se detiene hasta completar el numero de ciclos dado
		T optmizacionMixta(int nCiclosMaximos, double aptitudAceptable);//La optmizacion se realiza hasta consumir los ciclos o llegar a un valor de aptitud aceptable en la mejor solucion
		//Nota: 		No se incluye un proceso basado solo en alcanzar una aptitud aceptable porque podria no terminar nunca
		~MicraGENETIC();//Destructor
		//Acceso a los atributos:
		int getNIndividuos();
		void setNIndividuos(int nIndividuos);
		int getNReproductores();
		void setNReproductores(int nReproductores);
		double getProbabilidadMutacion();
		void setProbabilidadMutacion(double probabilidadMutacion);
		void reiniciarSemillasAleatorias();
		void setOpSelector(TiposSeleccion opSelector);
		TiposSeleccion getOpSelector();
		void setTTorneo(int tTorneo);
		int getTTorneo();
	private:
		//Atributos configurables:
		int nReproductores;
		int nIndividuos;
		double probabilidadMutacion;
		//Atributos gestionados solo internamente para ahorrar calculos:
		int nDescendientes;
		int nIndividuosYnDescendientes;
		T* poblacion;//Region de memoria para guardar los individuos de cada ciclo
		T* nuevaPoblacion;//Region de memoria para la poblacion del ciclo siguiente (mas consumo de memoria constante, menos reservas dinamicas)
		double valorTotalPoblacion;//Para asignar las porciones de la seleccion por ruleta. Se calcula conforme se van alterando las poblaciones
		T* descendencia;//Region de memoria para guardar los descendientes de cada ciclo
		T* finDescendencia;
		//Fnuciones internas:
		void limpiarEntorno();
		void generarPoblacionInicial();
		void escogerReproducirMutar();
		void seleccionarReemplazo();
		TiposSeleccion opSelector;
		int tTorneo;//Tamagno del torneo para este tipo de seleccion
};

#endif

///IMPLEMENTACION:
///Constructor del entorno de optimizacion
template <class T> MicraGENETIC<T>::MicraGENETIC(int nIndividuos, int nReproductores, double probabilidadMutacion,
												 TiposSeleccion opSelector, int tTorneo){
	this->nIndividuos = nIndividuos;
	this->nReproductores = nReproductores;
	this->nDescendientes = nReproductores/2;
	this->probabilidadMutacion = probabilidadMutacion;
	this->nIndividuosYnDescendientes = nDescendientes + nIndividuos;
	this->opSelector = opSelector;
	this->tTorneo = tTorneo;
}

///Metodo que optimiza hasta alcanzar un cierto numero de ciclos <Evitando cualquier tipo de comprobacion de la mejor solucion encontrada>
template <class T> T MicraGENETIC<T>::optimizarPorCiclos(int nCiclos){
	generarPoblacionInicial();
	for(int i = 0; i<nCiclos; i++){//"i" es el numero de ciclo
		escogerReproducirMutar();
		seleccionarReemplazo();
	}
	T resultado = poblacion[0];
	limpiarEntorno();
	return resultado;
}

///Metodo que optimiza hasta alcanzar un minimo de error aceptable o consumir el total de ciclos <Desligado del por ciclos puro para evitar comparaciones innecesarias>
template <class T> T MicraGENETIC<T>::optmizacionMixta(int nCiclosMaximos, double aptitudAceptable){
	int ciclosConsumidos = 0;
	generarPoblacionInicial();
	while(ciclosConsumidos<nCiclosMaximos && poblacion[0].obtenerAptitud()<aptitudAceptable){
		escogerReproducirMutar();
		seleccionarReemplazo();
		ciclosConsumidos++;
	}
	T resultado = poblacion[0];
	limpiarEntorno();
	return resultado;
}

template <class T> void MicraGENETIC<T>::reiniciarSemillasAleatorias(){
	srand48(time(NULL));
	srand(time(NULL));
}

///Funciones internas:
template <class T> void MicraGENETIC<T>::generarPoblacionInicial(){
	this->poblacion = new T[nIndividuos];//Reservar la memoria de poblacion
	this->nuevaPoblacion = new T[nIndividuos];//Reservar la memoria de nueva poblacion (para hacer swapping...)
	this->descendencia = new T[nDescendientes];//Reservar la memoria de descendientes
	this->finDescendencia = descendencia + nDescendientes;
	this->valorTotalPoblacion = 0.0;
	for(int i = 0; i<nIndividuos; i++){
		T nuevoIndividuo;
		nuevoIndividuo.generarAleatoriamente();
		this->valorTotalPoblacion += nuevoIndividuo.obtenerAptitud();
		this->poblacion[i] = nuevoIndividuo;
	}
	sort(this->poblacion, this->poblacion + nIndividuos, std::greater<T>());//La poblacion se mantendra ya ordenada a partir de esta vez
}

template <class T> void MicraGENETIC<T>::escogerReproducirMutar(){
	switch(opSelector){//Alternativa: Usar "Punteros a funciones"
		case SelRuleta:
			seleccionRuleta<T>(poblacion, valorTotalPoblacion, nIndividuos,
										   nReproductores, tTorneo, probabilidadMutacion,
										   descendencia); break;
		case SelAleatorioPuro:
			seleccionAleatoriaPura<T>(poblacion, nIndividuos, nReproductores, probabilidadMutacion,
								   descendencia); break;
		case SelTorneo:
			seleccionPorTorneo<T>(poblacion, nIndividuos, nReproductores, tTorneo, probabilidadMutacion,
							   descendencia);break;
	}
	sort(this->descendencia, this->finDescendencia, std::greater<T>());//Ordenar la descendencia
}

template <class T> void MicraGENETIC<T>::seleccionarReemplazo(){//Tras los experimentos, resulta mucho mas rapido re-asignar nueva memoria que reubicar los elementos
	int escogidos = 0, focoPoblacionPrevia = 0, focoDescendencia = 0;
	this->valorTotalPoblacion = 0.0;//Reset para la nueva
	while(escogidos<nIndividuos && focoDescendencia<nDescendientes){
		if(poblacion[focoPoblacionPrevia].obtenerAptitud()>descendencia[focoDescendencia].obtenerAptitud()){
			nuevaPoblacion[escogidos] = poblacion[focoPoblacionPrevia];
			focoPoblacionPrevia++;
		}else{
			nuevaPoblacion[escogidos] = descendencia[focoDescendencia];
			focoDescendencia++;
		}
		valorTotalPoblacion += nuevaPoblacion[escogidos].obtenerAptitud();
		escogidos++;
	}
	if(escogidos<nIndividuos){//Si se llega aqui puede ser porque ya se han cogido todos los requeridos o porque ya solo importan los de la poblacion previa
		while(escogidos<nIndividuos){
			nuevaPoblacion[escogidos] = poblacion[focoPoblacionPrevia];
			valorTotalPoblacion += poblacion[focoPoblacionPrevia].obtenerAptitud();
			focoPoblacionPrevia++;
			escogidos++;
		}
	}
	T* swap = poblacion;//Ya no hay que destruir los elementos de la poblacion, se sobreescribiran como nueva poblacion...
	this->poblacion = nuevaPoblacion;//Se ha construido de forma ordenada
	this->nuevaPoblacion = swap;
}

///Destructor:
template <class T> MicraGENETIC<T>::~MicraGENETIC(){}

template <class T> void MicraGENETIC<T>::limpiarEntorno(){
	delete [] poblacion;
	delete [] nuevaPoblacion;
	delete [] descendencia;
}

///Acceso a atributos:
template <class T> int MicraGENETIC<T>::getNIndividuos(){
	return this->nIndividuos;
}

template <class T> void MicraGENETIC<T>::setNIndividuos(int nIndividuos){
	this->nIndividuos = nIndividuos;
	this->nIndividuosYnDescendientes = nIndividuos +  this->nDescendientes;
}

template <class T> int MicraGENETIC<T>::getNReproductores(){
	return this->nReproductores;
}

template <class T> void MicraGENETIC<T>::setNReproductores(int nReproductores){
	this->nDescendientes = nReproductores/2;
	this->nReproductores = nReproductores;
	this->nIndividuosYnDescendientes = nIndividuos +  nDescendientes;
}

template <class T> double MicraGENETIC<T>::getProbabilidadMutacion(){
	return this->probabilidadMutacion;
}

template <class T> void MicraGENETIC<T>::setProbabilidadMutacion(double probabilidadMutacion){
	this->probabilidadMutacion = probabilidadMutacion;
}

template <class T> void MicraGENETIC<T>::setOpSelector(TiposSeleccion opSelector){
	this->opSelector = opSelector;
}

template <class T> TiposSeleccion MicraGENETIC<T>::getOpSelector(){
	return opSelector;
}

template <class T> void MicraGENETIC<T>::setTTorneo(int tTorneo){
	this->tTorneo = tTorneo;
}

template <class T> int MicraGENETIC<T>::getTTorneo(){
	return tTorneo;
}
