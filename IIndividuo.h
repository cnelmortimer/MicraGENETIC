#ifndef IINDIVIDUO_H
#define IINDIVIDUO_H

//Interfaz generica para individuos en el entorno MicraGENETIC. Autor: Nicolas C
//Enfoque que prioriza una mayor aptitud de los individuos. Esquema orientativo para la definición de individuos propios a cada problema.
//NO es necesario ni recomendable heredar de esta clase. Es un mero resumen de las funciones necesarias. Las clase aplicables pueden, de hecho,
//contar con cualquier operacion adicional necesaria (acceso a variables, operadores de copia, asignacion...).
//NOTA: Se asume la definicion de un operador de reproduccion sexual y por parejas
class Individuo{
	public:
	    virtual void generarAleatoriamente();//Hacer que una instancia, que debe estar creada, escriba sus atributos de forma aleatoria
		virtual Individuo reproducir(Individuo progenitorB);//Generar un nuevo individuo a partir de otro, que puede ser el mismo
		virtual void mutar();//Alterar los atributos del individuo, que debe seguir existiendo
		virtual double obtenerAptitud();
		virtual bool operator > (const Individuo& str) const;
		virtual ~IIndividuo(){};//Destructor virtual
};

#endif
