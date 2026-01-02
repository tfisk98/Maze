/**
 * \file SFML_orig.cpp
 * \brief Affichage graphique du labyrinthe via SFML
 * \author Thomas Burns & Thomas Fisk
 * \version 0.2
 * \date 23/12/2025
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include "maze.hpp"

int main() {
    std::size_t nbrow, nbcol;
    std::cout << "Enter number of rows: ";
    std::cin >> nbrow;
    std::cout << "Enter number of columns: ";
    std::cin >> nbcol;

    Maze maze(nbrow, nbcol);
    maze.generate();

    const unsigned int windowWidth  = 800;
    const unsigned int windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Viewer");

    // --- Layout ---
    const float marge = 40.0f;

    float availableWidth  = windowWidth  - 2.0f * marge;
    float availableHeight = windowHeight - 2.0f * marge;

    float maxDim = static_cast<float>(std::max(nbrow, nbcol));
    float cellWidth  = availableWidth  / maxDim;
    float cellHeight = availableHeight / maxDim;

    float wallEpaisseur = std::max(1.0f, std::min(3.0f, std::min(cellWidth, cellHeight) * 0.15f));

    // Origine du dessin du labyrinthe
    float startX = marge;
    float startY = marge;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
            }
        }

        window.clear(sf::Color::White);

        // --- Frame / Cadre (corrigé) ---
        // Le cadre correspond exactement aux dimensions du labyrinthe dessiné :
        // nbcol cellules en largeur, nbrow cellules en hauteur.
        sf::RectangleShape cadre({cellWidth * nbcol, cellHeight * nbrow});
        cadre.setPosition({startX, startY});
        cadre.setFillColor(sf::Color::White);
        cadre.setOutlineThickness(2.0f);
        cadre.setOutlineColor(sf::Color::Black);
        window.draw(cadre);

        // --- Entrance (Top-Left) ---
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({startX, startY});
        startRect.setFillColor(sf::Color::Green);
        window.draw(startRect);

        // --- Exit (Bottom-Right) ---
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({startX + (nbcol - 1) * cellWidth, startY + (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // --- Wall shapes ---
        sf::RectangleShape vWall({wallEpaisseur, cellHeight});
        vWall.setFillColor(sf::Color::Black);

        sf::RectangleShape hWall({cellWidth, wallEpaisseur});
        hWall.setFillColor(sf::Color::Black);

        // --- Draw maze walls ---
        for (std::size_t r = 0; r < nbrow; ++r) {
            for (std::size_t c = 0; c < nbcol; ++c) {
                float x = startX + c * cellWidth;
                float y = startY + r * cellHeight;
                const Cell &cell = maze(r, c);

                // LEFT WALL
                // Draw if wall char OR left boundary (except entrance)
                if (cell.left == '|' || (c == 0 && !(r == 0 && c == 0))) {
                    vWall.setPosition({x, y});
                    window.draw(vWall);
                }

                // TOP WALL (boundary for first row)
                if (r == 0) {
                    hWall.setPosition({x, y});
                    window.draw(hWall);
                }

                // BOTTOM WALL
                // Draw if '_' except at exit cell (open)
                if (cell.bot == '_' && !(r == nbrow - 1 && c == nbcol - 1)) {
                    hWall.setPosition({x, y + cellHeight - wallEpaisseur});
                    window.draw(hWall);
                }

                // RIGHT WALL (boundary for last column)
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth - wallEpaisseur, y});
                    window.draw(vWall);
                }
            }
        }

        window.display();
    }

    return 0;
}

