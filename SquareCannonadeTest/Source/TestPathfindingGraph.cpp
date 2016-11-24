#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>


/**
 * There are multiple different test sets involving PathfindingGraph
 * in this file.
 */




/**
 * Tests for creation of correct number of vertices
 */

TEST_CASE("Created correct number of vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumVertices() == 12);
}

TEST_CASE("Created correct number of vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "0000";
  tileMap += "00w0";
  tileMap += "000w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumVertices() == 10);
}




/**
 * Tests for accessing vertex by position
 */

TEST_CASE("Vertex access by position #1: successful find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 10);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Get vertex to assert about
  int left = tileLength;
  int top = 0;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(vertex);
  REQUIRE(vertex->tile->getRect().left == left);
  REQUIRE(vertex->tile->getRect().top == top);
}

TEST_CASE("Vertex access by position #2: successful find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Get vertex to assert about
  int left = tileLength;
  int top = tileLength;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(vertex);
  REQUIRE(vertex->tile->getRect().left == left);
  REQUIRE(vertex->tile->getRect().top == top);
}

TEST_CASE("Vertex access by position #3: fail to find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Try to get vertex to assert about
  int left = tileLength * 2;
  int top = 0;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(!vertex);
}





/**
 * Tests for creation of correct number of edges
 */

// Test for creation of one non-diagonal edge
TEST_CASE("Created correct number of edges #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 10);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 1);
}

// Test for creation of a complete graph ("complete" as in there
// exists an edge between every pair of vertices)
TEST_CASE("Created correct number of edges #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 6);
}

// Basic test for the exclusion of an edge that would let an entity
// cut diagonally across a wall
TEST_CASE("Created correct number of edges #3")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  std::string tileMap = "";
  tileMap += "00";
  tileMap += "0w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 2);
}

TEST_CASE("Created correct number of edges #4")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 11);
}

TEST_CASE("Created correct number of edges #5")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "0000";
  tileMap += "00w0";
  tileMap += "000w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 15);
}

TEST_CASE("Created correct number of edges #6")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "000";
  tileMap += "00w";
  tileMap += "w00";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 9);
}

// Another test meant to make sure no edges that would let entities
// partially cut across walls are created
TEST_CASE("Created correct number of edges #7")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  std::string tileMap = "";
  tileMap += "w0";
  tileMap += "0w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 0);
}




/**
 * Tests for setting vertices at which pathfinding search should start/end
 *
 * Note that there is a confusing part in that an enemy's position is
 * centered, whereas a vertex's position uses its top-left coordinate.
 * This is a bad design choice on my part.
 *
 * tileGrid can't be local to this function because the generated
 * PathfindingGraph instance has vertices that reference the tiles
 * in tileGrid.
 */

// Setup function to help with the tests of the setup of the pathfinding
std::unique_ptr<PathfindingGraph> setupPathfindingSetupTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // Set tile and enemy length
  int tileLength = 0;
  int enemyLength = 0;
  switch (caseNum)
  {
  case 2: case 6:
    tileLength = 30;
    enemyLength = 20;
    break;
  case 3: case 4: case 7: case 8:
    tileLength = 10;
    enemyLength = 5;
    break;
  case 10:
    tileLength = 10;
    enemyLength = 1;
  default:
    tileLength = enemyLength = 10;
    break;
  }

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1: case 5:
    area = sf::IntRect(0, 0, 50, 40);
    break;
  case 2: case 6:
    area = sf::IntRect(0, 0, 150, 150);
    break;
  case 3: case 7:
    area = sf::IntRect(0, 0, 20, 20);
    break;
  case 4: case 8:
    area = sf::IntRect(0, 0, 30, 20);
    break;
  case 9:
    area = sf::IntRect(0, 0, 50, 40);
    break;
  case 10:
    area = sf::IntRect(0, 0, 60, 60);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // shouldn't be reached; no logical default area
    break;
  }

  // Create tile map
  std::string tileMap = "";
  switch (caseNum)
  {
  case 2: case 6: // some random walls
    tileMap += "00www";
    tileMap += "w000w";
    tileMap += "00w00";
    tileMap += "00000";
    tileMap += "00ww0";
    break;
  case 9:
    tileMap += "00000";
    tileMap += "0ww00";
    tileMap += "000w0";
    tileMap += "00000";
    break;
  case 10:
    tileMap += "000000";
    tileMap += "00w000";
    tileMap += "000000";
    tileMap += "000w00";
    tileMap += "0w000w";
    tileMap += "00000w";
    break;
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }

  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));

  // Run method-to-test
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(29, 18), enemyLength);
    break;
  case 2:
    pg->setSearchStart(sf::Vector2f(32, 94), enemyLength);
    break;
  case 3:
    pg->setSearchStart(sf::Vector2f(15, 5), enemyLength);
    break;
  case 4:
    pg->setSearchStart(sf::Vector2f(15, 10), enemyLength);
    break;
  case 5:
    pg->setSearchEnd(sf::Vector2f(29, 18), enemyLength);
    break;
  case 6:
    pg->setSearchEnd(sf::Vector2f(32, 94), enemyLength);
    break;
  case 7:
    pg->setSearchEnd(sf::Vector2f(15, 5), enemyLength);
    break;
  case 8:
    pg->setSearchEnd(sf::Vector2f(15, 10), enemyLength);
    break;
  case 9:
    pg->setSearchStart(sf::Vector2f(40, 10), enemyLength);
    pg->setSearchEnd(sf::Vector2f(20, 30), enemyLength);
    break;
  case 10:
    pg->setSearchStart(sf::Vector2f(20, 30), enemyLength);
    pg->setSearchEnd(sf::Vector2f(45, 15), enemyLength);
    break;
  default:
    assert(false); // no logical default
  }

  return pg;
} // setupPathfindingSetupTests()

TEST_CASE("Setting pathfinding search's start vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  std::unique_ptr<PathfindingGraph> pg =
    setupPathfindingSetupTests(1, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(20, 10));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(30, 20));
}

// Involves some random walls that *shouldn't* affect anything
TEST_CASE("Setting pathfinding search's start vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(2, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(0, 60));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(30, 60));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(0, 90));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(30, 90));
}

// Enemy completely fits in one tile
TEST_CASE("Setting pathfinding search's start vertices #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(3, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 1);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 0));
}

// Enemy completely fits in two tiles
TEST_CASE("Setting pathfinding search's start vertices #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(4, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 2);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 0));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(10, 10));
}

TEST_CASE("Setting pathfinding search's end vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  std::unique_ptr<PathfindingGraph> pg =
    setupPathfindingSetupTests(5, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(20, 10));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(30, 20));
}

// Involves some random walls that *shouldn't* affect anything
TEST_CASE("Setting pathfinding search's end vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(6, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(0, 60));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(30, 60));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(0, 90));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(30, 90));
}

// Target entity completely fits in one tile
TEST_CASE("Setting pathfinding search's end vertices #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(7, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 1);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 0));
}

// Target entity completely fits in two tiles
TEST_CASE("Setting pathfinding search's end vertices #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(8, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 2);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 0));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(10, 10));
}

TEST_CASE("Setting pathfinding search's start and end vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(9, tileGrid);

  // Assertions for start vertices
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(30, 0));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(40, 0));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(40, 10));

  // Assertions for end vertices
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 20));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(10, 30));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(20, 30));
}

TEST_CASE("Setting pathfinding search's start and end vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(10, tileGrid);

  // Assertions for start vertices
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 20));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(10, 30));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(20, 30));

  // Assertions for end vertices
  REQUIRE(pg->getNumSearchEndVertices() == 1);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(40, 10));
}








/**
 * Tests for performAStarSearch() (that is, for finding correct path
 * ending vertex)
 */

std::unique_ptr<PathfindingGraph> setupPathfindingEndTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // Set tile and enemy length
  int tileLength = 0;
  int enemyLength = 0;
  switch (caseNum)
  {
  case 1: case 2: case 3: case 6: // if tile should be larger than enemy
    tileLength = 10;
    enemyLength = 5;
    break;
  default:
    tileLength = 10;
    enemyLength = 10;
    break;
  }
  // So I don't mess up:
  assert(tileLength != 0);
  assert(enemyLength != 0);

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1:
    area = sf::IntRect(0, 0, 30, 10);
    break;
  case 2:
    area = sf::IntRect(0, 0, 30, 20);
    break;
  case 3:
    area = sf::IntRect(0, 0, 200, 200);
    break;
  case 4:
    area = sf::IntRect(0, 0, 80, 20);
    break;
  case 5:
    area = sf::IntRect(0, 0, 70, 70);
    break;
  case 6:
    area = sf::IntRect(0, 0, 20, 20);
    break;
  case 7:
    area = sf::IntRect(0, 0, 100, 90);
    break;
  default:
    // No suitable default; stop tests
    std::cerr << "Invalid case number\n";
    assert(false);
  }

  // Set tile map
  std::string tileMap = "";
  switch (caseNum)
  {
  case 2:
    tileMap += "000";
    tileMap += "0w0";
    break;
  case 3: // just one wall for first spot of second row
    tileMap = createTileMapAllDefault(area, tileLength);
    tileMap.at(20) = 'w';
    break;
  case 4:
    tileMap += "00000000";
    tileMap += "00w00000";
    break;
  case 7:
    tileMap += "0000000000";
    tileMap += "0000000000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "0000www000";
    tileMap += "0000000000";
    tileMap += "0000000000";
    break;
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }

  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));

  // Set search and end
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(5, 5), enemyLength);
    pg->setSearchEnd(sf::Vector2f(25, 5), enemyLength);
    break;
  case 2:
    pg->setSearchStart(sf::Vector2f(5, 15), enemyLength);
    pg->setSearchEnd(sf::Vector2f(25, 15), enemyLength);
    break;
  case 3:
    pg->setSearchStart(sf::Vector2f(5, 5), enemyLength);
    pg->setSearchEnd(sf::Vector2f(195, 195), enemyLength);
    break;
  case 4:
    pg->setSearchStart(sf::Vector2f(10, 10), enemyLength);
    pg->setSearchEnd(sf::Vector2f(70, 10), enemyLength);
    break;
  case 5:
    pg->setSearchStart(sf::Vector2f(60, 60), enemyLength);
    pg->setSearchEnd(sf::Vector2f(9, 11), enemyLength);
    break;
  case 6:
    pg->setSearchStart(sf::Vector2f(5, 15), enemyLength);
    pg->setSearchEnd(sf::Vector2f(15, 5), enemyLength);
    break;
  case 7:
    pg->setSearchStart(sf::Vector2f(80, 80), enemyLength);
    pg->setSearchEnd(sf::Vector2f(18, 11), enemyLength);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // no logical default
  }

  return pg;
} // setupPathfindingEndTests()

TEST_CASE("Correct path end #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(1, tileGrid)->performAStarSearch();

  REQUIRE(index == 2);
}

TEST_CASE("Correct path end #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(2, tileGrid)->performAStarSearch();

  REQUIRE(index == 4);
}

TEST_CASE("Correct path end #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(3, tileGrid)->performAStarSearch();

  REQUIRE(index == 398);
}

TEST_CASE("Correct path end #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(4, tileGrid)->performAStarSearch();

  REQUIRE(index == 6);
}

TEST_CASE("Correct path end #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(5, tileGrid)->performAStarSearch();

  REQUIRE(index == 8);
}

TEST_CASE("Correct path end #6")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(6, tileGrid)->performAStarSearch();

  REQUIRE(index == 1);
}

TEST_CASE("Correct path end #7")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(7, tileGrid)->performAStarSearch();

  REQUIRE(index == 12);
}







/**
 * Tests for finding the correct path with pathfinding algorithm
 */

std::vector<unsigned int> * setupGeneratePathTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // The test cases are handled in this method, which means performAStarSearch()
  // and generatePath() have same test cases (but different tested values)
  auto pg = setupPathfindingEndTests(caseNum, tileGrid);

  int pathEndingVertexId = pg->performAStarSearch();

  // run method-to-test
  return pg->generatePath(pathEndingVertexId);
} // setupGeneratePathTests()

TEST_CASE("Found correct path #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(1, tileGrid);

  REQUIRE(path.size() == 3);
  REQUIRE(path[0] == 0);
  REQUIRE(path[1] == 1);
  REQUIRE(path[2] == 2);
}

TEST_CASE("Found correct path #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(2, tileGrid);

  REQUIRE(path.size() == 5);
  REQUIRE(path[0] == 3);
  REQUIRE(path[1] == 0);
  REQUIRE(path[2] == 1);
  REQUIRE(path[4] == 4);
}

TEST_CASE("Found correct path #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(3, tileGrid);

  REQUIRE(path.size() == 21);
  REQUIRE(path[0] == 0);
  REQUIRE(path[1] == 1);
  REQUIRE(path[20] == 398);
}

TEST_CASE("Found correct path #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(4, tileGrid);

  REQUIRE(path.size() == 6);
  REQUIRE(path[0] == 1);
  REQUIRE(path[1] == 2);
  REQUIRE(path[2] == 3);
}

TEST_CASE("Found correct path #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(5, tileGrid);

  REQUIRE(path.size() == 5);
  REQUIRE(path[0] == 40);
  REQUIRE(path[1] == 32);
  REQUIRE(path[2] == 24);
}

TEST_CASE("Found correct path #6")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(6, tileGrid);

  REQUIRE(path.size() == 2);
  REQUIRE(path[0] == 2);
  REQUIRE(path[1] == 1);
}

TEST_CASE("Found correct path #7")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(7, tileGrid);

  REQUIRE(path.size() == 11);
  REQUIRE(path[0] == 58);
  REQUIRE(path[1] == 57);
  REQUIRE(path[2] == 56);
}