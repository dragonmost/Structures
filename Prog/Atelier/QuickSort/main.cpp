#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

const int ARR_SIZE = 1000000;

int arrTab[ARR_SIZE];

void quickSort(int _iMin, int _iMax);

void main()
{
	unsigned int ui_TimeBegin = time(NULL);
	

	srand(time(NULL));
	for (int ii = 0; ii < ARR_SIZE; ii++)
	{
		arrTab[ii] = rand() % 1000;
	}

	quickSort(0, (ARR_SIZE - 1));


	unsigned int ui_Time = time(NULL) - ui_TimeBegin;

	cout << ui_Time << endl;

	system("pause");
}

void quickSort(int _iMin, int _iMax)
{
	int iGauche = _iMin;
	int iDroite = _iMax;
	int iPivot = _iMin;
	int iTransit;

	while (iDroite != iGauche)
	{
		if (arrTab[iGauche] > arrTab[iDroite])
		{
			iTransit = arrTab[iGauche];
			arrTab[iGauche] = arrTab[iDroite];
			arrTab[iDroite] = iTransit;
			iPivot = iGauche + iDroite - iPivot;
		}


		if (iPivot == iGauche)
			iDroite--;
		else
			iGauche++;
	}

	if (_iMin < iPivot - 1)
	{
		quickSort(_iMin, iPivot - 1);
	}
	if (_iMax > iPivot + 1)
	{
		quickSort(iPivot + 1, _iMax);
	}
}