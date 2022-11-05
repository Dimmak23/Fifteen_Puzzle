import QtQuick

GridView {
    id: gameGrid
	cellWidth: _parsedGamePage._parsedCellWidth
	cellHeight: _parsedGamePage._parsedCellHeight

	// Not used
	DropArea {
		id: _dropArea
		anchors.fill: parent
		onDropped: {
			applicationW.toIndex
					= gameGrid.indexAt(_dropArea.drag.x,_dropArea.drag.y);
		}
	}

	delegate: Item {
		id: _oneTile
		width: gameGrid.cellWidth
		height: gameGrid.cellHeight

		// Don't show the #<last>-tile
		visible: display !== _parsedGamePage.model.hiddenPos ? true : false

		//
		Drag.active: _userTouch.drag.active
		Drag.hotSpot.x: _oneTile.width / 2
		Drag.hotSpot.y: _oneTile.height / 2

		//
		states: [
			State {
//				name: "name"
				when: _oneTile.Drag.active
				ParentChange {
					target: _oneTile
					parent: gameGrid.parent
				}
				AnchorChanges {
					target: _oneTile
					anchors.horizontalCenter: undefined
					anchors.verticalCenter: undefined
				}
			}
		]

		Tile {
			id: _oneTileText
			// TODO: need to understand how std::vector
			// connect with this 'display'
			initialText: display

			anchors.fill: _oneTile
			anchors.margins: 2

			MouseArea {
				id: _userTouch

				anchors.fill: parent
				acceptedButtons: Qt.LeftButton
				onClicked: {
					if(clickingTiles)
					{
						// We are passing tile by index to back end
						_parsedGamePage.model.move(index);
					}
				}
				drag.target: _oneTile
				drag.onActiveChanged: {
					if(draggingTiles)
					{
						if(_userTouch.drag.active)
						{
							applicationW.fromIndex = index;
							if (!_parsedGamePage.model.validateDrag(fromIndex))
								drag.target = parent;
						}
						else
							_parsedGamePage.model.move(fromIndex);
					}
					else drag.target = parent;
				}
			}
		}
	}
}
