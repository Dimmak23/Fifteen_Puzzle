//Qt headers
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
	//Init window constructor
	QGuiApplication game(argc, argv);

	//Init game engine
	QQmlApplicationEngine engine;

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
