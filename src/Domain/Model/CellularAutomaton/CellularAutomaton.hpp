#ifndef __CELLULAR_AUTOMATON_H
#define __CELLULAR_AUTOMATON_H

#include <vector>
#include <memory>
#include "../Cell/Cell.hpp"
#include "../Rule/Rule.hpp"

class CellularAutomaton {
protected:
  std::size_t width_;
  std::size_t height_;
  std::vector<std::vector<Cell>> grid_;
  std::size_t iteration_ = 0;
  std::vector<std::shared_ptr<IRule>> rules;

  std::vector<std::vector<Cell::State>> getNewStates();
  void applyNewStates(const std::vector<std::vector<Cell::State>>& newStates);
public:
  CellularAutomaton(std::size_t width = 40, std::size_t height = 40);

  std::size_t getWidth() const {
    return width_;
  }

  std::size_t getHeight() const {
    return height_;
  }

  std::vector<std::vector<Cell>> getGrid() const {
    return grid_;
  }

  std::size_t getIteration() const {
    return iteration_;
  }

  CellularAutomaton& addRule(std::shared_ptr<IRule>);
  void update();
};

#endif
