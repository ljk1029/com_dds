/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file Semaphore.h
 *
 *  Created on: May 5, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

namespace eprosima {
namespace rtps {

/**
 * Class Semaphore implements an easy to use Semaphore.
 * Based on Boost Mutex.
 */
class Semaphore {
public:
	Semaphore():m_count(0){};
	virtual ~Semaphore(){};
	void wait()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		while(m_count <= 0)
			m_condition.wait(lock);
		--m_count;
	}

	void post()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		++m_count;
		m_condition.notify_one();
	}

	void reset()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_count = 0;
	}

private:
	uint32_t m_count;
	boost::mutex m_mutex;
	boost::condition_variable m_condition;



};

} /* namespace dds */
} /* namespace eprosima */

#endif /* SEMAPHORE_H_ */
