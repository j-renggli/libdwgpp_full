#ifndef ARISTOTELES_COMMON_THREADING_LOCK_H
#define ARISTOTELES_COMMON_THREADING_LOCK_H

// Boost
#include <boost/thread/condition.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/thread.hpp>

namespace core {

// Mutex : ensures single thread uses data at once
typedef boost::mutex Mutex;

// SharedMutex : allows reader/writer locks
typedef boost::shared_mutex SharedMutex;

// Simple lock: locks on construction, unlocks on deletion
typedef boost::lock_guard<Mutex> SimpleLock;

// Normal lock: can lock() and unlock() multiple times
typedef boost::unique_lock<Mutex> NormalLock;

// Reader lock: multiple readers can access data at the same time
typedef boost::shared_lock<SharedMutex> ReaderLock;

// Writer lock: single writer can access data at a given time
typedef boost::unique_lock<SharedMutex> WriterLock;

// Condition : lock will wait until condition is fulfilled
typedef boost::condition_variable LockCondition;

}

#endif
