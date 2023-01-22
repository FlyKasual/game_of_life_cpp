#ifndef __CELL_H
#define __CELL_H

class Cell {
public:
  enum class State {
    ALIVE,
    DEAD
  };
  Cell(): Cell{State::DEAD} {}
  Cell(Cell::State state): state_(state) {}

  State getState() const {
    return state_;
  }

  Cell& setState(State state) {
    state_ = state;

    return *this;
  }
protected:
  State state_;
};

#endif
