#include "my.h"
#include "code.h"

bool abc_vardai(const studentai& A, const studentai& B) { return raide(A.v) < raide(B.v); }
bool abc_pavardes(const studentai& A, const studentai& B) { return raide(A.pav) < raide(B.pav); }
bool did_vid(const studentai& A, const studentai& B) { return A.paz_vid < B.paz_vid; }
bool maz_vid(const studentai& A, const studentai& B) { return A.paz_vid > B.paz_vid; }
bool did_med(const studentai& A, const studentai& B) { return A.paz_m < B.paz_m; }
bool maz_med(const studentai& A, const studentai& B) { return A.paz_m > B.paz_m; }


static double vidurkis(studentai& A)
{
    double suma = 0;
	
    for (list<double>::iterator it = A.hw.begin(); it != A.hw.end(); ++it)
    {
        suma += *it;
    }
    return (A.hw.size() > 0) ? suma / A.hw.size() : 0;
}
//-------------------------------------------------------------------------------------------
static double mediana(studentai& A)
{
    if (A.hw.size() == 0) return 0;

    list<double> sorted_hw = A.hw;  // Create a copy to avoid modifying the original
    sorted_hw.sort();

    auto slow = sorted_hw.begin();
    auto fast = sorted_hw.begin();

    // Move `fast` by two steps and `slow` by one step
    while (fast != sorted_hw.end() && next(fast) != sorted_hw.end()) {
        ++slow;
        advance(fast, 2);
    }
    // If the number of elements is odd, return the middle element
    if (sorted_hw.size() % 2 == 0 && next(slow) != sorted_hw.end()) {
       // auto next_slow = next(slow);
        return (*slow + *next(slow)) / 2.0;
    }
    // If the number of elements is even, return the average of the two middle elements
    else {
        return *slow;
    }
   
}
//-------------------------------------------------------------------------------------------
void pazymys_mediana(studentai& A)
{
    A.paz_m = (round ((0.4 * mediana(A) + 0.6 * A.egz) * 100.0)) / 100.0;
}
//-------------------------------------------------------------------------------------------
void pazymys_vidurkis(studentai& A)
{
    A.paz_vid = (round ((0.4 * vidurkis(A) + 0.6 * A.egz) * 100.0)) / 100.0;
}
//-------------------------------------------------------------------------------------------
void iv1(studentai& A)
{
    double nd;
    string t = "taip";
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> A.v >> A.pav;
    cout << "Iveskite studento egzamino pazymi: ";
    cin >> A.egz;

    while (t != "ne")
    {
        cout << "Iveskite studento namu darbu pazymi: ";
        cin >> nd;
        A.hw.push_back(nd);
        cout << " Ar norite testi? (taip/ne): ";
        cin >> t;
    }
}
//------------------------------------------------------------------------------------------
void iv2(studentai& A, mt19937& gen)
{
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> A.v >> A.pav;
    uniform_int_distribution<int> egz(1, 10);
    A.egz = egz(gen);
    uniform_int_distribution<int> kiek(1, 50);
    for (int i = 0; i < kiek(gen); i++)
    {
		uniform_real_distribution<double> nd(1.0, 10.0);
		A.hw.push_back(nd(gen));
    }
}
//------------------------------------------------------------------------------------------
void iv3(studentai& A, list <string>& vardai, list <string>& pavardes, mt19937& gen)
{
    uniform_int_distribution<int> kiek_v(0, vardai.size() - 1);
    uniform_int_distribution<int> kiek_pav(0, pavardes.size() - 1);
    uniform_int_distribution<int> egz(1, 10);
    uniform_int_distribution<int> kiek(1, 50);
    uniform_real_distribution<double> nd(1.0, 10.0);
    list<string>::iterator vard = next(vardai.begin(), kiek_v(gen));
    A.v = *vard;
    list<string>::iterator pavard = next(pavardes.begin(), kiek_v(gen));
    A.pav = *pavard;
    A.egz = egz(gen);
   
    for (int i = 0; i < kiek(gen); i++)
    {
        A.hw.push_back(nd(gen));
    }
}
//-------------------------------------------------------------------------------------------
double iv4(list<studentai>& grupe, ofstream& laiko_failas)
{
    string choose, filename;
    double nd, skaitymo_laikas;
    studentai B;
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
            while (fd >> B.v >> B.pav)
            {
                B.hw.clear();
                while (fd >> nd)
                {
                    B.hw.push_back(nd);
                    if (fd.peek() == '\n')
                        break;
                }
                B.egz = B.hw.back();
                B.hw.pop_back();

                pazymys_vidurkis(B);
                pazymys_mediana(B);
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
        /*if (choose == "g") {

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
    random_device rd;  
    mt19937 gen(rd());
    uniform_int_distribution<int> sk(1, 50);
    uniform_real_distribution<double> nd(1.0, 10.0);
    uniform_int_distribution<int> egz(1, 10);
    ofstream file(failas);
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
            if (dydis <= 0) {
                throw out_of_range(" Skaicius turi buti didesnis uz 0. ");
            }
            break;
        }
        catch (const invalid_argument& e) { cerr << "Klaida: " << e.what() << endl; }
        catch (const out_of_range& e) { cerr << "Klaida: " << e.what() << endl; }
    }
 
    for (int i = 0; i < dydis; i++)
    {
        file << left << setw(20) << ("Vardas" + to_string(i)) << left << setw(20) << ("Pavarde" + to_string(i));
        
        for (int j = 0; j < sk(gen); j++)
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
	duration<double> skirtumas;

void Disk(ofstream& report) {
    system("wmic logicaldisk get name, freespace, size > disk_usage.txt");
    std::ifstream diskFile("disk_usage.txt");
    std::string line;
    while (getline(diskFile, line)) {
        report << "- Disko bûsena: " << line << "\n";
    }
    diskFile.close();
}*/


//------------------------------------------------------------------------------------------------------------------------
double apdorojimo_laikas(high_resolution_clock::time_point start, high_resolution_clock::time_point end)
{
    duration<double> skirtumas = end - start;
    return skirtumas.count();
}
