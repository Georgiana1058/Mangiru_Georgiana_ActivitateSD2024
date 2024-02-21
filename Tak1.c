#include <iostream>

#include<string>

using namespace std;

//Mangiru Georgiana 

class Magazin {

	int id;

	string denumire;

	string categorie;

	int nrproduse;

	float* cantitate;

public:

	Magazin() : id(0), denumire("-"), categorie("-"), nrproduse(0) {

		this->cantitate = nullptr;


	}

	Magazin(int id, string denumire, string categorie, int nrproduse, float* cantitate) : id(id), denumire(denumire), categorie(categorie), nrproduse(nrproduse) {

		this->cantitate = new float[nrproduse];

		for (int i = 0; i < nrproduse; i++)

		{

			this->cantitate[i] = cantitate[i];

		}


	}

	friend istream& operator>>(istream& is, Magazin& m) {

		cout << "ID: "; is >> m.id;

		cout << "Denumire: "; is >> m.denumire;

		cout << "Categorie: "; is >> m.categorie;

		cout << "Numar Produse: "; is >> m.nrproduse;

		delete[]m.cantitate;

		m.cantitate = new float[m.nrproduse];

		cout << "Introduce-ti cantitatea produselor: ";

		for (int i = 0; i < m.nrproduse; i++)

		{

			is >> m.cantitate[i];


		}

		return is;

	}

	friend ostream& operator<<(ostream& os, Magazin& m) {

		os << "ID: " << m.id << endl;

		os << "Denumire: " << m.denumire << endl;

		os << "Categorie: " << m.categorie << endl;

		for (int i = 0; i < m.nrproduse; i++)

		{

			os << "Cantitate:" << m.cantitate[i] << endl;

		}

		return os;

	}

	~Magazin() {

		delete[]cantitate;

	}

	void setDenumire(string denumire) {

		this->denumire = denumire;

	}

	void cantitateaMaxima() {

		float p = 0;

		for (int i = 0; i < nrproduse; i++)

		{

			if (p < cantitate[i]) p = cantitate[i];



		}

		cout << "Cantitatea maxima este: " << p;

		cout << endl;

	}

};

int main() {

	float v[] = { 0.5,2,2.5 };

	Magazin t(1, "CocaCola", "Bautura", 3, v);

	cout << t << endl;

	t.setDenumire("Fanta");

	cout << t << endl;

	t.cantitateaMaxima();

	Magazin t1;

	cin >> t1;

	cout << t1;

	return 0;

}

