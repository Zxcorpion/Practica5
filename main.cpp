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
    //MediExpress medBatman2("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.68);
    //medBatman2.mostrarEstado();
    MediExpress medBatman("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.65);
    medBatman.mostrarEstado();

    std::string medicamentos[6]={
        {"MAGNESIO CLORURO HEXAHIDRATO"},
        {"CLORURO"},
        {"ANHIDRO CALCIO CLORURO"},
        {"LIDOCAINA HIDROCLORURO"},
        {"MENTA PIPERITA"},
        {"VIRUS GRIPE"}
    };
    std::vector<std::vector<PaMedicamento*> > vector_Loco(6);
    vector_Loco[0] = medBatman.buscaCompuesto(medicamentos[0]);
    vector_Loco[1] = medBatman.buscaCompuesto(medicamentos[1]);
    vector_Loco[2] = medBatman.buscaCompuesto(medicamentos[2]);
    vector_Loco[3] = medBatman.buscaCompuesto(medicamentos[3]);
    vector_Loco[4] = medBatman.buscaCompuesto(medicamentos[4]);
    vector_Loco[5] = medBatman.buscaCompuesto(medicamentos[5]);

    std::cout<<"Comienzo de la prueba 1"<<std::endl;
    for (int k = 0; k < vector_Loco.size(); k++) {
        std::cout<<"Buscando "<<medicamentos[k]<<"..."<<std::endl;
        std::cout<<"Se han encontrado "<<vector_Loco[k].size()<<std::endl;
        for (int l = 0; l < vector_Loco[k].size(); l++){
            std::cout<<"Nombre del medicamento "<< l+1 <<" : "<< vector_Loco[k][l]->get_nombre()<<std::endl;
        }
    }

    //Prueba 2
    std::vector<Farmacia*> farmas_Sevilla = medBatman.buscar_Farmacia_Provincia("SEVILLA");
    std::cout<<"Farmacias encontradas situadas Sevilla: "<< farmas_Sevilla.size()<<std::endl;// esto lo tengo como comprobacion de cuantas de sevilla hay
    /*
    int id_Magnes = 3640, id_Carbonato = 3632, id_Cloruro = 3633;
    PaMedicamento *oxido = medBatman.buscaCompuestoMed(id_Magnes);
    PaMedicamento *carbonato = medBatman.buscaCompuestoMed(id_Carbonato);
    PaMedicamento *cloruro = medBatman.buscaCompuestoMed(id_Cloruro);
    */
    PaMedicamento* nuevomag= medBatman.buscaCompuestoMed(3640);
    //Aqui empezamos a buscar los medicamentos
    //cambiar pq busca ahora es private
    std::cout<<"Stock inicial de las farmacias"<<std::endl;
    std::cout<<"=============================================="<<std::endl;
    for (int i = 0; i < farmas_Sevilla.size(); i++) {
        std::vector<PaMedicamento*> Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        std::cout<<"La farmacia "<<farmas_Sevilla[i]->get_nombre()<<" tiene "<<Magnesio.size()<<" tipos de magnesio"<<std::endl;
    }
    for (int i = 0;i < farmas_Sevilla.size(); i++) {
        //Aqui sacamos los stock de cada PAmedicamento de cada farmacia
        std::vector<PaMedicamento*> Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        std::cout<<"Comprando en la farmacia "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        for (int k = 0; k < Magnesio.size(); k++) {
            int stock1=farmas_Sevilla[i]->buscaMedicamID(Magnesio[k]->get_id_num());
            std::cout<<Magnesio[k]->get_nombre()<<": "<<stock1<<std::endl;
        }
        /* int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
        int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
        int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);

        std::cout<<"==============================="<<std::endl;
        std::cout<<"Stock inicial de cada medicamento de la Farmacia "<<i+1<< ": "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        std::cout<<"Oxido: "<<stock_Magnesio<<", Carbonato: "<<stock_Carbonat<<", Cloruro: "<<stock_Clorur<<std::endl;
        std::cout<<"==============================="<<std::endl;
    */
        if(Magnesio.size()==0) {
            std::cout<<"En la farmacia "<<farmas_Sevilla[i]->get_nombre() <<" no queda nada de magnesio, por tanto pedimos OXIDO DE MAGNESIO"<<std::endl;
            farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
            Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        }
        for (int j = 0; j < 12; j++) {
            std::cout<<"Persona "<<j+1<<": "<<std::endl;
            //int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
            //int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
            //int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);
            //Hacemos las 12 compras, empezando por oxido
            if (Magnesio.size() > 0) {
                bool comprado=false;
                for (int k = 0; k < Magnesio.size(); k++) {
                    int stock = farmas_Sevilla[i]->buscaMedicamID(Magnesio[k]->get_id_num());
                    if(stock>0) {
                        farmas_Sevilla[i]->comprarMedicam(Magnesio[k]->get_id_num(),stock,Magnesio[k]);
                        std::cout<<"Ha comprado "<<Magnesio[k]->get_nombre()<<" correctamente "<<Magnesio[k]->get_nombre() <<std::endl;
                        comprado=true;
                    }/*else {
                        std::vector<PaMedicamento*> aux = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
                        if(aux.size()==0) {
                            std::cout<<"Como no queda ningun magnesio, pedimos OXIDO DE MAGNESIO"<<std::endl;
                            farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
                        }*/
                }
                if(comprado==false){
                    std::cout<<"No hay stock, por tanto pedimos OXIDO DE MAGNESIO"<<std::endl;
                    farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
                }
                //std::cout<<"No hay oxido, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Magnes,10,oxido);//Compro 10 por si las moscas
                //if (stock_Carbonat > 0) {
                //compramos sin problemas
                //  farmas_Sevilla[i]->comprarMedicam(id_Carbonato,1,carbonato);
                //std::cout<<"Ha comprado carbonato"<<std::endl;
                //}else {
                //  std::cout<<"No hay carbonato, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Carbonato, 10,carbonato);
                //if (stock_Clorur > 0) {
                //  std::cout<<"Ha comprado cloruro"<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Cloruro,1,cloruro);

                //}else{
                //  std::cout<<"No hay cloruro, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Cloruro, 10,cloruro);
                //}
                //}
            }
        }
        std::cout<<"Nuevo estado: "<<std::endl;
        std::vector<PaMedicamento*> Magnesioversion2 = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        std::cout<<"Tipos de de Magnesio en la farmacia " << i+1 <<": "<<Magnesioversion2.size()<<std::endl;//No se si se refiere a esto con lo del estado pero bueno
        for (int k = 0; k < Magnesioversion2.size(); k++) {
            int stock1=farmas_Sevilla[i]->buscaMedicamID(Magnesioversion2[k]->get_id_num());
            std::cout<<Magnesioversion2[k]->get_nombre()<<": "<<stock1<<std::endl;
        }
    }
    //Prueba 3
    //Primero buscamos la unica farmacia que hay en jaen
    std::vector<Farmacia*> farmas_Jaen = medBatman.buscar_Farmacia_Provincia("JAEN");
    //Despues lo que hacemos es, buscar TODOS los antigenos que existan, para luego comprobar si la farmacia los tiene
    std::vector<PaMedicamento*> antigenos= medBatman.buscaCompuesto("ANTIGENO OLIGOSACARIDO");
    std::cout<<"Stock inicial de la farmacia "<<farmas_Jaen[0]->get_nombre()<<" de cualquier tipo de ANTIGENO OLIGOSACARIDO : "<<std::endl; //Hago esto porque sé que solo hay una farmacia
    //Aqui comprobamos si los tiene, y en cualquier caso, pedimos 10 unidades
    for (int i = 0 ; i < antigenos.size(); i++) {
        std::cout<< "Stock inicial de "<<antigenos[i]->get_nombre()<< " " <<farmas_Jaen[0]->buscaMedicamID(antigenos[i]->get_id_num())<<std::endl;
        std::cout<< "Pidiendo 10 unidades"<<std::endl;
        farmas_Jaen[0]->nuevoStock(antigenos[i],10);
    }
    std::cout<<"Stock final de la farmacia "<<farmas_Jaen[0]->get_nombre()<<" de cualquier tipo de ANTIGENO OLIGOSACARIDO : "<<std::endl; //Hago esto porque sé que solo hay una farmacia
    for (int i = 0 ; i < antigenos.size(); i++) {
        std::cout<< "Stock final de "<<antigenos[i]->get_nombre()<< " " <<farmas_Jaen[0]->buscaMedicamID(antigenos[i]->get_id_num())<<std::endl;
    }

    //Prueba 4
    std::vector<PaMedicamento*> cianuro_borrar = medBatman.buscaCompuesto("CIANURO");
    if (cianuro_borrar.size() == 0) {
        std::cout<<"No existe stock de CIANURO"<<std::endl;
    }else {
        //Bucle para borrar todos los meds que contienen cianuro
        for (int i = 0 ; i < cianuro_borrar.size(); i++) {
            if (medBatman.eliminarMedicamento(cianuro_borrar[i]->get_id_num()) == true) {
                std::cout<<"Se ha eliminado con exito el medicamento "<<cianuro_borrar[i]->get_nombre()<<std::endl;
            }else {
                std::cout<<"No se ha eliminado con exito el medicamento "<<cianuro_borrar[i]->get_nombre()<<std::endl;
            }
        }
    }
    std::vector<PaMedicamento*> bismuto_borrar = medBatman.buscaCompuesto("BISMUTO");
    //Bucle para borrar todos los meds que contienen bismuti
    if (bismuto_borrar.size() == 0) {
        std::cout<<"No existe stock de BISMUTO"<<std::endl;
    }else {
        //Bucle para borrar todos los meds que contienen cianuro
        for (int i = 0 ; i < bismuto_borrar.size(); i++) {
            if (medBatman.eliminarMedicamento(bismuto_borrar[i]->get_id_num()) == true) {
                std::cout<<"Se ha eliminado con exito el medicamento "<<bismuto_borrar[i]->get_nombre()<<std::endl;
            }else {
                std::cout<<"No se ha eliminado con exito el medicamento "<<bismuto_borrar[i]->get_nombre()<<std::endl;
            }
        }
    }

    //Parejas

    return 0;
}