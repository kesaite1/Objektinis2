#include "my.h"
#include "code.h"
#include "students.h"


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
    uniform_int_distribution<int> nd(1, 10);
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

//------------------------------------------------------------------------------------------------------------------------
double apdorojimo_laikas(high_resolution_clock::time_point start, high_resolution_clock::time_point end)
{
    duration<double> skirtumas = end - start;
    return skirtumas.count();
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

