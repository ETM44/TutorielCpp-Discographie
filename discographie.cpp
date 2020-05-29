#include "discographie.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


void cherche_morceau(Discographie & discographie, std::string const & instruction)
{
    bool morceau_connu {false};
    for (auto morceau : discographie)
    {
        if(morceau.nom == instruction)
            morceau_connu = true;
    }
    if(morceau_connu == false)
        throw std::runtime_error("Morceau introuvable.");

    std::sort(std::begin(discographie), std::end(discographie),[instruction](Morceau const & lhs, Morceau = {})
    {
        if(lhs.nom == instruction)
        {
            return true;
        }
        return false;
    });
}

void cherche_album(Discographie & discographie, std::string const & instruction)
{
    bool album_connu {false};
    for (auto morceau : discographie)
    {
        if(morceau.album.nom == instruction)
            album_connu = true;
    }
    if(album_connu == false)
        throw std::runtime_error("Album introuvable.");

    std::sort(std::begin(discographie), std::end(discographie),[instruction](Morceau const & lhs, Morceau const & rhs)
    {
        if(lhs.album.nom == instruction)
        {
            if(lhs.album.nom == rhs.album.nom )
            {
                return lhs.nom < rhs.nom;
            }
            return true;
        }
        return false;
    });
}

void cherche_artiste(Discographie & discographie, std::string const & instruction)
{
    bool artiste_connu {false};
    for (auto morceau : discographie)
    {
        if(morceau.compositeur.nom == instruction)
            artiste_connu = true;
    }
    if(artiste_connu == false)
        throw std::runtime_error("Artiste introuvable.");

    std::sort(std::begin(discographie), std::end(discographie),[instruction](Morceau const & lhs, Morceau const & rhs)
    {
        if(lhs.compositeur.nom == instruction)
        {
            if(lhs.compositeur.nom == rhs.compositeur.nom)
            {
                if(lhs.album.nom < rhs.album.nom)
                    return true;

                return lhs.album.nom == rhs.album.nom && lhs.nom < rhs.nom;
            }
            return true;
        }
        return false;
    });
}

void tri_morceau(Discographie& discographie)
{
    std::sort(std::begin(discographie), std::end(discographie), [](Morceau const & lhs, Morceau const & rhs)
    {
        return lhs.nom < rhs.nom;
    });
}

void tri_album(Discographie & discographie)
{
    std::sort(std::begin(discographie), std::end(discographie), [](Morceau const & lhs, Morceau const & rhs)
    {
        if (lhs.album.nom < rhs.album.nom)
            return true;

        return lhs.album.nom == rhs.album.nom && lhs.nom < rhs.nom;
    });
}

void tri_artiste(Discographie & discographie)
{
    std::sort(std::begin(discographie), std::end(discographie), [](Morceau const & lhs, Morceau const & rhs)
    {
        if (lhs.compositeur.nom < rhs.compositeur.nom)
            return true;

        if (lhs.compositeur.nom == rhs.compositeur.nom)
        {
            if (lhs.album.nom < rhs.album.nom)
                return true;

            return lhs.album.nom == rhs.album.nom && lhs.nom < rhs.nom;
        }

        return false;
    });
}

// Affichage de la discographie d'un morceau.
void affichage_morceau(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    auto morceau = discographie[0];

    std::cout << config_log.puce_niveau1 << " " << morceau << std::endl;
}

// Affichage de la discographie d'un album.
void affichage_album(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::cout << config_log.puce_niveau1 << " " << discographie[0].album << " ";
    std::cout << config_log.separateur_affichage << " " << discographie[0].compositeur << std::endl;

    Album album_precedent = discographie[0].album;
    for (Morceau const & morceau : discographie)
    {
        if(album_precedent.nom != morceau.album.nom)
            break;

        std::cout << "\t" << config_log.puce_niveau2 << " " << morceau.nom << std::endl;
    }
}

// Affichage de la discographie d'un artiste.
void affichage_artiste(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    Artiste artiste_precedent{discographie[0].compositeur};
    Album album_precedent{};

    std::cout << config_log.puce_niveau1 << " " << discographie[0].compositeur << std::endl;

    for (Morceau const & morceau : discographie)
    {
        if(artiste_precedent.nom != morceau.compositeur.nom)
            break;

        if (morceau.album.nom != album_precedent.nom)
        {
            std::cout << "\t" << config_log.puce_niveau2 << " " << morceau.album << std::endl;
        }

        std::cout << "\t\t" << config_log.puce_niveau3 << " " << morceau.nom << std::endl;

        artiste_precedent = morceau.compositeur;
        album_precedent = morceau.album;
    }
}

// Affichage de la discographie par morceau, dans l'ordre alphabétique.
void affichage_morceaux(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    for (Morceau const & morceau : discographie)
    {
        std::cout << config_log.puce_niveau1 << " " << morceau << std::endl;
    }
}

// Affichage de la discographie par album, dans l'ordre alphabétique.
void affichage_albums(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    Album album_precedent{};
    for (Morceau const & morceau : discographie)
    {
        if (morceau.album.nom != album_precedent.nom)
        {
            std::cout << config_log.puce_niveau1 << " " << morceau.album << " ";
            std::cout << config_log.separateur_affichage << " " << morceau.compositeur << std::endl;
        }
        std::cout << "\t" << config_log.puce_niveau2 << " " << morceau.nom << std::endl;

        album_precedent = morceau.album;
    }
}

// Affichage de la discographie par artiste, dans l'ordre alphabétique.
void affichage_artistes(Discographie const & discographie)
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    Artiste artiste_precedent{};
    Album album_precedent{};

    for (Morceau const & morceau : discographie)
    {
        if (morceau.compositeur.nom != artiste_precedent.nom)
        {
            std::cout << config_log.puce_niveau1 << " " << morceau.compositeur << std::endl;
        }

        if (morceau.album.nom != album_precedent.nom)
        {
            std::cout << "\t" << config_log.puce_niveau2 << " " << morceau.album << std::endl;
        }

        std::cout << "\t\t" << config_log.puce_niveau3 << " " << morceau.nom << std::endl;

        artiste_precedent = morceau.compositeur;
        album_precedent = morceau.album;
    }
}

void affichage(Discographie & discographie, Affichage type_affichage, std::string const & instruction)
{
    if (type_affichage == Affichage::Album)
    {
        cherche_album(discographie,instruction);
        affichage_album(discographie);
    }
    else if (type_affichage == Affichage::Artiste)
    {
        cherche_artiste(discographie,instruction);
        affichage_artiste(discographie);
    }
    else if (type_affichage == Affichage::Morceau)
    {
        cherche_morceau(discographie,instruction);
        affichage_morceau(discographie);
    }
    else if (type_affichage == Affichage::Albums)
    {
        tri_album(discographie);
        affichage_albums(discographie);
    }
    else if (type_affichage == Affichage::Artistes)
    {
        tri_artiste(discographie);
        affichage_artistes(discographie);
    }
    else if (type_affichage == Affichage::Morceaux)
    {
        tri_morceau(discographie);
        affichage_morceaux(discographie);
    }
    else
    {
        // Par exemple si on met à jour l'énumération mais qu'on oublie d'ajouter la fonction correspondante.
        throw std::runtime_error("Commande d'affichage inconnue.");
    }
}

void ajouter(Discographie & discographie, std::string const & instructions)
{
    //On regarde si on a déjà le morceau pour éviter les doublons
    Morceau new_morceau {};
    std::istringstream flux {instructions};
    flux >> new_morceau;

    bool morceau_inconnu = true;
    for(Morceau morceau : discographie)
    {
        if(morceau == new_morceau)
        {
            morceau_inconnu = false;
            break;
        }
    }
    if(morceau_inconnu == true)
        discographie.push_back(new_morceau); //Puis on charge
}

void enregistrement(Discographie const & discographie, std::string const & nom_fichier)
{
    std::ofstream fichier { nom_fichier };
    if (!fichier)
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier en écriture.");
    }

    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    for (Morceau const & morceau : discographie)
    {
        std::ostringstream flux {};
        flux << morceau;
        std::string morceau_str {flux.str()};

        //On échange les séparateurs de la configuration_logiciel contre
        //des séparateurs par défault pour éviter des problème au chargement
        std::string old_sep {config_log.separateur_affichage};
        std::string new_sep {"|"};
        for(unsigned i{}; i < config_log.separateur_affichage.size(); i++)
            new_sep += " ";

        for(unsigned i{}; i < morceau_str.size(); i++)
        {
            if(equal(std::begin(morceau_str) + i, std::begin(morceau_str) + old_sep.size() +i,
                     std::begin(old_sep)        , std::end(old_sep)))
            {
                copy(std::begin(new_sep), std::end(new_sep), std::begin(morceau_str) + i);
            }
        }
        fichier << morceau_str << std::endl; //Puis on enregistre
    }
}

void chargement(Discographie & discographie, std::string const & nom_fichier)
{
    std::ifstream fichier { nom_fichier };
    if (!fichier)
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier en lecture.");
    }

    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::string ligne {};
    while (std::getline(fichier, ligne))
    {
        //On échange les séparateurs par défault contre des séparateurs
        //de la configuration_logiciel pour éviter des problème au chargement
        std::string old_sep {"|"};
        std::string new_sep {config_log.separateur_ajout};

        for(unsigned i{}; i < ligne.size(); i++)
        {
            if(equal(std::begin(ligne) + i, std::begin(ligne) + old_sep.size() +i,
                     std::begin(old_sep)  , std::end(old_sep)))
            {
                copy(std::begin(new_sep), std::end(new_sep), std::begin(ligne) + i);
            }
        }
        ajouter(discographie, ligne);
    }
}
