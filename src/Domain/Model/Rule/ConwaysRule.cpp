/*!
 * @copyright
 * Copyright 2023 Johannes Nielsen <flykasual@gmail.com
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
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"


Cell::State ConwaysRule::apply(const Cell& c, const CellularAutomaton& aut) {
  NeighborStates ns = aut.getNeighborStates(c);
  int numberOfLivingNeighbors = 0;
  if (ns.NW == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.N == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.NE == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.W == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.E == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.SW == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.S == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (ns.SE == Cell::State::ALIVE)
    ++numberOfLivingNeighbors;
  if (numberOfLivingNeighbors == 3)
    return Cell::State::ALIVE;
  if (c.getState() == Cell::State::ALIVE && numberOfLivingNeighbors == 2) {
    return Cell::State::ALIVE;
  }
  return Cell::State::DEAD;
}