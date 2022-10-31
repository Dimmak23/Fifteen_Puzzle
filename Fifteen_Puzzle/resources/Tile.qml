import QtQuick

Rectangle {
    id: thisTile

    property string initialText: ""

    color: "transparent"
//    radius: 15
    border.color: "black"
    border.width: 2.5
    clip: true

    Image {
        id: backer
        source: "qrc:/Resources/pics/wood.jpg"
        z: thisTile.z - 1
        width: thisTile.width
        height: thisTile.height
        smooth: true //
        opacity: 0.9 //
        fillMode: Image.PreserveAspectCrop //
    }

    DefaultText {
        id: tileText
        text: thisTile.initialText

        font {
			// Math.min(thisTile.width, thisTile.height) / 2 - give us
			// reasonable font size => RS depending on the tile size.
            // BUT! We should prevent assigning of the value '0' to it.
			// So we set the font size to the max between RS and '1'
			// (the smallest aceptable value)
			pointSize: Math.max(
						   Math.min(thisTile.width, thisTile.height) / 2,
						   1)
        }

        anchors.centerIn: thisTile
    }

}
