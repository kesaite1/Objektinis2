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

class Studentas {
    private:
        string vardas;
        string pavarde;
        vector <double> hw;
        int egzaminas;
        double paz_m;
        double paz_vid;
    public:
        // Default constructor
        Studentas() 
        : vardas(""), pavarde(""), egzaminas(0), paz_m(0), paz_vid(0) {}
        
        Studentas(const string& vardas, const string& pavarde, const vector<double>& hw, int egzaminas)
        : vardas(vardas), pavarde(pavarde), hw(hw), egzaminas(egzaminas) {}

        ~Studentas() {}

        Studentas(const Studentas& other) 
        : vardas(other.vardas), pavarde(other.pavarde), 
        egzaminas(other.egzaminas), hw(other.hw),
         paz_m(other.paz_m), paz_vid(other.paz_vid){}

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
        : vardas(move(other.vardas)), pavarde(move(other.pavarde)),
         hw(move(other.hw)), egzaminas(other.egzaminas),
        paz_m(other.paz_m), paz_vid(other.paz_vid) {}

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
    friend ostream& operator<<(ostream& os, const Studentas& s);
    friend istream& operator>>(istream& is, Studentas& s);

    // Getters
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    double getPazVid() const { return paz_vid; }
    double getPazM() const { return paz_m; }
    int getEgzaminas() const { return egzaminas; }
    vector<double> getHw() const { return hw; }

    //Setters 
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }
    void setPazVid(const double& vid) { paz_vid = vid; }
    void setPazM(const double& med) { paz_m = med; }
    void setEgzaminas(const int& egz) { egzaminas = egz; }
    void setHw(const vector<double>& nd) { hw = nd; }


    void pazymioPridejimas(int nd) { 
        if (nd >= 0  && nd <= 10) {
            hw.push_back(nd); }
        else {
            cout << "Neteisingas pazymys! Iveskite skaiciu nuo 0 iki 10." << endl;
        }}

    void istrintiPaskutiniHw() {
            if (!hw.empty()) hw.pop_back();
        }

    // Methods
    double vidurkis() const;
    double mediana() const;
    void pazymys_mediana();
    void pazymys_vidurkis();
    void iv1();
    void iv2(mt19937& gen);
    void iv3(vector <string>& vardai, vector <string>& pavardes, mt19937& gen);
    double iv4(vector<Studentas>& grupe, ofstream& laiko_failas);

    };


#endif