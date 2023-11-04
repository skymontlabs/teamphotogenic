#include <cstdint>
#include <iostream>
#include <mutex>
#include <chrono>
#include <stdexcept>

class snowflake
{
	uint64_t starting_unix;
	uint64_t starting_sysclock;
	uint32_t increment;

public:
	snowflake(): {}

	inline void generate_sid()
	{
		return (current_unix << 12) | () | ();
	}
}

class SnowflakeIdGenerator {
private:
    std::mutex mutex_;
    int64_t last_timestamp_ = -1;
    int64_t sequence_ = 0;

    // Configuration
    const int64_t twepoch_ = 1288834974657L;
    const int64_t machine_id_bits_ = 5L;
    const int64_t datacenter_id_bits_ = 5L;
    const int64_t max_machine_id_ = -1L ^ (-1L << machine_id_bits_);
    const int64_t max_datacenter_id_ = -1L ^ (-1L << datacenter_id_bits_);
    const int64_t sequence_bits_ = 12L;

    // Shifts
    const int64_t machine_id_shift_ = sequence_bits_;
    const int64_t datacenter_id_shift_ = sequence_bits_ + machine_id_bits_;
    const int64_t timestamp_left_shift_ = sequence_bits_ + machine_id_bits_ + datacenter_id_bits_;

    // Mask
    const int64_t sequence_mask_ = -1L ^ (-1L << sequence_bits_);

    int64_t machine_id_;
    int64_t datacenter_id_;

    // Time references
    int64_t steady_start_;
    int64_t system_start_;

    int64_t get_current_timestamp() {
        auto now = std::chrono::steady_clock::now().time_since_epoch();
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        return system_start_ + (now_ms - steady_start_);
    }

public:
    SnowflakeIdGenerator(int64_t machine_id, int64_t datacenter_id) {
        if (machine_id > max_machine_id_ || machine_id < 0) {
            throw std::invalid_argument("Machine ID can't be greater than " + std::to_string(max_machine_id_) + " or less than 0");
        }
        if (datacenter_id > max_datacenter_id_ || datacenter_id < 0) {
            throw std::invalid_argument("Datacenter ID can't be greater than " + std::to_string(max_datacenter_id_) + " or less than 0");
        }
        machine_id_ = machine_id;
        datacenter_id_ = datacenter_id;

        // Initialize time references
        auto system_now = std::chrono::system_clock::now().time_since_epoch();
        system_start_ = std::chrono::duration_cast<std::chrono::milliseconds>(system_now).count();
        auto steady_now = std::chrono::steady_clock::now().time_since_epoch();
        steady_start_ = std::chrono::duration_cast<std::chrono::milliseconds>(steady_now).count();
    }

    int64_t next_id() {
        std::lock_guard<std::mutex> lock(mutex_);

        int64_t timestamp = get_current_timestamp();

        if (timestamp < last_timestamp_) {
            throw std::runtime_error("Clock moved backwards. Refusing to generate id for " + std::to_string(last_timestamp_ - timestamp) + " milliseconds");
        }

        if (last_timestamp_ == timestamp) {
            sequence_ = (sequence_ + 1) & sequence_mask_;
            if (sequence_ == 0) {
                // Spin until the next millisecond
                while ((timestamp = get_current_timestamp()) <= last_timestamp_);
            }
        } else {
            sequence_ = 0;
        }

        last_timestamp_ = timestamp;

        return ((timestamp - twepoch_) << timestamp_left_shift_) |
               (datacenter_id_ << datacenter_id_shift_) |
               (machine_id_ << machine_id_shift_) |
               sequence_;
    }
};
