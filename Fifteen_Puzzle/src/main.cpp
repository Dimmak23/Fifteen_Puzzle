//Qt headers
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//User headers
#include "../headers/gamepage.hpp"

int main(int argc, char *argv[])
{
	//Init window constructor
	QGuiApplication game(argc, argv);

	//Init game engine
	QQmlApplicationEngine engine;

	//Init GamePage utility
	GamePage model;

	/*
	This template function registers the C++ type in the QML system
	with the name qmlName, in the library imported from uri having
	the version number composed from versionMajor and versionMinor.
	*/
	qmlRegisterType<GamePage> ("BackEnd", 1, 0, "CPP_Tiles");

	//Init address of the main.qml
	const QUrl url(u"qrc:/Fifteen_Puzzle/resources/main.qml"_qs);

	//
	QObject::connect(
				//
				&engine,
				//
				&QQmlApplicationEngine::objectCreated,
				//
				&game,
				//
				[url](QObject *obj, const QUrl &objUrl)
	{
		if (!obj && url == objUrl) QCoreApplication::exit(-1);
	},
	//
	Qt::QueuedConnection
	);

	//
	engine.load(url);

	//
	return game.exec();
}
