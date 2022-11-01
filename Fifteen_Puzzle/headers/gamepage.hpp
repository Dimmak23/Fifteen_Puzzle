#ifndef GAMEPAGE_H
#define GAMEPAGE_H

// Qt headers
#include <QAbstractListModel>

// C++ headers
#include <vector>

// Aliases
using identificator = std::pair<size_t, size_t>;

// Defines
#define to_i(lvalue) static_cast<int>(lvalue)

class GamePage : public QAbstractListModel
{
	Q_OBJECT

	// Using Q_PROPERTY to pass game size consts to the FrontEnd
	Q_PROPERTY(int width READ width CONSTANT)
	// We know about hidden tile from this property
	Q_PROPERTY(int hiddenPos READ size CONSTANT)
	//
	Q_PROPERTY(NOTIFY statusChanged)

	public:
		GamePage(
				const size_t& parseWidth = initialPageWidth,
				QObject* parent = nullptr
		);

		struct Tile
		{
			size_t value{};

			/*
			Setting up a very RAW assign operator
			when we are going to assign an integer (size_t but still integer)
			to the Tile. So we are open Tile,
			touch value and assign src to it.
			Then we return reference to the Tile object
			*/
			Tile& operator= (const size_t& src)
			{
				this->value = src;
				return *this;
			}

			// Setting up a method to compare and give result.
			// Are Tile left operand and right value - equal?
			bool operator== (const size_t& right_value) const
			{
				return right_value == this->value;
			}
			// Are Tile left operand and right_operand.value - equal?
			bool operator== (const Tile& right_operand) const
			{
				return right_operand.value == this->value;
			}
		};

		// Send to the front end game page width in tile units
		size_t width() const;

		// Send to the front end tile content that we don't want to show
		size_t size() const;

		// We could ignore move so return type is bool
		// add Q_INVOKABLE to use method in the QML
		Q_INVOKABLE /*bool*/void move(const int& index);

		// Invoke initializing the new game
		Q_INVOKABLE void newPage();

		// Invoke reset to the start position of the current game
		Q_INVOKABLE void resetPage();

		bool status;

	signals:

		void statusChanged();

	private:

		// Shuffle the tiles with Mersenne Twister random generator
		void shuffle();

		// Let's prevent us from passing the too big value as rowIndex
		bool validatePosition(const size_t& pos) const;

		/*
		Validation method for checking if we are generate the
		solvable shuffle
		*/
		bool validateShuffle() const;

		// Identify position on the game page (2D index) by some 1D index
		identificator getTablePos(const size_t& index) const;

		/*
		We check tiles in the container, and if it's a win position
		we emmit signal to front end
		*/
		void checkWin();

		/*
		Returns the data stored under the given
		role for the item referred to by the index.
		*/
		QVariant data(
				//The QModelIndex class is used to locate data in a data model
				const QModelIndex &index,
				/*
				Each item in the model has a set of data elements associated
				with it, each with its own role. The roles are used by the
				view to indicate to the model which type of data it needs.
				Custom models should return data in these types.
				*/
				int role = Qt::DisplayRole // == 0
				//The key data to be rendered in the from of text (QString)
		) const override;

		/*
		Returns the number of rows under the given parent.
		When the parent is valid it means that rowCount
		is returning the number of children of parent.
		*/
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;

		static constexpr size_t initialPageWidth {4};
		const size_t m_width;
		const size_t m_size;

		// Container with tiles content
		std::vector<Tile> m_tiles;

		// Container with initial tiles content after succesful shuffle
		std::vector<Tile> tiles_saved;

		// Win position
		std::vector<Tile> winner;
};

#endif // GAMEPAGE_H
