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
#include "maze.hpp"
#include "solver.hpp"

void display(const Maze& maze) {
    std::size_t nbrow = maze.rows();
    std::size_t nbcol = maze.cols();

    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Game");
    
    // Load a music to play
    //sf::Music music("nice_music.ogg");
 
    // Play the music
    //music.play();

    const float marge = 40.0f;
    int max = nbrow > nbcol ? nbrow : nbcol;
    float cellWidth = (windowWidth - 2.0f*marge) / max;
    float cellHeight = (windowHeight - 2.0f*marge) / max;
    float wallEpaisseur = std::min(3.0f, std::min(cellWidth, cellHeight) * 0.15f);

    std::size_t playerR = 0;
    std::size_t playerC = 0;

    // --- Solution path ---
    bool showSolution = false;
    std::vector<std::pair<int,int>> solutionPath;
    Solver solver(maze);

    while (window.isOpen()) {
        // --- Event polling (SFML 3 Fixed) ---
        while (const std::optional event = window.pollEvent()) {
            
            // 1. Handle Window Close
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // 2. Handle Key Presses
            // Use getIf to safely retrieve the key event data
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                
                // SFML 3: Keys are in sf::Keyboard::Key enum
                sf::Keyboard::Key code = keyEvent->code;

                // --- Global Keys ---
                if (code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                else if (code == sf::Keyboard::Key::H) {
                    showSolution = !showSolution;
                    //if (showSolution) {
                    solutionPath = solver.solveAStar();
                    //}
                }

                // --- Player Movement ---
                else if (code == sf::Keyboard::Key::Up && playerR > 0) {
                    if (maze(playerR - 1, playerC).bot == ' ') 
                        playerR--;
                }
                else if (code == sf::Keyboard::Key::Down && playerR < nbrow - 1) {
                    if (maze(playerR, playerC).bot == ' ') 
                        playerR++;
                }
                else if (code == sf::Keyboard::Key::Left && playerC > 0) {
                    if (maze(playerR, playerC).left == ' ') 
                        playerC--;
                }
                else if (code == sf::Keyboard::Key::Right && playerC < nbcol - 1) {
                    if (maze(playerR, playerC + 1).left == ' ') 
                        playerC++;
                }
            }
        }

        window.clear(sf::Color::White);

        // --- Draw frame ---
        const float rectWidth = cellWidth*(nbcol + 1) ;
        const float rectHeight = cellHeight*(nbrow + 1) ;
        sf::RectangleShape cadre({(rectWidth - 2*marge) + 4*wallEpaisseur, (rectHeight - 2*marge) + 4*wallEpaisseur});
        cadre.setPosition({marge - wallEpaisseur / 2, marge - wallEpaisseur / 2});
        cadre.setFillColor(sf::Color::White);
        cadre.setOutlineThickness(2.0f);
        cadre.setOutlineColor(sf::Color::Black);
        window.draw(cadre);

        // --- Draw entrance & exit ---
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({marge, marge});
        startRect.setFillColor(sf::Color(200, 255, 200));
        window.draw(startRect);

        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({marge + (nbcol - 1) * cellWidth, marge + (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color(255, 200, 200));
        window.draw(endRect);

        // --- Draw maze walls ---
        sf::RectangleShape vWall({wallEpaisseur, cellHeight});
        vWall.setFillColor(sf::Color::Black);
        sf::RectangleShape hWall({cellWidth, wallEpaisseur});
        hWall.setFillColor(sf::Color::Black);

        for (std::size_t r = 0; r < nbrow; ++r) {
            for (std::size_t c = 0; c < nbcol; ++c) {
                float x = marge + c * cellWidth;
                float y = marge + r * cellHeight;
                const Cell &cell = maze(r, c);

                // LEFT WALL
                if (cell.left == '|') {
                    if (!(r == 0 && c == 0)) {
                        vWall.setPosition({x, y});
                        window.draw(vWall);
                    }
                } else if (c == 0 && !(r == 0 && c == 0)) {
                     vWall.setPosition({x, y});
                     window.draw(vWall);
                }

                // TOP WALL
                if (r == 0) {
                     hWall.setPosition({x, y});
                     window.draw(hWall);
                }

                // BOTTOM WALL
                if (cell.bot == '_') {
                    if (!(r == nbrow - 1 && c == nbcol - 1)) {
                        hWall.setPosition({x, y + cellHeight - wallEpaisseur});
                        window.draw(hWall);
                    }
                }

                // RIGHT WALL
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth - wallEpaisseur, y});
                    window.draw(vWall);
                }
            }
        }

        // --- Draw solution path ---
        if (showSolution) {
            sf::RectangleShape solRect({cellWidth*0.5f, cellHeight*0.5f});
            solRect.setFillColor(sf::Color(255, 0, 255, 150));
            solRect.setOrigin({cellWidth*0.25f, cellHeight*0.25f});

            for (auto [r, c] : solutionPath) {
                float x = marge + c * cellWidth + cellWidth / 2.0f;
                float y = marge + r * cellHeight + cellHeight / 2.0f;
                solRect.setPosition({x, y});
                window.draw(solRect);
            }
        }

        // --- Draw player ---
        float radius = std::min(cellWidth, cellHeight) * 0.375f;
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
