#ifndef VALIDATIONFORMAT_H_
#define VALIDATIONFORMAT_H_


bool validerGeom(const std::string& p_geom);
bool valideLigneCVS (std::string& p_ligne, std::ostringstream& p_parametres);
bool valideStationnemementGEOJSON (const std::string& p_enregistrement, std::ostringstream& p_attributs);
#endif