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

#include <iostream>
#include <memory>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "Cell.hpp"
#include "CellularAutomaton.hpp"
#include "CellularAutomatonPrinter.hpp"
#include "Rule.hpp"
#include "LambdaBasedRule.hpp"
#include "TorusTopology.hpp"
#include "KleinBottleTopology.hpp"
#include "ConwaysRule.hpp"

int main() {
  KleinBottleTopology top;
  CellularAutomaton c{top, 40, 80};
  CellularAutomatonPrinter cp{c};

  // LambdaBasedRule killEverything{
  //     [](const Cell& c, const CellularAutomaton& aut) {
  //         return Cell::DEAD;
  //     },
  //     []() { return true; }
  // };

  // bool force = false;
  // Cell::State forcedState = Cell::ALIVE;

  // LambdaBasedRule forceEveryThingToLiveAfter10Generations{
  //     [&forcedState, &force](const Cell& c, const CellularAutomaton& aut) {
  //         if (aut.getIteration() >= 10) {
  //             force = true;
  //         }
  //         return forcedState;
  //     },
  //     [&force]() {
  //         return force;
  //     }
  // };

  c.addRule(std::make_shared<ConwaysRule>());
    // .addRule(std::make_shared<LambdaBasedRule>(forceEveryThingToLiveAfter10Generations))
    // .addRule(std::make_shared<LambdaBasedRule>(killEverything));

  std::cout << cp;
  while (true) {
    c.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(100 / 6));
    system("clear"); //FIXME: This is not very portable!
    std::cout << cp;
  }

  return 0;
}
