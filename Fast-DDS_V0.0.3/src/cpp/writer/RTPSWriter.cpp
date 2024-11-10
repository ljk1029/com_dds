/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * RTPSWriter.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *      		grcanosa@gmail.com
 */

#include "eprosimartps/writer/RTPSWriter.h"
#include "eprosimartps/HistoryCache.h"
#include "eprosimartps/CDRMessage.h"
#include "eprosimartps/dds/Publisher.h"

#include "eprosimartps/qos/ParameterList.h"

namespace eprosima {
namespace rtps {


RTPSWriter::RTPSWriter(uint16_t historysize,uint32_t payload_size):
		m_stateType(STATELESS),
		m_writer_cache(historysize,payload_size,WRITER,(Endpoint*)this),
		m_pushMode(true),
		m_heartbeatCount(0),
		m_Pub(NULL),
		mp_listener(NULL)

{
	pDebugInfo("RTPSWriter created"<<endl)
}

void RTPSWriter::init_header()
{
	CDRMessage::initCDRMsg(&m_cdrmessages.m_rtpsmsg_header);
	RTPSMessageCreator::addHeader(&m_cdrmessages.m_rtpsmsg_header,m_guid.guidPrefix);
}



RTPSWriter::~RTPSWriter()
{

	pDebugInfo("RTPSWriter destructor"<<endl;);
}

bool RTPSWriter::new_change(ChangeKind_t changeKind,void* data,CacheChange_t** change_out)
{
	pDebugInfo("Creating new change"<<endl);
	CacheChange_t* ch = m_writer_cache.reserve_Cache();
	if(ch == NULL)
	{
		pWarning("Problem reserving Cache"<<endl);
		return false;
	}
	if(changeKind == ALIVE && data !=NULL && mp_type !=NULL)
	{
		if(!mp_type->serialize(data,&ch->serializedPayload))
		{
			pWarning("RTPSWriter:Serialization returns false"<<endl);
			return false;
		}
	}
	ch->kind = changeKind;

	if(topicKind == WITH_KEY && mp_type !=NULL)
	{
		if(mp_type->m_isGetKeyDefined)
		{
			mp_type->getKey(data,&ch->instanceHandle);
		}
		else
		{
			pWarning("Get key function not defined"<<endl);
		}
	}
	//change->sequenceNumber = lastChangeSequenceNumber;
	ch->writerGUID = m_guid;
	*change_out = ch;
	return true;
}

bool RTPSWriter::add_new_change(ChangeKind_t kind,void*Data)
{
	if(kind != ALIVE && topicKind == NO_KEY)
	{
		pWarning("NOT ALIVE change in NO KEY Topic "<<endl)
		return false;
	}

	CacheChange_t* change;
	if(new_change(kind,Data,&change))
	{
		pDebugInfo("New change created"<<endl);
		if(!m_writer_cache.add_change(change))
		{
			pWarning("Change not added"<<endl);
			m_writer_cache.release_Cache(change);
			return false;
		}

		//DO SOMETHING ONCE THE NEW CHANGE HAS BEEN ADDED.
		unsent_change_add(change);
		if(m_writer_cache.isFull() && mp_listener !=NULL)
			mp_listener->onHistoryFull();
		return true;
	}
	else
		return false;
}




} /* namespace rtps */
} /* namespace eprosima */


