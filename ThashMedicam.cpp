

#include "ThashMedicam.h"

/**
 * @biref Funcion para comprobar si es primo o no
 * @param primo unsigned numero a comprobar
 * @return true si lo es o false sino
 */
bool ThashMedicam::es_Primo(unsigned primo) {
    if (primo <= 1) return false;
    if (primo == 2) return true;
    if (primo % 2 == 0) return false;

    for (int i=3; i*i <= primo; i++) {
        if (primo % i == 0) return false;
    }
    return true;
}

/**
 * @brief Funcion para cacluar el primo anterior a num
 * @param num unsigned
 * @return menor que es el primo previo a num
 */
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

/**
 * @brief Funcion para calcular el primo siguiente a num
 * @param num
 * @return num
 */
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

/**
 * @brief Funcion hash
 * @param clave
 * @param intento
 * @return pos unsigned long posicion
 */
int ThashMedicam::hash(unsigned long clave, int intento) {
    unsigned long pos=0;
    pos = (clave + (intento*intento)) % tamFisico;
    return pos;
}

/**
 * @brief Fuincon hash numero 2
 * @param clave
 * @param intento
 * @return h3 unsigned long posicion
 */
int ThashMedicam::hash2(unsigned long clave, int intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = 1 + (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}

/**
 * @brief Funcion hash3
 * @param clave
 * @param intento
 * @return h3 unsigned long posicion
 */
int ThashMedicam::hash3(unsigned long clave, int intento) {
    unsigned long h1=0,h2=0,h3=0;
    h1 = clave % tamFisico;
    h2 = primo_jr - (clave % primo_jr);
    h3 = (h1 + (intento * h2)) % tamFisico;
    return h3;
}

/**
 * @brief Constructor parametrizado
 * @param maxElementos
 * @param lambda
 */
ThashMedicam::ThashMedicam(int maxElementos, float lambda): tamFisico(primo_sig(maxElementos/lambda)),
                                                            tablaHash(tamFisico, Entrada()), tamLogico(0),promedio_Colisiones(0),
                                                            max10(0), total_Colisiones(0),primo_jr(0),maxcolisiones(0),redisp(0)
{
    primo_jr = primo_previo(tamFisico);
}

/**
 * @brief Constructor de copia
 * @param orig objeto copia
 */
ThashMedicam::ThashMedicam(const ThashMedicam &orig):tamFisico(orig.tamFisico),
                                                     tablaHash(orig.tablaHash), tamLogico(orig.tamLogico),promedio_Colisiones(orig.promedio_Colisiones),
                                                     max10(orig.max10), total_Colisiones(orig.total_Colisiones),primo_jr(orig.primo_jr),maxcolisiones(orig.maxColisiones()),redisp(0)
{
    primo_jr = orig.primo_jr;
}

/**
 * @brief Operador igual
 * @param orig objeto copia
 * @return this un puntero a nuestro objeto
 */
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
        tablaHash = orig.tablaHash;
    }
    return *this;
}

/**
 * @brief Funcion para calcular el promedio de colisiones
 * @return promedio_Colisiones float
 */
float ThashMedicam::get_promedio_colisiones() {
    promedio_Colisiones = (float)total_Colisiones/(float)tamLogico;
    return promedio_Colisiones;
}

/**
 * @brief Funcion para leer el atributo max10
 * @return max10 unsigned int
 */
unsigned int ThashMedicam::get_max10() const {
    return max10;
}

/**
 * @biref Funcion para leer el total_Colisiones
 * @return total_Colisiones unsigned long
 */
unsigned long ThashMedicam::get_total_colisiones() const {
    return total_Colisiones;
}
//CAMBIADO
/**
 * @brief Funcion para calcular y leer el factor de carga
 * @return aux
 */
float ThashMedicam::get_carga()const{
    float aux=static_cast<float>(tamLogico)/static_cast<float>(tamFisico);
    return aux;
}

//Libre = -, Disponible = ?, Ocupado = X
//CAMBIADO
/**
 * @brief Funcion para insertar un dato en la tabla
 * @param clave unsigned long
 * @param pa PaMedicamento
 * @return enc bool para saber si lo hemos insertado o no
 */
bool ThashMedicam::insertar(unsigned long clave, PaMedicamento &pa) {
    unsigned intento=0,y;
    bool enc = false;

    while (!enc) {
        //y = hash(clave, intento);
        y = hash2(clave, intento);
         //y = hash3(clave, intento);

        if (tablaHash[y].estado == '-' || tablaHash[y].estado == '?') {
            tamLogico++;
            tablaHash[y].dato = pa;
            tablaHash[y].estado = 'X';
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
    if (get_carga() > 0.7 ) {
        redispersar(tamFisico*1.3);
    }
    //poner estadisticos
    std::cout<<"La insercion del medicamento con id "<<clave<<" y nombre "<< pa.get_nombre()<<" intenta"
    " accedera la posicion "<<y<<" y conlleva:"<<std::endl;
    std::cout<<"Numero de intentos: "<<intento+1<<std::endl;
    std::cout<<"Numero de colisiones: "<<intento<<std::endl;
    return enc;
}

/**
 * @brief Funcion para leer el atributo maxcolisiones
 * @return maxcolisiones unsigned int
 */
unsigned int ThashMedicam::maxColisiones() const {
    return maxcolisiones;
}

/**
 * @brief Funcion para leer el atributo redisp
 * @return redisp unsigned long
 */
unsigned long ThashMedicam::get_redisp() const {
    return redisp;
}

//Libre = -, Disponible = ?, Ocupado = X
/**
 * @brief Funcion para buscar un elemento de la tabla
 * @param clave unsigned long
 * @return PaMedicamento* o 0 si no se ha encontrado
 */
PaMedicamento *ThashMedicam::buscar(unsigned long clave) {
    unsigned intento=0,y;
    bool enc = false;

    while (!enc) {
        // y = hash(clave, intento);
        y = hash2(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].estado == 'X' && tablaHash[y].clave == clave) {
            return (&tablaHash[y].dato);
        }else {
            if (tablaHash[y].estado == '-') {
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
/**
 * @brief Funcion para borrar un elemento de la tabla
 * @param clave unsigned long
 * @return fin para saber si se ha conseguido borrar o no
 */
bool ThashMedicam::borrar(unsigned long clave) {
    unsigned intento=0,y;
    bool fin = false;

    /*while (!fin) {
        y = hash2(clave, intento);
         y = hash(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].estado == 'O' && tablaHash[y].clave == clave) {
            tablaHash[y].estado = 'D';
            fin = true;
        }else {
            if (tablaHash[y].estado == 'L') {
                fin = false; //Para de buscar porque esta libre
            }else {
                intento++;
            }
        }
    }
    //poner estadisticos
    return false;*/
    while (!fin) {
        // y = hash(clave, intento);
        y = hash2(clave, intento);
        // y = hash3(clave, intento);

        if (tablaHash[y].estado == 'X' && tablaHash[y].clave == clave) {
            tablaHash[y].estado = '?';
            fin = true;
            tamLogico--;
        }else {
            if (tablaHash[y].estado == '-') {
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

/**
 * @brief Destructo de ThashMedicam
 */
ThashMedicam::~ThashMedicam() {}

/**
 * @brief Funcion para aumentar de manera correcta el tamaño de una tabla
 * @param tam unsigned
 */
void ThashMedicam::redispersar(unsigned tam) {
    unsigned nuevoTam = primo_sig(tam);
    std::vector<Entrada> vieja = tablaHash; //Copiamos la tabla original
    tamFisico = nuevoTam;
    tamLogico = 0;
    primo_jr = primo_previo(tamFisico);
    redisp++;

    std::vector<Entrada> nueva(nuevoTam);
    for (int i=0; i < vieja.size(); i++ ) {
        if (vieja[i].estado == 'X') {
            unsigned long clave = vieja[i].clave;
            PaMedicamento batDato = vieja[i].dato;

            bool encontrado = false;
            unsigned j = 0;
           while (j < tamFisico && !encontrado) {
               unsigned y = hash2(clave,j);

               if (nueva[y].estado == '-' || nueva[y].estado == '?') {
                   nueva[y].dato = batDato;
                   nueva[y].clave = clave;
                   nueva[y].estado = 'X';
                   tamLogico++;
                   encontrado = true;
               }else {
                   j++;
               }
           }
        }
    }
    tablaHash = nueva;
}

