#include <random>
#include <memory>
#include "CellularAutomaton.hpp"
#include "../Rule/Rule.hpp"

CellularAutomaton::CellularAutomaton(std::size_t width, std::size_t height): width_(width), height_(height) {
  grid_.resize(height_);
  for (auto row : grid_) {
    row.resize(width_);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  for (std::size_t i = 0; i < height_; ++i) {
    for (std::size_t j = 0; j < width_; ++j) {
      std::uniform_int_distribution<> distr(0, 100);
      Cell::State state{ distr(gen) > 90 ? Cell::State::ALIVE : Cell::State::DEAD };
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
  for (std::size_t i = 0; i < height_; ++i) {
    newStates.push_back(std::vector<Cell::State>());
    newStates.at(i).resize(width_);
    for (std::size_t j = 0; j < width_; ++j) {
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
  for (std::size_t i = 0; i < height_; ++i) {
    for (std::size_t j = 0; j < width_; ++j) {
      grid_.at(i).at(j).setState(newStates.at(i).at(j));
    }
  }
};

void CellularAutomaton::update() {
  auto newStates = getNewStates();
  applyNewStates(newStates);
  ++iteration_;
}
