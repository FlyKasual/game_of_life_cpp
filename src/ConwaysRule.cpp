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
#include "ConwaysRule.hpp"
#include "Cell.hpp"
#include "CellularAutomaton.hpp"


Cell::State ConwaysRule::apply(const Cell& c, const CellularAutomaton& aut) {
  NeighborStates ns = aut.getNeighborStates(c);
  int numberOfLivingNeighbors = 0;
  if (ns.NW == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.N == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.NE == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.W == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.E == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.SW == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.S == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.SE == Cell::ALIVE)
    ++numberOfLivingNeighbors;
  if (numberOfLivingNeighbors == 3)
    return Cell::ALIVE;
  if (c.getState() == Cell::ALIVE && numberOfLivingNeighbors == 2) {
    return Cell::ALIVE;
  }
  return Cell::DEAD;
}
