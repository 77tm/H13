/*  Toms Madžuls, tm22005
    H13. Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksti ar struktūru: atslēga (int),
    vārds (nepārsniedz 30 simbolus). Failu komponentes sakārtotas atslēgu pieaugšanas secībā.
    Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3 tā, lai arī f3 komponentes būtu atslēgu
    pieaugšanas secībā (failos nedrīkst parādīties divas komponentes ar vienādu atslēgu vērtību).
    Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
    Programma izveidota: 18.04.2023
*/

#include <iostream>
#include <fstream>

using namespace std;

void checkEOF(fstream &file1, fstream &file2, fstream &file3, int &key1, int &key2, char name1[], char name2[])
{
    if (file1.eof())
    {
        while (!file2.eof())
        {
            file3.write(reinterpret_cast<char *>(&key2), 1);
            file3.write(name2, 30);
            file2.read(reinterpret_cast<char *>(&key2), 1); // nolasa no faila 1 baitu (atslegu)
            file2.read(name2, 30);
        }
    }
    else if (file2.eof())
    {
        while (!file1.eof())
        {
            file3.write(reinterpret_cast<char *>(&key1), 1);
            file3.write(name1, 30);
            file1.read(reinterpret_cast<char *>(&key1), 1); // nolasa no faila 1 baitu (atslegu)
            file1.read(name1, 30);
        }
    }
}

void mergeSort(fstream &file1, fstream &file2, fstream &file3)
{
    int key1 = 0;
    int key2 = 0;
    char name1[30];
    char name2[30];

    file1.read(reinterpret_cast<char *>(&key1), 1); // nolasa no faila1 1 baitu (atslegu)
    file1.read(name1, 30);                          // nolasa no faila1 30 baitus (vardu)
    file2.read(reinterpret_cast<char *>(&key2), 1); // nolasa no faila2 1 baitu (atslegu)
    file2.read(name2, 30);                          // nolasa no faila2 30 baitus (vardu)

    checkEOF(file1, file2, file3, key1, key2, name1, name2); // parbaudam, vai kads no failiem nav tukss
    while (!file1.eof() && !file2.eof())
    {
        if (key1 < key2)
        {
            file3.write(reinterpret_cast<char *>(&key1), 1);
            file3.write(name1, 30);
            file1.read(reinterpret_cast<char *>(&key1), 1); // ja key1 mazaks, tad ierakstam to file3 un nolasam
            file1.read(name1, 30);                          // jaunu key1 + name1
        }
        if (key1 > key2)
        {
            file3.write(reinterpret_cast<char *>(&key2), 1);
            file3.write(name2, 30);
            file2.read(reinterpret_cast<char *>(&key2), 1); // ja key2 mazaks, tad ierakstam to file3 un nolasam
            file2.read(name2, 30);                          // jaunu key2 + name2
        }
        checkEOF(file1, file2, file3, key1, key2, name1, name2);
    }
}

int main()
{
    fstream f1("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f1.bin", ios::in | ios::binary);
    fstream f2("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f2.bin", ios::in | ios::binary);
    fstream f3("/Users/a77/Documents/programmesana/laboratorijas_darbi/H13/f3.bin", ios::out | ios::binary);

    mergeSort(f1, f2, f3);

    f1.close();
    f2.close();
    f3.close();

    return 0;
}