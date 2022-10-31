import QtQuick

/*
Once this is registered, the type can be used in QML by importing the specified
type namespace and version number:
*/
import BackEnd 1.0

GridView {
    id: gameGrid

	// We have passed BackEnd model
	model: CPP_Tiles {

	}

	cellWidth: width / gameGrid.model.width
	cellHeight: height / gameGrid.model.width

    delegate: Item {
        id: _oneTile

		width: gameGrid.cellWidth
		height: gameGrid.cellHeight

		// Don't show the #16-tile
		visible: display !== gameGrid.model.hiddenPos ? true : false

        Tile {
			initialText: display

            anchors.fill: _oneTile
            anchors.margins: 2

//			MouseArea: {
//				anchors.fill: parent,
//				onClicked: {

//				}
//			}
        }
    }
}
