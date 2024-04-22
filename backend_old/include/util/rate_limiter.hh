#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include <utility>

class RateLimiter
{
	// Maximum number of requests per client within the duration.
	int max_requests_;

	// Time window for the rate limit.
	std::chrono::seconds duration_; 
	
	// Maximum number of clients to track for rate limiting.
	size_t capacity_;
	
	// Least Recently Used (LRU) list of client IDs.
	std::list<std::string> lru_list_;

	// Maps a client ID to a pair of ClientInfo and an iterator to the LRU list.
	std::unordered_map<std::string, std::pair<ClientInfo, std::list<std::string>::iterator>> access_log_;
	
	// Evicts the least recently used clients if necessary.
	void evict() {
		while (access_log_.size() > capacity_) {
			// Remove from the access log and LRU list.
			auto lru_it = --lru_list_.end();
			access_log_.erase(*lru_it);
			lru_list_.pop_back();
		}
	}

public:
	// Client's information.
	struct ClientInfo
	{
		int requests = 0; // Number of requests made.
		std::chrono::steady_clock::time_point last_request_time; // Last request time.
	};

	// Constructs a Rate Limiter with a specified limit and duration.
	RateLimiter(int max_requests, std::chrono::seconds duration, size_t capacity):
	max_requests_(max_requests), duration_(duration), capacity_(capacity) {}

	// Checks if the request can go through.
	bool grant_access(const std::string& client_id)
	{
		auto now = std::chrono::steady_clock::now();

		// Clean up before proceeding.
		evict();

		// Find the client in the access log.
		auto it = access_log_.find(client_id);
		if (it != access_log_.end()) {
			// Move the client to the front of the LRU list.
			lru_list_.splice(lru_list_.begin(), lru_list_, it->second.second);
			// Update the iterator in the map.
			it->second.second = lru_list_.begin();

			ClientInfo& info = it->second.first;

			// If the client is within the rate limit, grant access.
			if (now - info.last_request_time < duration_) {
				if (info.requests < max_requests_) {
					++info.requests;
					return true;
				}
				return false;
			} else {
				// Reset the request count and time.
				info.requests = 1;
				info.last_request_time = now;
				return true;
			}
		} else {
			// If the client is new and there's capacity, grant access.
			if (access_log_.size() < capacity_) {
				// Add the new client to the LRU list and access log.
				lru_list_.push_front(client_id);
				access_log_[client_id] = { {1, now}, lru_list_.begin() };
				return true;
			}
			return false;
		}
	}
};

int main() {
	// Rate limit: 100 requests per minute, with a maximum of 10 clients tracked.
	RateLimiter limiter(100, std::chrono::minutes(1), 10);

	// Simulating requests.
	for (int i = 0; i < 150; ++i) {
		bool granted = limiter.grant_access("client1");
		std::cout << "Request " << i << " for client1: " << (granted ? "Granted" : "Denied") << std::endl;
	}

	return 0;
}
