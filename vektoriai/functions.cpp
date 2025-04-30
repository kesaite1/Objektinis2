#include "my.h"
#include "code.h"
#include "students.h"

double Studentas:: vidurkis()
{
    double suma = 0, sk;
    sk = A.getHW.size();
    for (int i = 0; i < sk; i++)
    {
        suma += A.getHW[i];
    }
    return (sk > 0) ? suma / sk : 0;
}
//-------------------------------------------------------------------------------------------
static double mediana()
{
    int sk;
    sk = A.hw.size();
    sort(A.hw.begin(), A.hw.end());
    if (sk == 0) return 0;
    if (sk % 2 == 0)  return (A.hw[sk / 2] + A.hw[(sk / 2) - 1]) / 2.0;
    else return A.hw[sk / 2];
}
//-------------------------------------------------------------------------------------------
void pazymys_mediana()
{
    A.paz_m = (round ((0.4 * mediana(A) + 0.6 * A.egz) * 100.0)) / 100.0;
}
//-------------------------------------------------------------------------------------------
void pazymys_vidurkis()
{
    A.paz_vid = (round ((0.4 * vidurkis(A) + 0.6 * A.egz) * 100.0)) / 100.0;
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
    uniform_real_distribution<int> hw(1, 10);
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
    uniform_real_distribution<int> hw(1, 10);
	
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
//------------------------------------------------------------------------------------------------------------------
string raide(string vardai)
{
    transform(vardai.begin(), vardai.end(), vardai.begin(), ::tolower);
    return vardai;
}
//------------------------------------------------------------------------------------------------------------------------
void generavimas(string failas)
{
    random_device rd1;
    mt19937 gen(rd1());
    ofstream file(failas);
    uniform_int_distribution<int> kiek(1, 50);
    uniform_real_distribution<int> nd(1, 10);
    uniform_int_distribution<int> egz(1, 10);
    int dydis;
    string userInput;
    cin.ignore(1000, '\n');
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

    file << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(5) << "Pazymiai + egzamino balas\n";
    file << "-----------------------------------------------------------------------------\n";
    for (int i = 0; i < dydis; i++)
    {
        file << left << setw(20) << ("Vardas" + to_string(i)) << left << setw(20) << ("Pavarde" + to_string(i));

        for (int j = 0; j < kiek(gen); j++)
        {
            file << fixed << setprecision(2) << left << setw(5) << nd(gen);
        }
        file << egz(gen) << endl;
    }
    file.close();
}
/*void RAM(ofstream& report) {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    report << "- RAM naudojimas: " << statex.dwMemoryLoad << "%\n";
}

void CPU(ofstream& report) {
    system("wmic cpu get loadpercentage > cpu_usage.txt");
    ifstream cpuFile("cpu_usage.txt");
    string line;
    while (getline(cpuFile, line)) {
        if (isdigit(line[0])) {
            report << "- CPU naudojimas: " << line << "%\n";
        }
            break;
    }
    cpuFile.close();
}
	//duration<double> skirtumas;

       // auto start = high_resolution_clock::now();
        generavimas(filename, dydis);
        //auto end = high_resolution_clock::now();
        //skirtumas = end - start;
    //laiko_failas << "Failo generavimo laikas: " << skirtumas.count() << endl;

void Disk(ofstream& report) {
    system("wmic logicaldisk get name, freespace, size > disk_usage.txt");
    std::ifstream diskFile("disk_usage.txt");
    std::string line;
    while (getline(diskFile, line)) {
        report << "- Disko b�sena: " << line << "\n";
    }
    diskFile.close();
}*/


//------------------------------------------------------------------------------------------------------------------------
double apdorojimo_laikas(high_resolution_clock::time_point start, high_resolution_clock::time_point end)
{
    duration<double> skirtumas = end - start;
    return skirtumas.count();
}