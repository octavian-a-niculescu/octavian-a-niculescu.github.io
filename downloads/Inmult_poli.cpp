// Inmult_poli.cpp : Acest fisier contine alforitmul de inmultire a doua polinoame utuluzant Tranfsormata Rapida Fourider.
//

#define _USE_MATH_DEFINES
#include <bits.h> 
#include <math.h>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Pentru a stoca valorile complexe ale radacinilor de ordin n ale unitatilor folosim complex<double>
typedef complex<double> cd;


// Functia recursiva pentru FFT - Transformata Rapida Fourier
vector<cd> fft(vector<cd> a)
{
	int n = a.size();

	// verificare daca polinomul introdus nu este cumva o constanta
	if (n == 1)
		return vector<cd>(1, a[0]);

	// definire vector pentru stocarea radacinilor de ordin n ale unitatilor
	vector<cd> w(n);
	for (int i = 0; i < n; i++)
	{
		double alpha = 2 * M_PI * i / n;
		w[i] = cd(cos(alpha), sin(alpha));
	}

	vector<cd> Ae(n / 2), Ao(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		// stocarea elementelor de grad par ale polinomului
		Ae[i] = a[i * 2];

		// stocarea elementelor de grad impar ale polinomului
		Ao[i] = a[i * 2 + 1];
	}

	// apelarea recursiva a functiei pentru elementele de ordin par
	vector<cd> y0 = fft(Ae);

	// apelarea recursiva a functiei pentru elementele de ordin impar
	vector<cd> y1 = fft(Ao);

	// definire vector pentru stocarea valorilor polinomului y0, y1, y2, ..., yn-1. 
	vector<cd> y(n);

	for (int k = 0; k < n / 2; k++) 
	{
		y[k] = y0[k] + w[k] * y1[k];
		y[k + n / 2] = y0[k] - w[k] * y1[k];
	}
	return y;
}



// Functia recursiva pentru IFFT - Inversa Transformatei Rapide Fourier
vector<cd> ifft(vector<cd> y)
{
	int n = y.size();
	// verificare daca valorea introdusa este un punct
	if (n == 1)
		return vector<cd>(1, y[0]);

	// definire vector pentru stocarea radacinilor de ordin n ale unitatilor
	vector<cd> wn(n);
	for (int i = 0; i < n; i++)
	{
		double alpha = -2 * M_PI * i / n;
		wn[i] = cd(cos(alpha), sin(alpha));
	}

	vector<cd> Ye(n / 2), Yo(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		// stocarea valorilor de grad par pentru determinarea coeficientilor polinomului
		Ye[i] = y[i * 2];

		// stocarea valorilor de grad impar pentru determinarea coeficientilor polinomului
		Yo[i] = y[i * 2 + 1];
	}

	// apelarea recursiva a functiei pentru determinarea coeficientilor pari ai polinimului
	vector<cd> a0 = ifft(Ye);

	// Rapelarea recursiva a functiei pentru determinarea coeficientilor impari ai polinimului
	vector<cd> a1 = ifft(Yo);

	// definire vector pentru stocarea valorilor polinomului a0, a1, a2, ..., an-1. 
	vector<cd> a(n);

	for (int k = 0; k < n / 2; k++)
	{
		a[k] = ((a0[k] + wn[k] * a1[k]));
		a[k + n / 2] = ((a0[k] - wn[k] * a1[k]));
	}
	return a;
}



void afisarePolinom1(vector<cd>& polinom1)
{
	cout << "Polinom 1: " << "\n";
	for (int indexPoli1 = 0; indexPoli1 < polinom1.size(); ++indexPoli1)
	{
		cout << polinom1[indexPoli1] << "\n";
	}
	cout << "\n";
}

void afisarePolinom2(vector<cd>& polinom2)
{
	cout << "Polinom 2: " << "\n";
	for (int indexPoli2 = 0; indexPoli2 < polinom2.size(); ++indexPoli2)
	{
		cout << polinom2[indexPoli2] << "\n";
	}
	cout << "\n";
}

void fftPolinom1(vector<cd> polinom1, vector<cd>& vectorFftPolinom1)
{
	cout << "FFT pentru polinomul 1: " << "\n";
	vectorFftPolinom1 = fft(polinom1);
	for (int indexFftPoli1 = 0; indexFftPoli1 < polinom1.size(); ++indexFftPoli1)
	{
		cout << vectorFftPolinom1[indexFftPoli1] << "\n";
	}
	cout << "\n";
}

void fftPolinom2(vector<cd> polinom2, vector<cd>& vectorFftPolinom2)
{
	cout << "FFT pentru polinomul 2: " << "\n";
	vectorFftPolinom2 = fft(polinom2);
	for (int indexFftPoli2 = 0; indexFftPoli2 < polinom2.size(); ++indexFftPoli2)
	{
		cout << vectorFftPolinom2[indexFftPoli2] << "\n";
	}
	cout << "\n";
}


cd inmultire(cd termen1, cd termen2)
{
	cd produs = termen1 * termen2;
	return produs;
}


void inmultireValori(vector<cd> vectorFftPolinom1, vector<cd> vectorFftPolinom2, vector<cd>& vectorMultipicareValori)
{
	cout << "Inmultirea valorilor celor doua polinoame: " << "\n";
	for (int indexMultip = 0; indexMultip < vectorFftPolinom1.size(); ++indexMultip)
	{
		vectorMultipicareValori[indexMultip] = inmultire(vectorFftPolinom1[indexMultip], vectorFftPolinom2[indexMultip]);
		cout << vectorMultipicareValori[indexMultip] << "\n";
	}
	cout << "\n";
}


void ifftPolinom(vector<cd> vectorMultipicareValori, vector<cd> vectorIfftPolinom)
{
	cout << "IFFT: " << "\n";
	cd N = vectorIfftPolinom.size();
	cd finalIfft = 0;
	vectorIfftPolinom = ifft(vectorMultipicareValori);
	for (int indexIfft = 0; indexIfft < vectorIfftPolinom.size(); ++indexIfft)
	{
		finalIfft = vectorIfftPolinom[indexIfft] / N;
		cout << finalIfft << "\n";
	}
	cout << "\n";
}


int main()
{
	//definire polinoame pentru inmultit
	vector<cd> polinom1{ 1, 2, 1 }, polinom2{ 1, -2, 1 };

	//definire vectori pentru FFT si IFFT
	vector<cd> vectorFftPolinom1, vectorFftPolinom2;
	vector<cd> vectorIfftPolinom(polinom1.size() + polinom2.size());
	vector<cd> vectorMultipicareValori(polinom1.size() + polinom2.size() - 1);

	afisarePolinom1(polinom1);
	afisarePolinom2(polinom2);
	fftPolinom1(polinom1, vectorFftPolinom1);
	fftPolinom2(polinom2, vectorFftPolinom2);

	inmultireValori(vectorFftPolinom1, vectorFftPolinom2, vectorMultipicareValori);
	ifftPolinom(vectorMultipicareValori, vectorIfftPolinom);

	return 0;
}