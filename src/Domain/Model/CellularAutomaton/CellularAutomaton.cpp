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
#include <random>
#include <memory>
#include <array>
#include "CellularAutomaton.hpp"
#include "../Rule/Rule.hpp"
#include "../Topology/Topology.hpp"

CellularAutomaton::CellularAutomaton(ITopology& topology, int width, int height): topology_(topology), width_(width), height_(height) {
  grid_.resize(height_);
  for (auto row : grid_) {
    row.resize(width_);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      std::uniform_int_distribution<> distr(0, 100);
      Cell::State state{ distr(gen) > 99 ? Cell::State::ALIVE : Cell::State::DEAD };
      grid_.at(i).push_back(Cell{ state });
    }
  }
}

CellularAutomaton& CellularAutomaton::addRule(std::shared_ptr<IRule> rule) {
  rules.push_back(rule);
  return *this;
}

std::vector<std::vector<Cell::State>> CellularAutomaton::getNewStates() {
  std::vector<std::vector<Cell::State>> newStates;
  newStates.resize(height_);
  for (int i = 0; i < height_; ++i) {
    newStates.push_back(std::vector<Cell::State>());
    newStates.at(i).resize(width_);
    for (int j = 0; j < width_; ++j) {
      for (auto& rule : rules) {
        newStates.at(i).at(j) = (*rule).apply(grid_.at(i).at(j), *this);

        if ((*rule).enforce() == true) {
          break;
        }
      }
    }
  }

  return newStates;
}

void CellularAutomaton::applyNewStates(const std::vector<std::vector<Cell::State>>& newStates) {
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      grid_.at(i).at(j).setState(newStates.at(i).at(j));
    }
  }
};

void CellularAutomaton::update() {
  auto newStates = getNewStates();
  applyNewStates(newStates);
  ++iteration_;
}

NeighborStates CellularAutomaton::getNeighborStates(const Cell& cell) const {
  return topology_.getNeighbors(cell, *this);
}

std::array<int, 2> CellularAutomaton::getPosition(const Cell& c) const {
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      if (&grid_.at(i).at(j) == &c)
        return std::array{i, j};
    }
  }

  // TODO: Should we throw here if c is not in this automaton?
  return std::array{-1, -1};
}
