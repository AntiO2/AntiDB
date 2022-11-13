#include <mutex>
#include <shared_mutex>
namespace antidb
{
    class ReaderWriterLatch
    {
    public:
        void WLock()
        {
            wlock.lock();
        }
        void WUnlock()
        {
            wlock.unlock();
        }
        void Rlock()
        {
            rlock.lock();
        }
        void RUnlock()
        {
            rlock.unlock();
        }

    private:
        /**
         * @brief 读锁
         *
         */
        std::shared_mutex rlock;
        /**
         * @brief 写锁
         *
         */
        std::mutex wlock;
    };
}