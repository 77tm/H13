#include <iostream>
#include <fstream>

using namespace std;

void populateFile(fstream &file, int *usedKeys)
{
    int numRecords;
    int key = 0;
    char name[30];
    int prevKey = 0;
    int currKey = 0;

    cout << "How many records would you like to enter?" << endl;
    cin >> numRecords;

    for (int i = 0; i < numRecords; i++)
    {
        prevKey = key;
        cout << "Enter key: ";
        cin >> key;
        currKey = key;
        while (prevKey > currKey) // kontrolejam, ka key tiek ievaditi augosa seciba
        {
            cout << "Error: Keys must be in ascending order : ";
            cin >> key;
            currKey = key;
        }
        if (usedKeys[key] == 1) // parbaudam vai atslega ir jau izmantota
        {
            cout << "Error: Key already used" << endl;
            i--; // samazinam i, lai velreiz ievaditu atslegu
            continue;
        }
        usedKeys[key] = 1; // nomainam 0 -> 1 , atslega izmantota
        file.write(reinterpret_cast<char *>(&key), 1);
        cout << "Enter name (max 30 characters): ";
        cin >> name;
        if (strlen(name) == 0 || strlen(name) > 30)
        {
            cout << endl
                 << "Max name length is 30 characters: ";
            cin >> name;
        }
        else
        {
            file.write(name, 30);
        }
    }
}

int main()
{
    int ok;
    string chosenFile;
    int usedKeys[100] = {0}; // inicializejam masivu, kura glabat izmantotas atslegas

    do
    {
        cout << "Izvelieties failu (f1 / f2): ";
        cin >> chosenFile;

        if (chosenFile == "f1")
        {
            fstream f1("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f1.bin", ios::out | ios::binary);
            populateFile(f1, usedKeys);
            f1.close();
        }
        else if (chosenFile == "f2")
        {
            fstream f2("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f2.bin", ios::out | ios::binary);
            populateFile(f2, usedKeys);
            f2.close();
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
