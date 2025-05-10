#include "my.h"
#include "code.h"
#include "students.h"
#include "Zmogus.h"

int main()
{
    //ofstream report("sistemos_testavimo_duomenys.txt");
    ofstream laiko_failas("../laikas.txt", ios::app);
    double skirstymo_laikas, rusiavimo_laikas, skaitymo_laikas;
    vector <Studentas> pazangus;
    vector <Studentas> nepazangus;
    vector <Studentas> grupe;
    int iv = 0, sorting = 0, strateg = 0 ;
    string isvestis;
    Studentas  A;
    vector <string> vardai = { "Emile", "Greta", "Haroldas", "Guste", "Paulius", "Aleksas", "Kristina", "Aidas", "Vasare", "Diana" };
    vector <string> pavardes = { "Jonaitis", "Pavardaite", "Pavardenis", "Adomaitis", "Lapaite", "Apuokas", "Karalaite", "Nausediene" };

    random_device rd;  
    mt19937 gen(rd());
    //auto programa_start = high_resolution_clock::now();
    laiko_failas << "------------------------------------------------------------------------------------------\n";
	laiko_failas << "Programos su vector konteineriais laikai:\n";
	laiko_failas << " " << endl;
	cout << "VECTOR KONTEINERIU PROGRAMA\n";

    //TEST 

    A.test(grupe); 

    //TEST
    while (iv != 5)
    {
        try {
			cout << "-----------------------------------------------------------------\n";
            cout << "Pasirink, kokiu budu bus ivedami studento duomenys\n";
            cout << "1 - ranka, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes,\n";
            cout << "4 - skaityti duomenis is failo, 5 - baigti darba\n";
            cin >> iv;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw  invalid_argument("Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 5.");
            }
            if (iv < 1 || iv > 5)
            {
                throw out_of_range("Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 5.");
            }
            if (iv == 1)
            {
                A.iv1();
                A.pazymys_vidurkis();
                A.pazymys_mediana();

                grupe.push_back(A);
            }
            else if (iv == 2)
            {
                A.iv2(gen);
                A.pazymys_vidurkis();
                A.pazymys_mediana();

                grupe.push_back(A);
            }
            else if (iv == 3)
            {
                A.iv3(vardai, pavardes, gen);
                A.pazymys_vidurkis();
                A.pazymys_mediana();

                grupe.push_back(A);
            }
            else if (iv == 4)
            {
                skaitymo_laikas = A.iv4(grupe, laiko_failas);
            }

            else {
                while (true) {
                    try {
                        cout << "Pasirinkite, kaip norite rikiuoti duomenis:\n";
                        //cout << "1 - vardai abeceles tvarka,\n";
                        //cout << "2 - pavardes abeceles tvarka,\n";
                        //cout << "3 - galutini vidurkio pazymiai didejimo tvarka,\n";
                        cout << "1 - galutiniai vidurkio pazymiai mazejimo tvarka,\n";
                       // cout << "5 - galutiniai medianos pazymiai didejimo tvarka,\n";
                        cout << "2 - galutiniai medianos pazymiai mazejimo tvarka\n";
                        cin >> sorting;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 2.");
                        }
						auto rusiavimo_start = high_resolution_clock::now();
                        if (sorting < 1 || sorting > 2) {

                            throw out_of_range(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 2.");
                        }
                    
                        if (sorting == 1)
                        {
                            sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) { return A.getPazVid() > B.getPazVid(); });
                        }
                        else if (sorting == 2)
                        {
                            sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) { return A.getPazM() > B.getPazM(); });
                        }
                    auto rusiavimo_end = high_resolution_clock::now();
				    rusiavimo_laikas = apdorojimo_laikas(rusiavimo_start, rusiavimo_end);
                    laiko_failas << "Studentu rikiavimo pasirinkta tvarka laikas: " << rusiavimo_laikas << endl;
                    break;
                    }
                    catch (const invalid_argument& e) { cerr << "Klaida:" << e.what() << endl; }
                    catch (const out_of_range& e) { cerr << "Klaida:" << e.what() << endl; }
                }
                while (true) {
                    try {
                        cout << "Pasirinkite studentu skirstymo strategija 1-3: ";
                        cin >> strateg;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 3.");
                        }
                        if (strateg < 1 || strateg > 3) {

                            throw out_of_range(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 3.");
                        }
                        auto skirstymas_start = high_resolution_clock::now();

                        if (strateg == 1) {
                            for (const auto& A : grupe) {
                                if (A.getPazVid() >= 5 || A.getPazM() >= 5) {
                                    pazangus.push_back(A);
                                }
                                else {
                                    nepazangus.push_back(A);
                                }
                            }
                        }
                        else if (strateg == 2)
                        { 
                            for (int i = grupe.size() - 1; i >= 0; --i) {
                                if (grupe[i].getPazVid() < 5.0 && grupe[i].getPazM() < 5.0) {
                                    nepazangus.push_back(grupe[i]);
                                    grupe.erase(grupe.begin() + i); 
                                }
                            }
                            pazangus = grupe;
                        }
                        else if (strateg == 3)
                        {
                            copy_if(grupe.begin(), grupe.end(), back_inserter(nepazangus), [](const Studentas& A) { return A.getPazVid() < 5 && A.getPazM() < 5; }); 

                            grupe.erase(remove_if(grupe.begin(), grupe.end(), [](const Studentas& A) { return A.getPazVid() < 5 && A.getPazM() < 5; }), grupe.end());

                            pazangus = grupe;  // Remaining students are "pazangus"
                        }

                            auto skirstymas_end = high_resolution_clock::now();
                            skirstymo_laikas = apdorojimo_laikas(skirstymas_start, skirstymas_end);
                            laiko_failas << "Studentu skirstymo i dvi grupes " << strateg << " strategija laikas: " << skirstymo_laikas << endl;
                            break;
                    }
                    catch (const invalid_argument& e) { cerr << "Klaida: " << e.what() << endl; }
					catch (const out_of_range& e) { cerr << "Klaida: " << e.what() << endl; }
                }
                while (true) {
                    try {
                        cout << "Pasirinkite, kur norite isvesti duomenis: i ekrana - e, i faila - f\n";
                        cin >> isvestis;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument(" Neteisinga ivestis! Iveskite raide e arba f.");
                        }
                        if (isvestis != "f" && isvestis != "e") {

                            throw out_of_range(" Neteisinga ivestis! Iveskite raide e arba f.");
                        }
                        if (isvestis == "f")
                        {
                            ofstream sp("pazangus.txt");
                            ofstream sn("nepazangus.txt");

                            sp << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(18) << "Galutinis (vid.)" << "Galutinis (med.)\n";
                            sp << "-----------------------------------------------------------------\n";
                            sn << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(18) << "Galutinis (vid.)" << "Galutinis (med.)\n";
                            sn << "-----------------------------------------------------------------\n";

                          //  auto isvedimas_start = high_resolution_clock::now();
                            for (const auto& A : pazangus) {
                                sp << A;
                            }

                            for (const auto& A : nepazangus) {
                                sn << A;
                            }
                            //auto isvedimas_end = high_resolution_clock::now();
                            //isvedimo_laikas = apdorojimo_laikas(isvedimas_start, isvedimas_end);
                            //laiko_failas<<"Surusiuotu studentu isvedimo i atskirus failus laikas: "<<isvedimo_laikas<<endl;
                       
                            sp.close();
                            sn.close();
                            break;
                        }
                        else
                        {
                            cout << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(18) << "Galutinis (vid.)" << "Galutinis (med.)\n";
                            cout << "-----------------------------------------------------------------\n";
                            cout << "Pazangus studentai: \n";
                            cout << "-----------------------------------------------------------------\n";
                            // auto isvedimas_start = high_resolution_clock::now();
                            for (const auto& A : pazangus) {

                                cout << A;
                            }
                            cout << "-----------------------------------------------------------------\n";
                            cout << "Nepazangus studentai: \n";
                            cout << "-----------------------------------------------------------------\n";
                            for (const auto& A : nepazangus) {

                                cout << A;
                            }
                            cout << "-----------------------------------------------------------------\n";
                            //auto isvedimas_end = high_resolution_clock::now();
                            //isvedimo_laikas = apdorojimo_laikas(isvedimas_start, isvedimas_end);
                            if (skaitymo_laikas != 0) {
                            cout << "Failo skaitymo laikas " << setprecision(5) << skaitymo_laikas << endl;
                        }
                            cout << "Studentu skirstymo i dvi grupes laikas: " << setprecision(5) << skirstymo_laikas << endl;
                           // cout << "Surusiuotu studentu isvedimo laikas: " << setprecision(5) << isvedimo_laikas << endl;
                            break;
                        }
                    }
                    catch (const invalid_argument& e) { cerr << "Klaida: " << e.what() << endl; }
                    catch (const out_of_range& e) { cerr << "Klaida: " << e.what() << endl; }
                }
            }
        }
        catch (const invalid_argument& e) { cerr << "Klaida: " << e.what() << endl; }
        catch (const out_of_range& e) { cerr << "Klaida: " << e.what() << endl; }
    }
	//auto programa_end = high_resolution_clock::now();
   // programos_laikas = apdorojimo_laikas(programa_start, programa_end);
	//laiko_failas << "Programos darbo laikas: " << programos_laikas << endl;
    laiko_failas << "\n";
    laiko_failas << "Testu laiku vidurkis: " << (skirstymo_laikas + rusiavimo_laikas + skaitymo_laikas) / 5.0 << endl;
    laiko_failas << "------------------------------------------------------------------------------------------\n";
     if (isvestis == "e")
     {
        // cout << "Programos darbo laikas: " << setprecision(5) << programos_laikas << endl;
         cout << "-----------------------------------------------------------------\n";
         cout << "Testu laiku vidurkis: " << setprecision(5) <<(skirstymo_laikas + rusiavimo_laikas + skaitymo_laikas) / 5.0 << endl;
     }
    /* CPU(report);
     RAM(report);
     Disk(report);
     report.close();*/
    laiko_failas.close();
    system("pause");
    return 0;
}


