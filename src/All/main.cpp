/*
  ShashChess, a UCI chess playing engine derived from Stockfish
  Copyright (C) 2004-2021 The Stockfish developers (see AUTHORS file)

  ShashChess is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ShashChess is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "bitboard.h"
#include "endgame.h"
#include "misc.h"
#include "position.h"
#include "psqt.h"
#include "search.h"
#include "syzygy/tbprobe.h"
#include "thread.h"
#include "learn.h"
#include "uci.h"
#include "polybook.h" //cerebellum
using namespace Stockfish;

int main(int argc, char* argv[]) {

  std::cout << engine_info() << std::endl;

  CommandLine::init(argc, argv);
  Utility::init(argv[0]); //Khalid
  UCI::init(Options);
  Tune::init();
  //from Kelly begin
  setUsePersistedLearning();
  if (usePersistedLearning != PersistedLearningUsage::Off)
  {
  	LD.init();
  }
  //from Kelly end
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Endgames::init();
  Threads.set(size_t(Options["Threads"]));
  Threads.setFull(Options["Full depth threads"]);//Full threads patch
  //cerebellum begin
  polybook.init(Options["BookFile"]);
  polybook2.init(Options["BookFile2"]);
  //cerebellum end
  Search::clear(); // After threads are up
  Eval::NNUE::init();

  UCI::loop(argc, argv);

  Threads.set(0);
  return 0;
}
