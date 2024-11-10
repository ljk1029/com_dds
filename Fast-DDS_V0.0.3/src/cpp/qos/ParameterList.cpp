/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file ParamListt.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */

#include "eprosimartps/qos/ParameterList.h"

namespace eprosima {
namespace dds {

bool ParameterList::updateCDRMsg(ParameterList_t* plist,Endianness_t endian)
{
	CDRMessage::initCDRMsg(&plist->m_cdrmsg);
	plist->m_cdrmsg.msg_endian = endian;
	for(std::vector<Parameter_t*>::iterator it=plist->m_parameters.begin();
			it!=plist->m_parameters.end();++it)
	{
		if(!(*it)->addToCDRMessage(&plist->m_cdrmsg))
		{
			return false;
		}
	}
	if(!CDRMessage::addParameterSentinel(&plist->m_cdrmsg))
	{
		return false;
	}
	else
	{
		plist->m_hasChanged = false;
		pDebugInfo("Param msg created correctly"<<endl);
		return true;
	}
}


uint32_t ParameterList::readParameterListfromCDRMsg(CDRMessage_t*msg,ParameterList_t*plist,InstanceHandle_t* handle,ChangeKind_t* chkind)
{
	uint32_t paramlist_byte_size = 0;
	bool is_sentinel = false;
	bool valid = true;
	ParameterId_t pid;
	uint16_t plength;
	while(!is_sentinel)
	{
		valid = true;
		valid&=CDRMessage::readUInt16(msg,(uint16_t*)&pid);
		valid&=CDRMessage::readUInt16(msg,&plength);
		paramlist_byte_size +=4;
		if(valid)
		{
		//	cout << "readparameterlistfromcdrmsg Param with pid: " << pid << endl;
			switch(pid)
			{
			case PID_UNICAST_LOCATOR:
			case PID_MULTICAST_LOCATOR:
			case PID_DEFAULT_UNICAST_LOCATOR:
			case PID_DEFAULT_MULTICAST_LOCATOR:
			case PID_METATRAFFIC_UNICAST_LOCATOR:
			case PID_METATRAFFIC_MULTICAST_LOCATOR:
			{
				ParameterLocator_t* p = new ParameterLocator_t(pid,plength);
				valid &= CDRMessage::readLocator(msg,&p->locator);
				if(plength == PARAMETER_LOCATOR_LENGTH && valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_DEFAULT_UNICAST_PORT:
			case PID_METATRAFFIC_UNICAST_PORT:
			case PID_METATRAFFIC_MULTICAST_PORT:
			{
				ParameterPort_t* p = new ParameterPort_t(pid,plength);
				valid &= CDRMessage::readUInt32(msg,&p->port);
				if(plength == PARAMETER_LOCATOR_LENGTH && valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_PROTOCOL_VERSION:
			{
				ParameterProtocolVersion_t* p = new ParameterProtocolVersion_t(pid,plength);
				valid &= CDRMessage::readOctet(msg,&p->protocolVersion.m_major);
				valid &= CDRMessage::readOctet(msg,&p->protocolVersion.m_minor);
				msg->pos+=2;
				if(plength == PARAMETER_PROTOCOL_LENGTH && valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_VENDORID:
			{
				ParameterVendorId_t* p = new ParameterVendorId_t(pid,plength);
				valid &= CDRMessage::readOctet(msg,&p->vendorId[0]);
				valid &= CDRMessage::readOctet(msg,&p->vendorId[1]);
				msg->pos+=2;
				if(plength == PARAMETER_VENDOR_LENGTH && valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_MULTICAST_IPADDRESS:
			case PID_DEFAULT_UNICAST_IPADDRESS:
			case PID_METATRAFFIC_UNICAST_IPADDRESS:
			case PID_METATRAFFIC_MULTICAST_IPADDRESS:
			{
				ParameterIP4Address_t* p = new ParameterIP4Address_t(pid,plength);
				if(plength == PARAMETER_IP4_LENGTH)
				{
					p->address[0] = msg->buffer[msg->pos];
					p->address[1] = msg->buffer[msg->pos+1];
					p->address[2] = msg->buffer[msg->pos+2];
					p->address[3] = msg->buffer[msg->pos+3];
					msg->pos +=4;
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_PARTICIPANT_GUID:
			case PID_GROUP_GUID:
			{
				ParameterGuid_t* p = new ParameterGuid_t(pid,plength);
				valid &= CDRMessage::readData(msg,p->guid.guidPrefix.value,12);
				valid &= CDRMessage::readData(msg,p->guid.entityId.value,4);
				if(plength == PARAMETER_GUID_LENGTH && valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
			}
			case PID_TOPIC_NAME:
			case PID_TYPE_NAME:
			case PID_ENTITY_NAME:
			{
				ParameterString_t* p = new ParameterString_t(pid,plength);
				uint32_t str_size = 1;
				valid&=CDRMessage::readUInt32(msg,&str_size);
				p->m_string.resize(str_size);
				octet* oc=new octet[str_size];
				valid &= CDRMessage::readData(msg,oc,str_size);
				for(uint32_t i =0;i<str_size;i++)
					p->m_string.at(i) = oc[i];
				if(valid)
				{
					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
					delete(oc);
				}
				else
				{
					delete(p);
					delete(oc);
					return -1;
				}
				break;
			}
			case PID_PROPERTY_LIST:
			{
				ParameterPropertyList_t* p = new ParameterPropertyList_t(pid,plength);
				uint32_t num_properties;
				valid&=CDRMessage::readUInt32(msg,&num_properties);
								//uint16_t msg_pos_first = msg->pos;
				std::string str;
				std::pair<std::string,std::string> pair;
				uint32_t rest=0;
				for(uint32_t n_prop =0;n_prop<num_properties;++n_prop)
				{

					//STRING 1
					uint32_t str_size = 1;
					valid&=CDRMessage::readUInt32(msg,&str_size);

					str = std::string();str.resize(str_size);
					octet* oc1 = new octet[str_size];
					valid &= CDRMessage::readData(msg,oc1,str_size);
					for(uint32_t i =0;i<str_size;i++)
						str.at(i) = oc1[i];
					pair.first = str;
					rest = (uint32_t)(str_size-4*floor((float)str_size/4));
					rest = rest==0 ? 0 : 4-rest;
					msg->pos+=rest;
					//STRING 2
					valid&=CDRMessage::readUInt32(msg,&str_size);
					str = std::string();str.resize(str_size);

					octet* oc2 = new octet[str_size];
					valid &= CDRMessage::readData(msg,oc2,str_size);
					for(uint32_t i =0;i<str_size;i++)
						str.at(i) = oc2[i];
					pair.second = str;
					rest = (uint32_t)(str_size-4*floor((float)str_size/4));
										rest = rest==0 ? 0 : 4-rest;
										msg->pos+=rest;
					p->properties.push_back(pair);
					delete(oc1);
					delete(oc2);
				}
				if(valid)
				{

					plist->m_parameters.push_back((Parameter_t*)p);
					plist->m_hasChanged = true;
					paramlist_byte_size += plength;
				}
				else
				{
					delete(p);
					return -1;
				}
				break;
				break;
			}
			case PID_STATUS_INFO:
			{
				octet status = msg->buffer[msg->pos+3];
				if(status == 1)
					*chkind = NOT_ALIVE_DISPOSED;
				else if (status == 2)
					*chkind = NOT_ALIVE_UNREGISTERED;
				msg->pos+=4;
				paramlist_byte_size+=4;
				break;
			}
			case PID_KEY_HASH:
			{
				CDRMessage::readData(msg,handle->value,16);
				paramlist_byte_size+=16;
				break;
			}
			case PID_SENTINEL:
			{
				is_sentinel = true;
				break;
			}
			case PID_PAD:
			default:
			{
				msg->pos +=plength;
				paramlist_byte_size +=plength;
				break;
			}
			}
		}
		else
		{
			return -1;
		}
	}
	return paramlist_byte_size;
}

} /* namespace dds */
} /* namespace eprosima */
