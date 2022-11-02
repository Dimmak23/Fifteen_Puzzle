import QtQuick

GridView {
    id: gameGrid
	cellWidth: _parsedGamePage._parsedCellWidth
	cellHeight: _parsedGamePage._parsedCellHeight

    delegate: Item {
        id: _oneTile
		width: gameGrid.cellWidth
		height: gameGrid.cellHeight

		// Don't show the #<last>-tile
		visible: display !== _parsedGamePage.model.hiddenPos ? true : false

        Tile {
			id: _oneTileText
			initialText: display

			anchors.fill: _oneTile
			anchors.margins: 2

			MouseArea {
				anchors.fill: parent
				acceptedButtons: Qt.LeftButton
				onClicked: {
					// We are passing tile by index to back end
					_parsedGamePage.model.move(index);
				}
			}
        }
    }
}
