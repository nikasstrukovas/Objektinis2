#include "Studentas.h"


bool compareStudentasByVardas(const Studentas& s1, const Studentas& s2) {
    return s1.vardas() < s2.vardas();
}

void sortVector(std::vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), compareStudentasByVardas);
}

int GetIntInput()
{
    int num;
    std::string input;

    while (true)
    {
        std::cin >> input;

        try {
            num = std::stoi(input);

            if(num >= 0 && num < 11){
                break;
            } else if(num == 11){
                return num;
            } else {
                std::cout << "Pazymys " << num << " neegzistuoja. Jis bus ignoruojamas." << std::endl;                
            }

        } catch (std::invalid_argument const &e) {
            if (std::cin.eof()) {
                std::cout << "Programa baigiama." << std::endl;
                break;
            }
            std::cout << "Vienas is ivestu simboliu nėra skaicius. Jis bus ignoruojamas." << std::endl;
        }
    }
    return num;
}


float RastiMediana(int arr[], int n)
{
    std::sort(arr, arr+n);
    if(n % 2 == 0)
    {
        return (arr[n/2 - 1] + arr[n/2]) / 2.0;
    }
    return arr[n/2];
}

// Generates randomly
void Ivestis3(std::vector<Studentas> &studentai)
{
    // Generates random number between 100 and 10'000
    srand(time(nullptr));
    int m = rand() % 9901 + 100;

    // array for holding grades of every student
    int sk[100];

    for(int i=0; i<m; i++)
    {
        float pazymiu_suma = 0;

        // generates between 2 and 20 random numbers (of values between 1 and 10)
        // last number in an array is grade for exam
        int n = rand() % 19 + 2;
        for(int j=0; j<=n; j++)
        {
            sk[j] = rand() % 10 + 1;
            pazymiu_suma += sk[j];
        }

        pazymiu_suma -= sk[n]; // atimam egzamino rezultato verte

        float mediana = RastiMediana(sk, n);
        Studentas studentas{
            ("Vardas" + std::to_string(i)),
            ("Pavarde" + std::to_string(i)),
            ((pazymiu_suma/n * 0.4) + (sk[n] * 0.6)),
            mediana
        };

        studentai.push_back(studentas);
    }
}

// Gets from user input
void Ivestis2(std::vector<Studentas> &studentai)
{
    std::string vardas, pavarde;
    int sk[100], m;
    
    while(true)
    {
        float pazymiu_suma = 0;
        std::cout << "Iveskite varda: \n>>> ";
        std::cin >> vardas;
        if (std::cin.eof()) break;

        std::cout << "Iveskite pavarde:\n>>> ";
        std::cin >> pavarde;
        if (std::cin.eof()) break;

        std::cout << "Iveskite visus pazymius (paskutnis pazymys yra egzamino rezultatas). Surase visus pazymius iveskite 11 ir spauskite enter:\n>>> ";

        int n=0;

        while (n < 100)
        {
            sk[n] = GetIntInput();
            if(sk[n] == 11 && n>1){
                break;
            } else if(sk[n] == 11 && n<2){
                std::cout << "Reikia įvesti bent 2 skaicius. Veskite is naujo\n>>> ";
                n = 0;
            }

            pazymiu_suma += sk[n];
            n++;
        }

        n--; // nes mums nereikia paskutinio skaiciaus, nes jis reiskia skaiciu ivedimo pabaiga
        pazymiu_suma -= sk[n]; // atimam egzamino rezultato verte, nes paskutine verte yra egzamino rezultatas

        std::cout << "Ivesti sie pazymiai: \n";
        for(int za=0; za<n; za++) std::cout << sk[za] << " ";
        std::cout << "Egzamino rez: " << sk[n] << std::endl;
        std::cout << "Enter -> testi  /  r + enter -> ivesti is naujo\n>>> ";

        std::string pasirinkimas;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, pasirinkimas);
        std::cout << "Pasirinkimas: " << pasirinkimas << std::endl;

        if(pasirinkimas == "r"){
            std::cout << "\nIvedimas is naujo\n";
            m--;
        } else {
            float mediana = RastiMediana(sk, n);

            Studentas studentas{
                vardas, pavarde,
                ((pazymiu_suma/(n) * 0.4) + (sk[n] * 0.6)),
                mediana
            };
            studentai.push_back(studentas);
        }

        m++;

       std::cout << "\n(norint nutraukti -> ctrl+Z ir Enter)\n";
    }
}

void Ivestis(std::vector<Studentas> &studentai, int &kiekis){
    std::string INFILENAME = "failai/sugeneruoti/studentai" + std::to_string(kiekis) + ".txt";

    // Open file for buffered reading
    std::ifstream infile_count(INFILENAME);
    if (!infile_count) {
        std::cout << "Failas negalejo buti atidarytas." << std::endl;
    } else{
        infile_count.rdbuf()->pubsetbuf(new char[1 << 20], 1 << 20); // Set buffer to 1 MB
        std::string s;
        std::getline(infile_count, s);
        int n = CountN(s);
        int m = 0;
        while (std::getline(infile_count, s)) m++;
        infile_count.close();

        std::ifstream infile(INFILENAME);
        //infile.rdbuf()->pubsetbuf(new char[1 << 20], 1 << 20); // Set buffer to 1 MB
        std::string vardas, pavarde;
        int sk[100];
        std::getline(infile, vardas);

        for (int i = 0; i < m; i++)
        {
            float pazymiu_suma = 0;

            // Nuskaitom ir apskaiciuojam vidurki
            infile >> vardas >> pavarde;
            for (int j = 0; j < n; j++) {
                infile >> sk[j];
                pazymiu_suma += sk[j];
            }
            infile >> sk[n];

            float mediana = RastiMediana(sk, n);

            Studentas studentas{
                vardas, pavarde,
                ((pazymiu_suma / n * 0.4) + (sk[n] * 0.6)),
                mediana
            };

            studentai.push_back(studentas);
        }
        infile.close();
    }
}

int CountN(std::string line)
{
    std::stringstream s (line);

    std::string word;
    int count = 0;
    while (s >> word)
        count++;

    return count-3;
}