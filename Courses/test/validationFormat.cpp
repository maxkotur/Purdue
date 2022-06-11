#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "validationFormat.h"
#include <map>

using namespace std;

double convertirChaineEnDouble(const std::string& p_chaine);

bool valideLigneCVS (std::string& p_ligne, std::ostringstream& p_parametres)
{
  bool resultat = false;
	string nomPropriete[] = {"ID","COTE_RUE","LECT_MET","SEGMENT_RU","DIRECTION","NOM_TOPOG","NO_BORNE","LONGITUDE","LATITUDE"};
	int i = 0;
	while (p_ligne.length() > 0){
		unsigned int pos = p_ligne.find("|");
		if (i > 8){
			resultat = false;
						break;
		}
		string subString;
		if (pos == string::npos){
			subString = p_ligne;
			p_ligne = "";
		}
		else {
			subString = p_ligne.substr(0, pos);
			p_ligne = p_ligne.substr(pos+1);
		}
    if (i == 7 || i == 8) {
      subString = convertirChaineEnDouble(subString);
    }

		p_parametres << nomPropriete[i] << " : " << subString << endl;
    
		i++;
	}
	return resultat;
}

bool validerGeom(const std::string& p_geom) {
  int startPos = p_geom.find("(");
	string geom = p_geom.substr(startPos+1);
	bool resultat = false;
	char* pEnd;
	double latit = strtod(geom.c_str(),&pEnd);
	double longit = strtod(pEnd,NULL);
	if (latit != 0 && longit != 0){
		resultat = true;
	}

	return resultat;
}

bool valideStationnemementGEOJSON (const std::string& p_enregistrement, std::ostringstream& p_attributs) {
  bool resultat = false;
	string nomPropriete[] = {"ID","COTE_RUE","LECT_MET","SEGMENT_RU","DIRECTION","NOM_TOPOG","NO_BORNE","NO_CIVIQ","ID_VOIE_PUB","GEOM"};

	unsigned pos = p_enregistrement.find("\"ID\":");
	string values = p_enregistrement.substr(pos);
	string properties[10];
	try{
		for(int i = 0; i < 10; i++){
			pos = values.find(":");
			string tempValue = values.substr(pos+1,1);
			if (tempValue == "\""){
				values = values.substr(pos+2);
				pos = values.find("\"");
			}
			else{
				values = values.substr(pos+1);
				pos = values.find(",");
			}
			properties[i] = values.substr(0,pos);
			if (i != 7 && i!= 8){
			p_attributs << nomPropriete[i] << " : " << properties[i] << endl;
			}
			if (i == 9){
				if(validerGeom(properties[i])){
				resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
	}
	catch(int e){
		resultat = false;
	}
	return resultat;
}

/**
* \brief Méthode qui permet de convertir une chaîne de caractères
* de la forme 123,456 en double.
* \param[in] p_chaine la chaîne de caractères à convertir.
* \return un double résultat de la conversion.
*/

double convertirChaineEnDouble(const std::string& p_chaine)
{
 string chaineFormate = p_chaine;
 //on remplace la , en .
 for (unsigned int i = 0; i < chaineFormate.length(); i++)
 {
 if (chaineFormate[i] == ',')
 {
 chaineFormate[i] = '.';
 }
 }
 istringstream is(chaineFormate);
 double chaineConvertiEnDouble;
 is >> chaineConvertiEnDouble;
 return chaineConvertiEnDouble;
}

