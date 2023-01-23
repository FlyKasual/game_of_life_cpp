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

#include <iostream>
#include <memory>
#include "Domain/Model/Cell/Cell.hpp"
#include "Domain/Model/CellularAutomaton/CellularAutomaton.hpp"
#include "Domain/Model/CellularAutomatonPrinter/CellularAutomatonPrinter.hpp"
#include "Domain/Model/Rule/Rule.hpp"
#include "Domain/Model/Rule/LambdaBasedRule.hpp"

int main() {
  CellularAutomaton c;
  CellularAutomatonPrinter cp{c};

  std::cout << cp << "--------------------------------------------------\n" << std::endl;

  LambdaBasedRule killEverything{
      [](const Cell& c, const CellularAutomaton& aut) {
          return Cell::State::DEAD;
      },
      []() { return true; }
  };

  bool force = false;
  Cell::State forcedState = Cell::State::ALIVE;

  LambdaBasedRule forceEveryThingToLiveAfter10Generations{
      [&forcedState, &force](const Cell& c, const CellularAutomaton& aut) {
          if (aut.getIteration() >= 10) {
              force = true;
          }
          return forcedState;
      },
      [&force]() {
          return force;
      }
  };

  c
    .addRule(std::make_shared<LambdaBasedRule>(forceEveryThingToLiveAfter10Generations))
    .addRule(std::make_shared<LambdaBasedRule>(killEverything));

  int i = 0;

  while (i < 14) {
    c.update();
    std::cout << cp << "--------------------------------------------------\n" << std::endl;
    ++i;
  }

  return 0;
}
