/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * Endpoint.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 */

#include "eprosimartps/Endpoint.h"

namespace eprosima {
namespace rtps {

Endpoint::Endpoint() {
	mp_type = NULL;
	mp_send_thr = NULL;
	mp_event_thr = NULL;
	topicKind = NO_KEY;
	m_userDefinedId = 0;

}

Endpoint::~Endpoint() {

}

} /* namespace rtps */
} /* namespace eprosima */
