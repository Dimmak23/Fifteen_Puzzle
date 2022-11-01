// C++ headers
#include <algorithm>
#include <random>
#include <ranges>

// Qt headers
#include <QDebug>

// User headers
#include "gamepage.hpp"

//TODO: send to class Controller
namespace
{
	// Function aprooved that distance between cells is equal '1'
	bool aproove(const size_t& pos1, const size_t& pos2)
	{
		if(std::abs(to_i(pos1)-to_i(pos2)) == 1) return true;
		else return false;
	}

	bool movableCells(
			const identificator& first_operand,
			const identificator& second_operand
	)
	{
		//{}: means initialize with '0', that will convert to 'false'
		bool result {};

		if (first_operand == second_operand) return false;

		// dummy distance between tiles
//		int distance {};

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
	: QAbstractListModel(parent),
	  m_width(parseWidth),
	  m_size(parseWidth*parseWidth)
{
	qDebug() << "Constructing game ogject";

	status = false;
	pause = false;

	// Make sure that we are not dealing with game page with width: '0' or less
	Q_ASSERT(parseWidth > 0);

	// Prepare tiles
	m_tiles.resize(m_size);
	std::iota(m_tiles.begin(), m_tiles.end(), 1);

	// Prepare win position
	winner = m_tiles;

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	// Shuffle tiles
	shuffle();

	// Save this shuffle for the reseting
	tiles_saved = m_tiles;
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
	if(status || pause) return;

	beginResetModel();

	if(!validatePosition(static_cast<size_t>(index))) return;

	//
	const identificator pressedTile {getTablePos(index)};

	// TODO: ranges
	auto hiddenTileIterator = std::find(m_tiles.begin(), m_tiles.end(), m_size);

	// Make sure that we get hidden tile
	Q_ASSERT(hiddenTileIterator != m_tiles.end());

	identificator hiddenTile {
		getTablePos(
					std::distance(m_tiles.begin(), hiddenTileIterator)
					)
	};

	// We can't swap hidden tile with tile on the diagonal or far from it
	if (!movableCells(pressedTile, hiddenTile)) return;

	// Iterator to the pressed tile
	auto pressedTileIterator = std::ranges::find(m_tiles, m_tiles.at(index));

	// Swap data in the tiles by iterators
	std::iter_swap(hiddenTileIterator, pressedTileIterator);

	//
	endResetModel();

	// Check are we finish game
	checkWin();
}

// Invoke initializing the new game
void GamePage::newPage()
{
	status = false;
	pause = false;

	beginResetModel();
	shuffle();
	tiles_saved = m_tiles;
	endResetModel();
}

// Invoke reset to the start position of the current game
void GamePage::resetPage()
{
	status = false;
	pause = false;

	beginResetModel();
	m_tiles = tiles_saved;
	endResetModel();
}

void GamePage::resizeGrid(const int& width)
{
	beginResetModel();

	qDebug() << "Resizing game ogject";

	status = false;
	pause = false;

	// Make sure that we are not dealing with game page with width: '0' or less
	Q_ASSERT(width > 0);

	m_width = width;
	m_size = width*width;

	// Prepare tiles
	m_tiles.resize(m_size);
	std::iota(m_tiles.begin(), m_tiles.end(), 1);

	// Prepare win position
	winner = m_tiles;

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);
	winner.erase(winner.end()-1);

	// Shuffle tiles
	shuffle();

	// Save this shuffle for the reseting
	tiles_saved = m_tiles;

	endResetModel();
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

	// We need to traverse m_tiles
	// to find 16-tile and add appropriate coefficient to the conversions count
	// TODO: ranges
	auto dummy = std::find(m_tiles.begin(), m_tiles.end(), m_size);

	size_t indexer {};

	// If somehow we didn't receive 16-tile in the container
	// we will return false
	if (dummy == m_tiles.end()) return false;
	else
	{
		// We are starting with Tile numbered '1'
		const size_t start_tile {1};

		//
		indexer = dummy - m_tiles.begin();

		// Add to the conversions count the number of
		// rows (plus one) that that empty space have to pass
		// to get to the position: '0' - left up corner
		inverionsCount += start_tile + indexer / m_width;
	}

	// But if number of conversions are even
	// this means that game is solvable
	return (inverionsCount % 2) == 0;
}

// Identify position on the game page (2D index) by some 1D index
identificator GamePage::getTablePos(const size_t& index) const
{
	identificator result {};

	result.first = index / m_width;
	result.second = index % m_width;

	return result;
}

/*
We check tiles in the container, and if it's a win position
we emmit signal to front end
*/
void GamePage::checkWin()
{
	// TERRIBLE CYCLE
	for(size_t index{}; index < winner.size(); index++)
	{
		if(m_tiles.at(index).value != winner.at(index).value)
		{
			qDebug() << "Game not finished!";
			qDebug() << m_tiles.at(index).value << "!=" << winner.at(index).value;

			return;
		}
	}

	status = true;

	//emit pop_window for win
	emit statusChanged();

	qDebug() << "You won!";
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
