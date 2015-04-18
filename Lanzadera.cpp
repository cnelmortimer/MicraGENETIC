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

        IndividuoSimple(const IndividuoSimple& referencia){//Operador de copia  (No requerido)
            this->valor = referencia.valor;
        }

        IndividuoSimple& operator = (const IndividuoSimple& referencia){//Operador de asignacion  (No requerido)
            if(this != &referencia){
                this->valor = referencia.valor;
            }
            return *this;
        }

        IndividuoSimple reproducir(IndividuoSimple progenitorB){
            IndividuoSimple descendiente((valor + progenitorB.valor)/2);//Valor medio como ejemplo (Sin tener en cuenta la forma de la funcion...)
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
            if(preValor>=0 && preValor<=100){//Si lamutacion hace al individuo inconsistente no se aplica
                this->valor = preValor;
            }
        }

        bool operator > (const IndividuoSimple& str) const{
            return (valor > str.valor);
        }

        int obtenerAptitud(){
            return valor;
        }

        int leerVariable(){//Metodo adicional que no se requiere por la libreria aunque se añade por cuenta propia sin problemas
            return valor;
        }

        ~IndividuoSimple(){}

    private:
        int valor;
};

int main(){//Uso:
    //Poblacion de 100 individuos, 20 de ellos pueden reproducirse en cada ciclo. Probabilidad de mutacion del 0.5 (50%) 
    MicraGENETIC<IndividuoSimple> optimizador(100, 20, 0.5);//Preparar el problema
    optimizador.reiniciarSemillasAleatorias();//Reiniciar las semillas de valores aleatorios
    IndividuoSimple resultado = optimizador.optimizarPorCiclos(1000000);//Ejecutar 1000000 ciclos
    printf("Mejor Resultado: %d\n", resultado.leerVariable());//Mostrar los resultados
    return 0;
}
