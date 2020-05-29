#ifndef DISCOGRAPHIE_HPP_INCLUDED
#define DISCOGRAPHIE_HPP_INCLUDED

#include "donnees_disco.hpp"
#include <string>

void cherche_morceau(Discographie & discographie, std::string const & instruction);
void cherche_album(Discographie & discographie, std::string const & instruction);
void cherche_artiste(Discographie & discographie, std::string const & instruction);

void tri_morceau(Discographie & discographie);
void tri_album(Discographie & discographie);
void tri_artiste(Discographie & discographie);

void affichage_morceau(Discographie const & discographie);
void affichage_album(Discographie const & discographie);
void affichage_artiste(Discographie const & discographie);

void affichage_morceaux(Discographie const & discographie);
void affichage_albums(Discographie const & discographie);
void affichage_artistes(Discographie const & discographie);

enum class Affichage { Artistes, Albums, Morceaux, Artiste, Album, Morceau };

void affichage(Discographie & discographie, Affichage type_affichage,std::string const & instruction = "");

void ajouter(Discographie & discographie, std::string const & instructions);

void enregistrement(Discographie const & discographie, std::string const & nom_fichier);
void chargement(Discographie & discographie, std::string const & nom_fichier);

#endif
