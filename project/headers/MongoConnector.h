//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_MONGOCONNECTOR_H
#define CODESHARE_MONGOCONNECTOR_H

#include <string>
//#include <bsoncxx/builder/basic/document.hpp>
//#include <bsoncxx/builder/basic/kvp.hpp>
//#include <bsoncxx/json.hpp>
//#include <mongocxx/client.hpp>
//#include <mongocxx/instance.hpp>
//#include <mongocxx/uri.hpp>


class MongoConnector {
public:
    MongoConnector(std::string db, std::string coll) : dbName(std::move(db)), collName(std::move(coll)) {};
    std::string getCurrText();
    std::string getChunk();
    bool saveDiff();

private:
    std::string dbName;
    std::string collName;

//    mongocxx::instance instance;
//    mongocxx::client client;
//    mongocxx::database database;
//    mongocxx::collection collection;

    bool createTextTable(std::string tableName);
};

#endif //CODESHARE_MONGOCONNECTOR_H