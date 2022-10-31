#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QAbstractListModel>
#include <vector>


class GamePage : public QAbstractListModel
{
	Q_OBJECT

	// Using Q_PROPERTY to pass game size consts to the FrontEnd
	Q_PROPERTY(int width READ width CONSTANT)
	// We know about hidden tile from this property
	Q_PROPERTY(int hiddenPos READ size CONSTANT)

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

			// Setting up a method to compare and give result
			// Are Tile left operand and Tile right operand - equal?
			bool operator==(const Tile& r_operand)
			{
				return r_operand.value == this->value;
			}
		};

		// Send to the front end game page width in tile units
		size_t width() const;

		// Send to the front end tile content that we don't want to show
		size_t size() const;

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
};

#endif // GAMEPAGE_H
