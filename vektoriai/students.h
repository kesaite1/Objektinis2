#ifndef STUDENTS_H
#define STUDENTS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "my.h"
#include "code.h"
#include "Zmogus.h"
#include "vector.h"

    class Studentas: public Zmogus{
        ManoVektorius <int> hw;
        int egzaminas;
        double paz_m;
        double paz_vid;
    public:
        // Default constructor
        Studentas() 
        : Zmogus("",""), egzaminas(0), paz_m(0), paz_vid(0) {}
        
        Studentas(const string& vardas, const string& pavarde, const ManoVektorius<int>& hw, int egzaminas)
        : Zmogus(vardas, pavarde), hw(hw), egzaminas(egzaminas) {}

        ~Studentas() {
            hw.clear();
            egzaminas = 0;
            paz_vid = 0.0;
            paz_m = 0.0;
            vardas.clear();
            pavarde.clear();
        }
        // Copy constructor and assignment operator
        Studentas(const Studentas& other) 
        :   Zmogus(other), egzaminas(other.egzaminas), hw(other.hw),
         paz_m(other.paz_m), paz_vid(other.paz_vid) {}

        Studentas& operator=(const Studentas& other) {
            if (this != &other) {
                vardas = other.vardas;
                pavarde = other.pavarde;
                hw = other.hw;
                egzaminas = other.egzaminas;
                paz_m = other.paz_m;
                paz_vid = other.paz_vid;
            }
            return *this;
        }
        // Move constructor and assignment operator
        Studentas(Studentas&& other) noexcept:    
        Zmogus(move(other)),    
        hw(move(other.hw)), egzaminas((other.egzaminas)),
        paz_m((other.paz_m)), paz_vid((other.paz_vid)) {
            other.egzaminas = 0;
            other.paz_m = 0.0;
            other.paz_vid = 0.0;
        }

        Studentas& operator=(Studentas&& other) noexcept {
            if (this != &other) {
                Zmogus::operator = (move(other));
                
                hw = move(other.hw);
                egzaminas = other.egzaminas;
                paz_m = other.paz_m;
                paz_vid = other.paz_vid;

                other.egzaminas = 0;
                other.paz_m = 0.0;
                other.paz_vid = 0.0;
            }
            return *this;
        }

    //Input and output operations
    friend ostream& operator<<(ostream& os, const Zmogus& zm);
    friend istream& operator>>(istream& is, Studentas& s);

    // Getters
    string getVardas() const override;
    string getPavarde() const override;
    double getPazVid() const override { return paz_vid; }
    double getPazM() const override { return paz_m; }
    int getEgzaminas() const { return egzaminas; }
    ManoVektorius<int> getHw() const { return hw; }

    //Setters 
    void setVardas(const string& v) override { vardas = v; };
    void setPavarde(const string& p) override { pavarde = p; };
    void setPazVid(const double& vid) { paz_vid = vid; }
    void setPazM(const double& med) { paz_m = med; }
    void setEgzaminas(const int& egz) { egzaminas = egz; }
    void setHw(const ManoVektorius<int>& nd) { hw = nd; }

    void pazymioPridejimas(int nd) { 
            hw.push_back(nd); 
    }

    void istrintiPaskutiniHw() {
            if (!hw.empty()) hw.pop_back();
        }

    // Methods
    void test ();
    double vidurkis() const;
    double mediana() const;
    void pazymys_mediana();
    void pazymys_vidurkis();
    void iv1();
    void iv2(mt19937& gen);
    void iv3(ManoVektorius <string>& vardai, ManoVektorius <string>& pavardes, mt19937& gen);
    double iv4(ManoVektorius <unique_ptr<Zmogus>>& grupe, ofstream& laiko_failas);

    };

#endif