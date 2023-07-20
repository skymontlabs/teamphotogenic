static inline bool hotp(const std::string secret, const uint32_t input, uint32_t counter)
{
    uint8_t *time_raw = (uint8_t*)&counter;
    uint8_t *hmac = HMAC(EVP_sha1(), secret, 20, (uint8_t*)time_raw, sizeof(time_raw) - 1, NULL, NULL);
    
    uint8_t offset = hmac[sizeof(hmac)-1] & 0x0F;
    char buffer[4];
    
    memcpy(buffer, &hmac[offset], 4);
    
    for (int i = 0; i < 4; ++i)
        std::cout << buffer[i] << "\n";
    
    buffer[0] = buffer[0] & 0x7f;
    
    uint32_t ret = ((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3] << 0));
    uint32_t calc = (ret & 0x7fffffff) % 1000000;
    
    return (input == calc);
}