
#ifndef PRACTICA5_TRASHMEDICAM_H
#define PRACTICA5_TRASHMEDICAM_H

#include <iostream>
#include <vector>
#include <cmath>

#include "PaMedicamento.h"

//Libre = -, Disponible = ?, Ocupado = X
class ThashMedicam {
private:
    class Entrada {
    public:
        unsigned long clave;
        char marca;
        PaMedicamento dato;
        Entrada(): marca('-'), clave(0), dato(){}
        ~Entrada(){}
    };
    unsigned long tamFisico, tamLogico,promedio_Colisiones,max10,total_Colisiones,primo_jr,redisp;
    std::vector<Entrada> tablaHash;

    bool es_Primo(unsigned primo);//dice si primo es primo
    int primo_previo(unsigned num);//primo menor al que paso
    int primo_sig(unsigned num);//primo mayor al que paso
    int hash(unsigned long clave, int intento);
    int hash2(unsigned long clave, int intento);
    int hash3(unsigned long clave, int intento);
public:
    ThashMedicam(int maxElementos, float lambda=0.7);//quiero q la tabla este llena al 70%
    ThashMedicam(const ThashMedicam &orig);
    ThashMedicam& operator=(const ThashMedicam &orig);
    ~ThashMedicam();

    unsigned long getNumElem() const { return tamLogico; }
    unsigned long get_promedio_colisiones() const;
    unsigned long get_max10() const;
    unsigned long get_total_colisiones() const;
    unsigned long get_carga() const;//Carga es que tan llena está la tabla

    bool insertar(unsigned long clave, PaMedicamento &pa);
    PaMedicamento* buscar(unsigned long clave);
    bool borrar(unsigned long clave);
};


#endif //PRACTICA5_TRASHMEDICAM_H