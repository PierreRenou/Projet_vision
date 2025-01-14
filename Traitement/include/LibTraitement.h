#pragma once

/*
Adaptation du projet seuillage auto aux besoins du projet OuiOui
*/

#include "ImageClasse.h"
#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"

#include <windows.h>

class ClibTraitement {

	///////////////////////////////////////
private:
	///////////////////////////////////////

	// data n�cessaires � l'IHM donc fonction de l'application cibl�e
	int						nbDataImg; // nb champs Texte de l'IHM
	std::vector<double>		dataFromImg; // champs Texte de l'IHM
	CImageCouleur*          imgPt;       // 

	///////////////////////////////////////
public:
	///////////////////////////////////////

	// constructeurs
	_declspec(dllexport) ClibTraitement(); // par d�faut

	_declspec(dllexport) ClibTraitement(int nbChamps, byte* data, int stride, int nbLig, int nbCol); // par image format bmp C#

	_declspec(dllexport) ~ClibTraitement();

	// get et set 

	_declspec(dllexport) int lireNbChamps() const {
		return nbDataImg;
	}

	_declspec(dllexport) double lireChamp(int i) const {
		return dataFromImg.at(i);
	}

	_declspec(dllexport) CImageCouleur* imgData() const {
		return imgPt;
	}

	//m�thodes suppl�mentaires
	_declspec(dllexport) void Traitement2(int nbChamps, byte* data, int stride, int nbLig, int nbCol, double parametres[10]); //nouvelle m�thode de traitement test
};

/****************************************************************************************************************

DEBUT DES METHODES UTILISEES EN C#
Rennomage des m�thodes et constructeurs de la classe C++ pour contr�ler ce qu'on envoie en C#

****************************************************************************************************************/

// Convention C pour que le constructeur C# puisse les voir selon leur calling convention
extern "C" _declspec(dllexport) ClibTraitement* objetLib()
{
	ClibTraitement* pImg = new ClibTraitement();
	return pImg;
}

// m�thode de traitement par d�faut: constructeur
extern "C" _declspec(dllexport) ClibTraitement* objetLibDataImg(int nbChamps, byte* data, int stride, int nbLig, int nbCol)
{
	ClibTraitement* pImg = new ClibTraitement(nbChamps,data,stride,nbLig,nbCol);
	return pImg;
}

// m�thode dee traitement suppl�mentaire
extern "C" _declspec(dllexport) ClibTraitement* traitementTest(int nbChamps, byte* data, int stride, int nbLig, int nbCol, double parametres[10])
{
	ClibTraitement* pImg = new ClibTraitement();
	pImg->Traitement2(nbChamps, data, stride, nbLig, nbCol, parametres);
	return pImg;
}

// attention : n�cessaire de savoir o� trouver le bon param�tre (possiblilit� d'enum en C# taduits en nombres en C.
extern "C" _declspec(dllexport) double valeurChamp(ClibTraitement* pImg, int i)
{
	return pImg->lireChamp(i);
}

/****************************************************************************************************************

FIN DES METHODES UTILISEES EN C#

****************************************************************************************************************/
