#include "donnees_disco_tests.hpp"
#include "discographie.hpp"
#include "systeme_commandes.hpp"
#include "utils.hpp"

#include <stdexcept>

int main()
{
    test_charge_configuration_cherche_fichier();
    test_creation_morceau_entree_complete();
    test_creation_morceau_entree_espaces_partout();
    test_creation_morceau_entree_chanson_artiste();
    test_creation_morceau_entree_chanson_uniquement();
    test_creation_morceau_entree_chanson_artiste_barres_collees();
    test_creation_morceau_entree_vide();

    Artiste const dave_brubeck { "Dave Brubeck" };
    Artiste const secret_garden { "Secret Garden" };
    Artiste const indochine { "Indochine" };

    Album const time_out { "Time Out" };
    Album const songs_from_a_secret_garden { "Songs from a Secret Garden" };
    Album const l_aventurier { "L'aventurier" };
    Album const paradize { "Paradize" };

    Morceau const take_five { "Take Five", dave_brubeck, time_out };
    Morceau const blue_rondo_a_la_turk { "Blue Rondo a la Turk", dave_brubeck, time_out };
    Morceau const nocturne { "Nocturne", secret_garden, songs_from_a_secret_garden };
    Morceau const aventurier { "L'aventurier", indochine, l_aventurier };
    Morceau const j_ai_demande_a_la_lune { "J'ai demandé à la lune", indochine, paradize };

    Discographie discographie { take_five, blue_rondo_a_la_turk, nocturne, aventurier, j_ai_demande_a_la_lune };

    try
    {
        Configuration_Logiciel config_log;
        if(charge_configuration(config_log))
            throw std::runtime_error("Le fichier configuration_logiciel.txt n'a "
                                     "pas ete trouve. Configuration par default.");

    }
    catch (std::runtime_error const & exception)
    {
        std::cerr << "Erreur : " << exception.what() << std::endl;
    }

    bool continuer { true };
    do
    {
        try
        {
            std::string entree { recuperer_commande() };
            auto[commande, instructions] = analyser_commande(entree);
            instructions = traitement_chaine(instructions);
            continuer = executer_commande(discographie, commande, instructions);
        }
        catch (std::runtime_error const & exception)
        {
            std::cerr << "Erreur : " << exception.what() << std::endl;
        }

    } while (continuer);

    return 0;
}
