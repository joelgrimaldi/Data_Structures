#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "board.h"

// ==================================================================================
// ==================================================================================

// This function is called if there was an error with the command line arguments
bool usage(const std::string &executable_name) {
  std::cerr << "Usage: " << executable_name << " <puzzle_file>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -visualize <which_robot>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -visualize <which_robot>" << std::endl;
  exit(0);
}

// ==================================================================================
// ==================================================================================

// load a Ricochet Robots puzzle from the input file
Board load(const std::string &executable, const std::string &filename) {

  // open the file for reading
  std::ifstream istr (filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
    usage(executable);
  }

  // read in the board dimensions and create an empty board
  // (all outer edges are automatically set to be walls
  int rows,cols;
  istr >> rows >> cols;
  assert (rows > 0 && cols > 0);
  Board answer(rows,cols);

  // read in the other characteristics of the puzzle board
  std::string token;
  while (istr >> token) {
    if (token == "robot") {
      char a;
      int r,c;
      istr >> a >> r >> c;
      answer.placeRobot(Position(r,c),a);
    } else if (token == "vertical_wall") {
      int i;
      double j;
      istr >> i >> j;
      answer.addVerticalWall(i,j);
    } else if (token == "horizontal_wall") {
      double i;
      int j;
      istr >> i >> j;
      answer.addHorizontalWall(i,j);
    } else if (token == "goal") {
      std::string which_robot;
      int r,c;
      istr >> which_robot >> r >> c;
      answer.addGoal(which_robot,Position(r,c));
    } else {
      std::cerr << "ERROR: unknown token in the input file " << token << std::endl;
      exit(0);
    }
  }

  // return the initialized board
  return answer;
}


std::vector<std::vector<char>> Visualize(Board board, std::vector<std::vector<char>> ret, int index, 
  int max, int moves, std::string direction, const uint moving, std::vector<Direction> path, 
  std::vector<std::vector<Direction>> &all_paths, std::map<std::vector<Robot>, int> boards, 
  bool v, int numbersOnBoard){

  if(max == -1){
    max = 100;    //prevent -1 error
  }

  bool target = false;

  if(moves == -1){  //only enters this if statement once
    ret = std::vector<std::vector<char>>(board.getRows(), std::vector<char>(board.getCols(), '.')); //initialize ret
    ret[board.getRobots()[index].pos.row-1][board.getRobots()[index].pos.col-1] = '0';
    moves++;
    for(uint i = 0; i < board.numRobots(); i++){    //for loop made to send each robot in its starting position four diff directions
      ret = Visualize(board,ret,index,max,moves, "n", i, path, all_paths, boards, v, numbersOnBoard);
      ret = Visualize(board,ret,index,max,moves, "s", i, path, all_paths, boards, v, numbersOnBoard);
      ret = Visualize(board,ret,index,max,moves, "e", i, path, all_paths, boards, v, numbersOnBoard);
      ret = Visualize(board,ret,index,max,moves, "w", i, path, all_paths, boards, v, numbersOnBoard);
    }
  }
  else if(moves < max){  //otherwise while moves is less than max
    if(board.getRobot(index) == board.getRobot(moving))
      target = true;  //made to only add numbers to ret if it is robot that is being visualized

    if(board.moveRobot(moving,direction,false,0)){
      path.push_back(Direction(board.getRobots()[moving].pos, board.getRobots()[moving].which, direction)); //keeps current path
      moves++;

      if(target){
        char out = '0' + moves; //convert moves to char
        char old = ret[board.getRobots()[index].pos.row-1][board.getRobots()[index].pos.col-1]; //spot currently at target spot

        if(old == '.' || out <= old){
          ret[board.getRobots()[index].pos.row-1][board.getRobots()[index].pos.col-1] = out;
          all_paths.push_back(path);
          boards[board.getRobots()] = moves; //save board in map of boards
          if(!v && board.getGoalPosition(0) == board.getRobots()[index].pos){ //if not visualizing and robot pos is goal pos
            max = moves;
          }
          if(old == '.'){
            numbersOnBoard++;
            if(numbersOnBoard == board.getRows()*board.getCols()) //made for when max isn't specified before
              max = out - '0';
          }
        }
        else{
          if(boards.find(board.getRobots()) != boards.end()){     //if board had already been at this spot
            return ret;                                           //and moves > number already in the spot
          }                                                       //end the recursion at that point because
        }                                                         //it is redundant
      }

      for(uint j = 0; j < board.numRobots() && moves < max; j++){ //send each robot in a path that it has not been
        if(moving != j || path[path.size()-1].dir != "s")         //in the past move
          ret = Visualize(board,ret,index,max,moves, "n", j, path, all_paths, boards, v, numbersOnBoard);
        if(moving != j || path[path.size()-1].dir != "n")
          ret = Visualize(board,ret,index,max,moves, "s", j, path, all_paths, boards, v, numbersOnBoard);
        if(moving != j || path[path.size()-1].dir != "w")
          ret = Visualize(board,ret,index,max,moves, "e", j, path, all_paths, boards, v, numbersOnBoard);
        if(moving != j || path[path.size()-1].dir != "e")
          ret = Visualize(board,ret,index,max,moves, "w", j, path, all_paths, boards, v, numbersOnBoard);
      }
    }
  }
  path.clear();
  return ret;
}

std::vector<std::vector<Direction>> solution(const Position &goal, std::vector<std::vector<Direction>> all_paths, uint &smallest){

  smallest = 999;
  for(uint x = 0; x < all_paths.size(); x++){
    if(all_paths[x][all_paths[x].size()-1].pos == goal){
      if(all_paths[x].size() < smallest)  //if smaller than prev smallest
        smallest = all_paths[x].size();
      continue;
    }
    all_paths.erase(all_paths.begin() + x); //erase if last pos isnt goal
    x--;
  }

  for(uint x = 0; x < all_paths.size(); x++){
    if(all_paths[x].size() == smallest)
      continue;
    all_paths.erase(all_paths.begin() + x); //if paths that are still in less than smallest
    x--;                                    //remove them
  }  



  return all_paths;

}

// ==================================================================================
// ==================================================================================

int main(int argc, char* argv[]) {

  // There must be at least one command line argument, the input puzzle file
  if (argc < 2) {
    usage(argv[0]);
  }

  // By default, the maximum number of moves is unlimited
  int max_moves = -1;

  // By default, output one solution using the minimum number of moves
  bool all_solutions = false;

  // By default, do not visualize the reachability
  char visualize = ' ';   // the space character is not a valid robot!

  // Read in the other command line arguments
  for (int arg = 2; arg < argc; arg++) {
    if (argv[arg] == std::string("-all_solutions")) {
      // find all solutions to the puzzle that use the fewest number of moves
      all_solutions = true;
    } else if (argv[arg] == std::string("-max_moves")) {
      // the next command line arg is an integer, a cap on the  # of moves
      arg++;
      assert (arg < argc);
      max_moves = atoi(argv[arg]);
      assert (max_moves > 0);
    } else if (argv[arg] == std::string("-visualize")) {
      // As a first step towards solving the whole problem, with this
      // option, let's visualize where the specified robot can move
      // and how many steps it takes to get there
      arg++;
      assert (arg < argc);
      std::string tmp = argv[arg];
      assert (tmp.size() == 1);
      visualize = tmp[0];
      assert (isalpha(visualize) && isupper(visualize));
      visualize = toupper(visualize);
    } else {
      std::cout << "unknown command line argument" << argv[arg] << std::endl;
      usage(argv[0]);
    }
  }

  // Load the puzzle board from the input file
  Board board = load(argv[0],argv[1]);

  // board.print();

  // board.moveRobot(1,"s");
  //std::cout << board.moveRobot(0,"e",false) << std::endl;

  // board.print();

  // board.moveRobot(2,"w");

  // for now...  an example of how to use the board print function

  std::vector<std::vector<std::vector<Direction>>> everyPath;
  std::vector<std::vector<Direction>> all_paths;
  std::vector<Direction> path;
  std::vector<std::vector<char>> visualized;
  std::map<std::vector<Robot>, int> boards;

  if(visualize == ' '){ //if not visualizing
    board.print();

    uint smallest = 0;
    if(board.getGoalRobot(0) != '?'){ //if goal is a target goal for one robot
      int index;                      //only run visualize once
      for(uint i = 0; i < board.numRobots(); i++){
        if(board.getRobot(i) == board.getGoalRobot(0)){
          index = i;
          break;
        }
      }
      visualized = Visualize(board, visualized, index, max_moves, -1, "", 0, path, all_paths, boards, false, 0);
      all_paths = solution(board.getGoalPosition(0), all_paths, smallest);
      everyPath.push_back(all_paths);
      all_paths.clear();
    }
    else{   //if goal is for any robot then run visualize for amount numRobots
      for(uint x = 0; x < board.numRobots(); x++){
        visualized = Visualize(board, visualized, x, max_moves, -1, "", 0, path, all_paths, boards, false, 0);
        all_paths = solution(board.getGoalPosition(0), all_paths, smallest);
        everyPath.push_back(all_paths);
        all_paths.clear();

        for(uint y = 0; y < visualized.size(); y++){
          for(uint z = 0; z < visualized[y].size(); z++){
            if(Position(y+1,z+1) == board.getGoalPosition(0) && visualized[y][z] != '.')
              max_moves = visualized[y][z] - '0';
          }
        }
      }
    }

    int numPaths = 0; //count paths
    for(uint i = 0; i < everyPath.size(); i++){
      numPaths += everyPath[i].size();
    }

    if(numPaths == 0)
      std::cout << "no solutions with " << max_moves << " or fewer moves" << std::endl;

    else if(all_solutions){
      std::cout << numPaths << " different " << smallest << " move solutions:\n\n";

      for(uint z = 0; z < everyPath.size(); z++){
        for(uint x = 0; x < everyPath[z].size(); x++){
          for(uint y = 0; y < everyPath[z][x].size(); y++){
            std::string direction = "";
            if(everyPath[z][x][y].dir == "n")
              direction = "north";                      //print all paths with directions
            if(everyPath[z][x][y].dir == "s")           //for all solutions
              direction = "south";
            if(everyPath[z][x][y].dir == "e")
              direction = "east";
            if(everyPath[z][x][y].dir == "w")
              direction = "west";

            std::cout << "robot " << everyPath[z][x][y].which << " moves " << direction << std::endl;
          }
          std::cout << "All goals are satisfied after " << everyPath[z][x].size() << " moves" << std::endl;
          if(z != everyPath.size()-1 || x != everyPath[z].size()-1)
            std::cout << std::endl;
        }
      }
    }
    else{
      int index = 0;
      for(uint x = 0; x < everyPath[0][0].size(); x++){
        for(uint i = 0; i < board.numRobots(); i++){
          if(board.getRobot(i) == everyPath[0][0][x].which){
            index = i;
            break;
          }
        }

        board.moveRobot(index, everyPath[0][0][x].dir, false, 0);

        std::string direction = "";
        if(everyPath[0][0][x].dir == "n")   //print out one path and move the robot
          direction = "north";              //and print board every time for
        if(everyPath[0][0][x].dir == "s")   //one solution
          direction = "south";
        if(everyPath[0][0][x].dir == "e")
          direction = "east";
        if(everyPath[0][0][x].dir == "w")
          direction = "west";

        std::cout << "robot " << everyPath[0][0][x].which << " moves " << direction << std::endl;
        board.print();
      }
      std::cout << "All goals are satisfied after " << everyPath[0][0].size() << " moves" << std::endl;
    }
  }

  if(visualize != ' '){ //if visualizing a robot
    boards.clear();
    int index = 0;
    for(uint i = 0; i < board.numRobots(); i++){
      if(visualize == board.getRobot(i)){
        index = i;
        break;
      }
    }

    visualized = Visualize(board, visualized, index, max_moves, -1, "", 0, path, all_paths, boards, true, 0);

    std::cout << "Reachable by robot " << visualize << ":" << std::endl;
    for(uint x = 0; x < visualized.size(); x++){
      for(uint y = 0; y < visualized[x].size(); y++){
        std::cout << "  " << visualized[x][y];
      }
      std::cout << std::endl;
    }
  }
}

// ================================================================
// ================================================================
