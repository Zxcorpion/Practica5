
#include "ThashMedicam.h"


bool ThashMedicam::es_Primo(unsigned primo) {
    if (primo <= 1) return false;
    if (primo == 2) return true;
    if (primo % 2 == 0) return false;

    for (int i=3; i*i <= primo; i++) {
        if (primo % i == 0) return false;
    }
    return true;
}

int ThashMedicam::primo_previo(unsigned num) {
    if (num == 0 || num == 1) {
        throw std::invalid_argument("0 y 1 no pueden ser primos");
    }
    int menor = num - 1;
    while (!es_Primo(menor)) {
        menor--;
    }
    return menor;
}


int ThashMedicam::primo_sig(unsigned num) {
    if (num == 0 || num == 1) {
        throw std::invalid_argument("0 y 1 no pueden ser primos");
    }
    int mayor = num + 1;
    while (es_Primo(mayor) == false) {
        mayor++;
    }
    return mayor;
}

int ThashMedicam::hash(unsigned long clave, int intento) {
    unsigned long pos=0;
    pos = (clave + (intento*intento)) % tamFisico;
    return pos;
}


int ThashMedicam::hash2(unsigned long clave, int intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = 1 + (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}

int ThashMedicam::hash3(unsigned long clave, int intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = primo_jr - (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}


ThashMedicam::ThashMedicam(int maxElementos, float lambda): tamFisico(primo_sig(maxElementos/lambda)),
tablaHash(tamFisico, Entrada()), tamLogico(0),promedio_Colisiones(0),
max10(0), total_Colisiones(0),primo_jr(0),maxcolisiones(0),redisp(0)
{
    primo_jr = primo_previo(tamFisico);
}
ThashMedicam::ThashMedicam(const ThashMedicam &orig):tamFisico(orig.tamFisico),
tablaHash(orig.tablaHash), tamLogico(orig.tamLogico),promedio_Colisiones(orig.total_Colisiones),
max10(orig.max10), total_Colisiones(orig.total_Colisiones),primo_jr(orig.primo_jr),maxcolisiones(orig.maxColisiones()),redisp(0)
{
    primo_jr = orig.primo_jr;
}


ThashMedicam &ThashMedicam::operator=(const ThashMedicam &orig) {
    if (this != &orig) {
        tamFisico = orig.tamFisico;
        tamLogico = orig.tamLogico;
        promedio_Colisiones = orig.promedio_Colisiones;
        max10 = orig.max10;
        total_Colisiones = orig.total_Colisiones;
        primo_jr = orig.primo_jr;
        maxcolisiones=orig.maxcolisiones;
        redisp = orig.redisp;
    }
    return *this;
}
//CAMBIADO
unsigned int ThashMedicam::get_promedio_colisiones() {
    promedio_Colisiones=(total_Colisiones)/(tamLogico);
    return promedio_Colisiones;
}

unsigned int ThashMedicam::get_max10() const {
    return max10;
}

unsigned long ThashMedicam::get_total_colisiones() const {
    return total_Colisiones;
}
//CAMBIADO
float ThashMedicam::get_carga()const{
    float aux=static_cast<float>(tamLogico)/static_cast<float>(tamFisico);
    return aux;
}

//Libre = -, Disponible = ?, Ocupado = X
//CAMBIADO
bool ThashMedicam::insertar(unsigned long clave, PaMedicamento &pa) {
    unsigned intento=0,y;
    bool enc = false;

    while (!enc) {
        //y = hash(clave, intento);
        // y = hash2(clave, intento);
         y = hash3(clave, intento);

        if (tablaHash[y].marca == '-' || tablaHash[y].marca == '?') {
            tamLogico++;
            tablaHash[y].dato = pa;
            tablaHash[y].marca = 'X';
            tablaHash[y].clave = clave;
            enc = true;
        }else {
            if (tablaHash[y].dato.get_id_num() == clave) {//No se pueden meter repetidos
                return false;
            }else {
                total_Colisiones++;
                intento++;
            }
        }
    }
    if (intento > maxcolisiones) {
        maxcolisiones = intento;
    }
    if ( intento >10) {
        max10 = intento;
    }
    //poner estadisticos
    std::cout<<"La insercion del medicamento con id "<<clave<<" y nombre "<< pa.get_nombre()<<" intenta"
    " accedera la posicion "<<y<<" y conlleva:"<<std::endl;
    std::cout<<"Numero de intentos: "<<intento+1<<std::endl;
    std::cout<<"Numero de colisiones: "<<intento<<std::endl;
    return enc;
}


unsigned int ThashMedicam::maxColisiones() const {
    return maxcolisiones;
}

//Libre = -, Disponible = ?, Ocupado = X
PaMedicamento *ThashMedicam::buscar(unsigned long clave) {
    unsigned intento=0,y;
    bool enc = false;

    while (!enc) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'X' && tablaHash[y].clave == clave) {
            return (&tablaHash[y].dato);
        }else {
            if (tablaHash[y].marca == '-') {
                return 0;
            }else {
                intento++;
            }
        }
    }
    //poner estadisticos
    return 0;
}
//Dos o tres lineas cambiadas.La linea 166 hace el bucle infinito creo
//Libre = -, Disponible = ?, Ocupado = X
bool ThashMedicam::borrar(unsigned long clave) {
    unsigned intento=0,y;
    bool fin = false;

    /*while (!fin) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'O' && tablaHash[y].clave == clave) {
            tablaHash[y].marca = 'D';
            fin = true;
        }else {
            if (tablaHash[y].marca == 'L') {
                fin = false; //Para de buscar porque esta libre
            }else {
                intento++;
            }
        }
    }
    //poner estadisticos
    return false;*/
    while (!fin) {
        y = hash2(clave, intento);
        // y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].marca == 'X' && tablaHash[y].clave == clave) {
            tablaHash[y].marca = '?';
            fin = true;
            tamLogico--;
        }else {
            if (tablaHash[y].marca == '-') {
                //fin = false; //Para de buscar porque esta libre
                return fin; // Ya no hay mas que buscar y no se ha encontrado
            }else {
                intento++;
            }
        }
    }
    //poner estadisticos
    return fin; //fin=true
}
ThashMedicam::~ThashMedicam() {}