#include "AuthProtocol/Events/LoginRequest.h"
#include "AuthProtocol/AuthLink.h"
#include "DummyClass.h"

#include <ace/Mutex.h>
#include <ace/SOCK_Connector.h>
#include <ace/Connector.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <stdint.h>

static uint16_t SERVER_PORT = ACE_DEFAULT_SERVER_PORT;
static QString const SERVER_HOST = ACE_DEFAULT_SERVER_HOST;
static const int MAX_ITERATIONS = 4;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("AuthExerciser");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("SEGS AuthExerciser");

    qInfo().noquote().nospace() << parser.applicationDescription() << " v" << QCoreApplication::applicationVersion() << endl;

    parser.addPositionalArgument("serverHost", "The IP address authexerciser should connect to");
    parser.addPositionalArgument("serverPort", "The port authserver is listening to");
    parser.addPositionalArgument("maxIterations", "The maximum of messages to send authserver");

    parser.process(app);

    const QStringList args = parser.positionalArguments(); // Grab the arguments from the parser.
    QString serverHost = args.length() >= 1 ? args[0] : SERVER_HOST; // Place them in their own variables, or use the default values if they aren't given.
    uint16_t serverPort = args.length() >= 2 ? args[1].toInt() : SERVER_PORT;
    //int maxIterations = args.length() >= 3 ? args[2].toInt() : MAX_ITERATIONS;

    AuthLink::g_target = new DummyClass();
    AuthLink::g_target->activate();
    ACE_SOCK_Stream server;
    ACE_Connector<AuthLink, ACE_SOCK_Connector> connector;
    AuthLink client(AuthLinkType::Client);
    AuthLink *pc = &client;
    ACE_INET_Addr addr(serverPort, qPrintable(serverHost));

    qInfo().noquote().nospace() << "IP and Port entered: " << serverHost << ":" << serverPort;
    qInfo().noquote().nospace() << "Attempting to connect to authserver...";

    if(connector.connect(pc, addr) == -1) // Connection fails.
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "open"), -1);
    else // Connection succeeds.
        qInfo().noquote().nospace() << "Success!";

    // Attempt to communicate with authserver.
    while(1)
    {
        ACE_Reactor::instance()->run_reactor_event_loop();
    }

    if(server.close() == -1) // Close attempt fails.
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "close"), -1);
    else // Close attempt succeeds.
        qInfo().noquote().nospace() << "Disconnecting gracefully...";

    return 0;
}
