/* D_I_viteze.cpp : Unui inginer i se dau mai multe seturi de date constând in valori ale vitezei unu autovehicul in urma unor teste.
Inginerul trebuie sa sorteze crescător valorile vitezelor pentru a determina accelerația autovehiculului într-un interval de 2 valori succesive ale vitezelor măsurate, după care sa determine accelerația maxima.
Accelerația se va determina utilizând următoarea formula:
    • accel = (vitezaActuală^2 - vitezaPrecedentă^2)/(2*Spațiu)
*/

#include <iostream>
#include <math.h>
#include <cmath>
#include <bits.h> 
#include <vector>
#include <iomanip>
using namespace std;
#define NrVitezePerSet 4 
#define Spatiu 10


void MergeDate(vector<float>& vectorVitezeSortate, float vectorViteze[][NrVitezePerSet], int numarVitezePerSet, int numarSeturiViteze)
{
	for (int indexLinii = 0; indexLinii < numarSeturiViteze; ++indexLinii)
	{
		for (int indexColoane = 0; indexColoane < numarVitezePerSet; ++indexColoane)
		{
			vectorVitezeSortate.push_back(vectorViteze[indexLinii][indexColoane]);
		}
	}
}


void Swap(float* a, float* b)
{
	float t = *a;
	*a = *b;
	*b = t;
}


int Partitionare(vector<float>& vector, int low, int high)
{
	int pivot = vector[high];
	int indexElementMic = (low - 1);

	for (int indexPart = low; indexPart <= high - 1; ++indexPart)
	{
		if (vector[indexPart] < pivot)
		{
			indexElementMic++;
			Swap(&vector[indexElementMic], &vector[indexPart]);
		}
	}
	Swap(&vector[indexElementMic + 1], &vector[high]);
	return (indexElementMic + 1);
}


void QuickSort(vector<float>& vector, int low, int high)
{
	if (low < high)
	{
		int indexPartitionare = Partitionare(vector, low, high);
		QuickSort(vector, low, indexPartitionare - 1);
		QuickSort(vector, indexPartitionare + 1, high);
	}
}


void AfisareVector(vector<float> vector)
{
	for (int indexViteze = 0; indexViteze < vector.size(); ++indexViteze)
	{
		cout << vector[indexViteze] << " ";
	}
	cout << "\n";
}


void CalculVectorAcceleratie(vector<float> vectorVitezeSortate, vector<float>& vectorAcceleratii)
{
	cout << "Acceleratiile calculate sunt [m/s^2] : " << "\n";
	for (int indexViteze = 0; indexViteze < vectorAcceleratii.size() - 1; ++indexViteze)
	{
		vectorAcceleratii[indexViteze] = ((vectorVitezeSortate[indexViteze + 1] * vectorVitezeSortate[indexViteze + 1]) - (vectorVitezeSortate[indexViteze] * vectorVitezeSortate[indexViteze])) / (2 * Spatiu);
		cout << vectorAcceleratii[indexViteze] << " ";
	}
	cout << "\n";
}


float Maxim(vector<float> vector, int index, int l)
{
	float max;
	if (index >= l - 2) 
	{
		if (vector[index] > vector[index + 1])
			return vector[index];
		else
			return vector[index + 1];
	}
	max = Maxim(vector, index + 1, l);
	if (vector[index] > max)
		return vector[index];
	else
		return max;
}


int main()
{
	// Datele de intrare
	float vectorViteze[][NrVitezePerSet] = { { 5, 7, 15, 18 },
											{ 1, 8, 9, 17 },
										   { 1, 4, 7, 7 } };
	int numarVitezePerSet = NrVitezePerSet;
	vector<float> vectorVitezeSortate;


	// Determinarea numarului de seturi de date pentru viteze
	int numarSeturiViteze = sizeof(vectorViteze) / sizeof(vectorViteze[0]);

	// procesare date viteza autovehicul
	MergeDate(vectorVitezeSortate, vectorViteze, numarVitezePerSet, numarSeturiViteze);
	cout << "Vitezele nesortate sunt [m/s] : " << "\n";
	AfisareVector(vectorVitezeSortate);
	QuickSort(vectorVitezeSortate, 0, vectorVitezeSortate.size() - 1);
	cout << "Vitezele sortate crescator sunt [m/s] : " << "\n";
	AfisareVector(vectorVitezeSortate);

	// procesare date acceleratie autovehicul
	vector<float> vectorAcceleratii(vectorVitezeSortate.size());
	CalculVectorAcceleratie(vectorVitezeSortate, vectorAcceleratii);
	cout << "Acceleratia maxima este : "  << Maxim(vectorAcceleratii, 0, vectorAcceleratii.size()) << " m/s^2" << "\n";

	return 0;
}

