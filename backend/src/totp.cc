static inline bool hotp(const uint8_t* secret, const uint32_t input, uint32_t counter)
{
    uint8_t *time_raw = (uint8_t*)&counter;
    uint8_t *hmac = HMAC(EVP_sha1(), secret, 20, (uint8_t*)time_raw, sizeof(time_raw) - 1, NULL, NULL);
    
    uint8_t offset = hmac[sizeof(hmac)-1] & 0x0F;
    char buffer[4];
    
    memcpy(buffer, &hmac[offset], 4);
    
    for (int i = 0; i < 4; ++i)
        std::cout << buffer[i] << "\n";
    
    uint32_t ret = ((buffer[0] & 0x7F) << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3] << 0);
    uint32_t calc = (ret & 0x7fffffff) % 1000000;
    
    return (input == calc);
}


import hmac
import time

key = "$3cr3tP4$$"
key_bytes = bytearray(key, "utf-8")
unix_timestamp = int(time.time())
timestamp = unix_timestamp // 30

# In TOTP code sample we're using actual system time, thus
# PLEASE, MAKE SURE YOUR SYSTEM TIME IS ACCURATE IF YOU WANT
# TO VALIDATE THE ACCURACY OF THE GENERATED CODES!
print(f"The UNIX timestamp's value right now is: {unix_timestamp}")
print(f"And the timestamp we'll use to generate the code: {timestamp}")

# Alright, the timestamp above is the equivalent of the counter
# from HOTP. From this point on we treat it exactly as we would
# treat the counter in HOTP. That means, we're converting it to
# an array of 8 Big-Endian-ordered bytes that represent the
# integer value of the timestamp variable.
timestamp_big_endian = timestamp.to_bytes(8, "big")

# And calculate the hash. It'll keep changing every 30 seconds
h = hmac.new(key_bytes, timestamp_big_endian, "sha1")
hash_value = h.digest()

print(f"In TOTP we calculate the hash the same way: {h.hexdigest()}")

# Ok, no the code to do the above. First let's calculate the offset.
# Unlike my HOTP code example, here we're using actual system time
# so every time the hash -- and therefore the offset -- will likely
# be different.
offset = hash_value[len(hash_value) - 1] & 0x0f

# Now let's get the code integer (we zero-out the most significant
# bit but only in the 1st -- the most significant -- byte)
code =  (hash_value[offset] & 0x7f) * 0x1000000
code += (hash_value[offset + 1])    * 0x10000
code += (hash_value[offset + 2])    * 0x100
code += (hash_value[offset + 3])
print("The code integer: 0x%x" % code)
print(f"The code integer in decimal notation: {code}")

# And now we take only last 6 digits just like in HOTP.
code = code % 1000000
print(f"The final TOTP code: {code}")
