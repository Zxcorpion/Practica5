#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include <map>
#include <set>
#include <vector>
#include <list>
#include "Farmacia.h"
#include "ThashMedicam.h"


/**
 * @brief Definicion de la clase MediExpress
 */
class MediExpress {
private:
    ThashMedicam idMedication;
    std::multimap<std::string,PaMedicamento*> nombMedication;
    std::list<Laboratorio> labs;
    std::multimap<std::string,Farmacia> pharmacy;
    std::vector<int> vMedi;
    std::list<PaMedicamento> listaMeds;
public:
    MediExpress();
    MediExpress(const std::string &medicamentos, const std::string &laboratorios,
    const std::string &farmacias, unsigned long tam, float lambda);
    MediExpress(const MediExpress &orig);
    ~MediExpress();
    MediExpress& operator=(const MediExpress &orig);

    void set_medication(const std::map<int,PaMedicamento> &medication);
    void set_labs(const std::list<Laboratorio> &labs);

    void suministrarMed(PaMedicamento *pa,Laboratorio *l);
    Laboratorio *buscarLab(const std::string &nombreLab);
    std::list<Laboratorio*> buscarLabs(const std::string &nombrePA);
    std::vector<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    std::vector<PaMedicamento*> buscaCompuesto(const std::string &nombrePA);
    std::vector<PaMedicamento*> getMedicamentoSinLab();
    void borrarLaboratorio(const std::string &nombreCiudad);
    PaMedicamento* buscaCompuestoMed(const int &ID_);
    void suministrarFarmacia(Farmacia *farma, int id_num, int robin);
    Farmacia* buscaFarmacia(const std::string &cif_);
    bool eliminarMedicamento(const unsigned int &id_num);
    std::vector<Farmacia*> buscar_Farmacia_Provincia(const std::string &nombreProvin);

    void mostrarEstado();
    void pruebaRend();
    unsigned long tamTabla() const { return idMedication.getNumElem(); }
    float get_promedio_colisiones() ;//const borrado
    unsigned long get_max10() const;
    unsigned long get_total_colisiones() const;
    float get_factor_carga() const;
    int get_maxColisiones() const;
};
#endif //MEDIEXPRESS_H