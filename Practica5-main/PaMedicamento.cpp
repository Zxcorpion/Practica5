//
// Created by marco on 10/11/2025.
//

#include "PaMedicamento.h"
/**
 * @brief Constructor por defecto y parametrizado
 * @param int id_num numero de identificación de medicamento que por defecto es 0
 * @param string id_alpha otra forma de identificación del medicamento que por defecto es " "
 * @param string nombre_ numero nombre del medicamento que por defecto es " "
 */
PaMedicamento::PaMedicamento(int id_num_,std::string id_alpha_, std::string nombre_):
id_num(id_num_),
id_alpha(id_alpha_),
nombre(nombre_)

{
    serve = nullptr;
}

/**
 * @brief Constructor de copia
 * @param orig Objeto que se quiere copiar
 * @post Se crea un nuevo objeto de clase PaMedicamento con los atributos de orig
 */
PaMedicamento::PaMedicamento(const PaMedicamento &orig):
id_num(orig.id_num),
id_alpha(orig.id_alpha),
nombre(orig.nombre)

{
    serve = orig.serve;

}
/**
 * @brief Destructor de la clase PaMedicamento
 */
PaMedicamento::~PaMedicamento() {
    if(serve != nullptr)
    serve = nullptr;

}


/**
 * @brief Función para leer el atributo id_num
 * @return Devuelve el atributo id_num
 */
int PaMedicamento::get_id_num() const {
    return id_num;
}
/**
 * @brief Función para establecer un id_num
 * @param int id_num nuevo valor al atributo id_num
 */
void PaMedicamento::set_id_num(int id_num) {
    this->id_num = id_num;
}
/**
 * @brief Función para leer el atributo id_alpha
 * @return devuelve el atributo id_alpha
 */
std::string PaMedicamento::get_id_alpha() const {
    return id_alpha;
}
/**
 * @brief Función para establecer un nuevo valor al atributo id_alpha
 * @param string id_alpha nuevo valor al atributo id_alpha
 */
void PaMedicamento::set_id_alpha(const std::string &id_alpha) {
    this->id_alpha = id_alpha;
}
/**
 * @brief Función para leer el atributo nombre
 * @return El nombre del medicamento
 */
std::string PaMedicamento::get_nombre() const {
    return nombre;
}
/**
 * @brief Función para establecer un nombre
 * @param string nombre
 */
void PaMedicamento::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
}
/**
 * @brief Operador menor que
 * @param orig Objeto que vamos a usar para la comparación menor
 * @return bool verdadero si cumple que es menor o falso si no lo es
 */
bool PaMedicamento::operator<(const PaMedicamento &orig) const {
    return id_num < orig.id_num;
}
/**
 * @brief Operador de asignacion
 * @param orig Objeto del que se extraen los datos
 * @return Referencia al objeto mismo
 * @post Los datos del vector son reemplazados por los de orig
 */
PaMedicamento &PaMedicamento::operator=(const PaMedicamento &orig) {
    if (this != &orig) {
        id_num = orig.id_num;
        id_alpha = orig.id_alpha;
        nombre = orig.nombre;
        serve = orig.serve;
    }
    return (*this);
}
/**
 * @brief Operador comparación
 * @param orig Objeto que utilizamos para la comparación
 * @return bool verdadero si los dos objetos son iguales, falso si no lo es
 */
bool PaMedicamento::operator==(const PaMedicamento &orig) const {
    return orig.id_num == this->id_num;
}

/**
 * @brief Funcion para leer el atributo serve
 * @return puntero a serve
 */
Laboratorio *PaMedicamento::getServe() const {
    return serve;
}

/**
 * @brief Funcion para establecer un valor al atributo serve
 * @param serve_ puntero a laboratorio
 */
void PaMedicamento::servidoPor(Laboratorio *serve_) {
    this->serve = serve_;
}
