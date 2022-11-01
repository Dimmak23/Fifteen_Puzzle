import QtQuick
import QtQuick.Controls 2.5

//Item {

//    Label {
//        text: "Game designed and produced by Dmytro Kovryzhenko, 31 october 2022.\nAll rights reserved."
//    }

//}

Rectangle {
	id: _aboutNotice
	visible: false

	z: _parsedGamePage.z + 1

	width: _parsedGamePage.width
	height: _parsedGamePage.height

	color: "black"
	opacity: 0.87

	anchors.top: _parsedGamePage.top

	Text {
		id: _winText

		color: "white"
		text: "Game designed and produced by Dmytro Kovryzhenko,\n31 october 2022.\nAll rights reserved."

		anchors.left: parent.left
		anchors.top: parent.top
		anchors.leftMargin: 10
		anchors.topMargin: 10

		font {
			family: resFont.name

			// Math.min(thisTile.width, thisTile.height) / 2 - give us
			// reasonable font size => RS depending on the tile size.
			// BUT! We should prevent assigning of the value '0' to it.
			// So we set the font size to the max between RS and '1'
			// (the smallest aceptable value)
			pointSize: Math.max(_aboutNotice.width / 28, 1)
		}

	}

	Button {
		id: _closeAbout
		text: "Ok"
		flat: false

		width: Math.max(_parsedGamePage.width / 4, 5)
		height: Math.max(_parsedGamePage.height / 16, 10)

		anchors.right: _aboutNotice.right
		anchors.bottom: _aboutNotice.bottom
		anchors.bottomMargin: 10
		anchors.rightMargin: 10

		onClicked: {
//			_parsedGamePage.model.newPage()
			_aboutNotice.visible = false;
			_parsedGamePage.model.pause = false;
		}
	}
}
