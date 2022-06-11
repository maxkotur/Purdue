#ifndef  INCLUDE_SERVER_HH_
#define INCLUDE_SERVER_HH_

#include "socket.hh"
#include <pthread.h>
#include <chrono>
#include <ctime>

extern std::string IP;

class Server {
 private:
    SocketAcceptor const& _acceptor;
    struct stats {
      int min_time;
      int max_time;
      time_t start_time;
      std::string min_time_URL;
      std::string max_time_URL; 
      int num_requests;
    } statistics;

 public:
    explicit Server(SocketAcceptor const& acceptor);
    void run_linear() const;
    void run_fork() const;
    void run_thread_pool(const int num_threads) const;
    void run_thread() const;
    void * loop_thread() const;
    
    int get_min() const;
    int get_max() const;
    time_t get_start() const;
    std::string get_min_URL() const;
    std::string get_max_URL() const;
    int get_num_request() const;
    
    void set_min(int min);
    void set_max(int max);
    void set_min_URL(std::string url);
    void set_max_URL(std::string url);
    void set_num_requests();

    void handle(const Socket_t& sock) const;
};

#endif  // INCLUDE_SERVER_HH_
