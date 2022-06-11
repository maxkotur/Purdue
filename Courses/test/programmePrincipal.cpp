/**
 * \file programmePrincipal.cpp
 * \brief  programme de simmulation d'un ...
 * commence par ...
 * ensuite ...
 *
 *
 *
 * \author THE
 * \version 0.1
 */

#include <cstdlib>
#include <iostream>
#include "fonctionsUtilitaires.h"
using namespace std;

int main()
{
    srand(time(0));
    int reponse;
    int jeu[4][13] = {0};
    int poignee[5][2] = {0};

    battre(jeu, poignee);
    distribue(jeu, poignee);

    afficheJeu(jeu);

    paires(poignee);
    brelans(poignee);
    carres(poignee);
    couleurs(poignee);
    suites(poignee);

    cout << "fin";
    return 0;

}

