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
#ifndef __GOL_TOPOLOGY_H
#define __GOL_TOPOLOGY_H

#include "../Cell/Cell.hpp"

class CellularAutomaton; // Forward declaration to avoid curcular includes

struct NeighborStates {
  Cell::State NW;
  Cell::State N;
  Cell::State NE;
  Cell::State W;
  Cell::State E;
  Cell::State SW;
  Cell::State S;
  Cell::State SE;
};

class ITopology {
public:
  virtual NeighborStates getNeighbors(const Cell&, const CellularAutomaton&) const = 0;
};

#endif
