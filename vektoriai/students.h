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

    class Studentas: public Zmogus{
        vector <double> hw;
        int egzaminas;
        double paz_m;
        double paz_vid;
    public:
        // Default constructor
        Studentas() 
        : egzaminas(0), paz_m(0), paz_vid(0) { vardas = ""; pavarde = "";}
        
        Studentas(const string& vardas, const string& pavarde, const vector<double>& hw, int egzaminas)
        : hw(hw), egzaminas(egzaminas) { this->vardas = vardas; this->pavarde = pavarde;}

        ~Studentas() {}

        Studentas(const Studentas& other) 
        : egzaminas(other.egzaminas), hw(other.hw),
         paz_m(other.paz_m), paz_vid(other.paz_vid){ vardas = other.vardas; pavarde = other.pavarde;}

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

        Studentas(Studentas&& other) noexcept
        : hw(move(other.hw)), egzaminas(other.egzaminas),
        paz_m(other.paz_m), paz_vid(other.paz_vid) { vardas = move(other.vardas); pavarde = move(other.pavarde);}

        Studentas& operator=(Studentas&& other) noexcept {
            if (this != &other) {
                vardas = move(other.vardas);
                pavarde = move(other.pavarde);
                hw = move(other.hw);
                egzaminas = other.egzaminas;
                paz_m = other.paz_m;
                paz_vid = other.paz_vid;
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
    vector<double> getHw() const { return hw; }

    //Setters 
    void setVardas(const string& v) override { vardas = v; };
    void setPavarde(const string& p) override { pavarde = p; };
    void setPazVid(const double& vid) { paz_vid = vid; }
    void setPazM(const double& med) { paz_m = med; }
    void setEgzaminas(const int& egz) { egzaminas = egz; }
    void setHw(const vector<double>& nd) { hw = nd; }

    void pazymioPridejimas(int nd) { 
            hw.push_back(nd); 
    }

    void istrintiPaskutiniHw() {
            if (!hw.empty()) hw.pop_back();
        }

    // Methods
    void test (vector<Zmogus*>& grupe);
    double vidurkis() const;
    double mediana() const;
    void pazymys_mediana();
    void pazymys_vidurkis();
    void iv1();
    void iv2(mt19937& gen);
    void iv3(vector <string>& vardai, vector <string>& pavardes, mt19937& gen);
    double iv4(vector<Zmogus*>& grupe, ofstream& laiko_failas);

    };

#endif