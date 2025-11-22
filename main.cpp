#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include "Farmacia.h"
#include "Stock.h"
#include "ThashMedicam.h"

/**
 * @brief La funcion muestra por pantalla una farmacia con sus respectivos datos
 * @param farma Farmacia que vamos a mostrar
 * @post Se muestran por pantalla todos los datos relacionados con una farmacia
 */
void mostrarFarmacia(Farmacia &farma) {
    std::cout<<"CIF = " << farma.get_cif()
    << ", Provincia = " << farma.get_provincia()
    << ", Localidad = " << farma.get_localidad()
    << ", Nombre = " << farma.get_nombre()
    << ", Direccion = " << farma.get_direccion()
    << ", CodPostal = " << farma.get_cod_postal()
    << std::endl;
}

/**
 * @author Pablo Rodriguez Gniadek prg00054@red.ujaen.es
 * @author Marco Diaz Vera mdv00011@red.ujaen.es
 */
int main() {
    //Prueba 1
    MediExpress medBatman("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.65);
    MediExpress medBatman2("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.68);
    std::vector<Farmacia*> farmas_Sevilla = medBatman.buscar_Farmacia_Provincia("SEVILLA");
    std::cout<<"Farmacias encontradas situadas Sevilla: "<< farmas_Sevilla.size()<<std::endl;// esto lo tengo como comprobacion de cuantas de sevilla hay
    int id_Magnes = 3640, id_Carbonato = 3632, id_Cloruro = 3633;
    PaMedicamento *oxido = medBatman.buscaCompuestoMed(id_Magnes);
    PaMedicamento *carbonato = medBatman.buscaCompuestoMed(id_Carbonato);
    PaMedicamento *cloruro = medBatman.buscaCompuestoMed(id_Cloruro);

    //Aqui empezamos a buscar los medicamentos
    //cambiar pq busca ahora es private

    for (int i = 0;i < farmas_Sevilla.size(); i++) {
        //Aqui sacamos los stock de cada PAmedicamento de cada farmacia
        int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
        int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
        int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);

        std::cout<<"==============================="<<std::endl;
        std::cout<<"Stock inicial de cada medicamento de la Farmacia "<<i+1<< ": "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        std::cout<<"Oxido: "<<stock_Magnesio<<", Carbonato: "<<stock_Carbonat<<", Cloruro: "<<stock_Clorur<<std::endl;
        std::cout<<"==============================="<<std::endl;

        for (int j = 0; j < 12; j++) {
            std::cout<<"Persona "<<j+1<<": "<<std::endl;
            int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
            int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
            int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);
            //Hacemos las 12 compras, empezando por oxido
            if (stock_Magnesio > 0) {
                //hemos comprado sin problemas
                farmas_Sevilla[i]->comprarMedicam(id_Magnes,1,oxido);

                std::cout<<"Ha comprado oxido"<<std::endl;
            }else {
                std::cout<<"No hay oxido, pidiendo para la proxima..."<<std::endl;
                farmas_Sevilla[i]->comprarMedicam(id_Magnes,10,oxido);//Compro 10 por si las moscas

                if (stock_Carbonat > 0) {
                    //compramos sin problemas
                    farmas_Sevilla[i]->comprarMedicam(id_Carbonato,1,carbonato);
                    std::cout<<"Ha comprado carbonato"<<std::endl;
                }else {
                    std::cout<<"No hay carbonato, pidiendo para la proxima..."<<std::endl;
                    farmas_Sevilla[i]->comprarMedicam(id_Carbonato, 10,carbonato);
                    if (stock_Clorur > 0) {
                        std::cout<<"Ha comprado cloruro"<<std::endl;
                        farmas_Sevilla[i]->comprarMedicam(id_Cloruro,1,cloruro);

                    }else{
                        std::cout<<"No hay cloruro, pidiendo para la proxima..."<<std::endl;
                        farmas_Sevilla[i]->comprarMedicam(id_Cloruro, 10,cloruro);
                    }
                }
            }
        }
        std::cout<<"==============================="<<std::endl;
        std::cout<<"Stock final de cada medicamento de la Farmacia "<<i+1<< ": "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        std::cout<<"Oxido: "<<farmas_Sevilla[i]->buscaMedicamID(id_Magnes)<<", Carbonato: "<<farmas_Sevilla[i]->buscaMedicamID(id_Carbonato)<<", Cloruro: "<<farmas_Sevilla[i]->buscaMedicamID(id_Cloruro)<<std::endl;
        std::cout<<"==============================="<<std::endl;

    }

    //Prueba2
    std::vector<Farmacia*> farmas_Madrid = medBatman.buscar_Farmacia_Provincia("MADRID");
    std::vector<Farmacia*> farmas_Madrid_Virus;
    // int contadorMadridVirus = 0;
    for (int i=0; i<farmas_Madrid.size(); i++) {
        if (farmas_Madrid[i]->buscaMedicamNombre("VIRUS").size() != 0) {
            farmas_Madrid_Virus.push_back(farmas_Madrid[i]);
            // contadorMadridVirus++;
        }
    }
    std::cout<<"El numero de farmacias de Madrid que tienen algun medicamento que tiene virus es "<<farmas_Madrid_Virus.size()<<" y sus datos son: "<<std::endl;
    for (int l = 0; l < farmas_Madrid_Virus.size(); l++) {
         mostrarFarmacia(*farmas_Madrid_Virus[l]);
     }

    return 0;
}