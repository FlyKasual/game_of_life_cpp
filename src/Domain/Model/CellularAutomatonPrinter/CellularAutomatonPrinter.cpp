#include <iostream>
#include "../CellularAutomatonPrinter/CellularAutomatonPrinter.hpp"
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"

std::ostream& operator<<(std::ostream &os, const CellularAutomatonPrinter& cap) {
  for (const auto& row : cap.ca.getGrid()) {
    for (const auto& cell : row) {
      switch (cell.getState()) {
        case Cell::State::ALIVE:
          os << "*";
          break;
        case Cell::State::DEAD:
          os << " ";
          break;
        default:
          os << " ";
      }
    }
    os << '\n';
  }
  return os;
}
