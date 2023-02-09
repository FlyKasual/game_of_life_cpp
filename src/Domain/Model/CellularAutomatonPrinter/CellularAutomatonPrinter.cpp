/*!
 * @copyright
 * Copyright 2023 Johannes Nielsen <flykasual@gmail.com>
 */
/*!
 * This file is part of the game_of_life_cpp project.
 *
 * The game_of_life_cpp project is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * The game_of_life_cpp project is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with the game_of_life_cpp project. If not, see <https://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "../CellularAutomatonPrinter/CellularAutomatonPrinter.hpp"
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"

std::ostream& operator<<(std::ostream &os, const CellularAutomatonPrinter& cap) {
  for (const auto& row : *(cap.ca.getGrid())) {
    for (const auto& cell : row) {
      switch (cell.getState()) {
        case Cell::ALIVE:
          os << "*";
          break;
        case Cell::DEAD:
          os << " ";
          break;
        default:
          os << " ";
      }
    }
    os << '\n';
  }
  os << cap.ca.getIteration()<< '\n';
  return os;
}
