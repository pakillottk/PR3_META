/* 
 * File:   AG.h
 * Author: Fco. Gázquez
 *
 * Created on 3 de diciembre de 2014, 10:15
 */

#ifndef AG_H
#define	AG_H

#include "Metaheuristica.h"

#include <vector>
#include <utility>
#include <iostream>
using namespace std;

 /*
    Clase base para definir algoritmos genéticos
  */
class AG : public Metaheuristica {
    protected:        
        unsigned n_cruces;
        unsigned n_mutac;
        unsigned tam_pob;
        
        unsigned evaluaciones;
        unsigned long mejorCoste;
        
        unsigned t_subcadena;
        
        void iniciarPob(vector<pair<unsigned*, unsigned long> >& pob); //Genera la población inicial
        
        void mutar(unsigned* p, unsigned i); //Muta el gen i del cromosoma p
        
        unsigned* cruce_pos(unsigned* p, unsigned* m); 
        //Cruza p con m y devuelve el hijo
        
        pair<unsigned*, unsigned*> cruce_pmx(unsigned* p, unsigned* m); 
        //Cruza p con m y devuelve el hijo
        
    public:
        AG(const string& rutaFichero, float _pc = 0.7, float _pm = 0.01, unsigned _tam_pob = 50);
        virtual ~AG();
        virtual unsigned long ejecutar()=0;
};


#endif	/* AG_H */

