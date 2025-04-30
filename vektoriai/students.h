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
        : vardas(vardas), pavarde(pavarde), hw(hw), egzaminas(egzaminas) {
        
            //pazymys_mediana();
           // pazymys_vidurkis();
        }

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
    double setPazVid(const double& vid) { paz_vid = vid; }
    double setPazM(const double& med) { paz_m = med; }
    int setEgzaminas(const int& egz) { egzaminas = egz; }
    vector<double> setHw(const vector<double>& nd) { hw = nd; }

   

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