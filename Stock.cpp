//
// Created by marco on 10/11/2025.
//

#include "Stock.h"
/**
* @brief Constructor por defecto y parametrizado
* @param id identificador del medicamento
* @param num numero de stock actual
* @param number_ puntero al medicamento que representamos su stock
* @post se crea un objeto stock
*/
Stock::Stock(int id, int num, PaMedicamento *number_):
id_Pa_Med(id),num_stock(num), number(number_)
{}

/**
 * @brief Constructor copia
 * @param orig Objeto que usamos para copiar
 * @post se crea un objeto stock
 */
Stock::Stock(const Stock& orig):
id_Pa_Med(orig.id_Pa_Med),num_stock(orig.num_stock),number(orig.number)
{}

/**
 *@brief Destructor de la clase Stock
 * @post Se libera la memoria
 */
Stock::~Stock() {

}

/**
 * @biref Funcion para leer el id_Pa_Med
 * @return id_Pa_Med
 */
int Stock::get_id_pa_med() const {
    return id_Pa_Med;
}

/**
 * @brief Funcion para asignar un valor al atributo id_Pa_Med
 * @param id_pa_med
 */
void Stock::set_id_pa_med(int id_pa_med) {
    id_Pa_Med = id_pa_med;
}
/**
 * @biref Funcion para leer el num_stock
 * @return num_stock
 */
int Stock::get_num_stock() const {
    return num_stock;
}
/**
 * @brief Funcion para asignar un valor al atributo num_stock
 * @param num_stock
 */
void Stock::set_num_stock(int num_stock) {
    this->num_stock = num_stock;
}
/**
 * @biref Funcion para leer el number
 * @return number
 */
PaMedicamento * Stock::get_number() const {
    return number;
}
/**
 * @brief Funcion para asignar un valor al atributo number
 * @param number
 */
void Stock::set_number(PaMedicamento *number) {
    this->number = number;
}

/**
 * @brief Operador < de la calse Stock
 * @param parametro Objeto Stock que vamos a comparar
 * @return True si se cumple la condicion o falso si no se cumple
 */
bool Stock::operator<(const Stock &parametro) const{
    return id_Pa_Med < parametro.id_Pa_Med;
}

/**
 * @brief Operador ==
 * @param parametro Objeto Stock que vamos a comparar
 * @return True si se cumple la condicion o falso si no se cumple
 */
bool Stock::operator==(const Stock &parametro) const{
    return id_Pa_Med == parametro.id_Pa_Med;
}

/**
 * @brief Funcion que sirve para incrementar el valor del atributo num_stock
 * @param cantidad entero que vamos a sumar a num_stock
 */
void Stock::incrementa(const int &cantidad) {
    num_stock+=cantidad;
}

/**
 * @brief Funcion que sirve para decrementar el valor del atributo num_stock
 * @param cantidad entero que vamos a restar a num_stock
 */
void Stock::decrementa(const int &cantidad) {
    num_stock-=cantidad;
}
