#include "donnees_disco_tests.hpp"

#include <sstream>
#define NDEBUG
#include <cassert>
#include "donnees_disco.hpp"

void test_charge_configuration_cherche_fichier()
{
    Configuration_Logiciel config_log;

    assert(charge_configuration(config_log) == false && u8"Le fichier configuration_logiciel.txt n'a pas ete trouve");
}

void test_creation_morceau_entree_complete()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { "Frica " + config_log.separateur_ajout + " Frica " + config_log.separateur_ajout + " Carla's Dreams" };
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Frica" && u8"Le nom du morceau doit être Frica.");
    assert(morceau.album.nom == "Frica" && u8"Le nom de l'album doit être Frica.");
    assert(morceau.compositeur.nom == "Carla's Dreams" && u8"Le nom du compositeur doit être Carla's Dreams.");
}

void test_creation_morceau_entree_espaces_partout()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { "Levels      " + config_log.separateur_ajout + "  Levels     " + config_log.separateur_ajout + "  Avicii" };
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Levels" && u8"Le nom du morceau doit être Levels.");
    assert(morceau.album.nom == "Levels" && u8"Le nom de l'album doit être Levels.");
    assert(morceau.compositeur.nom == "Avicii" && u8"Le nom du compositeur doit être Avicii.");
}

void test_creation_morceau_entree_chanson_artiste()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { "Subeme la radio " + config_log.separateur_ajout + " " + config_log.separateur_ajout + " Enrique Iglesias" };
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Subeme la radio" && u8"Le nom du morceau doit être Subeme la radio.");
    assert(morceau.album.nom == "Album inconnu" && u8"Le nom de l'album doit être Album inconnu.");
    assert(morceau.compositeur.nom == "Enrique Iglesias" && u8"Le nom du compositeur doit être Enrique Iglesias.");
}

void test_creation_morceau_entree_chanson_uniquement()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { "Duel of the fates " + config_log.separateur_ajout + " " + config_log.separateur_ajout};
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Duel of the fates" && u8"Le nom du morceau doit être Duel of the Fates.");
    assert(morceau.album.nom == "Album inconnu" && u8"Le nom de l'album doit être Album inconnu.");
    assert(morceau.compositeur.nom == "Artiste inconnu" && u8"Le nom du compositeur doit être Artiste inconnu.");
}

void test_creation_morceau_entree_chanson_artiste_barres_collees()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { "Subeme la radio " + config_log.separateur_ajout + config_log.separateur_ajout + " Enrique Iglesias" };
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Subeme la radio" && u8"Le nom du morceau doit être Subeme la radio.");
    assert(morceau.album.nom == "Album inconnu" && u8"Le nom de l'album doit être Album inconnu.");
    assert(morceau.compositeur.nom == "Enrique Iglesias" && u8"Le nom du compositeur doit être Enrique Iglesias.");
}

void test_creation_morceau_entree_vide()
{
    Configuration_Logiciel config_log;
    charge_configuration(config_log);

    std::istringstream entree { config_log.separateur_ajout + " " + config_log.separateur_ajout};
    Morceau morceau {};

    entree >> morceau;

    assert(morceau.nom == "Morceau inconnu" && u8"Le nom du morceau doit être Morceau inconnu.");
    assert(morceau.album.nom == "Album inconnu" && u8"Le nom de l'album doit être Album inconnu.");
    assert(morceau.compositeur.nom == "Artiste inconnu" && u8"Le nom du compositeur doit être Artiste inconnu.");
}


