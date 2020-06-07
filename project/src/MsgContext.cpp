//
// Created by ivan on 5/22/20.
//

#include <MsgContext.h>
#include <cstring>

MsgContext::MsgContext() : body_size(0) {}

const char *MsgContext::data() const {
    return buf_str;
}

char *MsgContext::getData() {
    return buf_str;
}

const char *MsgContext::body() const {
    return buf_str + HEADER;
}

char *MsgContext::getBody() {
    return buf_str + HEADER;
}

std::size_t MsgContext::length() const {
    return HEADER + body_size;
}

std::size_t MsgContext::getBodyLength() const {
    return body_size;
}

void MsgContext::setBodyLength(std::size_t new_length) {
    body_size = new_length;
}

void MsgContext::decodeHeader() {
    char header[HEADER + 2] = "";
    std::strncat(header, buf_str + 1, HEADER);
    body_size = std::atoi(header);
    this->setLastChunk(*buf_str);
}

void MsgContext::encodeHeader() {
    char header[HEADER + 1] = "";
    std::sprintf(header, "%5d", static_cast<int>(body_size));
    std::memcpy(buf_str + 1, header, HEADER);
}

char& MsgContext::isThisLastChunk() {
    return isLastChunk;
}

void MsgContext::setLastChunk(char val) {
    this->isLastChunk = val;
}

MsgContext MsgContext::createMessage(const std::string& chunkResponse, char isLastChunk) {
    MsgContext msg;
    msg.setLastChunk(isLastChunk);
    msg.setBodyLength(chunkResponse.size());
    std::memcpy(msg.getBody()+1, chunkResponse.data(), msg.getBodyLength());
    msg.setBodyLength(chunkResponse.size());
    msg.getBody()[msg.getBodyLength()+1] = '\0';
    msg.encodeHeader();
    std::memcpy(msg.getData(), &msg.isThisLastChunk(), 1);
    return msg;
}