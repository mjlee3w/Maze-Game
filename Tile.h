#ifndef TILE_H
#define TILE_H

#include <iostream>

using namespace std;

class Tile
{

public:
  char tile_char = '_';

public:
  virtual bool try_walk()
  {
    return false;
  }

  virtual bool is_start()
  {
    return false;
  }

  virtual bool is_end()
  {
    return false;
  }
};

class WallTile : public Tile
{
  // implement this class
public:
  WallTile()
  {
    tile_char = 'W';
  }
};

class EmptyTile : public Tile
{
  // implement this class
public:
  EmptyTile()
  {
    tile_char = 'X';
  }
  bool try_walk() override
  {
    return true;
  }
};

class StartingTile : public EmptyTile
{
  // implement this class
public:
  StartingTile()
  {
    tile_char = 'S';
  }
  bool is_start() override
  {
    return true;
  }
};

class EndingTile : public EmptyTile
{
  // implement this class
public:
  EndingTile()
  {
    tile_char = 'E';
  }
  bool try_walk() override
  {
    return true;
  }
  bool is_end() override
  {
    return true;
  }
};

ostream &operator<<(ostream &out, const Tile &t);
istream &operator>>(istream &in, Tile *&t);

#endif
