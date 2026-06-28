-- Configuration du drone lue par le C++
drone_name = "Quad_Pro_2026"
max_altitude = 150

-- Fonction appelée par le C++ pour calculer la poussée des moteurs
-- Poids en kg, facteur de gravité (ex: 9.81)
function calculate_thrust(weight, gravity)
    local safety_factor = 1.2
    local total_force = weight * gravity * safety_factor
    print("[Lua] Calcul de la poussée requis pour " .. weight .. "kg...")
    return total_force -- Renvoyé sur la pile pour le C++
end
