import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

//move this
import QtQuick.Window 2.3

/*
Once C++ GamePage class type is registered,
that type can be used in QML by importing the specified
type namespace and version number:
*/
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
		smooth: true //?
	}

	property int fromIndex: -1 // origin point
	// Not used
	property int toIndex: -1 // destination point

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

		// We need this properties to pass them to the SmartBar later
		property real _parsedCellWidth: width / _parsedGamePage.model.width
		property real _parsedCellHeight: height / _parsedGamePage.model.width

		// We can change cells sizes by resizing utility
		// BUT! Also we should allow to resize them when window is resized

		// _parsedGamePage width changes so do cell width
		onWidthChanged: {
			_parsedCellWidth = width / _parsedGamePage.model.width;
		}
		// _parsedGamePage height changes so do cell height
		onHeightChanged: {
			_parsedCellHeight = height / _parsedGamePage.model.width;
		}
	}

	property bool clickingTiles: false
	property bool draggingTiles: true

	SmartBar {
		id: _parsedMenuBar
	}

	TwoButtonPage {
		id: _parsedWinPage
		visible: false
		backColorValue: "black"
		titleTextValue: "Congratulations!"
		subtitleTextValue: "You have won...\nDo you want to start the new game?"
		okButtonText: "Ok"
		quitButtonVisible: true
	}

	TwoButtonPage {
		id: _parsedAboutPage
		visible: false
		backColorValue: "gray"
		titleTextValue: "Production info"
		// TODO: fix this
		subtitleTextValue: "Game designed and produced by Dmytro Kovryzhenko,
4 november 2022.\n\n\nAll rights reserved."
		okButtonText: "Ok"
		quitButtonVisible: false
	}

	Connections{
		target: _parsedGamePage.model
		function onFinishedChanged() { _parsedWinPage.visible = true; }
	}

	function proceedOk() {
		if(_parsedGamePage.model.finished)
		{
			_parsedGamePage.model.newPage();
			_parsedWinPage.visible = false;
		}
		else if(_parsedGamePage.model.pause)
		{
			_parsedAboutPage.visible = false;
			_parsedGamePage.model.pause = false;
		}
	}
}
