#undef NDEBUG
#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;

void thirdparty_function(auto callback) {
    using std::this_thread::sleep_for;
    using namespace std::chrono_literals;

    std::thread{[cb = std::move(callback)]() mutable {
        std::cout << "Work started" << std::endl;
        sleep_for(3s); // emulate interesting work
        std::cout << "Work done" << std::endl;
        cb();
    }}.detach();
}

template <typename executor_type = asio::any_io_executor>
struct MyIoObject {
    MyIoObject(executor_type ex): _executor(ex) {}

    template <typename Token> auto async_function(Token&& token) {
        return asio::async_initiate<Token, void()>(
            [](auto handler, auto default_ex) {
                auto ex = get_associated_executor(handler, default_ex);
                thirdparty_function(
                    [handler, default_ex, work = asio::make_work_guard(ex)]() mutable {
                        post(default_ex, handler);
                    });
            },
            token, _executor);
    }

  private:
    executor_type _executor;
};

int main() {
    asio::thread_pool tp;
    auto s1 = make_strand(tp);
    auto s2 = make_strand(tp);
    assert(s1 != s2);

    MyIoObject obj{s1};

    {
        std::future<void> f = obj.async_function(asio::use_future); // 1
        f.wait(); // 1 completes here
    }

    auto verify_completion = [](auto& strand) {
        return [&] {
            std::cout << "Handler invoked on expected strand: "
                      << (strand.running_in_this_thread() ? "yes" : "no") << std::endl;
        };
    };

    // naked, should use s1 from MyIoObject
    obj.async_function(verify_completion(s1)); // 2

    // bound to s2
    obj.async_function(asio::bind_executor(s2, verify_completion(s2))); // 3

    // both //2 and //3 complete concurrently
    tp.join();
}
