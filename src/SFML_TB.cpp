#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include "maze.hpp"





void display(const Maze& maze) {
    // Get dimensions from the maze object
    std::size_t nbrow = maze.rows();
    std::size_t nbcol = maze.cols();

    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Viewer");

    const float marge = 40.0f;
    float cellWidth = (windowWidth - 2.0f * marge) / nbcol;
    float cellHeight = (windowHeight - 2.0f * marge) / nbrow;
    
    float wallEpaisseur = std::min(3.0f, std::min(cellWidth, cellHeight) * 0.15f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
            }
        }

        window.clear(sf::Color::White);

        // Draw Frame
        sf::RectangleShape cadre({(windowWidth - 2 * marge) + wallEpaisseur, (windowHeight - 2 * marge) + wallEpaisseur});
        cadre.setPosition({marge - wallEpaisseur / 2, marge - wallEpaisseur / 2});
        cadre.setFillColor(sf::Color::White);
        cadre.setOutlineThickness(2.0f);
        cadre.setOutlineColor(sf::Color::Black);
        window.draw(cadre);

        // Draw Green Entrance (Top-Left)
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({marge, marge});
        startRect.setFillColor(sf::Color::Green);
        window.draw(startRect);

        // Draw Red Exit (Bottom-Right)
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({marge + (nbcol - 1) * cellWidth, marge + (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Setup Wall Shapes
        sf::RectangleShape vWall({wallEpaisseur, cellHeight}); 
        vWall.setFillColor(sf::Color::Black);
        
        sf::RectangleShape hWall({cellWidth, wallEpaisseur}); 
        hWall.setFillColor(sf::Color::Black);

        for (std::size_t r = 0; r < nbrow; ++r) {
            for (std::size_t c = 0; c < nbcol; ++c) {
                float x = marge + c * cellWidth;
                float y = marge + r * cellHeight;
                const Cell &cell = maze(r, c);

                // --- LEFT WALL ---
                if (cell.left == '|') {
                    if (!(r == 0 && c == 0)) { 
                        vWall.setPosition({x, y});
                        window.draw(vWall);
                    }
                } 
                else if (c == 0 && !(r == 0 && c == 0)) {
                     vWall.setPosition({x, y});
                     window.draw(vWall);
                }

                // --- TOP WALL ---
                if (r == 0) {
                     hWall.setPosition({x, y});
                     window.draw(hWall);
                }

                // --- BOTTOM WALL ---
                if (cell.bot == '_') {
                    if (!(r == nbrow - 1 && c == nbcol - 1)) {
                        hWall.setPosition({x, y + cellHeight - wallEpaisseur});
                        window.draw(hWall);
                    }
                }

                // --- RIGHT WALL ---
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth - wallEpaisseur, y});
                    window.draw(vWall);
                }
            }
        }

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
