#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdint>
#include "eprosimartps/rtps_all.h"
#include "eprosimartps/dds/DomainParticipant.h"


using namespace eprosima;
using namespace rtps;

// 根据字节序定义默认字节序
#if defined(__LITTLE_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = LITTLEEND;
#elif defined (__BIG_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = BIGEND;
#endif

// 全局的参与者参数
ParticipantParams_t globalParam;

// 创建参与者
Participant* createParticipant() {
    globalParam.domainId = 80;
    return DomainParticipant::createParticipant(globalParam);
}

// 销毁参与者
void destroyParticipant(Participant* p) {
    if (p) {
        dds::DomainParticipant::getInstance()->removeParticipant(p);
    }
}

// 简单的发布者函数示例
void publisherExample(Participant* p) {
    if (p) {
        WriterParams_t writerParams;
        // 初始化写入器参数，这里只是示例，可能需要更多设置
        writerParams.topic.topicKind = NO_KEY;
        writerParams.topic.topicName = "MyTopic";
        writerParams.topic.topicDataType = "MyDataType";
        // 创建写入器
        Writer* writer = DomainParticipant::createWriter(p, writerParams);
        if (writer) {
            CDRMessage_t msg;
            // 初始化消息，这里只是示例，需要根据实际情况填充消息内容
            msg.pos = 0;
            msg.length = 100;  // 假设消息长度为100
            msg.max_size = RTPSMESSAGE_MAX_SIZE;
            msg.buffer = new char[msg.max_size];
            msg.msg_endian = DEFAULT_ENDIAN;
            // 发送消息
            DomainParticipant::write(writer, msg);
            // 清理消息内存
            delete[] msg.buffer;
            // 删除写入器
            DomainParticipant::deleteWriter(p, writer);
        }
    }
}

// 简单的订阅者函数示例
void subscriberExample(Participant* p) {
    if (p) {
        ReaderParams_t readerParams;
        // 初始化读取器参数，这里只是示例，可能需要更多设置
        readerParams.topic.topicKind = NO_KEY;
        readerParams.topic.topicName = "MyTopic";
        readerParams.topic.topicDataType = "MyDataType";
        // 创建读取器
        Reader* reader = DomainParticipant::createReader(p, readerParams);
        if (reader) {
            CDRMessage_t receivedMsg;
            // 接收消息，这里只是示例，可能需要更复杂的接收逻辑
            if (DomainParticipant::read(reader, receivedMsg)) {
                // 处理接收到的消息
                std::cout << "Received message with length: " << receivedMsg.length << std::endl;
            }
            // 删除读取器
            DomainParticipant::deleteReader(p, reader);
        }
    }
}

int main() {
    Participant* participant = createParticipant();
    if (participant) {
        publisherExample(participant);
        subscriberExample(participant);
        destroyParticipant(participant);
    }
    return 0;
}