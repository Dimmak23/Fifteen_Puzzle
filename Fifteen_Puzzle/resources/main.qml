import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
//import QtQuick.Dialogs

//move this
import QtQuick.Window 2.3
//import QtGraphicalEffects 1.15

import BackEnd 1.0

Window {
    id: applicationW

	width: 600
	height: 630
    visible: true
    title: qsTr("15-Puzzle")

	FontLoader {
		id: resFont
		source: "qrc:/Resources/fonts/NinjaGarden-1gAL.ttf"
	}

	Image {
		id: background
		source: "qrc:/Resources/pics/metalic.jpg"
		z: applicationW.z - 1
		width: applicationW.width
		height: applicationW.height
		smooth: true //
	}

	GamePage {
		id: _parsedGamePage

		// MIND your steps, you need to initialize model
		// from back end only once!
		model: CPP_Tiles {
			// This model will be used in the GamePage, MenuBar,...
		}

		anchors.bottom: parent.bottom
		width: applicationW.width
		height: applicationW.height - 30
	}

	SmartBar {
		id: _parsedMenuBar
	}

	Rectangle {
		id: _winNotice
		visible: false

		z: _parsedGamePage.z + 1

		width: _parsedGamePage.width
		height: _parsedGamePage.height

		color: "black"
		opacity: 0.93

		anchors.top: _parsedGamePage.top

//		Text {
//			id: _winText


//		}

		Button {
			id: _newGame
			text: "New..."
			flat: false

			width: _parsedGamePage.width / 4
			height: _parsedGamePage.height / 14

			anchors.right: _winNotice.right
			anchors.bottom: _winNotice.bottom
			anchors.bottomMargin: 10
			anchors.rightMargin: 10

			onClicked: {
				_parsedGamePage.model.newPage()
				_winNotice.visible = false
			}
		}

		Button {
			id: _quitGame
			text: "Quit"
			flat: false

			width: _parsedGamePage.width / 4
			height: _parsedGamePage.height / 14

			anchors.left: _winNotice.left
			anchors.bottom: _winNotice.bottom
			anchors.bottomMargin: 10
			anchors.leftMargin: 10

			onClicked: {
				Qt.quit()
			}
		}

	}

	Connections{
		target: _parsedGamePage.model
		onStatusChanged: _winNotice.visible = true;
	}

}
