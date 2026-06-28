#include <iostream>
#define SOL_ALL_SAFETIES_ON 1 // Active les vérifications de sécurité strictes de Sol2
#include <sol/sol.hpp>        // La bibliothèque Sol2

int main() {
    // 1. Initialisation de la machine virtuelle Lua avec Sol2
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math); // Ouvre les bibliothèques de base

    // 2. Charger le fichier de configuration de manière sécurisée
    auto load_result = lua.script_file("config.lua");
    if (!load_result.valid()) {
        sol::error err = load_result;
        std::cerr << "[-] Erreur de chargement Lua : " << err.what() << std::endl;
        return 1;
    }

    // --- EXEMPLE 1 : Lire des variables globales de manière intuitive ---
    // Sol2 surcharge l'opérateur [] pour accéder aux variables comme dans une Map/Dictionnaire
    std::string name = lua["drone_name"];
    int alt = lua["max_altitude"];
    
    std::cout << "[C++ / Sol2] Donnees lues -> Nom: " << name << " | Alt Max: " << alt << "m\n\n";

    // --- EXEMPLE 2 : Récupérer et exécuter la fonction Lua ---
    // Sol2 convertit automatiquement la fonction Lua en un objet appelable en C++
    sol::protected_function calc_thrust = lua["calculate_thrust"];
    
    if (calc_thrust.valid()) {
        // Appel direct comme une fonction C++ classique, avec gestion des types automatique
        auto result = calc_thrust(2.5, 9.81);
        
        if (result.valid()) {
            double thrust = result; // Conversion implicite sécurisée du résultat
            std::cout << "[C++ / Sol2] Poussee totale requise : " << thrust << " Newtons.\n";
        } else {
            sol::error err = result;
            std::cerr << "[-] Erreur pendant l'execution Lua : " << err.what() << std::endl;
        }
    }

    return 0;
}
