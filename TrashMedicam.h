
#ifndef PRACTICA5_TRASHMEDICAM_H
#define PRACTICA5_TRASHMEDICAM_H

#include <iostream>
#include <vector>
#include <cmath>

#include "PaMedicamento.h"

//Libre = -, Disponible = ?, Ocupado = X
class TrashMedicam {
private:
    class Entrada {
        public:
        unsigned long clave;
        char marca;
        PaMedicamento dato;
        Entrada(): marca('-'), clave(0), dato(){}
        ~Entrada(){}
    };
    unsigned long tamFisico, tamLogico,tope_Colisiones,max10,total_Colisiones,primo_jr,redisp;
    std::vector<Entrada> tablaHash;

    bool es_Primo(unsigned primo);//dice si num es primo
    int primo_Min(unsigned num);//primo menor al q paso
    int primo_Max(unsigned num);//primo mayor al q paso
    int hash(unsigned long clave, int intento);
    int hash2(unsigned long clave, int intento);
    int hash3(unsigned long clave, int intento);
public:
    TrashMedicam(int maxElementos, float lambda=0.7);//quiero q la tabla este llena al 70%
    TrashMedicam(const TrashMedicam &orig);
    TrashMedicam& operator=(const TrashMedicam &orig);
    ~TrashMedicam();

    bool insertar(unsigned long clave, PaMedicamento &pa);
    PaMedicamento* buscar(unsigned long clave);
    bool borrar(unsigned long clave);
    unsigned long getNumElem() const { return tamLogico; };
};


#endif //PRACTICA5_TRASHMEDICAM_H
