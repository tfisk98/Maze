#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "maze.hpp"


void display(Maze& const maze){
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Viewer");

    float cellWidth  = static_cast<float>(windowWidth) / maze;
    float cellHeight = static_cast<float>(windowHeight) / maze;
    
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

        // Draw Green Entrance (Top-Left)
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({0.f, 0.f});
        startRect.setFillColor(sf::Color::Green);
        window.draw(startRect);

	// Draw Red Exit (Bottom-Right)
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({(nbcol - 1) * cellWidth, (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Draw Walls
        sf::RectangleShape vWall({2.f, cellHeight}); // Vertical Wall
        vWall.setFillColor(sf::Color::Black);

        sf::RectangleShape hWall({cellWidth, 2.f}); // Horizontal Wall
        hWall.setFillColor(sf::Color::Black);

	for (std::size_t r = 0; r < nbrow; ++r) {
                // Draw Red Exit (Bottom-Right)
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({(nbcol - 1) * cellWidth, (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Draw Walls
        sf::RectangleShape vWall({2.f, cellHeight}); // Vertical Wall
        vWall.setFillColor(sf::Color::Black);

        sf::RectangleShape hWall({cellWidth, 2.f}); // Horizontal Wall
        hWall.setFillColor(sf::Color::Black);

	for (std::size_t c = 0; c < nbcol; ++c) {
                float x = c * cellWidth;
                float y = r * cellHeight;
                const Cell &cell = maze(r, c);

                // --- LEFT WALL ---
                // Draw if it is a wall char AND it's not the entrance at 0,0
                if (cell.left == '|') {
                    if (!(r == 0 && c == 0)) {
                        vWall.setPosition({x, y});
                        window.draw(vWall);
                    }
                }
                // Always draw left boundary if not column 0 (handled by cell.left usually) 
                // but strictly: boundary is column 0.
                else if (c == 0 && !(r == 0 && c == 0)) {
                     vWall.setPosition({x, y});
                     window.draw(vWall);
                } sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({(nbcol - 1) * cellWidth, (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Draw Walls
        sf::RectangleShape vWall({2.f, cellHeight}); // Vertical Wall
        vWall.setFillColor(sf::Color::Black);

        sf::RectangleShape hWall({cellWidth, 2.f}); // Horizontal Wall
        hWall.setFillColor(sf::Color::Black);



                // --- TOP WALL ---
                // Draw top boundary for first row
                if (r == 0) {
                     hWall.setPosition({x, y});
                     window.draw(hWall);
                }

                // --- BOTTOM WALL ---
                if (cell.bot == '_') {
                    // Don't draw bottom wall for Exit
                    if (!(r == nbrow - 1 && c == nbcol - 1)) {
                        hWall.setPosition({x, y + cellHeight});
                        window.draw(hWall);
                    }
                }

                // --- RIGHT WALL ---
                // Draw right boundary for last column
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth, y});
                    window.draw(vWall);
                }
            }
        }
	window.display();


}

int main() {
    std::size_t nbrow, nbcol;
    std::cout << "Enter number of rows: ";
    std::cin >> nbrow;
    std::cout << "Enter number of columns: ";
    std::cin >> nbcol;

    Maze maze(nbrow, nbcol);
    maze.generate();

    display();
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Viewer");

    const unsigned int M = max(nbcol, nbrow);

    float cellWidth  = static_cast<float>(windowWidth) / max(nbcol,nbrow);
    float cellHeight = static_cast<float>(windowHeight) / max(nbcol,nbrow);

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

        // Draw Green Entrance (Top-Left)
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({0.f, 0.f});
        startRect.setFillColor(sf::Color::Green);
        window.draw(startRect);

        // Draw Red Exit (Bottom-Right)
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({(nbcol - 1) * cellWidth, (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Draw Walls
        sf::RectangleShape vWall({2.f, cellHeight}); // Vertical Wall
        vWall.setFillColor(sf::Color::Black);
        
        sf::RectangleShape hWall({cellWidth, 2.f}); // Horizontal Wall
        hWall.setFillColor(sf::Color::Black);

        for (std::size_t r = 0; r < nbrow; ++r) {
                // Draw Red Exit (Bottom-Right)
        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({(nbcol - 1) * cellWidth, (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color::Red);
        window.draw(endRect);

        // Draw Walls
        sf::RectangleShape vWall({2.f, cellHeight}); // Vertical Wall
        vWall.setFillColor(sf::Color::Black);

        sf::RectangleShape hWall({cellWidth, 2.f}); // Horizontal Wall
        hWall.setFillColor(sf::Color::Black);

    for (std::size_t c = 0; c < nbcol; ++c) {
                float x = c * cellWidth;
                float y = r * cellHeight;
                const Cell &cell = maze(r, c);

                // --- LEFT WALL ---
                // Draw if it is a wall char AND it's not the entrance at 0,0
                if (cell.left == '|') {
                    if (!(r == 0 && c == 0)) { 
                        vWall.setPosition({x, y});
                        window.draw(vWall);
                    }
                } 
                // Always draw left boundary if not column 0 (handled by cell.left usually) 
                // but strictly: boundary is column 0.
                else if (c == 0 && !(r == 0 && c == 0)) {
                     vWall.setPosition({x, y});
                     window.draw(vWall);
                }


                // --- TOP WALL ---
                // Draw top boundary for first row
                if (r == 0) {
                     hWall.setPosition({x, y});
                     window.draw(hWall);
                }

                // --- BOTTOM WALL ---
                if (cell.bot == '_') {
                    // Don't draw bottom wall for Exit
                    if (!(r == nbrow - 1 && c == nbcol - 1)) {
                        hWall.setPosition({x, y + cellHeight});
                        window.draw(hWall);
                    }
                }

                // --- RIGHT WALL ---
                // Draw right boundary for last column
                if (c == nbcol - 1) {
                    vWall.setPosition({x + cellWidth, y});
                    window.draw(vWall);
                }
            }
        }

        window.display();
    }
    return 0;
}
