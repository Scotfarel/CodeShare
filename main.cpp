#include "headers/NoteBook.h"
#include "headers/ClientConnector.h"
#include <QApplication>

int main(int argc, char *argv[]){

    qRegisterMetaType<std::pair<int,wchar_t>>("std::pair<int,wchar_t>");
    qRegisterMetaType<std::string>("std::string");

    QCoreApplication::setOrganizationName("Friends co");
    QCoreApplication::setOrganizationDomain("https://github.com/Scotfarel/CodeShare");
    QCoreApplication::setApplicationName("Codeshare");
    QApplication app(argc, argv);
    ClientConnector *client;
   if (argc == 2) {
       client = new ClientConnector(argv[1]);
   } else {
       client = new ClientConnector("anon");
   }
    NoteBook w = NoteBook(client);
    w.show();
    return app.exec();
}
