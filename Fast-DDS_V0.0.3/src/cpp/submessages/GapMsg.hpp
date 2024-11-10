/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * GapMsg.hpp
 *
 *  Created on: Feb 20, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 */



namespace eprosima{
namespace rtps{

bool RTPSMessageCreator::addMessageGap(CDRMessage_t* msg,GuidPrefix_t& guidprefix,
		SequenceNumber_t& seqNumFirst,SequenceNumberSet_t& seqNumList,
		const EntityId_t& readerId,const EntityId_t& writerId)
{
	try
	{
		RTPSMessageCreator::addHeader(msg,guidprefix);
		RTPSMessageCreator::addSubmessageInfoTS_Now(msg,false);
		RTPSMessageCreator::addSubmessageGap(msg,seqNumFirst,seqNumList,readerId, writerId);
	}
	catch(int e)
	{
		pError("Gap message error"<<e<<endl)
		return false;
	}
	return true;
}

bool RTPSMessageCreator::addSubmessageGap(CDRMessage_t* msg,SequenceNumber_t& seqNumFirst,SequenceNumberSet_t& seqNumList,const EntityId_t& readerId,const EntityId_t& writerId)
{

	CDRMessage_t& submsgElem = g_pool_submsg.reserve_Object();
		CDRMessage::initCDRMsg(&submsgElem);
	octet flags = 0x0;
	if(EPROSIMA_ENDIAN == BIGEND)
	{
		flags = flags | BIT(0);
		submsgElem.msg_endian   = BIGEND;
	}
	else
	{
		submsgElem.msg_endian  = LITTLEEND;
	}

	try{
		CDRMessage::addEntityId(&submsgElem,&readerId);
		CDRMessage::addEntityId(&submsgElem,&writerId);
		//Add Sequence Number
		CDRMessage::addSequenceNumber(&submsgElem,&seqNumFirst);
		CDRMessage::addSequenceNumberSet(&submsgElem,&seqNumList);
	}
	catch(int e)
	{
		pError("Gap submessage error"<<e<<endl)
		return false;
	}


	//Once the submessage elements are added, the header is created
	RTPSMessageCreator::addSubmessageHeader(msg, GAP,flags,submsgElem.length);
	//Append Submessage elements to msg
	CDRMessage::appendMsg(msg, &submsgElem);
	g_pool_submsg.release_Object(submsgElem);

	return true;
}


}
}
