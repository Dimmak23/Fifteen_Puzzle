import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

//move this
import QtQuick.Window 2.3
//import QtGraphicalEffects 1.15

//import BackEnd 1.0

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

	SmartBar {
		id: _parsedMenuBar
	}

	GamePage {
		id: _parsedGamePage
		anchors.bottom: parent.bottom
		width: applicationW.width
		height: applicationW.height - 30
	}

//	TabBar {
//		id: bar
//		width: parent.width
//		contentHeight: 30
//		y: parent.height - 30

//		TabButton {
//			text: qsTr("Game")
//			font.bold: true
//			font.pointSize: 16
//		}
//		TabButton {
//			text: qsTr("About...")
//			font.pointSize: 14
//		}
//	}

//	StackLayout {
//		width: parent.width
//		currentIndex: bar.currentIndex

//		Item {
//			id: gameTab

//			GamePage {
//				anchors.fill: gameTab
//				width: applicationW.width
//				height: applicationW.height - 30
//			}
//		}

//		Item {
//			id: aboutTab

//			AboutPage {

//			}
//		}
//	}

}
