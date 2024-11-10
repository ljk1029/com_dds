/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file QosList.h
 *	QosList
 *  Created on: Apr 9, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */

#ifndef QOSLIST_H_
#define QOSLIST_H_
#include "eprosimartps/rtps_all.h"
#include "eprosimartps/qos/ParameterList.h"

namespace eprosima {
namespace dds {

/**
 * QosList_t class contains two ParameterList_t for the Qos.
 */
class QosList_t {
public:
	QosList_t();
	virtual ~QosList_t();
	//! All the Qos as a parameter List.
	ParameterList_t allQos;
	//! Only the Qos that can be send as inline.
	ParameterList_t inlineQos;
};

/**
 * QosList class.
 * Contains static methods to add Qos to a QosList_t structure.
 */
class QosList
{
public:
	/**
	 * @name AddQos methods.
	 * @param qos Pointer to the QOsList_t list.
	 * @param pid PID of the parameter to add to the QosList_t.
	 * @param param Parameter to add.
	 * @return True if correct.
	 */
	///@{
	static bool addQos(QosList_t* qos,ParameterId_t pid ,std::string& string_in);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,Locator_t& loc);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,uint32_t uintlong);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,GUID_t& guid);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,ProtocolVersion_t& protocol);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,VendorId_t& vendor);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,octet o1,octet o2,octet o3,octet o4);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,EntityId_t& entity);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,Time_t& entity);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,bool in_bool);
	static bool addQos(QosList_t* qos,ParameterId_t pid ,std::string& str1,std::string& str2);
	///@}
};

} /* namespace rtps */
} /* namespace eprosima */

#endif /* QOSLIST_H_ */
