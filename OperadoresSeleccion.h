//Operadores de seleccion alternativos (inyectado la reproduccion y mutacion para optimizar)
//Archivo de expansion del nucleo MicraGENETIC (en su versio 3.0)
//Autor: Nicolas C

#ifndef OPERADORESSELECCION_H_INCLUDED
#define OPERADORESSELECCION_H_INCLUDED

///Seleccion por ruleta:
template <class T> void seleccionRuleta(T* poblacion, double valorTotalPoblacion, int nIndividuos,
                                           int nReproductores, int tTorneo, double probabilidadMutacion,
                                           T* descendencia){
    double q[nIndividuos], preQ = 0.0, vRuleta, qPuntual;//Seleccion por ruleta:
    for(int i = 0; i<nIndividuos; i++){
        qPuntual = (poblacion[i].obtenerAptitud()/valorTotalPoblacion) + preQ;
        q[i] = qPuntual;
        preQ = qPuntual;
    }//Hacer la seleccion de individuos sobre la poblacion:
    int focoSeleccionA, focoSeleccionB, nSeleccionados = 0;
    for(int i = 0; i<nReproductores; i+=2){//Desenrollado manual. Prescindiendo de una funcion de busqueda adicional
        vRuleta = drand48();
        focoSeleccionA = 0; focoSeleccionB = 0;
        while(focoSeleccionA<nIndividuos){
            if(vRuleta < q[focoSeleccionA]){
                break;
            }
            focoSeleccionA++;
        }
        vRuleta = drand48();
        while(focoSeleccionB<nIndividuos){
            if(vRuleta < q[focoSeleccionB]){
                break;
            }
            focoSeleccionB++;
        }
        T descendiente = poblacion[focoSeleccionA].reproducir(poblacion[focoSeleccionB]);
        if(drand48()<probabilidadMutacion){//¿Solicitar mutacion?
            descendiente.mutar();
        }
        descendencia[nSeleccionados] = descendiente;
        nSeleccionados++;
    }
}

///Seleccion aleatoria pura:
template <class T> void seleccionAleatoriaPura(T* poblacion, int nIndividuos, int nReproductores,
                                                  double probabilidadMutacion, T* descendencia){
    int nSeleccionados = 0;
    for(int i = 0; i<nReproductores; i+=2){
        T descendiente = poblacion[rand()%nIndividuos].reproducir(poblacion[rand()%nIndividuos]);
        if(drand48()<probabilidadMutacion){//¿Solicitar mutacion?
            descendiente.mutar();
        }
        descendencia[nSeleccionados] = descendiente;
        nSeleccionados++;
    }
}

///Seleccion por torneos
template <class T> void seleccionPorTorneo(T* poblacion, int nIndividuos, int nReproductores,
                                                int tTorneo, double probabilidadMutacion, T* descendencia){
    int nSeleccionados = 0, progA, progB, j, candidato;
    double aptA = -1, aptB = -1, aptCandidata;
    for(int i = 0; i<nReproductores; i+=2){
        for(j = 0; j<tTorneo; j++){//Inyectando los torneos para los dos progenitores
            candidato = rand()%nIndividuos;//Candidatos a progenitores tipo A
            aptCandidata = poblacion[candidato].obtenerAptitud();
            if(aptCandidata>aptA){
                progA = candidato; aptA = aptCandidata;//Actualizar ronda
            }
            candidato = rand()%nIndividuos;//Candidatos a progenitores tipo B
            aptCandidata = poblacion[candidato].obtenerAptitud();
            if(aptCandidata>aptB){
                progB = candidato; aptB = aptCandidata;//Actualizar ronda
            }
        }
        T descendiente = poblacion[progA].reproducir(poblacion[progB]);
        if(drand48()<probabilidadMutacion){//¿Solicitar mutacion?
            descendiente.mutar();
        }
        descendencia[nSeleccionados] = descendiente;
        nSeleccionados++;
    }
}

#endif // OPERADORESSELECCION_H_INCLUDED
