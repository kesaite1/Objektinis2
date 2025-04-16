#include "my.h"
#include "code.h"

int main()
{
    //fstream report("sistemos_testavimo_duomenys.txt");
    ofstream laiko_failas("../laikas.txt", ios::app);
    double skirstymo_laikas, rusiavimo_laikas, skaitymo_laikas;
    const double epsilon = 1e-6;
    list <studentai> pazangus;
    list <studentai> nepazangus;
    list <studentai> grupe;
    int iv = 0, sorting = 0, strateg = 0;
    string isvestis;
    studentai  A;
    list <string> vardai = { "Emile", "Greta", "Haroldas", "Guste", "Paulius", "Aleksas", "Kristina", "Aidas", "Vasare", "Diana" };
    list <string> pavardes = { "Jonaitis", "Pavardaite", "Pavardenis", "Adomaitis", "Lapaite", "Apuokas", "Karalaite", "Nausediene" };

    random_device rd; 
    mt19937 gen(rd());
    //auto programa_start = high_resolution_clock::now();
    laiko_failas << "------------------------------------------------------------------------------------------\n";
    laiko_failas << "Programos su list konteineriais laikai:\n";
	laiko_failas << "\n";
	cout << "LIST KONTEINERIU PROGRAMA\n";
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
                iv1(A);
                pazymys_vidurkis(A);
                pazymys_mediana(A);

                grupe.push_back(A);
            }
            else if (iv == 2)
            {
                iv2(A, gen);
                pazymys_vidurkis(A);
                pazymys_mediana(A);

                grupe.push_back(A);
            }
            else if (iv == 3)
            {
                iv3(A, vardai, pavardes, gen);
                pazymys_vidurkis(A);
                pazymys_mediana(A);

                grupe.push_back(A);
            }
            else if (iv == 4)
            {
                skaitymo_laikas = iv4(grupe, laiko_failas);
            }

            else {
                while (true) {
                    try {
                        cout << "Pasirinkite, kaip norite rikiuoti duomenis:\n";
                       // cout << "1 - vardai abeceles tvarka,\n";
                       // cout << "2 - pavardes abeceles tvarka,\n";
                       // cout << "3 - galutini vidurkio pazymiai didejimo tvarka,\n";
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
                       /* if (sorting == 1)
                        {
                            grupe.sort(abc_vardai);
                        }
                        else if (sorting == 2)
                        {
                            grupe.sort(abc_pavardes);
                        }
                        else if (sorting == 3)
                        {
                            grupe.sort(did_vid);
                        }*/
                        else if (sorting == 1)
                        {
                            grupe.sort(maz_vid);
                        }
                        /*else if (sorting == 5)
                        {
                            grupe.sort(did_med);
                        }*/
                        else if (sorting == 2)
                        {
                            grupe.sort(maz_med);
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
                        cout << "Pasirinkite studentu skirstymo strategija 1-2: ";
                        cin >> strateg;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 2.");
                        }
                        if (strateg < 1 || strateg > 2) {

                            throw out_of_range(" Neteisinga ivestis! Iveskite skaiciu nuo 1 iki 2.");
                        }
                        auto skirstymas_start = high_resolution_clock::now();
                        if (strateg == 1) {
                            for (list<studentai>::iterator it = grupe.begin(); it != grupe.end();) {

                                if (it -> paz_vid >= 5 || it -> paz_m >= 5) {
                                    pazangus.push_back(*it);
                                }
                                else {
                                    nepazangus.push_back(*it);
                                }
                                it = grupe.erase(it);
                            }
                        }
                        else if (strateg == 2)
                        {
                            for (list<studentai>::iterator it = grupe.begin(); it != grupe.end();) {
                                if (it->paz_vid < 5.0 && it->paz_m < 5.0) {
                                    nepazangus.push_back(*it);
                                    it = grupe.erase(it);
                                }
                                else {
                                    ++it;
                                }
                            }
                            pazangus = grupe;
                        }
                        auto skirstymas_end = high_resolution_clock::now();
                        skirstymo_laikas = apdorojimo_laikas(skirstymas_start, skirstymas_end);
                        laiko_failas << "Studentu skirstymo i dvi grupes laikas strategija " << strateg << " : " << skirstymo_laikas << endl;
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
                            sp << "-----------------------------------------------------------------" << endl;
                            sn << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(18) << "Galutinis (vid.)" << "Galutinis (med.)\n";
                            sn << "-----------------------------------------------------------------\n";

                            //auto isvedimas_start = high_resolution_clock::now();
                            for (list<studentai>::iterator it = pazangus.begin(); it != pazangus.end(); it++) {
                                sp << left << setw(15) << it->v;
                                sp << left << setw(15) << it ->pav;
                                sp << left << setw(18) << fixed << setprecision(2) << it->paz_vid;
                                sp << fixed << setprecision(2) << it->paz_m << endl;
                            }

                            for (list<studentai>::iterator it = nepazangus.begin(); it != nepazangus.end(); it++) {
                                sn << left << setw(15) << it->v;
                                sn << left << setw(15) << it ->pav;
                                sn << left << setw(18) << fixed << setprecision(2) << it->paz_vid;
                                sn << fixed << setprecision(2) << it->paz_m << endl;
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
                          //  auto isvedimas_start = high_resolution_clock::now();
                            for (list<studentai>::iterator it = pazangus.begin(); it != pazangus.end(); it++) {
                               
                                    cout << left << setw(15) << it->v;
                                    cout << left << setw(15) << it->pav;
                                    cout << left << setw(18) << fixed << setprecision(2) << it->paz_vid;
                                    cout << fixed << setprecision(2) << it->paz_m << endl;
                                
                            }
                            cout << "-----------------------------------------------------------------\n";
                            cout << "Nepazangus studentai: \n";
                            cout << "-----------------------------------------------------------------\n";
                            for (list<studentai>::iterator it = nepazangus.begin(); it != nepazangus.end(); it++) {
             
                                    cout << left << setw(15) << it->v;
                                    cout << left << setw(15) << it->pav;
                                    cout << left << setw(18) << fixed << setprecision(2) << it->paz_vid;
                                    cout << fixed << setprecision(2) << it->paz_m << endl;
                            }
							cout << "-----------------------------------------------------------------\n";
                            //auto isvedimas_end = high_resolution_clock::now();
                           // isvedimo_laikas = apdorojimo_laikas(isvedimas_start, isvedimas_end);
                            if (skaitymo_laikas != 0)
                            {
                                cout << "Failo skaitymo laikas: " << setprecision(5) << skaitymo_laikas << endl;
                            }
                            cout << "Studentu rusiavimo laikas: " << setprecision(5) << skirstymo_laikas << endl;
                          //  cout << "Surusiuotu studentu isvedimo laikas: " << setprecision(5) << isvedimo_laikas << endl;
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
    //programos_laikas = apdorojimo_laikas(programa_start, programa_end);
	//laiko_failas << "Programos darbo laikas: " << programos_laikas << endl;
	laiko_failas << "\n";
    laiko_failas << "Testu laiku vidurkis: " << (skirstymo_laikas + rusiavimo_laikas + skaitymo_laikas) / 5.0 << endl;
    laiko_failas << "------------------------------------------------------------------------------------------\n";
     if (isvestis == "e")
     {
         //cout << "Programos darbo laikas: " << setprecision(5) << programos_laikas << endl;
         cout << "-----------------------------------------------------------------\n";
         cout << "Testu laiku vidurkis: " << setprecision(5) <<(skirstymo_laikas + rusiavimo_laikas + skaitymo_laikas) / 5.0 << endl;
     }
     /*CPU(report);
     RAM(report);
     Disk(report);
     report.close();*/
    laiko_failas.close();
    return 0;
}


