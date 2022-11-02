// Qt headers
#include <QGuiApplication>
#include <QQmlApplicationEngine>
// User headers
#include "../headers/gamepage.hpp"

int main(int argc, char *argv[])
{
	// Init window constructor
	QGuiApplication game(argc, argv);

	// Init game engine
	QQmlApplicationEngine engine;

	// As you can see we don't initialize GamePage object here
	// Because we are forking it in the front end

	/*
	This template function registers the C++ type in the QML system
	with the name qmlName, in the library imported from uri having
	the version number composed from versionMajor and versionMinor.
	*/
	// But we still need to register our GamePage C++ class
	qmlRegisterType<GamePage> ("BackEnd", 1, 0, "CPP_Tiles");

	// Init address of the main.qml
	const QUrl url(u"qrc:/Fifteen_Puzzle/resources/main.qml"_qs);

	// Connect game application and game engine
	QObject::connect(
				// What's the engine?
				&engine,
				// What's the signal?
				&QQmlApplicationEngine::objectCreated,
				// Apply game slot
				&game,
				// In the Lambda function object is checked for NULLPTR
				// and objUrl is checked if it's created from the correct Url
				[url](QObject *obj, const QUrl &objUrl)
			// NOTE:
			/*
				We don't need this whole check.
				It would be enough to check if obj is not a null pointer,
				since that would mean that load failed, as states the
				documentation. The second check (url == objUrl) is superfluous
				and will never be true. The only way this fails,
				is if the url to qml file was provided as a QString,
				because:

						Note: If the path to the component was provided
						as a QString containing a relative path,
						the url will contain a fully resolved path to the file.

				But in that case it wouldn't be a good idea
				to kill the application.
			*/
	{
		// If urls is okay but object didn't created we will terminate app
		if (!obj && url == objUrl) QCoreApplication::exit(-1);
	},
	/*

	Assuming game's thread is running an event loop,
	emitting the signal (QQmlApplicationEngine::objectCreated)
	will post an event to game's event loop. The event loop queues the event,
	and eventually invokes the games slot method whenever control returns to it
	(it being the event loop). This makes it pretty easy to deal with
	communication between/among threads in Qt
	(again, assuming your threads are running their own local event loops).
	You don't have to worry about locks, etc. because the event loop serializes
	the slot invocations.

	If you specify a queued connection - even for two objects
	on the same thread. The event is still posted to the thread's event loop.
	So, the method call is still asynchronous, meaning it can be delayed in
	unpredictable ways (depending on any other events the loop may need
	to process). However, if you don't specify a connection method,
	the direct method is automatically used for connections between objects
	on the same thread.

	*/
	Qt::QueuedConnection
	);

	// pass url
	engine.load(url);

	// run application
	return game.exec();
}
