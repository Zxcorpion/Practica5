
#include "TrashMedicam.h"
#include "TrashMedicam.h"

//poner throw si pasan 0 o 1 pq no son primos
bool TrashMedicam::es_Primo(unsigned primo) {
    //Creamos una variable para ver si el resto de dividir entre dos es cero
    unsigned aux_primo=primo % 2;
    //Comprobamos
    if (aux_primo == 0) {
        return false;
    }
    return true;
}

int TrashMedicam::primo_previo(unsigned num) {
    //Comprobamos que no sea ni 0 ni 1 ya que no son primos y ademas que no sea 2 ya que antes que el 2 no hay ningun primo
    if (num <= 0 ||num <= 1 || num <= 2)
        throw std::invalid_argument("Error [TrashMedicam::primo_previo] numero invalido");
    int menor = num - 1;
    while (!es_Primo(menor)) {
        menor--;
    }
    return menor;
}

int TrashMedicam::primo_sig(unsigned num) {
    int mayor = num + 1;
    while (!es_Primo(mayor)) {
        mayor++;
    }
}

int TrashMedicam::hash(unsigned long clave, unsigned intento) {
    unsigned long batiposicion=0;
    batiposicion = (clave + intento*intento) % tamFisico;
    return batiposicion;
}


int TrashMedicam::hash2(unsigned long clave, unsigned intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = 1 + (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}

int TrashMedicam::hash3(unsigned long clave, unsigned intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = primo_jr - (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}


TrashMedicam::TrashMedicam(int maxElementos, float lambda): tamFisico(primo_sig(maxElementos/lambda)),
tablaHash(tamFisico, Entrada()), tamLogico(0),tope_Colisiones(0),
max10(0), total_Colisiones(0),primo_jr(0),redisp(0)
{
    primo_jr = primo_previo(tamFisico);
}
TrashMedicam::TrashMedicam(const TrashMedicam &orig):tamFisico(orig.tamFisico),
tablaHash(orig.tablaHash), tamLogico(orig.tamLogico),tope_Colisiones(orig.total_Colisiones),
max10(orig.max10), total_Colisiones(orig.total_Colisiones),primo_jr(orig.primo_jr),redisp(0)
{
    primo_jr = orig.primo_jr;
}


TrashMedicam &TrashMedicam::operator=(const TrashMedicam &orig) {
    if (this != &orig) {
        tamFisico = orig.tamFisico;
        tamLogico = orig.tamLogico;
        tope_Colisiones = orig.tope_Colisiones;
        max10 = orig.max10;
        total_Colisiones = orig.total_Colisiones;
        primo_jr = orig.primo_jr;
        redisp = orig.redisp;
        tablaHash=orig.tablaHash;
    }
    return *this;
}

bool TrashMedicam::insertar(unsigned long clave, PaMedicamento &pa) {
    unsigned intento=0,y;
    bool enc = false;

    while (!enc) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'L' || tablaHash[y].marca == 'D') {
            tamLogico++;
            tablaHash[y].dato = pa;
            tablaHash[y].marca = 'O';
            tablaHash[y].clave = clave;
            enc = true;
        }else {
            if (tablaHash[y].dato.get_id_num() == clave) {
                return false;
            }else {
                intento++;
            }
        }
    }
    //poner estadisticos
    return enc;
}

PaMedicamento *TrashMedicam::buscar(unsigned long clave) {
    unsigned intento=0,y;
    //Esta vez usamos el tamaño de la tabla para parar o no el while
    while (intento < tablaHash.size()) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'O' && tablaHash[y].clave == clave) {
            return (&tablaHash[y].dato);
        }else {
            intento++;
        }
    }
    //poner estadisticos
    return 0;
}

bool TrashMedicam::borrar(unsigned long clave) {
    unsigned intento=0,y;
    bool fin = false;

    while (!fin) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'O' && tablaHash[y].clave == clave) {
            tablaHash[y].marca = 'D';
            fin = true;
        }else {
            if (tablaHash[y].marca == 'L') {
                return fin; //Para de buscar porque esta libre y ya no se va a encontrar
            }else {
                if (intento == tablaHash.size()) { // Si llegamos al final y no lo encontramos, return false
                    return false;
                }
                intento++;
            }
        }
    }
    //Actualizamos el tamaño
    tamLogico--;
    //poner estadisticos
    return fin;
}