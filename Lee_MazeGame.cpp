// implementation of MazeGame functions

#include "MazeGame.h"
#include "MazePlayer.h"

MazeGame::MazeGame(string filename)
{
  save_out.open(out_name);
  ifstream in;
  in.open(filename);
  if (!in) {
    cerr << "Wrong maze tiles file: " + filename << endl;
    throw IncorrectFile();
  }
  save_out << "Maze tiles file: " << filename << endl << endl;
  in >> maze;
  print_maze();
}

MazeGame::~MazeGame()
{
  save_out.close();
}

void MazeGame::start_game(istream & is)
{
  // implement this function
  int i=0;
  for(auto row : maze.get_tiles()) {
    int j=0;
    for(auto t : row){
      if(t->is_start())
      {
         players.push_back(new MazePlayer(Position(i,j)));
      }
      j++;
    }    
    i++;
  }

  update_loop(is);
}

// Important: if you use cout << something
// do the same with save_out << something
// Otherwise, the file output.txt would be incorrect
void MazeGame::update_loop(istream & is)
{
  int pnum = 0; // player's number
  string str;
      
  for(auto player : players) {
    pnum++;
    // implement code here
    cout << "\n\n";
    save_out << "\n\n";

    print_maze();
    cout << "Player " << pnum << " Position = " << player->get_position() << endl;
    save_out << "Player " << pnum << " Position = " << player->get_position() << endl;
    cout << "Move #" << player -> move_number() << " : ";    
    cin >> str;
    save_out << "Move #" << player -> move_number() << " : " << str << endl;

    Position pos = player->take_turn(str);
    if(maze.can_move_to_tile(pos))
    {
        player->set_position(pos);
        if(maze.is_tile_end(pos))
        {
           cout << "\n";
           save_out << "\n";
           cout << "Player " << pnum << " win...\n";
           save_out << "Player " << pnum << " win...\n";
           print_maze();
           exit(0);
        }
    }
    else
    {
      while (maze.can_move_to_tile(pos) != true)
      {
        cout << "Invalid Move. Try again\n\n";
        save_out << "Invalid Move. Try again\n\n";

        cout << "Player " << pnum << " Position = " << player->get_position() << endl;
        save_out << "Player " << pnum << " Position = " << player->get_position() << endl;
        cout << "Move #" << player -> move_number() << " : ";    
        cin >> str;
        save_out << "Move #" << player -> move_number() << " : " << str << endl;

        Position pos = player->take_turn(str);
        if(maze.can_move_to_tile(pos))
        {
          player -> set_position(pos);
          if(maze.is_tile_end(pos))
          {
            cout << "\n";
            save_out << "\n";
            cout << "Player " << pnum << " win...\n";
            save_out << "Player " << pnum << " win...\n";
            print_maze();
            exit(0);
          }
          break;
        }
      }
    }
  }

  update_loop(is);
}

void MazeGame::print_maze()
{
  vector<string> grid;
  for(auto row : maze.get_tiles()) {
    string tiles = "";
    for(auto t : row) 
      tiles += t->tile_char;

    grid.push_back(tiles);
  }

  for(auto player : players)
    grid[player->get_position().row][player->get_position().col] = 'P';

  cout << " ";
  save_out << " ";
  
  for(int i = 0; i < grid[0].size(); i++) {
    cout << i;
    save_out << i;
  }

  cout << endl;
  save_out << endl;
  
  for(int i = 0; i < grid.size(); i++) {
    cout << i << grid[i] << endl;
    save_out << i << grid[i] << endl;
  }
}

