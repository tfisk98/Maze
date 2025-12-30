/**
 * \file SFMLgame.cpp
 * \brief Jeu de resolution du labyrinthe
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Affiche le labyririnthe. L'utilisateur peut tenter de le resoudre en utilisant les flèches du clavier.
 * Affiche la solution lorsque l'utilisateur appuie sur la touche 'h'
 * Quitte l'ecran si l'utilisateur appuie sur la touche 'esc' ou 'echap'
 *
 */





#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include <vector>
#include "maze.hpp"
#include "solver.hpp"


void display(const Maze& maze) {
    std::size_t nbrow = maze.rows();
    std::size_t nbcol = maze.cols();

    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Game");

    const float marge = 40.0f;
    float availableWidth = windowWidth - 2.0f * marge;
    float availableHeight = windowHeight - 2.0f * marge;

    float maxDim = static_cast<float>(std::max(nbrow, nbcol));
    float cellWidth = availableWidth / maxDim;
    float cellHeight = availableHeight / maxDim;
    float wallEpaisseur = std::max(1.0f, std::min(3.0f, cellWidth * 0.1f));

    std::size_t playerR = 0;
    std::size_t playerC = 0;

    // --- Trail tracking ---
    // Store pairs of (row, col) that the player has visited
    std::vector<std::pair<std::size_t, std::size_t>> playerTrail;
    playerTrail.push_back({playerR, playerC}); // Add starting position

    bool showSolution = false;
    std::vector<std::pair<int,int>> solutionPath;
    Solver solver(maze);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                sf::Keyboard::Key code = keyEvent->code;
                
                // Store current position to check if we moved
                std::size_t oldR = playerR;
                std::size_t oldC = playerC;

                if (code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                else if (code == sf::Keyboard::Key::H) {
                    showSolution = !showSolution;
                    solutionPath = solver.solveAStar();
                }
                // Movement logic
                else if (code == sf::Keyboard::Key::Up && playerR > 0) {
                    if (maze(playerR - 1, playerC).bot == ' ') playerR--;
                }
                else if (code == sf::Keyboard::Key::Down && playerR < nbrow - 1) {
                    if (maze(playerR, playerC).bot == ' ') playerR++;
                }
                else if (code == sf::Keyboard::Key::Left && playerC > 0) {
                    if (maze(playerR, playerC).left == ' ') playerC--;
                }
                else if (code == sf::Keyboard::Key::Right && playerC < nbcol - 1) {
                    if (maze(playerR, playerC + 1).left == ' ') playerC++;
                }

                // If position changed, add to trail
                if (playerR != oldR || playerC != oldC) {
                    playerTrail.push_back({playerR, playerC});
                }
            }
        }

        window.clear(sf::Color::White);

        // 1. Draw frame
        sf::RectangleShape cadre({cellWidth * nbcol, cellHeight * nbrow});
        cadre.setPosition({marge, marge});
        cadre.setFillColor(sf::Color::White);
        cadre.setOutlineThickness(2.0f);
        cadre.setOutlineColor(sf::Color::Black);
        window.draw(cadre);

        // 2. Draw entrance/exit
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({marge, marge});
        startRect.setFillColor(sf::Color(200, 255, 200));
        window.draw(startRect);

        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({marge + (nbcol - 1) * cellWidth, marge + (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color(255, 200, 200));
        window.draw(endRect);

        // --- 3. Draw Player Trail ---
        // We draw this before the walls and player so it stays in the background
        sf::CircleShape trailDot(std::min(cellWidth, cellHeight) * 0.15f);
        trailDot.setFillColor(sf::Color(100, 100, 255, 100)); // Transparent blue
        trailDot.setOrigin({trailDot.getRadius(), trailDot.getRadius()});

        for (const auto& pos : playerTrail) {
            float x = marge + pos.second * cellWidth + cellWidth / 2.0f;
            float y = marge + pos.first * cellHeight + cellHeight / 2.0f;
            trailDot.setPosition({x, y});
            window.draw(trailDot);
        }

        // 4. Draw maze walls (same logic as previous fix)
        sf::RectangleShape vWall({wallEpaisseur, cellHeight});
        vWall.setFillColor(sf::Color::Black);
        sf::RectangleShape hWall({cellWidth, wallEpaisseur});
        hWall.setFillColor(sf::Color::Black);

        for (std::size_t r = 0; r < nbrow; ++r) {
            for (std::size_t c = 0; c < nbcol; ++c) {
                float x = marge + c * cellWidth;
                float y = marge + r * cellHeight;
                const Cell &cell = maze(r, c);
                if (cell.left == '|' || (c == 0 && !(r == 0 && c == 0))) {
                    vWall.setPosition({x, y});
                    window.draw(vWall);
                }
                if (r == 0) {
                     hWall.setPosition({x, y});
                     window.draw(hWall);
                }
                if (cell.bot == '_' || (r == nbrow - 1 && !(r == nbrow - 1 && c == nbcol - 1))) {
                    hWall.setPosition({x, y + cellHeight - wallEpaisseur});
                    window.draw(hWall);
                }
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth - wallEpaisseur, y});
                    window.draw(vWall);
                }
            }
        }

        // 5. Draw solution path (Magenta dots)
        if (showSolution) {
            sf::CircleShape solDot(std::min(cellWidth, cellHeight) * 0.1f);
            solDot.setFillColor(sf::Color(255, 0, 255, 200));
            solDot.setOrigin({solDot.getRadius(), solDot.getRadius()});
            for (auto [r, c] : solutionPath) {
                float x = marge + c * cellWidth + cellWidth / 2.0f;
                float y = marge + r * cellHeight + cellHeight / 2.0f;
                solDot.setPosition({x, y});
                window.draw(solDot);
            }
        }

        // 6. Draw player
        float radius = std::min(cellWidth, cellHeight) * 0.35f;
        sf::CircleShape player(radius);
        player.setOrigin({radius, radius});
        player.setPosition({marge + playerC * cellWidth + cellWidth / 2.0f,
                            marge + playerR * cellHeight + cellHeight / 2.0f});
        player.setFillColor(sf::Color::Blue);
        window.draw(player);

        window.display();
    }
}

int main() {
    std::size_t nbrow, nbcol;
    std::cout << "Enter number of rows: ";
    std::cin >> nbrow;
    std::cout << "Enter number of columns: ";
    std::cin >> nbcol;

    Maze maze(nbrow, nbcol);
    maze.generate();

    display(maze);

    return 0;
}
