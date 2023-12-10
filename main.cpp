#include <iostream>
#include "studentas.h"
#include "Timer.h"

using namespace std;

int main()
{
    vector<Studentas> studentai;

    float tipas;
    float pasirinkimas;
    int kiekis;
    cout << "Pasirinkite ka noresite daryti:\na) skaityti pazymius is failo (rasykite 1)\nb) patys ivesite varda pavarde ir pazymius (rasykite 2)\nc) programa sugeneruos atsitiktini kieki atsitiktiniu pazymiu atsitiktiniam kiekiui studentu (rasykite 3): ";
    while (true)
    {
        pasirinkimas = GetIntInput();
        if ( pasirinkimas == 1 ){
            
            Timer t;

            cout << "Iveskite kieki kuri skaitysite pagal failo pavadinima: ";
            cin >> kiekis;

            t.reset();

            Ivestis(studentai, kiekis);
            cout << "Failas nuskaitytas. Rikiuojama..." << endl;
            sortVector(studentai);
            
            cout << "Failas buvo nuskaitytas ir isrikiuotas per: " <<  t.elapsed() << endl;
            break;
        }
        else if (pasirinkimas == 2){
            Ivestis2(studentai); // Reading from user input
            break;
        }
        else if (pasirinkimas == 3){
            Ivestis3(studentai); // Generating random number of random grades for random number of students
            break;
        }
        else if (cin.eof()) {
            break;
        }
        else cout << "Tokio pasirinkimo nera. Iveskite is naujo: ";
    }
    system("pause");
    
    cout << endl << setw(17) << left << "Pavarde" << setw(17) << "Vardas" << setw(17)
        << "Galutinis (Vid.)"<< "/ Galutinis (Med.)\n" << string(70, '-') << endl;
    
    for(const auto& studentas : studentai)
        cout << studentas;

    system("pause");
    return 0;
}
