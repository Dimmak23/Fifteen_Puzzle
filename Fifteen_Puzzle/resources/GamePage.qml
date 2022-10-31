import QtQuick

GridView {
    id: gameGrid

	model: 16

	cellWidth: width / 4
	cellHeight: height / 4

    delegate: Item {
        id: _oneTile

		width: gameGrid.cellWidth
		height: gameGrid.cellHeight

		// Don't show the #16-tile
		visible: index !== 15 ? true : false

        Tile {
			initialText: index + 1

            anchors.fill: _oneTile
            anchors.margins: 2
        }
    }
}
