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
#ifndef __CELLULAR_AUTOMATON_H
#define __CELLULAR_AUTOMATON_H

#include <vector>
#include <memory>
#include <array>
#include "../Cell/Cell.hpp"
#include "../Rule/Rule.hpp"
#include "../Topology/Topology.hpp"

class CellularAutomaton {
protected:
  ITopology& topology_;
  int width_;
  int height_;
  std::vector<std::vector<Cell>> grid_;
  int iteration_ = 0;
  std::vector<std::shared_ptr<IRule>> rules;

  std::vector<std::vector<Cell::State>> getNewStates();
  void applyNewStates(const std::vector<std::vector<Cell::State>>& newStates);
public:
  CellularAutomaton(ITopology&, int width = 40, int height = 40);

  int getWidth() const {
    return width_;
  }

  int getHeight() const {
    return height_;
  }

  std::vector<std::vector<Cell>> getGrid() const {
    return grid_;
  }

  int getIteration() const {
    return iteration_;
  }

  NeighborStates getNeighborStates(const Cell&) const;

  CellularAutomaton& addRule(std::shared_ptr<IRule>);
  void update();
  std::array<int, 2> getPosition(const Cell&) const;
};

#endif
