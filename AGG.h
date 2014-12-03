/* 
 * File:   AGG_POS.h
 * Author: alumno
 *
 * Created on 3 de diciembre de 2014, 11:30
 */

#ifndef AGG_POS_H
#define	AGG_POS_H

#include "AG.h"

class AGG : public AG {
    public:
        AGG(const string& rutaFichero, float _pc = 0.7, float _pm = 0.01, unsigned _tam_pob = 50);
        virtual ~AGG();
        virtual unsigned long ejecutar();
};

#endif	/* AGG_POS_H */

