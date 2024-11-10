/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file StatelessReader.h
 *  StatelessReader class.
 *  Created on: Feb 27, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */


#ifndef STATELESSREADER_H_
#define STATELESSREADER_H_


#include "eprosimartps/rtps_all.h"
#include "eprosimartps/reader/RTPSReader.h"

#include <boost/bind.hpp>

namespace eprosima {
namespace rtps {

/**
 * Class StatelessReader, specialization of the RTPSReader.
 * @ingroup READERMODULE
 */
class StatelessReader: public RTPSReader {
public:
	//StatelessReader();
	virtual ~StatelessReader();
	StatelessReader(const SubscriberAttributes* param,uint32_t payload_size);



	 bool readNextCacheChange(void*data,SampleInfo_t* info);
	 bool takeNextCacheChange(void*data,SampleInfo_t* info);
	 bool isUnreadCacheChange();


//	 bool takeAllCacheChange(std::vector<void*>* data,int32_t* n_removed);
//	 bool readAllCacheChange(std::vector<void*>* data);

};

} /* namespace rtps */
} /* namespace eprosima */

#endif /* STATELESSREADER_H_ */
