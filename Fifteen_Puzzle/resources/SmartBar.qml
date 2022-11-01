import QtQuick 2.15
import QtQuick.Controls 2.5

MenuBar {
	id: _menuBar
	width: applicationW.width
	height: 30
	visible: true

	Menu {
		id: _menuGame
		title: qsTr("Game")

		Action {
			text: qsTr("Start &new game (Ctrl+N)")
			shortcut: "Ctrl+N"
			onTriggered: {
				_parsedGamePage.model.newPage()
			}
		}
		Action {
			text: qsTr("&Reset current game (Ctrl+R)")
			shortcut: "Ctrl+R"
			onTriggered: {
				_parsedGamePage.model.resetPage()
			}
		}
		MenuSeparator { }
		Action {
			text: qsTr("Quit (Esc)")
			shortcut: "Esc"
			onTriggered: { Qt.quit() }
		}
	}
	Menu {
		title: qsTr("Settings")

		Menu {
			title: "Edit difficulty level"
			Action {
				text: qsTr("&Easy - 3x3 (Ctrl+E)")
				shortcut: "Ctrl+E"
				onTriggered: {
					_parsedGamePage.model.resizeGrid(3);
					// Recalculate width and height
					_parsedGamePage._parsedCellWidth =
							_parsedGamePage.width / _parsedGamePage.model.width
					_parsedGamePage._parsedCellHeight =
							_parsedGamePage.height / _parsedGamePage.model.width
				}
			}
			Action {
				text: qsTr("&Medium - 4x4 (Ctrl+M)")
				shortcut: "Ctrl+M"
				onTriggered: {
					_parsedGamePage.model.resizeGrid(4);
					// TODO: REPETETIVE CODE!
					_parsedGamePage._parsedCellWidth =
							_parsedGamePage.width / _parsedGamePage.model.width
					_parsedGamePage._parsedCellHeight =
							_parsedGamePage.height / _parsedGamePage.model.width
				}
			}
			Action {
				text: qsTr("&Hard - 5x5 (Ctrl+H)")
				shortcut: "Ctrl+H"
				onTriggered: {
					_parsedGamePage.model.resizeGrid(5);
					// TODO: REPETETIVE CODE!
					_parsedGamePage._parsedCellWidth =
							_parsedGamePage.width / _parsedGamePage.model.width
					_parsedGamePage._parsedCellHeight =
							_parsedGamePage.height / _parsedGamePage.model.width
				}
			}
		}
	}

	Menu {
		title: qsTr("Help")
		// TODO: implement this
//		Action { text: qsTr("How &to play? (Ctrl+T)") }
		Action {
			text: qsTr("&About... (Ctrl+A)")
			shortcut: "Ctrl+A"
			onTriggered: {
				_parsedAboutPage.visible = true;
				_parsedGamePage.model.pause = true;
			}
		}
	}
}
