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
#pragma once

#include <functional>
#include "Rule.hpp"
#include "Cell.hpp"
#include "CellularAutomaton.hpp"

typedef std::function<Cell::State(const Cell&, const CellularAutomaton&)> LambdaRuleFunction;
typedef std::function<bool()> LambdaForceRuleFunction;

class LambdaBasedRule: public IRule
{
protected:
  LambdaRuleFunction application;
  LambdaForceRuleFunction forceRule;

public:
  LambdaBasedRule(LambdaRuleFunction apply): LambdaBasedRule{apply, []() { return false; }} {}
  LambdaBasedRule(
    LambdaRuleFunction apply,
    LambdaForceRuleFunction force
  ): application(apply), forceRule(force) {}

  Cell::State apply(const Cell&, const CellularAutomaton&) override;

  bool enforce() override;
};
