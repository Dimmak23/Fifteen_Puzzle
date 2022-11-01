import QtQuick

/*
Once this is registered, the type can be used in QML by importing the specified
type namespace and version number:
*/
import BackEnd 1.0

GridView {
    id: gameGrid

	// We have passed BackEnd model
//	model: CPP_Tiles {

//	}

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
