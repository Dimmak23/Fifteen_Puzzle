import QtQuick
import QtQuick.Controls 2.5

Rectangle {
	id: _aboutNotice
	visible: false

	z: _parsedGamePage.z + 1

	width: _parsedGamePage.width
	height: _parsedGamePage.height

	color: "gray"
	opacity: 0.87

	anchors.top: _parsedGamePage.top

	Text {
		id: _aboutText

		color: "white"

		//TODO: fix this
		text: "Game designed and produced\nby Dmytro Kovryzhenko,
2 november 2022.\n\n\nAll rights reserved."

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
		focus: true //focus on this button, need to be activated by 'Enter' key
		highlighted: true //also highlight it, that user will know

		width: Math.max(_parsedGamePage.width / 4, 5)
		height: Math.max(_parsedGamePage.height / 16, 10)

		anchors.right: _aboutNotice.right
		anchors.bottom: _aboutNotice.bottom
		anchors.bottomMargin: 10
		anchors.rightMargin: 10

		onClicked: applicationW.proceedOk()
		Keys.onReturnPressed: applicationW.proceedOk() // Enter key
		Keys.onEnterPressed: applicationW.proceedOk() // Numpad enter key
	}
}
