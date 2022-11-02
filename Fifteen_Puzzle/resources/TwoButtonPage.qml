import QtQuick
import QtQuick.Controls 2.5

Rectangle {
	id: _notifier

	property string backColorValue: ""
	property string titleTextValue: ""
	property string subtitleTextValue: ""
	property bool quitButtonVisible: false

	color: backColorValue
	opacity: 0.87
	visible: false
	z: _parsedGamePage.z + 1
	width: _parsedGamePage.width
	height: _parsedGamePage.height

	anchors.top: _parsedGamePage.top

	Text {
		id: _title
		color: "white"
		text: titleTextValue

		anchors.left: parent.left
		anchors.top: parent.top
		anchors.leftMargin: 10
		anchors.topMargin: 10

		font {
			family: resFont.name
			// ! We should prevent assigning of the value '0' to size.
			// So we set the font size to the max between
			// calculated value and '1' (the smallest acceptable value)
			pointSize: Math.max(_parsedGamePage.width / 28, 1)
		}
	}

	Button {
		id: _okButton
		text: "Ok"
		flat: false
		focus: true //focus on this button, need to be activated by 'Enter' key
		highlighted: true //also highlight it, that user will know

		width: Math.max(parent.width / 4, 5)
		height: Math.max(parent.height / 16, 10)

		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		anchors.rightMargin: 10

		onClicked: applicationW.proceedOk()
		Keys.onReturnPressed: applicationW.proceedOk() // Enter key
		Keys.onEnterPressed: applicationW.proceedOk() // Numpad enter key
	}

	Text {
		id: _subtitle
		color: "white"
		text: subtitleTextValue

		anchors.left: parent.left
		anchors.top: _title.bottom
		anchors.leftMargin: 10
		anchors.topMargin: 50

		font {
			family: resFont.name
			// ! We should prevent assigning of the value '0' to size.
			// So we set the font size to the max between
			// calculated value and '1' (the smallest acceptable value)
			pointSize: Math.max(_parsedWinPage.width / 50, 1)
		}
	}

	Button {
		id: _quitButton
		text: "Quit"
		flat: false
		visible: quitButtonVisible

		width: Math.max(parent.width / 4, 5)
		height: Math.max(parent.height / 16, 10)

		anchors.left: parent.left
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		anchors.leftMargin: 10

		onClicked: {
			if (visible) Qt.quit()
		}
	}
}
