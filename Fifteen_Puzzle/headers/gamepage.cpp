#include "gamepage.hpp"
#include <algorithm>
#include <random>
#include <ranges>

GamePage::GamePage(const size_t &parseWidth, QObject *parent)
	: QAbstractListModel(parent),
	  m_width(parseWidth),
	  m_size(parseWidth*parseWidth)
{
	m_tiles.resize(m_size);
	std::iota(m_tiles.begin(), m_tiles.end(), 1);
	shuffle();
}

// Send to the front end game page width in tile units
size_t GamePage::width() const
{
	return m_width;
}

// Send to the front end tile content that we don't want to show
size_t GamePage::size() const
{
	return m_size;
}

// Shuffle the tiles with Mersenne Twister random generator
void GamePage::shuffle()
{
	//This can be improoved
	static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);

	/*
	FROM TEST TASK:
	==> OPTIONAL:
				 Ensure that generated start positions
				 are solvable (half of all randomly generated
				 positions is impossible to solve)
	*/
	// Let's check if we are generate te solvable shuffle
	do {
		std::shuffle(m_tiles.begin(), m_tiles.end(), generator);
	} while(!validateShuffle());

}

// Let's prevent us from passing the too big value as rowIndex
bool GamePage::validatePosition(const size_t& pos) const
{
	return pos < m_tiles.size();
}

// Validation method for checking if we are generate the
// solvable shuffle
bool GamePage::validateShuffle() const
{
	// This variable holds how much inversions need to be done
	// to the tiles. If tile in the wrong position
	// (number on the tile bigger then it's position)
	// it have to be count as such that need to be inverted
	int inverionsCount{};

	// Count inversions
	for(size_t res{}; res < m_size; res++)
	{
		for(size_t before_res; before_res < res; before_res++)
		{
			if (m_tiles[before_res].value > m_tiles[res].value)
				inverionsCount++;
		}
	}

	// We are starting with Tile numbered '1'
	const size_t start_tile {1};
	size_t indexer{};

	// Definitely using lambda for traversing container
	auto checkSixteenTile = [&](const Tile& puzzle)
	{
		// We are looking for the empty space
		// Tile with #16 will give true here
		if(puzzle.value == m_size)
		{
			// Add to the conversions count the number of
			// rows (plus one) that that empty space have to pass
			// to get to the position: '0' - left up corner
			inverionsCount += start_tile + indexer / m_width;

			// We succesfully found 16-tile, let's come back
			return true;
		}

		// Move to another index
		indexer++;

		// Still looking for the 16-tile
		return false;
	};

	// We don't need this dummy itself, but we need to traverse m_tiles
	// find 16-tile and add appropriate coefficient to the conversions count
	auto dummy = std::ranges::find_if(m_tiles, checkSixteenTile);

	// If somehow we didn't receive 16-tile in the container
	// we will return false
	if (dummy == m_tiles.end()) return false;

	// But if number of conversions are even
	// this means that game is solvable
	return (inverionsCount % 2) == 0;
}

//The QVariant class acts like a union for the most common Qt data types.
QVariant GamePage::data(const QModelIndex &index, int role) const
{
	/*
	isValid(): Returns true if this model index is valid;
	otherwise returns false.
	*/
	if (!index.isValid() || role != Qt::DisplayRole) { return {}; }

	/*
	rowIndex - the element that we are going to pass
	row(): returns row by index
	index.row(): returns 'int'
	but in the nexxt step we are need size_t
	*/
	const size_t rowIndex {static_cast<size_t>(index.row())};

	// Check if index is valid
	if (!validatePosition(rowIndex)) { return {}; }

	/*
	Returns a QVariant containing a copy of value.
	Behaves exactly like setValue() otherwise.
	*/
	return QVariant::fromValue(m_tiles[rowIndex].value);
}

int GamePage::rowCount(const QModelIndex &parent) const
{
	/*
	Indicates to the compiler that the parameter
	with the specified name is not used in the body of a function.
	This can be used to suppress compiler warnings while allowing
	functions to be defined with meaningful parameter names
	in their signatures.
	*/
	Q_UNUSED(parent);
	//NOTE: size() returns size_t but we need int
	return static_cast<int>(m_tiles.size());
}
