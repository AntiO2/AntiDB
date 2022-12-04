#ifndef ANTIDB_RWLATCH
#define ANTIDB_RWLATCH

#include <mutex>
#include <shared_mutex>
namespace antidb
{
    class ReaderWriterLatch
    {
    public:
        void WLock()
        {
            rwlock.lock();
        }
        void WUnlock()
        {
            rwlock.unlock();
        }
        void Rlock()
        {
            rwlock.lock_shared();
        }
        void RUnlock()
        {
            rwlock.unlock_shared();
        }

    private:
        std::shared_mutex rwlock;
    };
}

#endif