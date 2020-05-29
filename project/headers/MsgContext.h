//
// Created by ivan on 5/22/20.
//

#ifndef CODESHARE_MSGCONTEXT_H
#define CODESHARE_MSGCONTEXT_H

#include <string>
#include <cstring>

#define MAX_CHUNK_SIZE 65000
#define HEADER 5

//  Class contains chars to send
class MsgContext {
private:
    char buf_str[MAX_CHUNK_SIZE + HEADER + 1]{};
    std::size_t bodySize;
    bool isLastChunk;

public:
    MsgContext();

    static MsgContext createMessage(const std::string &chunkResponse, bool isLastChunk);

    //  Getters
    const char *getData() const;

    char *getData();

    const char *getBody() const;

    char *getBody();

    std::size_t getBodyLength() const;

    std::size_t getLength() const;

    //  Setters
    void setBodyLength(std::size_t new_length);

    void setLastChunk(bool flag);

    // Serializers
    void decodeHeader();

    void encodeHeader();

    bool isEnd();
};

#endif //CODESHARE_MSGCONTEXT_H
