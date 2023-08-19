#include <functional>
#include <map>
#include <mutex>

class HighsCallbackManager {
 public:
  using CallbackType = std::function<void(int)>;

  int register_callback(CallbackType callback);
  void unregister_callback(int id);
  void call_callback(int id, int value);
  bool has_callbacks() const { return !callbacks_.empty(); }

 private:
  std::map<int, CallbackType> callbacks_;
  int next_id_ = 0;
  std::mutex mutex_;
};
