#ifndef TBPROGRESSMONITOR_H
#define TBPROGRESSMONITOR_H

#include <ostream>
#include <sys/time.h>

class ProgressMonitor
{
public:
	ProgressMonitor(const unsigned long nPos = 0, const bool bInstant = false, const unsigned long updateInterval = 1000);
	~ProgressMonitor();
	bool Update();
	bool Update(const unsigned long cPos);
	void IncMax(const unsigned long nPos);
	void Reset();
private:
	bool bShow, bInstant;
	unsigned long nPos, cPos;
	const unsigned long updateInterval;
	struct timeval tStartTime, tLastUpdate;
	static bool bAbort;
	static void CatchSignal(int);
	friend std::ostream &operator<<(std::ostream &os, ProgressMonitor &pm);
};

std::ostream &operator<<(std::ostream &os, ProgressMonitor &pm);

#endif
