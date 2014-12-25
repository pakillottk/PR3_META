
#include "AG.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
AG::AG(const string& rutaFichero, float _pc, float _pm, unsigned _tam_pob): Metaheuristica(rutaFichero) {
    tam_pob = _tam_pob;      
    evaluaciones = 0;
    mejorCoste = 99999999;
    t_subcadena = tam/2;   
    max_eval = 20000;
}

AG::~AG() {}

//MÉTODOS PROTECTED
//=================
void AG::iniciarPob(vector<pair<unsigned*, unsigned long> >& pob) {
    unsigned* p;
    unsigned long coste;
    pair<unsigned*, unsigned long> insert;
    
    for(unsigned i = 0; i < tam_pob; i++) {
        p = new unsigned[tam];
        generarSolucion(p);
        
        coste = calculaCoste(p);
        evaluaciones++;
        
        insert.first = p;
        insert.second = coste;
        
        if(coste < mejorCoste) {
            solucion = p;
            mejorCoste = coste;
        }
        
        pob.push_back(insert);
    }
}

unsigned* AG::cruce_pos(unsigned* p, unsigned* m) {
    unsigned* h = new unsigned[tam];    
    char* libres = new char[tam];
    char* asignados = new char[tam];   
    
    for(unsigned i = 0; i < tam; i++) {
        libres[i] = 1;
        asignados[i] = 0;
    }
    
    for(unsigned i = 0; i < tam; i++) {       
        if(p[i] == m[i]) {           
            h[i] = p[i];
            libres[i] = 0;
            asignados[h[i]] = 1;
        }
    }   
    
    
    for(unsigned i = 0; i < tam; i++) {        
        if(libres[i]) {            
            do {
                h[i] = rand() % tam;                
            } while(asignados[h[i]]);        
           
            asignados[h[i]] = 1;
        }
    }    
    
    delete [] libres;
    delete [] asignados;
    
    return h;
}

pair<unsigned*, unsigned*> AG::cruce_pmx(unsigned* p, unsigned* m) {
    unsigned* h1 = new unsigned[tam];
    unsigned* h2 = new unsigned[tam];  
    
    unsigned* ind_h1 = new unsigned[tam];
    unsigned* ind_h2 = new unsigned[tam];
    
    char* asignados_h1 = new char[tam];
    char* asignados_h2 = new char[tam];
    
    for(unsigned i = 0; i < tam; i++) {
        asignados_h1[i] = asignados_h2[i] = 0;       
    }
    
    for(unsigned i = 0; i < tam; i++) {
       asignados_h1[i] = asignados_h2[i] = 0;       
        
       h1[i] = m[i];
       h2[i] = p[i];
       
       asignados_h1[h1[i]] = 1;
       asignados_h2[h2[i]] = 1;
       
       ind_h1[h1[i]] = i;
       ind_h2[h2[i]] = i;
    }
    
    for(unsigned i = t_subcadena-1; i < (t_subcadena-1+t_subcadena); i++) {
        if(asignados_h1[p[i]]) {
            h1[ind_h1[p[i]]] = m[i];
            asignados_h1[m[i]] = 1;           
        }
        
        if(asignados_h2[m[i]]) {
            h2[ind_h2[m[i]]] = p[i];
            asignados_h2[p[i]] = 1;
        }
        
        h1[i] = p[i];
        h2[i] = m[i];       
        
        asignados_h1[h1[i]] = 1;
        asignados_h2[h2[i]] = 1;
    }    
    
    delete [] ind_h1;
    delete [] ind_h2;
    
    delete [] asignados_h1;
    delete [] asignados_h2;
    
    return pair<unsigned*, unsigned*>(h1, h2);
}

void AG::mutar(unsigned* p, unsigned i) {
    unsigned j;
    
    do {
        j = rand() % tam;
    } while(i == j);
    
    intercambiar(p, i ,j);
}