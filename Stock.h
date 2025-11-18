
#ifndef STOCK_H
#define STOCK_H

#include "PaMedicamento.h"

class Stock {
private:
    int id_Pa_Med=0;
    int num_stock=0;
    PaMedicamento* number= 0;
public:
    Stock(int id=0, int num=0, PaMedicamento* number_=0);
    Stock(const Stock& orig);
    virtual ~Stock();

    int get_id_pa_med() const;
    void set_id_pa_med(int id_pa_med);
    int get_num_stock() const;
    void set_num_stock(int num_stock);
    PaMedicamento * get_number() const;
    void set_number(PaMedicamento *number);

    void incrementa(const int &cantidad);
    void decrementa(const int &cantidad);
    bool operator< (const Stock& parametro) const;
    bool operator==(const Stock& parametro) const;

};



#endif //STOCK_H
