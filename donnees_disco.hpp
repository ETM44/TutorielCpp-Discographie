#ifndef DONNEES_DISCO_HPP_INCLUDED
#define DONNEES_DISCO_HPP_INCLUDED

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

struct Artiste
{
    std::string nom;
};

std::ostream & operator<<(std::ostream & sortie, Artiste const & artiste);

struct Album
{
    std::string nom;
};

std::ostream & operator<<(std::ostream & sortie, Album const & album);

struct Morceau
{
    std::string nom;
    Artiste compositeur;
    Album album;
};

std::ostream & operator<<(std::ostream & sortie, Morceau const & morceau);
std::istream & operator>>(std::istream & entree, Morceau & morceau);

bool operator==(Morceau const & lhs, Morceau const & rhs);
bool operator!=(Morceau const & lhs, Morceau const & rhs);

using Discographie = std::vector<Morceau>;

struct Configuration_Logiciel
{
    std::string invite;
    std::string separateur_affichage;
    std::string separateur_ajout;
    std::string puce_niveau1;
    std::string puce_niveau2;
    std::string puce_niveau3;
};

bool charge_configuration(Configuration_Logiciel & config_log);

#endif
