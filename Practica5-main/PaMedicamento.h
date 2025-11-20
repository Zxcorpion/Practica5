
#ifndef PAMEDICAMENTO_H
#define PAMEDICAMENTO_H

#include <iostream>
#include "Laboratorio.h"

class PaMedicamento {
private:
    int id_num=0;
    std::string id_alpha="-", nombre="-";
    Laboratorio *serve = nullptr;
public:
    PaMedicamento(int id_num_=0,std::string id_alpha_="", std::string nombre_="");
    PaMedicamento(const PaMedicamento &orig);
    virtual ~PaMedicamento();

    int get_id_num() const;

    void set_id_num(int id_num);

    std::string get_id_alpha() const;

    void set_id_alpha(const std::string &id_alpha);

    std::string get_nombre() const;

    void set_nombre(const std::string &nombre);

    Laboratorio *getServe() const;

    void servidoPor(Laboratorio *serve_);

    PaMedicamento &operator=(const PaMedicamento &orig);
    bool operator<(const PaMedicamento &orig) const;
    bool operator==(const PaMedicamento &orig) const;
};




#endif //PAMEDICAMENTO_H
