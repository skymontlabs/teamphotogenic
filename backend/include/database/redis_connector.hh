// redis_CONNECTOR.h
#ifndef REDIS_CONNECTOR_H
#define REDIS_CONNECTOR_H

#include <hiredis/hiredis.h>
#include <string>

class redis_connector
{
public:
    redis_connector(const uint32_t ip, int port);
    ~redis_connector();

    bool connect();

    bool set(const uint8_t* key, const uint32_t key_len,
             const uint8_t* value, const uint32_t value_len);

    bool append(const uint8_t* key, const uint32_t key_len,
                const uint8_t* value, const uint32_t value_len);
    
    size_t set(uint8_t* out, const uint8_t* key, const uint32_t key_len);

    // Add more functions as needed

private:
    std::string host_;
    int port_;

    bredis::Connection<tcp::socket> ctx_;

    Buffer tx_buff;

    Buffer rx_buff;

};

#endif // REDIS_CONNECTOR_H
