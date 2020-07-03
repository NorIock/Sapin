#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int etages_par_block(int size)
{
    int nombre_ligne_par_etage = size + 3;
    return nombre_ligne_par_etage;
}

int nombre_etoiles_derniere_ligne(int size)
{
    int block;
    int nombre_etoiles_derniere_ligne = 7;
    int decrementation_par_block = 2;
    for (block = 2; block <= size; block++)
    {
        int incrementation_etoiles = 0;
        if (block == 2 || block == 3)
        {
            nombre_etoiles_derniere_ligne = nombre_etoiles_derniere_ligne - decrementation_par_block;
        }

        else if (block != 2 && block != 3 && block % 2 == 0)
        {
            decrementation_par_block = decrementation_par_block + 2;
            nombre_etoiles_derniere_ligne = nombre_etoiles_derniere_ligne - decrementation_par_block;
        }

        else
        {
            nombre_etoiles_derniere_ligne = nombre_etoiles_derniere_ligne - decrementation_par_block;
        }

        for (int ligne = 1; ligne < etages_par_block(block); ligne++)
        {
            incrementation_etoiles = incrementation_etoiles + 2;
        }
        nombre_etoiles_derniere_ligne = nombre_etoiles_derniere_ligne + incrementation_etoiles;
    }

    return nombre_etoiles_derniere_ligne;
}

int nombre_etoiles_premiere_ligne(int size)
{
    int ligne = etages_par_block(size);
    int nombre_etoiles_premiere_ligne = nombre_etoiles_derniere_ligne(size);
    int decrementation = 0;
    while (ligne > 1)
    {
        decrementation = decrementation + 2;
        ligne--;
    }
    nombre_etoiles_premiere_ligne = nombre_etoiles_premiere_ligne - decrementation;
    return nombre_etoiles_premiere_ligne;
}

int calcul_espace_vide_premiere_ligne(int size)
{
    int largeur_totale = nombre_etoiles_derniere_ligne(size);
    int espace_flan = largeur_totale / 2;
    int nombre_total_etoiles = nombre_etoiles_premiere_ligne(size);
    int nombre_etoiles_necessaires = nombre_total_etoiles / 2;
    int espace_vide = espace_flan - nombre_etoiles_necessaires;
    return espace_vide;
}

void feuillage(int size)
{
    int block = 1;
    while (block <= size)
    {
        int espace_vide_flan_gauche = nombre_etoiles_derniere_ligne(size) / 2;
        int nombre_etoiles_ligne1;
        nombre_etoiles_ligne1 = nombre_etoiles_premiere_ligne(block);
        int nombre_etoiles_flan_gauche;
        nombre_etoiles_flan_gauche = nombre_etoiles_ligne1 / 2;
        int ligne_par_block = etages_par_block(block);
        for (int ligne = 1; ligne <= ligne_par_block; ligne++)
        {
            int i = 0;
            while (i < espace_vide_flan_gauche - nombre_etoiles_flan_gauche)
            {
                write(1, " ", 1);
                i++;
            }
            int j = 0;
            while (j < nombre_etoiles_ligne1)
            {
                write(1, "*", 1);
                j++;
            }
            write(1, "\n", 1);
            espace_vide_flan_gauche = espace_vide_flan_gauche - 1;
            nombre_etoiles_ligne1 = nombre_etoiles_ligne1 + 2;
        }
        block++;
    }
}

void tronc(int size)
{
    int espace_vide_flan_gauche = nombre_etoiles_derniere_ligne(size) / 2;
    int tronc_flanc_gauche;
    tronc_flanc_gauche = size / 2;
    if (size % 2 == 0)
    {
        size++;
        for (int ligne = 1; ligne < size; ligne++)
        {
            int i = 0;
            while (i < espace_vide_flan_gauche - tronc_flanc_gauche)
            {
                write(1, " ", 1);
                i++;
            }
            int j = 0;
            while (j < size)
            {
                write(1, "|", 1);
                j++;
            }
            write(1, "\n", 1);
        }
    }
    else
    {
        size = size;

        for (int ligne = 1; ligne <= size; ligne++)
        {
            int i = 0;
            while (i < espace_vide_flan_gauche - tronc_flanc_gauche)
            {
                write(1, " ", 1);
                i++;
            }
            int j = 0;
            while (j < size)
            {
                write(1, "|", 1);
                j++;
            }
            write(1, "\n", 1);
        }
    }
}

void tree(int size)
{
    feuillage(size);
    tronc(size);
}

int main(int argc, char **argv)
{
    int size = atoi(argv[1]);
    tree(size);
}