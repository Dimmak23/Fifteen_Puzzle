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
	// Provide access to front-end for 'status' variable
	Q_PROPERTY(bool finished READ getFinished NOTIFY finishedChanged)
	// Provide access to front-end for 'pause' variable
	Q_PROPERTY(bool pause READ getPause WRITE setPause NOTIFY pauseChanged)

	public:

		GamePage(
				const size_t& parseWidth = initialPageWidth,
				QObject* parent = nullptr
		);

		// Send to the front end game page width in tile units
		size_t width() const;

		// Send to the front end tile content that we don't want to show
		size_t size() const;

		// Write access to pause variable from front-end
		void setPause(const bool& boolean){ pause = boolean; emit pauseChanged(); }

		// Read access to pause variable from front-end
		bool getPause(){ return pause; }

		// Read access to status variable from front-end
		bool getFinished() { return finished; }

		// We could ignore move so return type is bool
		// add Q_INVOKABLE to use method in the QML
		Q_INVOKABLE void move(const int& index);

		// Invoke initializing the new game
		Q_INVOKABLE void newPage();

		// Invoke reset to the start position of the current game
		Q_INVOKABLE void resetPage();

		// Invoke resizing tiles grid method
		Q_INVOKABLE void resizeGrid(const int& width);

		// Win situation variable: true - it's a win, false - in the process
		bool finished;

		// Pause situation, when user can read info pages (about,...)
		bool pause;

	signals:

		void finishedChanged();

		void pauseChanged();

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
		We setting game page variables and containers multiple times
		so to get rid of repetetive code we can provide a special
		method to do this.
		*/
		void reusableConstructor(const int& parseWidth);

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
		size_t m_width;
		size_t m_size;

		// Container with tiles content
		std::vector<size_t> m_tiles;

		// Container with initial tiles content after succesful shuffle
		std::vector<size_t> tiles_saved;

		// Win position
		std::vector<size_t> tiles_win;
};

#endif // GAMEPAGE_H
