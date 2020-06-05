#ifndef PROJECT_INCLUDE_REQUEST_HANDLER_H_
#define PROJECT_INCLUDE_REQUEST_HANDLER_H_

#include <iostream>

#include "JsonUtility.h"
#include "json.hpp"
#include "Symbol.h"
#include "RoomScheduler.h"
#include "Connection.h"

class Connection;

template<class RoomSchedulerType>
class RequestHandler : public std::enable_shared_from_this<RequestHandler<RoomSchedulerType>> {
public:
    RequestHandler(RoomSchedulerType& roomScheduler);
    std::string handleRequest(const std::string &requestType, const json &jsonBuf, int &clientId) const;
    std::string newRoom(std::shared_ptr<Connection> connection);
    std::string joinRoom(const json &jsonBuf, std::shared_ptr<Connection> connection);
private:
    RoomSchedulerType& roomScheduler;
};

template<class RoomSchedulerType>
RequestHandler<RoomSchedulerType>::RequestHandler(RoomSchedulerType& roomScheduler) : roomScheduler(roomScheduler) {}

template<class RoomSchedulerType>
std::string RequestHandler<RoomSchedulerType>::handleRequest(const std::string &requestType, const json &jsonBuf, int &clientId) const {
    if (requestType == "INSERTION_REQUEST") {
        Symbol symbol;
        int indexEditor;
        int roomId;
        JsonUtility::fromJsonInsertion(jsonBuf, symbol, indexEditor, roomId);

        std::cout << "symbol received: " << symbol.getLetter() << "," << "ID: " << symbol.getSymbolId().first << "," << symbol.getSymbolId().second << std::endl;

        auto room = roomScheduler.getRoom(roomId);
        int newIndex = room->getSymbolIndex(indexEditor, room->getTextMap(), symbol);

        room->insertTextMap(newIndex, symbol);

        json jsonResponse;
        JsonUtility::toJsonInsertion(jsonResponse, "INSERTION_RESPONSE", symbol, indexEditor);
        const std::string response = jsonResponse.dump();
        return response;

    } else if (requestType == "REMOVAL_REQUEST") {
        std::vector<sId> symbolsId;
        int roomId;
        JsonUtility::fromJsonRemovalRange(jsonBuf, symbolsId, roomId);
        int newIndex;

        auto room = roomScheduler.getRoom(roomId);
        for(const sId& id : symbolsId) {
            newIndex = room->getIndexById(room->getTextMap(), id);
            if(newIndex != -1) {
                room->eraseTextMap(newIndex);
            }
        }

        json jsonResponse;
        JsonUtility::toJsonRemovalRange(jsonResponse, "REMOVAL_RESPONSE", symbolsId);
        const std::string response = jsonResponse.dump();
        return response;

    } else if (requestType == "CURSOR_CHANGE_REQUEST") {
        int pos;
        JsonUtility::fromJsonCursorChangeReq(jsonBuf, pos);
        std::cout << "pos received: " << std::to_string(pos) << std::endl;

        json jsonResponse;
        JsonUtility::toJsonCursorChange(jsonResponse, "CURSOR_CHANGE_RESPONSE", pos);
        const std::string response = jsonResponse.dump();
        return response;

    } else if (requestType == "INSERTIONRANGE_REQUEST") {
        std::vector<json> formattingSymbols;
        int startIndex;
        int roomId;
        JsonUtility::fromJsonInsertionRange(jsonBuf, formattingSymbols, startIndex, roomId);
        std::vector<Symbol> symbols = JsonUtility::fromJsonToFormattingSym(formattingSymbols);
        int newIndex = startIndex;

        auto room = roomScheduler.getRoom(roomId);
        for (const Symbol &s : symbols) {
            newIndex = room->getSymbolIndex(newIndex, room->getTextMap(), s);

            room->insertTextMap(newIndex, s);
        }

        json jsonResponse;
        std::vector<json> jsonSymbols = JsonUtility::fromSymToJson(symbols);
        JsonUtility::toJsonInsertionRange(jsonResponse, "INSERTIONRANGE_RESPONSE", startIndex, jsonSymbols, roomId);
        const std::string response = jsonResponse.dump();
        return response;

    }
    
    return std::string();
}

template<class RoomSchedulerType>
std::string RequestHandler<RoomSchedulerType>::newRoom(std::shared_ptr<Connection> connection) {
    auto room = roomScheduler.createRoom();
    room->enterRoom(connection);

    int roomId = room->getRoomId();
    json jsonResponse;
    JsonUtility::toJsonRoomId(jsonResponse, "CREATE_ROOM_RESPONSE", roomId);

    const std::string response = jsonResponse.dump();
    return response;
}

template<class RoomSchedulerType>
std::string RequestHandler<RoomSchedulerType>::joinRoom(const json &jsonBuf, std::shared_ptr<Connection> connection) {
    int roomId;
    JsonUtility::fromJsonRoomId(jsonBuf, roomId);

    auto room = roomScheduler.getRoom(roomId);
    room->enterRoom(connection);

    std::vector<Symbol> map = room->getTextMap();
    std::vector<json> symbols = JsonUtility::fromSymToJson(map);

    json jsonResponse;
    JsonUtility::toJsonInsertionRange(jsonResponse, "INSERTIONRANGE_RESPONSE", 0, symbols, roomId);

    const std::string response = jsonResponse.dump();
    return response;
}


#endif  //  PROJECT_INCLUDE_REQUEST_HANDLER_H_
