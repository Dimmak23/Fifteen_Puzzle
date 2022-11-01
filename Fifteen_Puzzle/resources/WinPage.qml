import QtQuick 2.15
import QtQuick.Controls 2.5

Rectangle {
	id: _winNotice
	visible: false

	z: _parsedGamePage.z + 1

	width: _parsedGamePage.width
	height: _parsedGamePage.height

	color: "black"
	opacity: 0.93

	anchors.top: _parsedGamePage.top

	Text {
		id: _winText

		color: "white"
		text: "Congratulations!"

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
			pointSize: Math.max(_winNotice.width / 28, 1)
		}

	}

	Text {
		id: _winSubText

		color: "white"
		text: "You have won...\nDo you want to start the new game?"

		anchors.left: parent.left
		anchors.top: _winText.bottom
		anchors.leftMargin: 10
		anchors.topMargin: 50

		font {
			family: resFont.name

			// Math.min(thisTile.width, thisTile.height) / 2 - give us
			// reasonable font size => RS depending on the tile size.
			// BUT! We should prevent assigning of the value '0' to it.
			// So we set the font size to the max between RS and '1'
			// (the smallest aceptable value)
			pointSize: Math.max(_winNotice.width / 50, 1)
		}
	}

	Button {
		id: _newGame
		text: "New..."
		flat: false
		focus: true //focus on this button, need to be activated by 'Enter' key
		highlighted: true //also highlight it, that user will know

		width: Math.max(_parsedGamePage.width / 4, 5)
		height: Math.max(_parsedGamePage.height / 16, 10)

		anchors.right: _winNotice.right
		anchors.bottom: _winNotice.bottom
		anchors.bottomMargin: 10
		anchors.rightMargin: 10

		onClicked: _newGame.proceedOk()
		Keys.onReturnPressed: _newGame.proceedOk() // Enter key
		Keys.onEnterPressed: _newGame.proceedOk() // Numpad enter key

		function proceedOk() {
			_parsedGamePage.model.newPage()
			_winNotice.visible = false
		}
	}

	Button {
		id: _quitGame
		text: "Quit"
		flat: false

		width: Math.max(_parsedGamePage.width / 4, 5)
		height: Math.max(_parsedGamePage.height / 16, 10)

		anchors.left: _winNotice.left
		anchors.bottom: _winNotice.bottom
		anchors.bottomMargin: 10
		anchors.leftMargin: 10

		onClicked: {
			Qt.quit()
		}
	}
}
