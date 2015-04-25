#include <stdio.h>

#include "MicraGENETIC.h"

class IndividuoSimple{//Individuo de ejemplo en: Obtener el maximo de la funcion y = x en [0, 100]
	public:
		IndividuoSimple(){
			this->valor = 0;
		}

		IndividuoSimple(int valor){
			this->valor = valor;
		}

		IndividuoSimple(const IndividuoSimple& referencia){//Operador de copia
			this->valor = referencia.valor;
		}

		IndividuoSimple reproducir(IndividuoSimple progenitorB){
			IndividuoSimple descendiente((valor + progenitorB.valor)/2);//Valor medio
			return descendiente;
		}

		void generarAleatoriamente(){
			this->valor = rand() % 101;
		}

		void mutar(){//Se puede avanzar en +-5
			int preValor = rand() % 6;
			if(drand48()>0.5){
				preValor = -preValor;
			}
			preValor += valor;
			if(preValor>=0 && preValor<=100){
				this->valor = preValor;
			}
		}

		bool operator > (const IndividuoSimple& str) const{
			return (valor > str.valor);
		}

		int obtenerAptitud(){
			return valor;
		}

		int leerVariable(){
			return valor;
		}

		~IndividuoSimple(){}

	private:
		int valor;
};

int main(){
	//50 individuos, 20 de ellos se reproducen por ciclo, probabilidad de solicitar mutacion del 0.5, seleccion por torneo
	MicraGENETIC<IndividuoSimple> optimizador(50, 20, 0.5, SelTorneo);
	///Ejemplos adicionales:
	//MicraGENETIC<IndividuoSimple> optimizador(50, 20, 0.5, SelTorneo, 6);//Torneos de 6 participantes por progenitor
	//MicraGENETIC<IndividuoSimple> optimizador(50, 20, 0.5, SelAleatorioPuro);//Seleccion aleatoria de cada progenitor
	//MicraGENETIC<IndividuoSimple> optimizador(50, 20, 0.5, SelRuleta);
	//MicraGENETIC<IndividuoSimple> optimizador(50, 20, 0.5);//Equivale a usar ruleta: Por defecto, seleccion de reproductores por ruleta
	optimizador.reiniciarSemillasAleatorias();
	IndividuoSimple resultado = optimizador.optimizarPorCiclos(10000);
	printf("Mejor Resultado: %d\n", resultado.leerVariable());
	return 0;
}
