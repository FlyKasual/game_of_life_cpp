#ifndef __CELLULAR_AUTOMATON_PRINTER_H
#define __CELLULAR_AUTOMATON_PRINTER_H

#include <iostream>
#include "../CellularAutomaton/CellularAutomaton.hpp"

class CellularAutomatonPrinter {
protected:
  CellularAutomaton& ca;
public:
  CellularAutomatonPrinter() = delete;
  CellularAutomatonPrinter(CellularAutomaton& ca_) : ca(ca_) {};

  friend std::ostream& operator<<(std::ostream&, const CellularAutomatonPrinter&);
};

#endif
