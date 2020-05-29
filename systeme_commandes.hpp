#ifndef SYSTEME_COMMANDES_HPP_INCLUDED
#define SYSTEME_COMMANDES_HPP_INCLUDED

#include "donnees_disco.hpp"

#include <string>
#include <tuple>

std::string recuperer_commande();

enum class Commande { Afficher, Ajouter, Enregistrer, Charger, Quitter };

std::tuple<Commande, std::string> analyser_commande(std::string const & commande_texte);
bool executer_commande(Discographie & discographie, Commande commande, std::string const & instructions);

#endif
