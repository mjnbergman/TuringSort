/*
 * QueueElement.hh
 *
 *  Created on: 3 Apr 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_QUEUEELEMENT_HH_
#define TURINGSORT_CODE_QUEUEELEMENT_HH_

#include "TimerHelper.hh"

struct QueueElement{
public:
	TimerHelper* th;
	unsigned long timeStamp;
};

class QueueCompare{
public:
	bool operator() (QueueElement& q1, QueueElement& q2){
		return q1.timeStamp <= q2.timeStamp;
	}
};


#endif /* TURINGSORT_CODE_QUEUEELEMENT_HH_ */
