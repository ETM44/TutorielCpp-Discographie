#include "utils.hpp"

#include <algorithm>

std::string traitement_chaine(std::string const & chaine)
{
    std::string copie { chaine };

    auto premier_non_espace { std::find_if_not(std::begin(copie), std::end(copie), isspace) };
    copie.erase(std::begin(copie), premier_non_espace);

    std::reverse(std::begin(copie), std::end(copie));
    premier_non_espace = std::find_if_not(std::begin(copie), std::end(copie), isspace);
    copie.erase(std::begin(copie), premier_non_espace);
    std::reverse(std::begin(copie), std::end(copie));

    return copie;
}

std::string traitement_chaine_digit_alpha(std::string const & chaine)
{
   std::string copie { chaine };

    auto premier_non_espace { std::find_if(std::begin(copie), std::end(copie), [](char carac)
        {
            return (carac >= 'a' && carac <= 'z') || (carac >= 'A' && carac <= 'Z') || (carac >= '0' && carac <= '9' || carac == '_');
        })};
    copie.erase(std::begin(copie), premier_non_espace);
    std::reverse(std::begin(copie), std::end(copie));

    premier_non_espace = std::find_if(std::begin(copie), std::end(copie), [](char carac)
    {
        return (carac >= 'a' && carac <= 'z') || (carac >= 'A' && carac <= 'Z') || (carac >= '0' && carac <= '9');
    });
    copie.erase(std::begin(copie), premier_non_espace);
    std::reverse(std::begin(copie), std::end(copie));

    return copie;
}

std::string traitement_chaine_guillemets(std::string const & chaine)
{
   std::string copie { chaine };

    auto premier_non_espace { std::find_if(std::begin(copie), std::end(copie), [](char carac)
        {
            return carac != '"';
        })};
    copie.erase(std::begin(copie), premier_non_espace);
    std::reverse(std::begin(copie), std::end(copie));

    premier_non_espace = std::find_if(std::begin(copie), std::end(copie), [](char carac)
    {
        return carac != '"';
    });
    copie.erase(std::begin(copie), premier_non_espace);
    std::reverse(std::begin(copie), std::end(copie));

    return copie;
}
