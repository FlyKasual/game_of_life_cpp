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
#include <random>
#include <memory>
#include <array>
#include <map>
#include "CellularAutomaton.hpp"
#include "../Rule/Rule.hpp"
#include "../Topology/Topology.hpp"

CellularAutomaton::CellularAutomaton(ITopology& topology, int width, int height): topology_(topology), width_(width), height_(height) {
  grid_ = std::make_shared<std::vector<std::vector<Cell>>>(
    std::vector<std::vector<Cell>>(
      height,
      std::vector<Cell>(width)
    )
  );
  tmpGrid_ = std::make_shared<std::vector<std::vector<Cell>>>(
    std::vector<std::vector<Cell>>(
      height,
      std::vector<Cell>(
        width,
        Cell{Cell::State::DEAD}
      )
    )
  );
  std::random_device rd;
  std::mt19937 gen(rd());

  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      std::uniform_int_distribution<> distr(0, 100);
      Cell::State state{ distr(gen) > 90 ? Cell::State::ALIVE : Cell::State::DEAD };
      grid_->at(i).at(j).setState(state);
      positionCache_[&grid_->at(i).at(j)] = std::array{i, j};
      positionCache_[&tmpGrid_->at(i).at(j)] = std::array{i, j};
    }
  }
}

CellularAutomaton& CellularAutomaton::addRule(std::shared_ptr<IRule> rule) {
  rules.push_back(rule);
  return *this;
}

void CellularAutomaton::update() {
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      for (auto& rule : rules) {
        tmpGrid_->at(i).at(j).setState(
          (*rule).apply(grid_->at(i).at(j), *this)
        );

        if ((*rule).enforce() == true) {
          break;
        }
      }
    }
  }
  grid_.swap(tmpGrid_);
  ++iteration_;
}

NeighborStates CellularAutomaton::getNeighborStates(const Cell& cell) const {
  return topology_.getNeighbors(cell, *this);
}

std::array<int, 2> CellularAutomaton::getPosition(const Cell& c) const {
  auto position{positionCache_.find(&c)};
  if (position != positionCache_.end())
    return position->second;

  // TODO: Should we throw here if c is not in this automaton?
  return std::array{-1, -1};
}
