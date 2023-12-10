#include "Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#include <vector>
#include <list>

using namespace std;

struct Studentas{
    string vardas;
    string pavarde;
    double galutinis_balas;
};
void IvestisIsvestis(int kiekis, int tipas);

int main()
{
    cout << "Pasirinkite duomenu tipa: 1-Vector 2-List" <<endl;
    int pasirinkimas;
    cin >> pasirinkimas;
    if (pasirinkimas == 1){cout<<"\n\n>>> Vector <<<\n\n";}
    else if (pasirinkimas == 2){cout<<"\n\n>>> List <<<\n\n";};
    Timer t;
    for(int i=1000; i<=10000000; i*=10){
        t.reset();
        IvestisIsvestis(i, pasirinkimas);
        cout << "Failas su: " << i << " studentais buvo paskirstytas.\n";
        cout << i << " eiluciu failo perskirstymas i skirtingus failus uztruko: " << t.elapsed() << " s\n";
    }

    system("pause");
    return 0;
}


void IvestisIsvestis(int kiekis, int tipas)
{
    string INFILENAME = "failai/sugeneruoti/studentai" + to_string(kiekis) + ".txt";
    string OUTFILENAME_vargsiukai = "failai/1strategija/vargsiukai" + to_string(kiekis) + ".txt";
    string OUTFILENAME_kietiakai = "failai/1strategija/kietiakai" + to_string(kiekis) + ".txt";

    ifstream infile(INFILENAME);
    ofstream outfileV(OUTFILENAME_vargsiukai);
    ofstream outfileK(OUTFILENAME_kietiakai);

    outfileV << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17)
                << "Galutinis (Vid.)\n" << string(70, '-') << endl;
    outfileK << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17)
            << "Galutinis (Vid.)\n" << string(70, '-') << endl;


    Studentas studentas;
    string vardas, pavarde, eilute;
    double pazymiu_suma, sk[16];
    stringstream temp_ss;

    getline(infile, eilute);

    if(tipas == 1){
        vector<Studentas> studentaiVector;
        studentaiVector.reserve(kiekis);


        for(int i=0; i<kiekis; i++){
            getline(infile, eilute);
            stringstream eilute_stream(eilute);

            eilute_stream >> studentas.vardas >> studentas.pavarde;

            pazymiu_suma = 0;
            for(int j=0; j<15; j++){
                eilute_stream >> sk[j];
                pazymiu_suma += sk[j];
            }

            eilute_stream >> sk[15];

            studentas.galutinis_balas = (pazymiu_suma/15 * 0.4) + (sk[15] * 0.6);
            studentaiVector.push_back(studentas);
        }


        for(int i=0; i<kiekis; i++){
            temp_ss.str("");
            temp_ss << setw(17) << left << studentaiVector[i].pavarde << setw(17) << studentaiVector[i].vardas
                << setw(17) << fixed << setprecision(2) << studentaiVector[i].galutinis_balas << "\n";
            if(studentaiVector[i].galutinis_balas < 5.0){
                outfileV.write(temp_ss.str().c_str(), temp_ss.str().size());
            } else {
                outfileK.write(temp_ss.str().c_str(), temp_ss.str().size());
            }
        }
    }
    else if(tipas == 2){
        list<Studentas> studentaiList;

        for(int i=0; i<kiekis; i++){
            getline(infile, eilute);
            stringstream eilute_stream(eilute);

            eilute_stream >> studentas.vardas >> studentas.pavarde;

            pazymiu_suma = 0;
            for(int j=0; j<15; j++){
                eilute_stream >> sk[j];
                pazymiu_suma += sk[j];
            }

            eilute_stream >> sk[15];

            studentas.galutinis_balas = (pazymiu_suma/15 * 0.4) + (sk[15] * 0.6);
            studentaiList.push_back(studentas);
        }


        for(auto itr=studentaiList.begin(); itr != studentaiList.end(); ++itr) {
            temp_ss.str("");
            temp_ss << setw(17) << left << itr->pavarde << setw(17) << itr->vardas
                << setw(17) << fixed << setprecision(2) << itr->galutinis_balas << "\n";
            if(itr->galutinis_balas < 5.0){
                outfileV.write(temp_ss.str().c_str(), temp_ss.str().size());
            } else {
                outfileK.write(temp_ss.str().c_str(), temp_ss.str().size());
            }
        }
    }

}
