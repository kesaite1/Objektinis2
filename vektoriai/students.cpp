#include "my.h"
#include "code.h"
#include "students.h"


double Studentas::vidurkis() const
{
    double suma = 0;
   
    for (double pazymys : hw)
    {
        suma += pazymys;
    }
    return !hw.empty() ? suma / hw.size() : 0;
}
//-------------------------------------------------------------------------------------------
double Studentas::mediana() const
{
    int sk;
    sk = hw.size();
    vector<double> temp = hw; 
    sort(temp.begin(), temp.end());
    if (sk == 0) return 0;
    if (sk % 2 == 0)  return (hw[sk / 2] + hw[(sk / 2) - 1]) / 2.0;
    else return hw[sk / 2];
}
//-------------------------------------------------------------------------------------------
void Studentas::pazymys_mediana()
{
    int egz = getEgzaminas();
    setPazM((round ((0.4 * mediana() + 0.6 * egz) * 100.0)) / 100.0);
}
//-------------------------------------------------------------------------------------------
void Studentas::pazymys_vidurkis()
{
    int egz = getEgzaminas();
    setPazVid((round ((0.4 * vidurkis() + 0.6 * egz) * 100.0)) / 100.0);
}
//-------------------------------------------------------------------------------------------
void Studentas::iv1()
{
    int nd, egz;
    string t = "taip", v, pav;
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> v >> pav;
    cout << "Iveskite studento egzamino pazymi: ";
    cin >> egz;

    while (t != "ne")
    {
        cout << "Iveskite studento namu darbu pazymi: ";
        cin >> nd;
        pazymioPridejimas(nd);
        cout << " Ar norite testi? (taip/ne): ";
        cin >> t;
    }

    setVardas(v);
    setPavarde(pav);
    setEgzaminas(egz);

}
//------------------------------------------------------------------------------------------
void Studentas::iv2(mt19937& gen)
{
    int nd, egz;
    string v, pav;
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> v >> pav;
    uniform_int_distribution<int> exam(1, 10);
    uniform_int_distribution<int> kiek(1, 50);
    uniform_int_distribution<int> hw(1, 10);
     egz = exam(gen);

    for (int i = 0; i < kiek(gen); i++)
    {
        pazymioPridejimas(hw(gen));
    }
    setVardas(v);
    setPavarde(pav);
    setEgzaminas(egz);

}
//------------------------------------------------------------------------------------------
void Studentas::iv3(vector <string>& vardai, vector <string>& pavardes, mt19937& gen)
{
    int nd, egz;
    string v, pav;
    uniform_int_distribution<int> kiek_v(0, vardai.size() - 1);
    uniform_int_distribution<int> kiek_pav(0, pavardes.size() - 1);
    uniform_int_distribution<int> exam(1, 10);
    uniform_int_distribution<int> kiek(1, 50);
    uniform_int_distribution<int> hw(1, 10);
	
    v = vardai[kiek_v(gen)];
	pav = pavardes[kiek_pav(gen)];
    egz = exam(gen);

    for (int i = 0; i < kiek(gen); i++)
    {
        pazymioPridejimas(hw(gen));
    }

    setVardas(v);
    setPavarde(pav);
    setEgzaminas(egz);

}
//-------------------------------------------------------------------------------------------
double Studentas::iv4(vector<Studentas>& grupe, ofstream& laiko_failas)
{
    string choose, filename;
    int nd, egz;
    string v, pav;
    double skaitymo_laikas;
    while (true) {
    try {
        cout << "Pasirinkite: generuoti nauja faila - g, ar skaityti is egzistuojancio - e: ";
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw invalid_argument(" Neteisinga ivestis! Iveskite raide g arbe e.");
        }

        if (choose != "g" && choose != "e" && choose != "G" && choose != "E") {

            throw out_of_range(" Neteisinga ivestis! Iveskite raide g arbe e.");
        }
        break;
    }
    catch (const invalid_argument& e) { cerr << "Klaida: " << e.what() << endl; }
    catch (const out_of_range& e) { cerr << "Klaida: " << e.what() << endl; }
	}
    auto skaitymo_start = high_resolution_clock::now();
    while (true) {
        try {
    cout << "Iveskite failo pavadinima tokiu formatu: pavadinimas.txt: ";
    cin >> filename;
    
        if (choose == "g" || choose == "G") {
            if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {

				filename += ".txt";  // automatiskia prideda .txt failo pavadinime
            }
            generavimas(filename);
            //generavimo_laikas(filename, laiko_failas);
        }

        ifstream fd(filename);
        if (!fd)
        {
            cout << "Nepavyko atidaryti failo!\n";
            throw runtime_error("Nepavyko atidaryti failo! Bandykite dar karta.");
        }
        string antrastes;
        getline(fd, antrastes);
        grupe.clear();
        while (getline (fd,antrastes))
        {
            Studentas B;
            istringstream iss(antrastes);
            //B.hw.clear();
            iss >> v >> pav;
            B.setVardas(v);
            B.setPavarde(pav);
            while (iss >> nd)
            {
                B.pazymioPridejimas(nd);
            }
           if (!B.getHw().empty()) {
            B.setEgzaminas(B.getHw().back());
            B.istrintiPaskutiniHw();
        }
            B.pazymys_vidurkis();
            B.pazymys_mediana();
            grupe.push_back(B);
        }
        auto skaitymo_end = high_resolution_clock::now();
        skaitymo_laikas = apdorojimo_laikas(skaitymo_start, skaitymo_end);
        laiko_failas << "Duomenu skaitymo is failo laikas: " << skaitymo_laikas << endl;
        fd.close();
        break;
        }
        catch (const exception& e) {
            cerr << "Klaida: " << e.what() << endl;
        }
    }
       /* if (choose == "g") {

            flaikas = skaitymo_laikas + glaikas;
        }
        else flaikas = skaitymo_laikas;*/

        return skaitymo_laikas;
}