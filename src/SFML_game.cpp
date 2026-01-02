#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include <vector>
#include <string> // For std::to_string
#include <iomanip> // For formatting time
#include <sstream>
#include "maze.hpp"
#include "solver.hpp"

void display(const Maze& maze) {
    std::size_t nbrow = maze.rows();
    std::size_t nbcol = maze.cols();

    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 800; // Keeping your original window size

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Game");

    // --- Layout adjustment ---
    const float timerSpace = 30.0f; // Height of the timer area
    const float marge = 40.0f;      // Your original margin
    
    float availableWidth = windowWidth - 2.0f * marge;
    // We subtract timerSpace so the maze shrinks slightly to fit the text above it
    float availableHeight = windowHeight - 2.0f * marge - timerSpace;

    float maxDim = static_cast<float>(std::max(nbrow, nbcol));
    float cellWidth = availableWidth / maxDim;
    float cellHeight = availableHeight / maxDim;
    float wallEpaisseur = std::max(1.0f, std::min(3.0f, cellWidth * 0.1f));

    // The maze starts exactly at 'marge' horizontally, 
    // but moves down by 'timerSpace' vertically.
    float startX = marge;
    float startY = marge + timerSpace;

    // --- State & Timer Setup ---
    std::size_t playerR = 0;
    std::size_t playerC = 0;

    sf::Font font;
    bool fontLoaded = font.openFromFile("arial.ttf");
    sf::Text statusText(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::Black);
    // Position text in the margin/timerSpace area
    statusText.setPosition({marge, 10.0f}); 

    sf::Clock gameClock;
    bool timerStarted = false;
    bool gameFinished = false;
    float finalTime = 0.0f;

    std::vector<std::pair<std::size_t, std::size_t>> playerTrail;
    playerTrail.push_back({playerR, playerC});

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
                std::size_t oldR = playerR;
                std::size_t oldC = playerC;

                if (code == sf::Keyboard::Key::Escape) window.close();
                else if (code == sf::Keyboard::Key::H) {
                    showSolution = !showSolution;
                    solutionPath = solver.solveAStar();
                }
                
                if (!gameFinished) {
                    if (code == sf::Keyboard::Key::Up && playerR > 0) {
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
                }

                if (playerR != oldR || playerC != oldC) {
                    playerTrail.push_back({playerR, playerC});
                    if (!timerStarted) {
                        timerStarted = true;
                        gameClock.restart();
                    }
                    if (playerR == nbrow - 1 && playerC == nbcol - 1 && !gameFinished) {
                        gameFinished = true;
                        finalTime = gameClock.getElapsedTime().asSeconds();
                    }
                }
            }
        }

        // Timer Text logic (French)
        if (fontLoaded) {
            if (!timerStarted) {
                statusText.setString("Le chrono commence quand vous demarrez");
            } else if (!gameFinished) {
                std::stringstream ss;
                ss << "Temps : " << std::fixed << std::setprecision(1) << gameClock.getElapsedTime().asSeconds() << "s";
                statusText.setString(ss.str());
            } else {
                std::stringstream ss;
                ss << "BRAVO ! Temps final : " << std::fixed << std::setprecision(2) << finalTime << "s";
                statusText.setString(ss.str());
                statusText.setFillColor(sf::Color(0, 150, 0)); 
            }
        }

        window.clear(sf::Color::White);
        if (fontLoaded) window.draw(statusText);

        // 1. Draw frame (now using startX and startY)
        sf::RectangleShape cadre({cellWidth * nbcol, cellHeight * nbrow});
        cadre.setPosition({startX, startY});
        cadre.setFillColor(sf::Color::White);
        cadre.setOutlineThickness(2.0f);
        cadre.setOutlineColor(sf::Color::Black);
        window.draw(cadre);

        // 2. Draw entrance/exit
        sf::RectangleShape startRect({cellWidth, cellHeight});
        startRect.setPosition({startX, startY});
        startRect.setFillColor(sf::Color(200, 255, 200));
        window.draw(startRect);

        sf::RectangleShape endRect({cellWidth, cellHeight});
        endRect.setPosition({startX + (nbcol - 1) * cellWidth, startY + (nbrow - 1) * cellHeight});
        endRect.setFillColor(sf::Color(255, 200, 200));
        window.draw(endRect);

        // 3. Draw Trail
        sf::CircleShape trailDot(std::min(cellWidth, cellHeight) * 0.15f);
        trailDot.setFillColor(sf::Color(100, 100, 255, 100));
        trailDot.setOrigin({trailDot.getRadius(), trailDot.getRadius()});
        for (const auto& pos : playerTrail) {
            float x = startX + pos.second * cellWidth + cellWidth / 2.0f;
            float y = startY + pos.first * cellHeight + cellHeight / 2.0f;
            trailDot.setPosition({x, y});
            window.draw(trailDot);
        }

        // 4. Draw Walls
        sf::RectangleShape vWall({wallEpaisseur, cellHeight});
        vWall.setFillColor(sf::Color::Black);
        sf::RectangleShape hWall({cellWidth, wallEpaisseur});
        hWall.setFillColor(sf::Color::Black);

        for (std::size_t r = 0; r < nbrow; ++r) {
            for (std::size_t c = 0; c < nbcol; ++c) {
                float x = startX + c * cellWidth;
                float y = startY + r * cellHeight;
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

        // 5. Solution
        if (showSolution) {
            sf::CircleShape solDot(std::min(cellWidth, cellHeight) * 0.1f);
            solDot.setFillColor(sf::Color(255, 0, 255, 200));
            solDot.setOrigin({solDot.getRadius(), solDot.getRadius()});
            for (auto [r, c] : solutionPath) {
                float x = startX + c * cellWidth + cellWidth / 2.0f;
                float y = startY + r * cellHeight + cellHeight / 2.0f;
                solDot.setPosition({x, y});
                window.draw(solDot);
            }
        }

        // 6. Draw player
        float radius = std::min(cellWidth, cellHeight) * 0.35f;
        sf::CircleShape player(radius);
        player.setOrigin({radius, radius});
        player.setPosition({startX + playerC * cellWidth + cellWidth / 2.0f,
                            startY + playerR * cellHeight + cellHeight / 2.0f});
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
