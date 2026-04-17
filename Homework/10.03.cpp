#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


class GameOfLife {
public:
    GameOfLife(size_t width, size_t height)
        : m_width(width), m_height(height),
          m_grid(height, std::vector<bool>(width, false)) {}

    void setInitialPattern() {
        if (m_height >= 3 && m_width >= 3) {
            m_grid[1][1] = true;
            m_grid[2][1] = true;
            m_grid[3][1] = true;
        }
    }

    void clear_console() {
        std::cout << "\033[2J\033[1;1H";
    }

    void printBoard() const {
        clear_console()
        for (auto i = 0uz; i < m_height; ++i) {
            for (auto j = 0uz; j < m_width; ++j) {
                std::cout << (m_grid[i][j] ? '*' : '.');
            }
            std::cout << std::endl;
        }
    }

    void nextGeneration() {
        std::vector<std::vector<bool>> next_grid = m_grid;

        for (auto i = 0uz; i < m_height; ++i) {
            for (auto j = 0uz; j < m_width; ++j) {
                int live_neighbors = countLiveNeighbors(i, j);

                if (m_grid[i][j]) {
                    if (live_neighbors < 2 || live_neighbors > 3) {
                        next_grid[i][j] = false;
                    }
                } else {
                    if (live_neighbors == 3) {
                        next_grid[i][j] = true;
                    }
                }
            }
        }
        m_grid = next_grid;
    }

private:
    int countLiveNeighbors(size_t row, size_t col) const {
        int count = 0;
        for (long i = -1; i <= 1; ++i) {
            for (long j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;

                long neighbor_row = row + i;
                long neighbor_col = col + j;

                if (neighbor_row >= 0 && neighbor_row < m_height &&
                    neighbor_col >= 0 && neighbor_col < m_width) {
                    if (m_grid[neighbor_row][neighbor_col]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    size_t m_width;
    size_t m_height;
    std::vector<std::vector<bool>> m_grid;
};

int main() {
    const size_t width = 10;
    const size_t height = 10;
    const int generations = 100;

    GameOfLife game(width, height);
    game.setInitialPattern();

    for (int i = 0; i < generations; ++i) {
        game.printBoard();
        std::cout << "Generation: " << i + 1 << std::endl;
        game.nextGeneration();
        std::this_thread::sleep_for(600ms);
    }

    return 0;
}
