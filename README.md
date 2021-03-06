# MicraGENETIC

Abstract: Simple and minimalistic template class with a genetic algorithm to handle optimization procedures.

-->Acerca de MicraGENETIC:

Implementación minimalista de un algoritmo genético en C++ para problemas sencillos de optimización (con perspectiva de maximización).
MicraGENETIC está construido como una clase template con la lógica propia del proceso evolutivo dejando así al usuario simplemente el 
diseño del individuo que encapsule las soluciones candidatas a su problema particular. Puede por tanto verse como una librería auxiliar para
acelerar desarrollos simples.

->Notas de la versión:

El proceso evolutivo espera que los individuos tengan una serie de operaciones que se resumen en la clase "IIndividuo". SIn embargo, no se espera
ni se requiere que hereden de la misma sino que se trata de un esquema ilustrativo y desligado. El enfoque a seguir al modelar y calcular la apitud 
de dichos individuos ha de ser el de la maximización de su aptitud.

Se realiza un proceso de selección de reproductores llamando además a la mutación de los descendientes según una probabilidad especificada
como parámetro. El proceso de selección predeterminado es "por ruleta" pero desde la versión 3.0 se ofrecen además "por torneo" y "aleatorio puro"
de forma completamente configurable. El operador de reproducción ha de ser binario (participan 2 individuos para generar un descendiente) admitiendo 
además la reproducción de un individuo con sí mismo. Cabe destacar que el operador de mutación de los individuos no debe en ningún caso destruirlos. 
En lo referente al reemplazo de individuos para el siguiente ciclos se hace por la selección directa de los N mejores.

Se espera que el número de reproductores sea par y en ningún caso superior al de individuos. No obstante, no se llevan a cabo comprobaciones sino
que es responsabilidad del usuario garantizar un contexto correcto de funcionamiento.

En el archivo Lanzadera se muestra un ejemplo de adaptación y uso a un problema sencillo-> Se busca obtener el máximo de la función y=x en el rango
[0,1]. Para tal fin se define la clase "IndividuoSimple". La implementación de sus operadores es meramente ejemplificante sin ser en absoluto la más
adecuada para el problema en cuestión.

MicraGENETIC ofrece dos modos de optimización: Por ciclos y mixta. En la optimización por ciclos se ejecuta el proceso evolutivo hasta consumir un
número de ciclos dado como parámetro sin prestar atención a la calidad de las soluciones. En la optimización mixta se especifica un número máximo
de ciclos a consumir pero también un valor de aptitud de la mejor solución que, una vez logrado, llevaría a detener el proceso sin importar el no haber
completado el número de ciclos máximo.

La librería permite reiniciar las semillas para números aleatorios entre sus operaciones por lo que no es necesario ni recomendable hacerlo de forma
externa.

La función y uso de los métodos se considera perfectamente deducible en base a sus nombres. Se recomienda por tanto y simplemente analizar el ejemplo
proporcionado antes de usar la librería en un problema propio. Se aconseja además consultar el archivo de licencia.

Autor: Nicolás C.
