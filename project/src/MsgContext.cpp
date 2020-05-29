//
// Created by ivan on 5/22/20.
//

#include <MsgContext.h>


MsgContext::MsgContext() : bodySize(0), isLastChunk(false) {}

char *MsgContext::getData() {
    return buf_str;
}

const char *MsgContext::getData() const {
    return buf_str;
}

char *MsgContext::getBody() {
    return buf_str + HEADER;
}

const char *MsgContext::getBody() const {
    return buf_str + HEADER;
}

std::size_t MsgContext::getLength() const {
    return HEADER + bodySize;
}

std::size_t MsgContext::getBodyLength() const {
    return bodySize;
}

void MsgContext::setBodyLength(std::size_t new_length) {
    bodySize = new_length;
}

void MsgContext::decodeHeader() {
    char header[HEADER + 2] = "";
    std::strncat(header, buf_str + 1, HEADER);
    bodySize = std::atoi(header);
    this->setLastChunk(*buf_str);
}

void MsgContext::encodeHeader() {
    char header[HEADER + 1] = "";
    std::sprintf(header, "%5lu", bodySize);
    std::memcpy(buf_str + 1, header, HEADER);
}

bool MsgContext::isEnd() {
    return isLastChunk;
}

void MsgContext::setLastChunk(bool flag) {
    this->isLastChunk = flag;
}


MsgContext MsgContext::createMessage(const std::string &chunkResponse, bool isLastChunk) {
    MsgContext msg;
    msg.setLastChunk(isLastChunk);
    msg.setBodyLength(chunkResponse.size());
    std::memcpy(msg.getBody() + 1, chunkResponse.data(), msg.getBodyLength());
    msg.setBodyLength(chunkResponse.size());
    msg.getBody()[msg.getBodyLength() + 1] = '\0';
    msg.encodeHeader();
    std::memcpy(msg.getData(), &msg.isLastChunk, 1);
    return msg;
}




