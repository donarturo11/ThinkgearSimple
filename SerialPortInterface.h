#pragma once

class SerialPortInterface
{
public:
    SerialPortInterface() {}
    ~SerialPortInterface() {}
    virtual bool setup(std::string portName, int baudrate) = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void flush() = 0;
    virtual int available() = 0;

    virtual long readBytes(unsigned char * buffer, size_t length) = 0;
    virtual long readBytes(char * buffer, size_t length) = 0;
    virtual int readByte() = 0;

    virtual long writeBytes(const unsigned char * buffer, size_t length) = 0;
    virtual long writeBytes(const char * buffer, size_t length) = 0;
    virtual bool writeByte(unsigned char singleByte) = 0;
    virtual bool writeByte(char singleByte) = 0;
};

class SerialPortInfo;
