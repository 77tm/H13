#include <iostream>
#include <fstream>

using namespace std;

void printFileContents(fstream &file)
{
    int key = 0;
    char name[30];

    file.read(reinterpret_cast<char *>(&key), 1); // nolasam fiksetu garumu 1 baits atslegu
    file.read(name, 30);                          // nolasam fiksetu garumu 30 baiti vardu
    while (not file.eof())                        // kamer nav faila beigas tikmer cout
    {
        cout << (int)key << ": " << name << endl;
        file.read(reinterpret_cast<char *>(&key), 1);
        file.read(name, 30);
    }
    cout << endl;
}

int main()
{
    int ok;
    string chosenFile;

    do
    {
        cout << "Izvelieties failu (f1 / f2 / f3): ";
        cin >> chosenFile;

        if (chosenFile == "f1")
        {
            fstream f1("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f1.bin", ios::in | ios::binary);
            printFileContents(f1);
            f1.close();
        }
        else if (chosenFile == "f2")
        {
            fstream f2("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f2.bin", ios::in | ios::binary);
            printFileContents(f2);
            f2.close();
        }
        else if (chosenFile == "f3")
        {
            fstream f3("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f3.bin", ios::in | ios::binary);
            printFileContents(f3);
            f3.close();
        }
        else
        {
            cout << "Invalid file choice" << endl;
            return 1;
        }
        cout << "Vai turpināt (1) vai beigt (0)?" << endl;
        cin >> ok;
    } while (ok == 1);

    return 0;
}