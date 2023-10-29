#include "Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <list>


using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    double vidurkis;
};

void Ivestis(int kiekis, list<Studentas>& studentai);
void Skirstymas(list<Studentas>& geriStudentai, list<Studentas>& blogiStudentai, list<Studentas>& studentai);
void Isvestis(int kiekis, bool pasiseke, list<Studentas>& studentai);

int main() {
    cout << "list" << endl;

    Timer t;
    Timer visas_t;

    for (int i = 1000; i <= 10000000; i *= 10) {

        list<Studentas> studentai;
        list<Studentas> blogiStudentai;
        list<Studentas> geriStudentai;

        visas_t.reset();
        t.reset();
        Ivestis(i, studentai);
        cout << i << " eiluciu failo nuskaitymas uztruko:" << t.elapsed()<< "s\n";

        t.reset();
        Skirstymas(geriStudentai, blogiStudentai, studentai);
        cout << i << " eiluciu failo skirstymas uztruko:" << t.elapsed()<< "s\n";

        t.reset();
        Isvestis(i, true, geriStudentai);
        Isvestis(i, false, blogiStudentai);
        cout << i << " eiluciu failo isvedimas i du failus uztruko:" << t.elapsed()<< "s\n";

        cout << "Failas su: " << i << " studentais buvo paskirstytas.\n";
        cout << i << " eiluciu failo perskirstymas i skirtingus failus uztruko: " << visas_t.elapsed() << "s\n\n\n";
    }

    system("pause");
    return 0;
}

void Skirstymas(list<Studentas>& geriStudentai, list<Studentas>& blogiStudentai, list<Studentas>& studentai) {
    for (const auto& stud : studentai) {
        if (stud.vidurkis >= 5) {
            geriStudentai.push_back(stud);
        }
        else {
            blogiStudentai.push_back(stud);
        }
    }
}

void Isvestis(int kiekis, bool pasiseke, list<Studentas>& studentai) {
    string OUTFILENAME;

    if (pasiseke) {
        OUTFILENAME = "failai/paskirstyti/pasiseke" + to_string(kiekis) + ".txt";
    }
    else {
        OUTFILENAME = "failai/paskirstyti/nepasiseke" + to_string(kiekis) + ".txt";
    }

    try {
        ofstream outfile(OUTFILENAME);

        outfile << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17) << "Galutinis (Vid.)\n"
            << string(70, '-') << endl;

        for (const auto& stud : studentai) {
            outfile << setw(17) << left << stud.pavarde
                << setw(17) << stud.vardas
                << setw(17) << fixed << setprecision(2) << stud.vidurkis << endl;
        }
    }
    catch (std::exception const& e) {
        cout << e.what() << endl;
    }
}

void Ivestis(int kiekis, list<Studentas>& studentai) {
    string INFILENAME = "failai/sugeneruoti/studentai" + to_string(kiekis) + ".txt";

    try {
        ifstream infile(INFILENAME);
        string vardas, pavarde;
        int sk[100];

        getline(infile, vardas);  // read header

        for (int i = 0; i < kiekis; i++) {
            float pazymiu_suma = 0;

            infile >> vardas >> pavarde;
            for (int j = 0; j < 16; j++) {
                infile >> sk[j];
                pazymiu_suma += sk[j];
            }
            infile >> sk[16];

            Studentas studentas{ vardas, pavarde, ((pazymiu_suma / 6.4) + (sk[16] * 0.6)) };
            studentai.push_back(studentas);
        }
    }
    catch (std::exception const& e) {
        cout << e.what() << endl;
    }
}

