import QtQuick 2.15
import QtQuick.Controls 2.5

import BackEnd 1.0

GridView {
	id: _menuHolder

	// We have passed BackEnd model
	model: CPP_Tiles {

	}

	delegate: MenuBar {
		id: _menuBar
		width: applicationW.width
		height: 30
		visible: true

		Menu {
			id: _menuGame
			title: qsTr("&Game")

			Action {
				text: qsTr("&Start new game")
				shortcut: "Ctrl+N"
				onTriggered: {
					_menuHolder.model.resetPage()
				}
			}
			MenuSeparator { }
			Action {
				text: qsTr("&Quit")
				shortcut: "Esc"
				onTriggered: { Qt.quit() }
			}
		}

		Menu {
			title: qsTr("&Settings")
			Action { text: qsTr("Edit difficulty level") }
		}

		Menu {
			title: qsTr("&Help")
			Action { text: qsTr("&How to play?") }
			Action { text: qsTr("&About...") }
		}
	}
}
