//
// Created by marco on 10/11/2025.
//

#include "MediExpress.h"
#include <map>


/**
 * @brief Constructor por defecto de la clase MediExpress
 * @post Se crea un objeto con los valores asignados por defecto
 */
MediExpress::MediExpress():
idMedication(3310,0.7),labs(),pharmacy(), vMedi() {
}

/**
 * @brief Constructor parametrizado de la clase MediExpress
 * @param medicamentos pasados por referencia
 * @param laboratorios pasador por referencia
 * @post Se crea un objeto de la clase MediExpress con los valores pasados por cabecera, que son leidos de varios ficheros .csv
 */
MediExpress::MediExpress(const std::string &medicamentos, const std::string &laboratorios, const std::string &farmacias) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_number_string = "";
    std::string id_alpha="";
    std::string nombre="";

    std::list<PaMedicamento> listaPAMeds;


    is.open(medicamentos); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');

                int id_num = 0;
                try {
                    id_num = std::stoi(id_number_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                PaMedicamento medicamento(id_num,id_alpha,nombre);
                idMedication.insertar(id_num,medicamento);
                listaPAMeds.push_back(medicamento);
                vMedi.push_back(id_num);

                fila="";
                columnas.clear();

                /*
                std::cout << ++contador
                          << " Medicamento: ( Id_number=" << id_num
                          << " id_alpha=" << id_alpha << " Nombre=" << nombre
                          << ")" << std::endl;
                          */

            }
        }

        is.close();

        std::cout << "Tiempo de lectura de meds: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    //Asociacion
    for (int i=0;i<vMedi.size();i++) {
        PaMedicamento *aux = idMedication.buscar(vMedi[i]);
        std::string aux_nom = aux->get_nombre();
        std::stringstream ss; //Usamos para cortar el medicamento
        std::string batNombre;
        while (getline(ss, batNombre, ' ')) {
            nombMedication.insert(std::pair<std::string,PaMedicamento*>(batNombre,aux));
        }
    }

    //Leemos el segundo fichero

    std::string id_numero_string = "";
    std::string nombreLab_ = "";
    std::string direccion_="";
    std::string codigPostal_="";
    std::string localidad_="";


    is.open(laboratorios); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_;direccion;codigPostal_;localidad_

                getline(columnas, id_numero_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombreLab_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, direccion_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, codigPostal_,';');
                getline(columnas, localidad_,';');

                int id_numero = 0;
                try {
                    id_numero = std::stoi(id_numero_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                Laboratorio lab(id_numero,nombreLab_,direccion_,codigPostal_,localidad_);
                try {
                    std::list<Laboratorio>::iterator it = labs.begin();
                    while (it != labs.end() && it->getId() < id_numero) {
                        it++;
                    }
                    labs.insert(it,lab);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }


                /*std::cout << ++contador
                          << " Laboratorio: ( Id= " << id_numero
                          << " Nombre= " << nombreLab_ << " Direccion= " << direccion_
                          << " Codigo Postal= " <<codigPostal_
                          << " Localidad= "<< localidad_ <<std::endl;
                          */

            }
        }

        is.close();

        std::cout << "Tiempo de lectura de labs: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //Enlazamos cada laboratorio con 2 PAmedicamentos
    std::list<Laboratorio>::iterator itLaboratorio = labs.begin();
    PaMedicamento *paMed_asociar;
    std::vector<int>::iterator batMedi = vMedi.begin();
    while (itLaboratorio != labs.end() && batMedi != vMedi.end()) {
        paMed_asociar = idMedication.buscar(*batMed);
        this->suministrarMed(&it_Medication->second,&(*itLaboratorio));
        it_Medication++;
        //Comprobamos si no hemos llegado al final
        if (it_Medication != medication.end()) {
            this->suministrarMed(&it_Medication->second,&(*itLaboratorio));
            it_Medication++;
        }
        itLaboratorio++;
    }
    //int cont=0;
    /*for (int i=0; i<medication.tamlog_(); i++){
        if (medication[i].getServe()) {
            std::cout << "ID del PaMedicamento: " << medication[i].get_id_num()<<
                ", ID del Laboratorio asociado: " << medication[i].getServe()->getId() << std::endl;
        }else{
            cont++;
        }
    }
    */
    //La comprobacion sobra ya que el tamaño logico de sinLabs es el contador
    std::vector<Laboratorio*> labsMadrid = this->buscarLabCiudad("Madrid");
    std::vector<PaMedicamento*> medSin = this->getMedicamentoSinLab();
    std::cout << "Medicamentos sin asignar: " << medSin.size() << std::endl;

    for (int i = 0; i < medSin.size(); i++) {
        medSin[i]->servidoPor(labsMadrid[i]);
    }/* Comprobamos que ya no hay PAmedicamentos sin laboratorio asignado
    int cont2=0;
    for (int i=0; i<medication.tamlog_(); i++) {
        if (!medication[i].getServe()) {
            cont2++;
        }
    }
    std::cout<<cont2<<std::endl;
    */ //Comprobacion de que no hay ninguno sin asignar ahora


    //Leemos el tercer archivo
    std::string cif_ = "";
    std::string provincia_= "";
    std::string localidadLab_= "";
    std::string nombre_= "";
    std::string direccionLab_= "";
    std::string codPostal_= "";

    is.open(farmacias); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidadLab_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccionLab_,';');
                getline(columnas, codPostal_,';');


                Farmacia farmacia_(cif_,provincia_,localidadLab_,nombre_, direccionLab_, codPostal_,this);
                try {
                    //pharmacy.push_back(farmacia_);
                    pharmacy.insert(std::pair<std::string ,Farmacia>(provincia_,farmacia_));
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.str(std::string());
                columnas.clear();
                columnas.str(fila);


                /*
                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidadLab_
                          << " Nombre = " << nombre_ << " Direccion = " << direccionLab_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
                          */

            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //abrir fichero para meter vector de string
    std::vector<std::string> vectorCIFS;
    is.open(farmacias); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'

                try {
                    vectorCIFS.push_back(cif_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.str(std::string());
                columnas.clear();
                columnas.str(fila);

                /*std::cout << ++contador
                          << " CIF de Farmacia = " << cif_
                          <<  std::endl;
                          */

            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    //Aniadimos todos los cifs a cada farmacia
    std::vector<int>::iterator it_asignar_LabsMedi = vMedi.begin();
    if (it_asignar_LabsMedi != vMedi.end()) { //No ha llegado al final
        std::vector<int>::iterator ultimoMedi = vMedi.end();
        --ultimoMedi;
        for (int i=0; i < vectorCIFS.size(); i++) {
            Farmacia *farmacia_Insercion = this->buscaFarmacia(vectorCIFS[i]);
            int contador=0;
            while (contador<100) {
                suministrarFarmacia(farmacia_Insercion,it_asignar_LabsMedi->second.get_id_num(),10);
                if (it_asignar_LabsMedi == ultimoMedi) { //Si he llegado al final de los medicamentos, reseteo el iterador para volver a asignar
                    it_asignar_LabsMedi = vMedi.begin();
                }else{
                    it_asignar_LabsMedi++;
                }
                contador++;
            }
        }
    }
}

/**
 * @brief Constructor de copia de la clase MediExpress
 * @param orig objeto que vamos a copiar
 * @post Se crea un objeto de la clase MediExpress copiando el objeto pasado por cabecera
 */
MediExpress::MediExpress(const MediExpress &orig):
idMedication(orig.idMedication),labs(orig.labs), pharmacy(orig.pharmacy),vMedi(orig.vMedi)
{}
/**
 * @brief Operador de igualacion
 * @param orig objeto de la clase MediExpress del que quieren coger los datos
 * @return Devuelve *this ya modificado o no
 * @post El metodo asigna los mismos valores del objeto pasado por cabecera
 */
MediExpress &MediExpress::operator=(const MediExpress &orig) {
    if(this!=&orig) {
        idMedication = orig.idMedication;
        labs = orig.labs;
        pharmacy = orig.pharmacy;
        vMedi = orig.vMedi;
    }
    return *this;
}

/**
 * @brief Funcion para establecer un valor al atributo medication
 * @param medication valor que queremos asignar a medication
 * @post El atributo medication es modificado por un nuevo valor
 */
void MediExpress::set_medication(const std::map<int,PaMedicamento> &medication) {
    this->medication = medication;
}


/**
 * @brief Funcion para establecer un valor al atributo labs
 * @param labs valor que queremos asignar a nuestro atributo labs
 * @post El atributo labs es modificado por un nuevo valor
 */
void MediExpress::set_labs(const std::list<Laboratorio> &labs) {
    this->labs = labs;
}

/**
 * @brief Destructor de los objetos MediExpress
 * @post Se libera la memoria
 */
MediExpress::~MediExpress() {
}

/**
 * @brief Funcion para asociar un laboratorio a un medicamento
 * @param pa Puntero de Pamedicamento
 * @param l Puntero de Laboratorio
 * @post PaMedicamento pasado por cabecera es asociado con un laboratorio
 */
void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l) {
    if (pa && l != 0 )
    pa->servidoPor(l);
}

/**
 * @brief Funcion para buscar un laboratorio
 * @param nombreLab pasado por referencia
 * @return &aux.dato si se ha encontrado el laboratorio o 0 si no se ha encontrado
 */
Laboratorio *MediExpress::buscarLab(const std::string &nombreLab) {
    std::list<Laboratorio>::iterator aux=labs.begin();
    while (aux!=labs.end()) {
        if(aux->getNomrbeLab().find(nombreLab) != std::string::npos) {
            return &(*aux);
        }
        aux++;
    }
    return 0;
}

/**
 * @brief Funcion para buscar laboratorios de una ciudad
 * @param nombreCiudad pasada por referencia
 * @return vector con los laboratorios que se encuentran en la ciudad pasada por cabecera
 */
std::vector<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    std::vector<Laboratorio*> vector;
    std::list<Laboratorio>::iterator aux=labs.begin();
    while (aux!=labs.end()) {
        if(aux->getLocalidad().find(nombreCiudad) != std::string::npos) {
            vector.push_back(&(*aux));
        }
        aux++;
    }
    return vector;
    }

/**
 * @brief Funcion para buscar compuestos en un vector dinamico de PaMedicamento
 * @param nombrePA  pasado por referencia
 * @return vector con los medicamentos que contienen el nombre pasado por referencia
 * @post se crea un vector auxiliar y se inserta en el lo medicametnos convenientes
 */
std::vector<PaMedicamento*> MediExpress::buscaCompuesto(const std::string &nombrePA) {
    std::vector<PaMedicamento*>auxiliar;
    for(std::map<int,PaMedicamento>::iterator aux = medication.begin();aux != medication.end();aux++) {
        if(aux->second.get_nombre().find(nombrePA) != std::string::npos) {
            auxiliar.push_back(&(aux->second));
        }
    }
    return auxiliar;
}

/**
 * @brief Funcion para leer un vector de medicamentos que no tienen asociados un laboratorio
 * @return aux, vector con todos los medicamentos sin laboratorio asociado
 * @post se crea y se modifica un vector con medicamentos dentro del él
 */
std::vector<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    std::vector<PaMedicamento*> aux;
    std::map<int,PaMedicamento>::iterator it_busca_SinLab = medication.begin();
    while (it_busca_SinLab != medication.end()) {
        if (it_busca_SinLab->second.getServe() == 0)
        aux.push_back(&(it_busca_SinLab->second));
        it_busca_SinLab++;
    }
    return aux;
}

/**
 * @brief Funcion para borrar laboratorios de forma correcta
 * @param nombreCiudad pasado por referencia
 * @post se borran todos los medicamentos que coinciden con el nombre pasado por referencia y desenlaza el laboratorio de sus medicamentos
 */
void MediExpress::borrarLaboratorio(const std::string &nombreCiudad) {
    std::list<Laboratorio>::iterator encontrado=labs.begin();

    int cont=0;
    for(int i=0;i<medication.size();i++) {
        if(medication[i].getServe() !=nullptr && medication[i].getServe()->getLocalidad().find(nombreCiudad) != std::string::npos) {
            medication[i].servidoPor(nullptr);
        }else {
            cont++;
        }
    }
    if(cont==medication.size()) {
        throw std::invalid_argument("Error al localizar la localidad");
    }
    while(encontrado != labs.end()) {
        if(encontrado->getLocalidad().find(nombreCiudad) != std::string::npos) {
            encontrado = labs.erase(encontrado);
        }else
            encontrado++;
    }
}

/**
 * @brief Metodo que se encarga de buscar un medicamento segun su id
 * @param ID_ Id del PAmedicamento a buscar
 * @return PAmedicamento que se quiere buscar
 * @post El medicamento buscado es encontrado y devuelto, en caso de no encontrarse, se devuelve un puntero a null
 */
PaMedicamento *MediExpress::buscaCompuestoMed(const int &ID_) {
    for(std::map<int,PaMedicamento>::iterator it_Batman = medication.begin();it_Batman != medication.end();it_Batman++) {
        if(it_Batman->second.get_id_num() == ID_) {
            return &(it_Batman->second);
        }
    }
    return 0;
}

/**
 * @brief El metodo permite suministrar un PAmedicamento en caso de que la farmacia no lo tenga
 * @param farma Farmacia sobre la que queremos añadir el PAmedicamento
 * @param ID_ ID del PAmedicamento que se quiere buscar
 */
void MediExpress::suministrarFarmacia(Farmacia *farma, int id_num, int robin) {
    //De entre todas las opciones para buscar en un map usamos find
    std::map<int,PaMedicamento>::iterator it = medication.find(id_num);
    //Comprobamos si lo hemos encontrado, de ser asi llamamos a nuevostock
    if(it != medication.end()) {
        farma->nuevoStock(&it->second,robin);
    }

    /* PaMedicamento *medicam = buscaCompuesto(id_num);
    if (medicam) {
        farma->nuevoStock(medicam,n);
    // }else {
    //     throw std::invalid_argument("Error al suministrar farmacia: Medicamrnto no encontrado");
    }*/
}

/**
 * @brief Funcion para buscar una farmacia en funcion de su cif
 * @param cif_ cif de la Farmacia
 * @return puntero de la farmacia encontrada
 */
Farmacia *MediExpress::buscaFarmacia(const std::string &cif_) {
    //Creamos un objeto de tipo farmacia para buscarlo
    std::vector<Farmacia>::iterator batFarmacia = pharmacy.begin();
    while(batFarmacia != pharmacy.end()) {
        if (batFarmacia->get_cif() == cif_) {
            return &(*batFarmacia);
        }
        batFarmacia++;
    }
    return 0;
}

/**
 * @brief Funcion para buscar laboratorios en funcion de nombrePA
 * @param nombrePA PaMedicamento
 * @return lista de laboratorios encontrados
 */
std::list<Laboratorio*> MediExpress::buscarLabs(const std::string &nombrePA) {
   std::list<Laboratorio*> lista;
   for (int i =0; i<medication.size();i++) {
       Laboratorio *auxilio = medication[i].getServe();
       if (medication[i].get_nombre() == nombrePA) {
           lista.push_back(auxilio);
       }
   }
    return lista;
}

/**
 * @brief Metodo que busca las farmacias de una determinada provincia y devuelve un vector con ellas
 * @param nombreProvin Nombre de la provincia sobre la que buscamos
 * @return Vector de Farmacias* de una provincia
 * @post Se crea un vector de Farmacias*, donde almacenamos aquellas farmacias pertenecientes a una provincia determinada
 */
std::vector<Farmacia*> MediExpress::buscar_Farmacia_Provincia(const std::string &nombreProvin) {
    std::vector<Farmacia*> farmacias_Nightwing;
    for (int i=0;i<pharmacy.size();i++) {
        if (pharmacy[i].get_provincia().find(nombreProvin) != std::string::npos) {
            farmacias_Nightwing.push_back(&(pharmacy[i]));
        }
    }
    return farmacias_Nightwing;
}

/**
 * @brief Metodo para eliminar un PAmedicamento de Mediexpress
 * @param if_num ID del numero
 * @return[true] Si el borrado ha sido exitoso
 * @return[false] Si no se ha borrado correctamente
 * @post El PAmedicamento y su stock quedan eliminados
 */
bool MediExpress::eliminarMedicamento(const unsigned int &if_num) {
    //Localizamos primero todos los medicamentos
    std::map<int,PaMedicamento>::iterator itTodd= medication.find(if_num);

    if (itTodd != medication.end()) {
        //Primero, debemos eliminar el stock de TODAS las farmacias
        for (int i=0;i<pharmacy.size();i++) {
            pharmacy[i].eliminarStock(if_num);
        }

        itTodd->second.servidoPor(0);//Desenlazamos el objeto ya que es relacion de asociacion para destruirlo
        //Eliminamos primero ese medicamento de MediExpress
        medication.erase(itTodd);
    }else {
        return false;
    }

    return true;
}

