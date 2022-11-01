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

	WinPage {
		id: _parsedWinPage
		visible: false
	}

	AboutPage {
		id: _parsedAboutPage
		visible: false
	}

	Connections{
		target: _parsedGamePage.model
		function onStatusChanged() { _parsedWinPage.visible = true; }
	}

}
