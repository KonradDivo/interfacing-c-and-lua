#include <iostream>
extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

int main() {
    // 1. Initialisation de l'état de la machine virtuelle Lua
    lua_State* L = luaL_newstate();
    luaL_openlibs(L); // Charger les bibliothèques standards de Lua (print, math, etc.)

    // 2. Charger et exécuter le fichier Lua
    if (luaL_dofile(L, "config.lua") != LUA_OK) {
        std::cerr << "[-] Erreur lors du chargement de config.lua : " 
                  << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    // --- EXEMPLE 1 : Lire des variables globales Lua depuis le C++ ---
    lua_getglobal(L, "drone_name"); // Pousse la variable sur la pile
    lua_getglobal(L, "max_altitude"); 

    if (lua_isstring(L, -2) && lua_isnumber(L, -1)) {
        std::string name = lua_tostring(L, -2);
        int alt = lua_tointeger(L, -1);
        std::cout << "[C++] Données lues depuis Lua -> Nom: " << name << " | Alt Max: " << alt << "m\n\n";
    }
    lua_pop(L, 2); // Nettoyer la pile (retirer les 2 éléments)


    // --- EXEMPLE 2 : Appeler une fonction Lua depuis le C++ ---
    lua_getglobal(L, "calculate_thrust"); // 1. Récupérer la fonction Lua

    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, 2.5);  // 2. Pousser le 1er argument (Poids = 2.5 kg)
        lua_pushnumber(L, 9.81); // 3. Pousser le 2e argument  (Gravité = 9.81)

        // 4. Exécuter l'appel : 2 arguments, 1 résultat attendu, 0 pour la gestion d'erreur personnalisée
        if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
            std::cerr << "[-] Erreur d'exécution de la fonction Lua\n";
        } else {
            // 5. Récupérer le résultat au sommet de la pile (index -1)
            double thrust = lua_tonumber(L, -1);
            std::cout << "[C++] Résultat retourné par Lua -> Poussée totale requise : " << thrust << " Newtons.\n";
            lua_pop(L, 1); // Nettoyer le résultat
        }
    }

    // 3. Fermeture propre de la VM Lua
    lua_close(L);
    return 0;
}
