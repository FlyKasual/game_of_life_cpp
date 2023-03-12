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
  CellularAutomaton c{ top, 120, 80 };
  CellularAutomatonPrinter cp{ c };

  std::vector<std::vector<int>> liveSpanMap(
    c.getHeight(),
    std::vector<int>(
      c.getWidth(),
      0
    )
  );

  // bool force = false;
  // int maxAge = 40;

  c
    // .addRule(
    //   std::make_shared<LambdaBasedRule>(
    //     [&liveSpanMap, &force, maxAge](const Cell& c, const CellularAutomaton& aut) {
    //       force = false;
    //       std::array<int, 2> pos{aut.getPosition(c)};
    //       if (c.getState() == Cell::ALIVE) {
    //         ++liveSpanMap[pos[0]][pos[1]];
    //         if (liveSpanMap[pos[0]][pos[1]] >= maxAge) {
    //           force = true;
    //           return Cell::DEAD;
    //         }
    //         return Cell::ALIVE;
    //       }
    //       liveSpanMap[pos[0]][pos[1]] = 0;

    //       return Cell::DEAD;
    //     },
    //     [&force]() {
    //       return force;
    //     }
    //   )
    // )
    .addRule(std::make_shared<ConwaysRule>());

  std::cout << cp;
  while (true) {
    c.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(100 / 6));
    system("clear"); //FIXME: This is not very portable!
    std::cout << cp;
  }

  return EXIT_SUCCESS;
}
