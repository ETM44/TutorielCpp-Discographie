#include "discographie.hpp"
#include "systeme_commandes.hpp"
#include "utils.hpp"

#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>




std::string recuperer_commande()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::cout << config_log.invite;

    std::string commande {};
    std::getline(std::cin, commande);
    return commande;
}

std::tuple<Commande, std::string> analyser_commande(std::string const & commande_texte)
{
    std::istringstream flux { commande_texte };

    std::string premier_mot {};
    flux >> premier_mot;
    premier_mot = traitement_chaine(premier_mot);

    std::string instructions {};
    std::getline(flux, instructions);
    instructions = traitement_chaine(instructions);

    if (premier_mot == "afficher")
    {
        return { Commande::Afficher, instructions };
    }
    else if (premier_mot == "ajouter")
    {
        return { Commande::Ajouter, instructions };
    }
    else if (premier_mot == "enregistrer")
    {
        return{ Commande::Enregistrer, instructions };
    }
    else if (premier_mot == "charger")
    {
        return { Commande::Charger, instructions };
    }
    else if (premier_mot == "quitter")
    {
        return { Commande::Quitter, std::string {} };
    }
    else
    {
        throw std::runtime_error("Commande invalide.");
    }
}

bool executer_commande(Discographie & discographie, Commande commande, std::string const & instructions)
{
    if (commande == Commande::Afficher)
    {    
        auto it = std::find(begin(instructions),end(instructions),' ');
        std::string instruction1 {begin(instructions),it};
        std::string instruction2 {it ,end(instructions)};
        instruction1 = traitement_chaine(instruction1);
        instruction2 = traitement_chaine(instruction2);

        if (instruction1 == "artiste" && !instruction2.empty())
        {
            affichage(discographie, Affichage::Artiste,instruction2);
        }
        else if (instruction1 == "album" && !instruction2.empty())
        {
            affichage(discographie, Affichage::Album, instruction2);
        }
        else if (instruction1 == "morceau" && !instruction2.empty())
        {
            affichage(discographie, Affichage::Morceau, instruction2);
        }
        else if (instructions == "artistes")
        {
             affichage(discographie, Affichage::Artistes);
        }
        else if (instructions == "albums")
        {
            affichage(discographie, Affichage::Albums);
        }
        else if (instructions == "morceaux")
        {
            affichage(discographie, Affichage::Morceaux);
        }
        else
        {
            throw std::runtime_error("Commande d'affichage inconnue.");
        }
    }
    else if (commande == Commande::Ajouter)
    {
        ajouter(discographie, instructions);
    }
    else if (commande == Commande::Charger)
    {
        chargement(discographie, instructions);
    }
    else if (commande == Commande::Enregistrer)
    {
        enregistrement(discographie, instructions);
    }
    else if (commande == Commande::Quitter)
    {
        return false;
    }

    return true;
}
