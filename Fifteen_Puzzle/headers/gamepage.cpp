// C++ headers
#include <algorithm>
#include <random>
#include <ranges>

// Qt headers
#include <QDebug>

// User headers
#include "gamepage.hpp"

namespace Utility
{
	// Function aprooved that distance between cells is equal '1'
	bool aproove(const size_t& pos1, const size_t& pos2)
	{
		if(std::abs(to_i(pos1)-to_i(pos2)) == 1) return true;
		else return false;
	}

	// Check if we can swap some cells
	bool movableCells(
			const identificator& first_operand,
			const identificator& second_operand
	)
	{
		//{}: means initialize with '0', that will convert to 'false'
		bool result {};

		if (first_operand == second_operand) return false;

		if (
			// This cells in the same row
			(first_operand.first == second_operand.first)
			&&
			// Distance between columns is '1'
			aproove(first_operand.second, second_operand.second)
			||
			// This cells in the same column
			(first_operand.second == second_operand.second)
			&&
			// Distance between rows is '1'
			aproove(first_operand.first, second_operand.first)
			)
		{
			result = true;
		}
		else result = false;

		return result;
	}
}

GamePage::GamePage(const size_t &parseWidth, QObject *parent)
	: QAbstractListModel(parent)
{
	// Invoke re-constructor for the game
	reusableConstructor(parseWidth);
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

// We could ignore move so return type is bool
void GamePage::move(const int& index)
{
	// Make sure that game isn't ended up
	if(finished || pause) return;

	// Initialize changing the model
	beginResetModel();

	// Maybe it's an invalid position
	if(!validatePosition(static_cast<size_t>(index))) return;

	// Identify 2D position of the pressed tile
	const identificator pressedTile {getTablePos(index)};

	// Get iterator to the hidden tile
	auto hiddenTileIterator = std::find(m_tiles.begin(), m_tiles.end(), m_size);

	// Make sure that we get hidden tile
	Q_ASSERT(hiddenTileIterator != m_tiles.end());

	// Identify 2D position of the hidden tile
	identificator hiddenTile {
		getTablePos(
					std::distance(m_tiles.begin(), hiddenTileIterator)
					)
	};

	// We can't swap hidden tile with tile on the diagonal or far from it
	if (!Utility::movableCells(pressedTile, hiddenTile)) return;

	// Iterator to the pressed tile
	auto pressedTileIterator = std::ranges::find(m_tiles, m_tiles.at(index));

	// Swap data in the tiles by iterators
	std::iter_swap(hiddenTileIterator, pressedTileIterator);

	// Finish changing the model and emit signal to the front end
	endResetModel();

	// Check: are we finish game?
	checkWin(); // if true the appropriate message will appear
}

/*
FROM TEST TASK (5.a):
´New game¡ button - generate a new random start position
*/
// Invoke initializing the new game
void GamePage::newPage()
{
	// Reset boolean statuses
	finished = false;
	pause = false;

	beginResetModel();
	shuffle();
	tiles_saved = m_tiles;
	endResetModel();
}

/*
FROM TEST TASK (5.b):
´Reset¡ - reset the current puzzle to starting position
*/
// Invoke reset to the start position of the current game
void GamePage::resetPage()
{
	// Reset boolean statuses
	finished = false;
	pause = false;

	beginResetModel();
	m_tiles = tiles_saved;
	endResetModel();
}

/*
   FROM TEST TASK:
   ==> OPTIONAL:
   Implement levels of difficulty.
   So this method will resize and shuffle tiles container
   according to the new width
*/
void GamePage::resizeGrid(const int& width)
{
	beginResetModel();
	// Invoke re-constructor for the game
	reusableConstructor(width);
	endResetModel();
}

// Let's validate user attempt to drag tiles
bool GamePage::validateDrag(const int& index)
{
	// Make sure that game isn't ended up
	if(finished || pause) return false;

	// Maybe it's an invalid position
	if(!validatePosition(static_cast<size_t>(index))) return false;

	// Identify 2D position of the pressed tile
	const identificator draggedTile {getTablePos(index)};

	// Get iterator to the hidden tile
	auto hiddenTileIterator = std::find(m_tiles.begin(), m_tiles.end(), m_size);

	// Make sure that we get hidden tile
	Q_ASSERT(hiddenTileIterator != m_tiles.end());

	// Identify 2D position of the hidden tile
	identificator hiddenTile {
		getTablePos(
					std::distance(m_tiles.begin(), hiddenTileIterator)
					)
	};

	// We can't drag given tile
	if (!Utility::movableCells(draggedTile, hiddenTile)) return false;
	// or we can draging it
	else return true;
}

// Shuffle the tiles with Mersenne Twister random generator
void GamePage::shuffle()
{

	// This can be improoved
	static auto seed = std::chrono
					   ::system_clock::now().time_since_epoch().count();
	/*
	Random number engine based on the Marsenne Twister algorithm.
	32-bit Mersenne Twister by Matsumoto and Nishimura, 1998.
	*/
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

/*
   FROM TEST TASK:
   ==> OPTIONAL:
   Ensure that generated start positions are solvable
   (half of all randomly generated positions is impossible to solve)
*/
// This method validate if we are generate the solvable shuffle
/*
In general, for a given grid of width N, we can find out check if a N*N puzzle
is solvable or not by following below simple rules:

1) If N is odd, then puzzle instance is solvable if number of inversions
is even in the input state.

2) If N is even puzzle instance is solvable if:

	- the blank is on an even row counting from the bottom
	(second-last, fourth-last, etc.) and number of inversions is odd.

	- the blank is on an odd row counting from the bottom
	(last, third-last, fifth-last, etc.) and number of inversions is even.

For all other cases, the puzzle instance is not solvable.
*/
bool GamePage::validateShuffle() const
{
	/*
	This variable holds how much inversions need to be done
	to the tiles. If tile in the wrong position
	(number on the tile bigger then it's position)
	it have to be count as such that need to be inverted
	*/
	int inverionsCount{};

	// Count inversions
	//NOTE: m_size - 1, not m_size
	// take tile in the array
	for(size_t pos{}; pos < m_size - 1; pos++)
	{
		// analize all tiles after tooked tile
		for(size_t after_pos = pos + 1; after_pos < m_size; after_pos++)
		{
			if (
				m_tiles[pos] != m_size          // it's shouldn't be hidden tile
				&&
				m_tiles[after_pos] != m_size    // it's shouldn't be hidden tile
				&&
				m_tiles[pos] > m_tiles[after_pos] // it's have to be moved
				)
				inverionsCount++;
		}
	}

	// We need to traverse m_tiles to find 16-tile.
	auto dummy = std::find(m_tiles.begin(), m_tiles.end(), m_size);

	// Calculate indexer from iterators for hidden tile
	size_t hiddenIndex{};

	//If somehow we didn't receive 16-tile in the container we will return false
	if (dummy == m_tiles.end()) return false;
	else
	{
		hiddenIndex = dummy - m_tiles.begin();
	}

	// Find row index from the bottom, indexing starts from '1'
	size_t hiddenRowB = m_width - getTablePos(hiddenIndex).first;

	// If width is odd we say that shuffle is VALID if inversion count is even
	if ((m_width % 2) != 0) return ((inverionsCount % 2) == 0);
	// BUT! If width is even...
	else
	{
		// If number of row of hidden tile from bottom is odd (1,3,5,...)
		if ((hiddenRowB % 2) != 0)
			// Inversions count should be even
			return ((inverionsCount % 2) == 0);
		// If number of row of hidden tile from bottom is even (2,4,6,...)
		else
			// Inversions count should be odd
			return ((inverionsCount % 2) != 0);
	}
}

/*
Identify position on the game page (2D index) by some 1D index
	first: row number
	second: column number
indexing starts from '1'
*/
identificator GamePage::getTablePos(const size_t& index) const
{
	identificator result {};
	result.first = index / m_width;
	result.second = index % m_width;
	return result;
}

/*
We setting game page variables and containers multiple times
so to get rid of repetetive code we can provide a special
method to do this.
*/
void GamePage::reusableConstructor(const int& parseWidth)
{
	// Make sure that we are not dealing with game page with width: '0' or less
	Q_ASSERT(parseWidth > 0);

	// Reset boolean statuses
	finished = false;
	pause = false;

	// Reset member width and size
	m_width = parseWidth;
	m_size = parseWidth*parseWidth;

	// Prepare tiles
	m_tiles.resize(m_size);
	std::iota(m_tiles.begin(), m_tiles.end(), 1);

	// Prepare win position
	tiles_win = m_tiles;

	// Shuffle tiles
	shuffle();

	// Save this shuffle for the reseting
	tiles_saved = m_tiles;
}

/*
We check tiles in the container, and if it's a win position
we emmit signal to front end
*/
void GamePage::checkWin()
{
	// Traverse containers and return after first unequality
	for(size_t index{}; index < tiles_win.size(); index++)
	{
		if(m_tiles.at(index) != tiles_win.at(index)) return;
	}

	// Change status: the game is finished
	finished = true;

	//emit pop window for win
	emit finishedChanged();
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
	return QVariant::fromValue(m_tiles[rowIndex]);
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
	return to_i(m_tiles.size());
}
