#include "Farmacia.h"
#include "MediExpress.h"

/**
 * @brief Constructor por defecto y parametrizado
 * @param cif CIF de la farmacia
 * @param provincia Provincia donde se encuantra la farmacia
 * @param localidad Localidad donde se encuantra la farmacia
 * @param nombre Nombre de la farmacia
 * @param direccion Direccion de la farmacia
 * @param codPostal Codigo postal de la farmacia
 * @param link Atributo que asocia una farmacia con MediExpress
 * @post Se crea un objeto Farmacia con los atributos pasados por cabecera
 */
Farmacia::Farmacia(std::string cif, std::string provincia, std::string localidad,
                   std::string nombre, std::string direccion, std::string codPostal, MediExpress *link):
cif_(cif),
provincia_(provincia),
localidad_(localidad),
nombre_(nombre),
direccion_(direccion),
codPostal_(codPostal),
linkMedi(link),
order()
{
}

/**
 * @brief Constructor copia de un objeto Farmacia
 * @param orig Objeto Farmacia que vamos a copiar
 * @post Se crea un objeto Farmacia asignando a sus atributos los valores de los atributos orig pasado por cabecera
 */
Farmacia::Farmacia(const Farmacia &orig):
cif_(orig.cif_),
provincia_(orig.provincia_),
localidad_(orig.localidad_),
nombre_(orig.nombre_),
direccion_(orig.direccion_),
codPostal_(orig.codPostal_),
linkMedi(orig.linkMedi),
order(orig.order)
{}

/**
 * @brief Destructor de Farmacia
 * @post Se libera la memoria correspondiente
 */
Farmacia::~Farmacia() {
    linkMedi = 0;
}
/**
 * @brief Función para leer el atributo cif_
 * @return Devuelve el atributo cif_
 */
std::string Farmacia::get_cif() const {
    return cif_;
}
/**
 * @brief Función para establecer un  cif_
 * @param cif nuevo valor al atributo cif_
 */
void Farmacia::set_cif(const std::string &cif) {
    cif_ = cif;
}
/**
 * @brief Función para leer el atributo provincia_
 * @return Devuelve el atributo provincia_
 */
std::string Farmacia::get_provincia() const {
    return provincia_;
}
/**
 * @brief Función para establecer un provincia_
 * @param provincia nuevo valor al atributo provincia_
 */
void Farmacia::set_provincia(const std::string &provincia) {
    provincia_ = provincia;
}
/**
 * @brief Función para leer el atributo localidad_
 * @return Devuelve el atributo localidad_
 */
std::string Farmacia::get_localidad() const {
    return localidad_;
}
/**
 * @brief Función para establecer un localidad_
 * @param localidad nuevo valor al atributo localidad_
 */
void Farmacia::set_localidad(const std::string &localidad) {
    localidad_ = localidad;
}
/**
 * @brief Función para leer el atributo nombre_
 * @return Devuelve el atributo nombre_
 */
std::string Farmacia::get_nombre() const {
    return nombre_;
}
/**
 * @brief Función para establecer un nombre_
 * @param nombre nuevo valor al atributo nombre_
 */
void Farmacia::set_nombre(const std::string &nombre) {
    nombre_ = nombre;
}
/**
 * @brief Función para leer el atributo direccion_
 * @return Devuelve el atributo direccion_
 */
std::string Farmacia::get_direccion() const {
    return direccion_;
}
/**
 * @brief Función para establecer un codigo direccion_
 * @param direccion nuevo valor al atributo direccion_
 */
void Farmacia::set_direccion(const std::string &direccion) {
    direccion_ = direccion;
}
/**
 * @brief Función para leer el atributo codPostal_
 * @return Devuelve el atributo codPostal_
 */
std::string Farmacia::get_cod_postal() const {
    return codPostal_;
}
/**
 * @brief Función para establecer un codigo postal
 * @param cod_postal nuevo valor al atributo codpostal_
 */
void Farmacia::set_cod_postal(const std::string &cod_postal) {
    codPostal_ = cod_postal;
}

/**
 * @brief Operador de asignacion de la clase Farmacia
 * @param orig  Objeto que usamos de referencia para asignar valores a nuestro objeto
 * @return Farmacia con los atributos de otra farmacia
 * @post Objeto this cambia los valores de sus atributos
 */
Farmacia &Farmacia::operator=(const Farmacia &orig) {
    if (this != &orig) {
        cif_ = orig.cif_;
        provincia_ = orig.provincia_;
        localidad_ = orig.localidad_;
        nombre_ = orig.nombre_;
        direccion_ = orig.direccion_;
        codPostal_ = orig.codPostal_;
    }
    return *this;
}

/**
 * @brief Operador <
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es menor al de orig
 */
bool Farmacia::operator<(const Farmacia &orig) const {
    return cif_ < orig.cif_;
}
/**
 * @brief Operador ==
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es igual al de orig
 */
bool Farmacia::operator==(const Farmacia &orig) const {
    return cif_ == orig.cif_;
}
/**
 * @brief Operador >
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es mayor al de orig
 */
bool Farmacia::operator>(const Farmacia &orig) const {
    return cif_ > orig.cif_;
}

/**
 * @brief Funcion para pedir un medicamento
 * @param ID Id del PAmedicamento a buscar
 * @post La farmacia es suministrada con un nuevo PAmedicamento
 */
void Farmacia::pedidoMedicam(const int &id_num,const int &robin) {
    linkMedi->suministrarFarmacia(this,id_num,robin);
}

//AÑADIDO. Hay que ver si robin siempre va aser 10 unidades o no
void Farmacia::pedidoMedicam(std::string nombrelol, const int &robin) {
    std::vector<PaMedicamento*> auxiliar = linkMedi->buscaCompuesto(nombrelol);
    for(int i=0; i < auxiliar.size(); i++) {
        linkMedi->suministrarFarmacia(this,auxiliar[i]->get_id_num(),robin);
    }
}

/**
 * @brief Metodo que devuelve el stock que tiene una farmacia sobre un PAmedicamento
 * @param id_num ID del PAmedicamento
 * @return Stock de la farmacia sobre un PAmedicamento
 * @post El metodo nos devuelve el numero de unidades de un PAmedicamento que dispone una farmacia
 */
int Farmacia::buscaMedicamID(const int &id_num) {
    //Creamos un stock para buscarlo
    //Stock ss1(id_num);
    //Creamos un iterador y usamos la funcion find para encontrar el medicamento con el id pasado por cabecera, creando uno con el id
    //std::set<Stock>::iterator it = order.find(ss1);
    std::map<unsigned int, Stock>::iterator it = order.find(id_num);
    if (it != order.end() && it->second.get_num_stock() > 0) {
        return it->second.get_num_stock();
    }
        //Si no existe o no le queda stock devuelve 0
        return 0;
}


/**
 * @brief El metodo devuelve un vector de Pamedicamentos segun un nombre dado
 * @param nombresito Nombre del PAmedicamento
 * @return Vector de PAmedicamentos
 */
std::vector<PaMedicamento*> Farmacia::buscaMedicamNombre(const std::string &nombresito) {
    std::vector<PaMedicamento*> vectorcillo;
    std::map<unsigned int, Stock>::iterator it = order.begin();
    while (it != order.end()) {
        PaMedicamento *med = it->second.get_number(); //Aqui guardamos el objeto tipo pamed sacado de order
        if (med != 0) {
            if (med->get_nombre().find(nombresito) != std::string::npos) {
                vectorcillo.push_back(med);
            }
        }
        it++;
    }
    return vectorcillo;
}


/**
 * @brief Funcion para comprar un medicamento
 * @param id_num identificacion del medicamento
 * @param robinunidades unidades que queremos comprar
 * @param paMed puntero al medicamento que queremos comprar
 * @post Pedimos un medicamento o decrementamos el stock
 * @return 0 si no hay suficiente stock o devolvemos el stock actual
 */
int Farmacia::comprarMedicam(const int &id_num,const int &robinunidades, PaMedicamento *&paMed) {
    int stock_PaMed = buscaMedicamID(id_num);
    //Comprobamos que hay unidades suficientes
    if(stock_PaMed >= robinunidades) {
        //Creamos un stock con el id del medicamento que queremos comprar
        //Stock aux1(id_num);
        //buscamos en nuestro order el medicamente mediante la funcion find
        //std::set<Stock>::iterator it1 = order.find(aux1);
        std::map<unsigned int, Stock>::iterator it1 = order.find(id_num);
        //Lo guardo en una auxiliar para poder modificarlo
        paMed = it1->second.get_number();
        Stock aux2 = it1->second;
        //Lo eliminamos ya que para modificar un objeto del order, antes hay que sacarlo
        order.erase(it1);
        //Cogemos las unidades necesarias
        aux2.decrementa(robinunidades);
        //Lo volvemos a insertar en nuestro order (revisar)
        order.insert(std::pair<unsigned int,Stock>(aux2.get_id_pa_med(),aux2));
    }else {
        //Si no hay suificiente stock llamamos a pedidoMedicam y le pasamos el numero de unidades que necesitamos
       // int aux3 = buscaMedicamID(id_num);
        //aux3 = robinunidades-aux3;
        pedidoMedicam(id_num,robinunidades);
        return 0;
    }
    return stock_PaMed;
}

/**
 * @brief Fucnion asignarle un nuevo stock a un medicamento
 * @param batmelatonina puntero al medicamento  que vamos a asignarle un nuevo stock
 * @param robin numero de stock que vamos a asignar
 * @post Incrementamos el stock de un medicamento  o insertamos un objeto stock nuevo si no existe
 */
void Farmacia::nuevoStock(PaMedicamento *batmelatonina, int &robin) {
    //Stock bat1(batmelatonina->get_id_num());
    //std::set<Stock>::iterator it1 = order.find(bat1);
    std::map<unsigned int, Stock>::iterator it1 = order.find(batmelatonina->get_id_num());
    if(it1 != order.end()) {
        //analogo a comprarMedicam solo que ahora incrementamos
        Stock aux2 = it1->second;
        order.erase(it1);
        aux2.incrementa(robin);
        order.insert(std::pair<unsigned int,Stock>(aux2.get_id_pa_med(),aux2));
    }else {
        //Cuando no existe lo creamos nosotros
        Stock nuevorobin(batmelatonina->get_id_num(),robin, batmelatonina);
        //Para enlazarlo correctamente con PaMedicamente lo insertamos en el order
        order.insert(std::pair<unsigned int,Stock>(nuevorobin.get_id_pa_med(),nuevorobin));
    }
}

/**
 * @brief Metodo que elimina el stock de un PAmedicamento
 * @param id_num ID del PAmedicamento
 * @return[true] Si se ha eliminado correctamente
 * @return[false] Si no se ha borrado con exito
 * @post Cuando una farmacia descataloga un PAmedicamento, lo borra de su stock
 */
bool Farmacia::eliminarStock(const int &id_num) {
    //Primero creo un stock y con find lo busco dentro del mapa
    //Stock buscado(id_num);
    //std::set<Stock>::iterator itPennyworth = order.find(buscado);
    std::map<unsigned int, Stock>::iterator itPennyworth = order.find(id_num);
    if(itPennyworth != order.end()) { //Si el iterador ha encontrado correctamente el PAmedicamento
    //Una vez localizado, procedo a borrarlo
        order.erase(itPennyworth);
    }else {
        return false;
    }
    return true;
}