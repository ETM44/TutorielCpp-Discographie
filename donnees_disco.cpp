#include "donnees_disco.hpp"

#include "utils.hpp"

std::ostream & operator<<(std::ostream & sortie, Artiste const & artiste)
{
    sortie << artiste.nom;
    return sortie;
}

std::ostream & operator<<(std::ostream & sortie, Album const & album)
{
    sortie << album.nom;
    return sortie;
}

std::ostream & operator<<(std::ostream & sortie, Morceau const & morceau)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    sortie << morceau.nom << " " << config_log.separateur_affichage << " ";
    sortie << morceau.album <<  " " << config_log.separateur_affichage << " " << morceau.compositeur;
    return sortie;
}

std::istream & operator>>(std::istream & entree, Morceau & morceau)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    //std::string
    std::string mot {};
    std::ostringstream flux {};

    while (entree >> mot && mot != config_log.separateur_ajout &&
           mot != config_log.separateur_ajout + config_log.separateur_ajout)
    {
        flux << mot << " ";
    }

    std::string nom_morceau { flux.str() };
    if (std::empty(nom_morceau))
    {
        nom_morceau = "Morceau inconnu";
    }
    morceau.nom = traitement_chaine(nom_morceau);
    flux.str(std::string {});

    if(mot != config_log.separateur_ajout + config_log.separateur_ajout)
        while (entree >> mot && mot != config_log.separateur_ajout)
        {
            flux << mot << " ";
        }

    std::string nom_album { flux.str() };
    if (std::empty(nom_album))
    {
        nom_album = "Album inconnu";
    }
    morceau.album.nom = traitement_chaine(nom_album);
    flux.str(std::string {});

    while (entree >> mot)
    {
        flux << mot << " ";
    }

    std::string nom_artiste { flux.str() };
    if (std::empty(nom_artiste))
    {
        nom_artiste = "Artiste inconnu";
    }
    morceau.compositeur.nom = traitement_chaine(nom_artiste);
    flux.str(std::string {});

    return entree;
}

bool operator==(Morceau const & lhs, Morceau const & rhs)
{
    return lhs.nom == rhs.nom && lhs.album.nom == rhs.album.nom
                              && lhs.compositeur.nom == rhs.compositeur.nom;
}
bool operator!=(Morceau const & lhs, Morceau const & rhs)
{
    return !(lhs == rhs);
}

std::istream & operator>>(std::istream & flux, Configuration_Logiciel & config_log)
{
    std::string mot, operateur, commande;
    flux >> mot >> operateur >> commande;

    mot = traitement_chaine_digit_alpha(mot);
    commande = traitement_chaine_guillemets(commande);

    if(mot == "invite" && operateur == "=")
    {
        config_log.invite = commande;
    }
    else if(mot == "separateur_affichage" && operateur == "=")
    {
        config_log.separateur_affichage = commande;
    }
    else if(mot == "separateur_ajout" && operateur == "=")
    {
        config_log.separateur_ajout = commande;
    }
    else if(mot == "puce_niveau1" && operateur == "=")
    {
        config_log.puce_niveau1 = commande;
    }
    else if(mot == "puce_niveau2" && operateur == "=")
    {
        config_log.puce_niveau2 = commande;
    }
    else if(mot == "puce_niveau3" && operateur == "=")
    {
        config_log.puce_niveau3 = commande;
    }

    return flux;
}

bool charge_configuration(Configuration_Logiciel & config_log)
{
    std::ifstream fichier("configuration_logiciel.txt");
    std::string ligne;

    if(fichier)
    {
        while(getline(fichier,ligne))
        {
            std::istringstream flux {ligne};

            flux >> config_log;
        }
        return false;
    }
    else
    {
         config_log.invite               = ">"   ;
         config_log.separateur_affichage = "|"   ;
         config_log.separateur_ajout     = "|"   ;
         config_log.puce_niveau1         = "-->" ;
         config_log.puce_niveau2         = "/-->";
         config_log.puce_niveau3         = "/-->";

         return true;
    }
}
