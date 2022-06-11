/**
 * \file fonctionsUtilitaires.cpp
 * \brief  implémentation (définitions) des fonctions utilitaires
 * \author THE
 * \version 0.1
 */

#include <cstdlib>
#include <iostream>

#include "fonctionsUtilitaires.h"
using namespace std;

void battre(int p_jeu[][13], int p_poignee[][2])
{
    // initialise le jeu
    int carte = 1;
    for (int ligne = 0; ligne <= 4; ++ligne)
        for (int colonne = 0; colonne <= 13; ++colonne)
            p_jeu[ligne][colonne] = carte++;

    int temp;
    int ligneAleatoire;
    int colonneAleatoire;

    for (int ligne = 0; ligne <= 4; ++ligne)
        for (int colonne = 0; colonne <= 13; ++colonne)
        {
            ligneAleatoire = rand() % 4;
            colonneAleatoire = rand() % 13;
            temp = p_jeu[ligne][colonne];
            p_jeu[ligne][colonne] = p_jeu[ligneAleatoire][colonneAleatoire];
            p_jeu[ligneAleatoire][colonneAleatoire] = temp;
        }
}

void distribue(const int p_jeu[][13], int p_poignee[][2])
{
    int ligneCourante;

    cout << "La main est:\n";

    for (int carte = 1; carte < 6; ++carte)
    {
        for (int ligne = 0; ligne < 4; ++ligne)
        {
            for (int colonne = 0; colonne < 13; ++colonne)
            {
                if (p_jeu[ligne][colonne] == carte)
                {
                    p_poignee[ligneCourante][0] = ligne;
                    p_poignee[ligneCourante][1] = colonne;
                    cout << FACE[colonne] << " de " << ENSEIGNE[ligne] << endl;
                    ++ligneCourante;
                }
            }
        }
    }
}

bool paires(const int p_poignee[][2])
{
    bool trouve = false;

    int compteur[13] = {0};

    for (int ligne = 0; ligne < 5; ++ligne)
    {
        ++compteur[p_poignee[ligne][1]];
    }

    cout << endl;

    for (int position = 0; position < 13; ++position)
    {
        if (compteur[position] == 2)
        {
            cout << "La main contient une paire de " << FACE[position] << endl;
            trouve = true;
        }
    }
    return trouve;
}

bool brelans(const int p_poignee[][2])
{
    bool trouve = false;

    int compteur[13] = {0};

    for (int ligne = 0; ligne < 5; ++ligne)
    {
        ++compteur[p_poignee[ligne][1]];
    }

    for (int positionBrelan = 0; positionBrelan < 13; positionBrelan++)
    {
        if (compteur[positionBrelan] == 3)
        {
            cout << "La main contient trois " << FACE[positionBrelan] << "(s)."
                    << endl;
            trouve = true;
        }
    }
    return trouve;
}

bool carres(const int p_poignee[][2])
{
    bool trouve = false;
    int c[13] = {0};

    for (int ligne = 0; ligne < 5; ++ligne)
    {
        ++c[p_poignee[ligne][1]];
    }

    for (int positionCarre = 0; positionCarre < 13; ++positionCarre)
    {
        if (c[positionCarre] == 4)
        {
            cout << "La main contient quatre " << FACE[positionCarre] << "(s)."
                    << endl;
            trouve = true;
        }
    }
    return trouve;
}

bool couleurs(const int p_poignee[][2])
{
    bool trouve = false;

    int compteur[4] = {0};

    for (int ligne = 0; ligne < 5; ++ligne)
    {
        ++compteur[p_poignee[ligne][0]];
    }

    for (int positionCouleur = 0; positionCouleur < 4; ++positionCouleur)
    {
        if (compteur[positionCouleur] == 5)
        {
            cout << "La main contient une couleur de "
                    << ENSEIGNE[positionCouleur] << endl;
            trouve = true;
        }
    }
    return trouve;
}

bool suites(int p_poignee[][2])
{
    bool trouve = false;

    int serie[5] = {0};
    int temp;

    // copie les colonnes pour le tri
    for (int ligne = 0; ligne < 5; ++ligne)
    {
        serie[ligne] = p_poignee[ligne][1];
    }

    // tri à bulle par position dans les colonnes
    for (int passage = 1; passage < 5; ++passage)
    {
        for (int compte = 0; compte < 4; ++compte)
        {
            if (serie[compte] > serie[compte + 1])
            {
                temp = serie[compte];
                serie[compte] = serie[compte + 1];
                serie[compte + 1] = temp;
            }
        }
    }

    // vérifie si les colonnes triées sont une suite
    if (serie[4] - 1 == serie[3] && serie[3] - 1 == serie[2]
            && serie[2] - 1 == serie[1] && serie[1] - 1 == serie[0])
    {
        cout << "La main contient une suite " << endl;

        for (int positionSuite = 0; positionSuite < 5; ++positionSuite)
        {
            cout << FACE[p_poignee[positionSuite][1]] << " de "
                    << ENSEIGNE[p_poignee[positionSuite][0]] << endl;
            trouve = true;
        }
    }
    return trouve;
}
void afficheJeu (int p_jeu[][13]){}
