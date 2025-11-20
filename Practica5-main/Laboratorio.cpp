//
// Created by marco on 10/11/2025.
//

#include "Laboratorio.h"

/**
 *
 * @param id_ @brief Constructor parametrizado y por defecto
 * @param nombreLab_ nombre del laboratorio
 * @param direccion_ direccion donde se encuentra laboratorio
 * @param codiPostal_ codigo postal
 * @param localidad_ localidad
 * @post Se crea un objeto Laboratorio asignando los atributos pasados por cabecera
 */
Laboratorio::Laboratorio(int id_, std::string nombreLab_, std::string direccion_, std::string codiPostal_,std::string localidad_):
id(id_),
nombreLab(nombreLab_),
direccion(direccion_),
codiPostal(codiPostal_),
localidad(localidad_)
{}

/**
 * @brief Constructor copia de Laboratorio
 * @param orig objeto que vamos a copiar
 * @post Se crea un objeto Laboratorio copiando los atributos del objeto pasado por cabecera
 */
Laboratorio::Laboratorio(const Laboratorio &orig):
id(orig.id),
nombreLab(orig.nombreLab),
direccion(orig.direccion),
codiPostal(orig.codiPostal),
localidad(orig.localidad)

{}

/**
 * @brief Destructor de Laboratorio
 * @post Se libera memoria
 */
Laboratorio::~Laboratorio() {}

/**
 * @brief Función para leer el atributo id
 * @return Devuelve el atributo id
 */
int Laboratorio::getId() const {
    return id;
}
/**
 * @brief Función para establecer un id
 * @param int id nuevo valor al atributo id
 */
void Laboratorio::setId(int id) {
    Laboratorio::id = id;
}
/**
 * @brief Función para leer el atributo nombreLab
 * @return Devuelve el atributo id
 */
const std::string &Laboratorio::getNomrbeLab() const {
    return nombreLab;
}
/**
 * @brief Función para establecer un nombreLab
 * @param string nomrbeLab nuevo valor al atributo nombreLab
 */
void Laboratorio::setNomrbeLab(const std::string &nomrbeLab) {
    Laboratorio::nombreLab = nomrbeLab;
}
/**
 * @brief Función para leer el atributo direccion
 * @return Devuelve el atributo direccion
 */
const std::string &Laboratorio::getDireccion() const {
    return direccion;
}
/**
 * @brief Función para establecer un direccion
 * @param string direccion nuevo valor al atributo direccion
 */
void Laboratorio::setDireccion(const std::string &direccion) {
    Laboratorio::direccion = direccion;
}
/**
 * @brief Función para leer el atributo codiPostal
 * @return Devuelve el atributo codiPostal
 */
const std::string &Laboratorio::getCodiPostal() const {
    return codiPostal;
}
/**
 * @brief Función para establecer un codigo postal
 * @param string codiPostal nuevo valor al atributo codiPostal
 */
void Laboratorio::setCodiPostal(const std::string &codiPostal) {
    Laboratorio::codiPostal = codiPostal;
}
/**
 * @brief Función para leer el atributo localidad
 * @return Devuelve el atributo localidad
 */
const std::string &Laboratorio::getLocalidad() const {
    return localidad;
}
/**
 * @brief Función para establecer un codigo localidad
 * @param string localidad nuevo valor al atributo localidad
 */
void Laboratorio::setLocalidad(const std::string &localidad) {
    Laboratorio::localidad = localidad;
}

/**
 * @brief Operador de asignacion
 * @param orig Objeto del que cogemos los datos
 * @return Laboratorio con datos de orig
 */
Laboratorio &Laboratorio::operator=(const Laboratorio &orig) {
    if (this != &orig) {
        id = orig.id;
        nombreLab = orig.nombreLab;
        direccion = orig.direccion;
        codiPostal = orig.codiPostal;
        localidad = orig.localidad;
    }
    return (*this);
}
