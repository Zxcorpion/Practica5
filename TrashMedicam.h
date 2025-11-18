
#ifndef PRACTICA5_TRASHMEDICAM_H
#define PRACTICA5_TRASHMEDICAM_H

#include <iostream>
#include "PaMedicamento.h"

class TrashMedicam {
private:
    unsigned int numElem = 0;
    int hash(unsigned long clave, int intento);
public:
    TrashMedicam(int maxElementos, float lambda=0.7);
    TrashMedicam(const TrashMedicam &orig);
    TrashMedicam& operator=(const TrashMedicam &orig);
    ~TrashMedicam();

    bool insertar(unsigned long clave, PaMedicamento &pa);
    PaMedicamento* buscar(unsigned long clave);
    bool borrar(unsigned long clave);
    unsigned int getNumElem() const;
};


#endif //PRACTICA5_TRASHMEDICAM_H
