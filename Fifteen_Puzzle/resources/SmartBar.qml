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
			}
			Action {
				text: qsTr("&Medium - 4x4 (Ctrl+M)")
			}
			Action {
				text: qsTr("&Hard - 5x5 (Ctrl+H)")
			}
		}
	}

	Menu {
		title: qsTr("Help")
		Action { text: qsTr("How &to play? (Ctrl+T)") }
		Action { text: qsTr("&About... (Ctrl+A)") }
	}
}
