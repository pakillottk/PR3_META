
#include "AGG.h"

AGG::AGG(const string& rutaFichero, bool usarPmx, float _pc, float _pm, unsigned _tam_pob ):
AG(rutaFichero, _tam_pob)
{
    pmx = usarPmx;
    n_cruces = _pc * (tam_pob/2);
    n_mutac = tam * _pm;
}

AGG::~AGG(){}

vector<unsigned*> AGG::seleccion(vector<pair<unsigned*,unsigned long> >& pob) {
    vector<unsigned*> selec;
    char* seleccionado = new char[pob.size()];
    for(unsigned i = 0; i < pob.size(); i++) {
        seleccionado[i] = 0;
    }
    
    unsigned p1, p2;
    for(unsigned i = 0; i < pob.size(); i++) {
        do {
            p1 = rand() % pob.size();
        } while(seleccionado[p1]);
        
        do {
            p2 = rand() % pob.size();
        } while(seleccionado[p2] || p1 == p2);
        
        if(pob[p1].second < pob[p2].second) {
            selec.push_back(pob[p1].first);
            seleccionado[p1] = 1;
        } else {
            selec.push_back(pob[p2].first);
            seleccionado[p2] = 1;
        }
    }
    
    return selec;
}

unsigned long AGG::ejecutar() {    
   //Vector población
    vector<pair<unsigned*, unsigned long> > pob;
    
    //Población inicial
    iniciarPob(pob);
    
    //Vector de padres
    vector<unsigned*> padres;
    //Vector de hijos
    vector<pair<unsigned*, unsigned long> > hijos;
    
    while(evaluaciones < max_eval) {
        //Generar padres
        padres = seleccion(pob);
        
        //Generar hijos
        unsigned h_act = 0;
        pair<unsigned*, unsigned*> h;       
        
        for(unsigned i = 0; i < n_cruces; i=i+2) {
            if(pmx)
                h = cruce_pmx(padres[i], padres[i+1]);
            else
                h.first = cruce_pos(padres[i], padres[i+1]); 
            
            hijos[h_act++].first = h.first;     
            if(pmx)
                hijos[h_act++].first = h.second;
        }
        
        //Mutar hijos
        unsigned j, gen;
        unsigned peorHijo;
        unsigned long peorCoste_h = 0;
        for(unsigned i = 0; i < n_mutac; i++) {
            j = rand() % hijos.size();
            gen = rand() % tam;        
            
            mutar(hijos[j].first, gen);
            hijos[j].second = calculaCoste(hijos[j].first);
            if(hijos[j].second > peorCoste_h) {
                peorHijo = j;
                peorCoste_h = hijos[i].second;
            }
            
            evaluaciones++;            
            if(evaluaciones == max_eval)
                break;
        }
        
        //Comprobamos si hemos cumplido condicion de parada
        if(evaluaciones == max_eval)
                break;
        
        //Reemplazo
        unsigned* mejorHijo;
        unsigned  mejorCoste_h = 9999999;
        unsigned cur_p = 0;
        
        if(pmx) {
            delete [] hijos[peorHijo].first;
            hijos[peorHijo] = 0;
        } else {
            for(unsigned i = 0; i < hijos.size(); i++) {
                if(!hijos[i])
                    continue;
                
                if(pob[cur_p].first == solucion) {
                    cur_p++;
                } 

                delete [] pob[cur_p].first;
                pob[cur_p].first = hijos[i];
                pob[cur_p].second = hijos[i].second; 
                cur_p++;
                
                if(hijos[i].second < mejorCoste_h) {
                    mejorHijo = hijos[i];
                    mejorCoste_h = hijos[i].second;
                }
            }
        }
        //Actualizar mejor solución
        if(mejorCoste_h < mejorCoste) {
            solucion = mejorHijo;
            mejorCoste = mejorCoste_h;
        }
        
        //Reiniciar vectores
        padres.clear();
        hijos.clear();
    }    
    
    //Liberamos la memora
    for(unsigned i = 0; i < tam_pob; i++)
        delete [] pob[i].first;
    
    //Devolvemos mejor coste encontrado
    return mejorCoste;
}

