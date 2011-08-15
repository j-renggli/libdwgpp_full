#pragma once

#include <sys/time.h>

class Clock
{
  private:
    timeval tStart_;

    int64_t iOffset_;

  public:
    Clock();

    void start();

    void stop();

    int64_t getElapsedMS() const;
};

Clock::Clock() :
iOffset_(0)
{
}

int64_t Clock::getElapsedMS() const
{
  return iOffset_;
}

void Clock::start()
{
  struct timezone tZone;

  gettimeofday(&tStart_, &tZone);
}

void Clock::stop()
{
  timeval tStop;
  struct timezone tZone;

  gettimeofday(&tStop, &tZone);

  int64_t iElapsed = (tStop.tv_sec - tStart_.tv_sec) * CLOCKS_PER_SEC;
  iElapsed += (tStop.tv_usec - tStart_.tv_usec);
  iElapsed /= (CLOCKS_PER_SEC / 1000);
  iOffset_ += iElapsed;
}
