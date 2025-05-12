#ifndef ZMOGUS_H
#define ZMOGUS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "my.h"
#include "code.h"


class Zmogus {
    protected:
    string vardas;
    string pavarde;

    public:
    virtual ~Zmogus() = 0; //pure virtual destructor

    //Getters
    virtual string getVardas() const { return vardas; }
    virtual string getPavarde() const {return pavarde;}
    virtual double getPazVid() const = 0;
    virtual double getPazM() const = 0;

    //Setters
    virtual void setVardas(const string& v) = 0;
    virtual void setPavarde(const string& p) = 0;


};

//Zmogus::~Zmogus() {} // definition of pure virtual destructor
ostream& operator<<(ostream& os, const Zmogus& zm);


#endif