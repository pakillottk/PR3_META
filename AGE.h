/* 
 * File:   AGE.h
 * Author: alumno
 *
 * Created on 3 de diciembre de 2014, 11:31
 */

#ifndef AGE_H
#define	AGE_H

#include "AG.h"

class AGG : public AG {
    public:
        AGE(const string& rutaFichero, float _pc = 0.7, float _pm = 0.01, unsigned _tam_pob = 50);
        virtual ~AGE();
        virtual unsigned long ejecutar();
};

#endif	/* AGE_H */

