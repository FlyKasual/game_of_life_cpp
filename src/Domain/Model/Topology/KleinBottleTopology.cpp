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
#include <array>
#include "Topology.hpp"
#include "KleinBottleTopology.hpp"
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"

NeighborStates KleinBottleTopology::getNeighbors(const Cell& c, const CellularAutomaton& ca) const {
  std::array<int, 2> pos{ca.getPosition(c)};
  int n{(pos[0] + ca.getHeight() - 1) % ca.getHeight()};
  int w{(pos[1] + ca.getWidth() - 1) % ca.getWidth()};
  int e{(pos[1] + ca.getWidth() + 1) % ca.getWidth()};
  int s{(pos[0] + ca.getHeight() + 1) % ca.getHeight()};

  return NeighborStates {
    ca.getGrid()->at(pos[1] == 0 ? ca.getHeight() - 1 - n : n).at(w).getState(),
    ca.getGrid()->at(n).at(pos[1]).getState(),
    ca.getGrid()->at(pos[1] == ca.getWidth() - 1 ? ca.getHeight() - 1 - n : n).at(e).getState(),
    ca.getGrid()->at(pos[1] == 0 ? ca.getHeight() - 1 - pos[0] : pos[0]).at(w).getState(),
    ca.getGrid()->at(pos[1] == ca.getWidth() - 1 ? ca.getHeight() - 1 - pos[0] : pos[0]).at(e).getState(),
    ca.getGrid()->at(pos[1] == 0 ? ca.getHeight() - 1 - s : s).at(w).getState(),
    ca.getGrid()->at(s).at(pos[1]).getState(),
    ca.getGrid()->at(pos[1] == ca.getWidth() - 1 ? ca.getHeight() - 1 - s : s).at(e).getState()
  };
}
