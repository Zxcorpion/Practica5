

#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <iostream>

class Laboratorio {
private:
    int id = 0;
    std::string nombreLab = "-", direccion = "-", codiPostal = "-", localidad = "-";
public:
    Laboratorio(int id_ = 0, std::string nombreLab_ = "-",std::string direccion_ = "-",std::string codiPostal_ = "-",std::string localidad_ = "-");
    Laboratorio(const Laboratorio &orig);
    ~Laboratorio();

    Laboratorio &operator=(const Laboratorio &orig);

    int getId() const;

    void setId(int id);

    const std::string &getNomrbeLab() const;
    void setNomrbeLab(const std::string &nomrbeLab);
    const std::string &getDireccion() const;
    void setDireccion(const std::string &direccion);
    const std::string &getCodiPostal() const;
    void setCodiPostal(const std::string &codiPostal);
    const std::string &getLocalidad() const;
    void setLocalidad(const std::string &localidad);
};



#endif //LABORATORIO_H
