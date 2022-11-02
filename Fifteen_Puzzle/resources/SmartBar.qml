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
				// FROM TEST TASK (5.a):
				// “New game” button - generate a new random start position
				// block start new game while win page or about page showing
				if(!_parsedGamePage.model.finished
						&& !_parsedGamePage.model.pause)
				{
					_parsedGamePage.model.newPage()
				}
			}
		}
		Action {
			text: qsTr("&Reset current game (Ctrl+R)")
			shortcut: "Ctrl+R"
			onTriggered: {
				// FROM TEST TASK (5.b):
				// “Reset” - reset the current puzzle to starting position
				// block reset while win page or about page showing
				if(!_parsedGamePage.model.finished
						&& !_parsedGamePage.model.pause)
				{
					_parsedGamePage.model.resetPage()
				}
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
		id: _settings
		title: qsTr("Settings")

		// Recalculate width and height
		function resizeTiles(value){
			// block resize while win page or about page showing
			if(!_parsedGamePage.model.finished
					&& !_parsedGamePage.model.pause)
			{
				_parsedGamePage.model.resizeGrid(value);
				_parsedGamePage._parsedCellWidth =
						_parsedGamePage.width / _parsedGamePage.model.width
				_parsedGamePage._parsedCellHeight =
						_parsedGamePage.height / _parsedGamePage.model.width
			}
		}

		Menu {
			title: "Edit difficulty level"

			/*
			   FROM TEST TASK:
			   ==> OPTIONAL:
			   Implement levels of difficulty.
			   And this script will resize game page according to the new
			   pattern: 3x3, 4x4, 5x5.
			*/
			Action {
				text: qsTr("&Easy - 3x3 (Ctrl+E)")
				shortcut: "Ctrl+E"
				onTriggered: { _settings.resizeTiles(3); }
			}
			Action {
				text: qsTr("&Medium - 4x4 (Ctrl+M)")
				shortcut: "Ctrl+M"
				onTriggered: { _settings.resizeTiles(4); }
			}
			Action {
				text: qsTr("&Hard - 5x5 (Ctrl+H)")
				shortcut: "Ctrl+H"
				onTriggered: { _settings.resizeTiles(5); }
			}
		}
	}
	Menu {
		id: _help
		title: qsTr("Help")
		// TODO: implement this
//		Action { text: qsTr("How &to play? (Ctrl+T)") }
		Action {
			text: qsTr("&About... (Ctrl+A)")
			shortcut: "Ctrl+A"
			onTriggered: {
				// block about page while win page are showing
				if(!_parsedGamePage.model.finished)
				{
					_parsedAboutPage.visible = true;
					_parsedGamePage.model.pause = true;
				}
			}
		}
	}
}
