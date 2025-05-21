#include "my.h"
#include "code.h"
#include "students.h"
#include "Zmogus.h"
#include <memory>
#include "vector.h"

Zmogus::~Zmogus() {} // definition of pure virtual destructor

string Studentas::getVardas() const {
    return vardas;
}

string Studentas::getPavarde() const {
    return pavarde;
}

void Studentas::test ()
{
    auto zm = make_unique<Studentas>("Vardas", "Pavarde", ManoVektorius<int>{2, 3, 6, 7}, 8);
    Studentas* S = dynamic_cast<Studentas*>(zm.get()); //kad pasiektu tik Studento klases metodus
    assert(S != nullptr); // patikrinimas

    S->pazymys_vidurkis();  // apskaičiuoja vidurkį
    S->pazymys_mediana();   // apskaičiuoja medianą

    assert(zm->getVardas() == "Vardas");                  // tikrina varda
    assert(zm->getPavarde() == "Pavarde");                // tikrina pavarde
    assert(S->getHw().size() == 4);
    assert(S->getEgzaminas() == 8);                      // tikrina egzamino rezultatą

    double expectedVid = 6.6;
    double expectedMed = 6.6;
    double tolerance = 0.001;

    assert(abs(S->getPazVid() - expectedVid) < tolerance); // tikrina vidurkį
    assert(abs(S->getPazM() - expectedMed) < tolerance);   // tikrina medianą

    Studentas copy(*S);  //dereference S
    assert(copy.getVardas() == "Vardas");

    Studentas C;
    C = *S;
    assert(C.getEgzaminas() == 8);

    Studentas laik1("Jonas", "Jonaitis", {10, 9}, 10);
    Studentas moveConstructor(move(laik1));  // laik1's data moved
    assert(moveConstructor.getPavarde() == "Jonaitis");
    cout << "Kintamuju reiksmes likusios laikiname objekte po move constructor: Vardas: " << laik1.getVardas() << " Egzamino pazymys: " << laik1.getEgzaminas() << endl;
    
    Studentas laik2("A", "B", {1, 2, 3}, 5);
    Studentas moveAssigned;
    moveAssigned = move(laik2);  // laik2's data moved
    assert(moveAssigned.getEgzaminas() == 5);
    cout << "Kintamuju reiksmes likusios laikiname objekte po move operator: Vardas: " << laik2.getVardas() << " Egzamino pazymys: " << laik2.getEgzaminas() << endl;

    //delete zm; // atlaisviname atmintį
    cout << "Visi metodai ir Rule of Five konstruktoriai veikia teisingai\n";
  
}

ostream& operator<<(ostream& os, const Zmogus& zm) {
    const Studentas* S = dynamic_cast<const Studentas*>(&zm);
    
    os << left << setw(15) << S->getVardas();
    os << left << setw(15) << S->getPavarde();
    os << left << setw(18) << fixed << setprecision(2) << S->getPazVid();
    os << fixed << setprecision(2) << S->getPazM() << endl;
   
    return os;
}

istream& operator>>(istream& is, Studentas& B) {
    string v, pav;
    int nd;
    ManoVektorius<int> laik;
        
            is >> v >> pav;
           
            while (is >> nd)
            {
               if (nd < 1 || nd > 10) {
                    throw out_of_range("Ivestas pazymys nera tarp 1 ir 10! ");
                }
                laik.push_back(nd);
            }

            if (is.fail() && !is.eof()) {
                // means it failed due to bad input, not end-of-stream
                throw runtime_error("Neteisingas formatas. Iveskite tik skaicius.");
            }

            if (laik.empty()) {
                throw logic_error("Nera pazymiu!");
            }

            B.setVardas(v);
            B.setPavarde(pav);
            for (size_t i = 0; i < laik.size() - 1; ++i) {
                B.pazymioPridejimas(laik[i]);
            }
            B.setEgzaminas(laik.back());
    
    return is;
}


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
    ManoVektorius<int> temp = hw; 
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
    //cout<<"Mediana apskaiciuota\n";
}
//-------------------------------------------------------------------------------------------
void Studentas::pazymys_vidurkis()
{
    int egz = getEgzaminas();
    setPazVid((round ((0.4 * vidurkis() + 0.6 * egz) * 100.0)) / 100.0);
    //cout<<"Vidurkis apskaiciuotas\n";
}
//-------------------------------------------------------------------------------------------
void Studentas::iv1()
{
    int nd, egz;
    string v, pav, line;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    while(true){
        try{
        cout <<"----------------------------------------------------------------------------------------------------------\n";   
        cout << "Iveskite studento varda, pavarde, visus namu darbu ir egzamino pazymi (noredami baigti paspauskite ENTER) \n";
        cout << "Pvz.: Jonas Jonaitis 10 4 7 8 5 9 \n";
        cout << "> ";

    getline(cin, line);
    if (line.empty()) {
        throw logic_error("Tuscia ivestis.");
    }
    istringstream iss(line);
    Studentas laik;
    iss >> laik;

    *this = laik; // kopijuojame laik i this
    break; // jei viskas gerai, nutraukiame cikla
        }
        catch (const exception& e) { cerr << "Klaida: " << e.what() << " Iveskite studento duomenis is naujo.\n"; }
    }
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
void Studentas::iv3(ManoVektorius <string>& vardai, ManoVektorius <string>& pavardes, mt19937& gen)
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
double Studentas::iv4(ManoVektorius <unique_ptr<Zmogus>>& grupe, ofstream& laiko_failas)
{
    string choose, filename;
    int nd, egz, dydis;
    string v, pav, userInput;
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

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    while (true) {
        try {
            cout << "Iveskite irasu skaiciu faile: ";
            getline(cin, userInput);
            stringstream ss(userInput);


            if (!(ss >> dydis) || !(ss.eof())) {  // Tikrina, kad visa ivestis butu integer
                throw invalid_argument("Neteisinga ivestis! Iveskite skaiciu.");
            }
            if (dydis <= 0)
            {
                throw out_of_range("Neteisinga ivestis! Iveskite skaiciu didesni uz 0.");
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
    
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {

				filename += ".txt";  // automatiskia prideda .txt failo pavadinime
            }
    
        if (choose == "g" || choose == "G") {
            
            generavimas(filename, dydis);
            //generavimo_laikas(filename, laiko_failas);
        }

        ifstream fd(filename);
        if (!fd)
        {
            cout << "Nepavyko atidaryti failo!\n";
            throw runtime_error("Nepavyko atidaryti failo! Bandykite dar karta.");
        }
        string antrastes;
        getline(fd, antrastes); //header line
        getline(fd, antrastes); //dashed line
        
        while (dydis > 0 && getline(fd, antrastes))
        {
            Studentas B;
            istringstream iss(antrastes);
            //B.hw.clear();
            iss >> B;
           
            B.pazymys_vidurkis();
            B.pazymys_mediana();
            //Zmogus* zm = new Studentas(B);
            grupe.push_back(make_unique<Studentas>(B));
            dydis--;
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