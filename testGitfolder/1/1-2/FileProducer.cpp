/*
 * FileProducer.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: saqib
 */

#include "FileProducer.h"

#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

NS_LOG_COMPONENT_DEFINE("FileProducer");

namespace ns3 {

// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(FileProducer);

TypeId
FileProducer::GetTypeId()
{
  static TypeId tid = TypeId("FileProducer").SetParent<ndn::App>().AddConstructor<FileProducer>();

  return tid;
}

FileProducer::FileProducer()
{
}

void
FileProducer::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest); // forward call to perform app-level tracing
  // do nothing else (hijack interest)

  NS_LOG_DEBUG("Do nothing for incoming interest for" << interest->getName());
}

void
FileProducer::StartApplication()
{
  App::StartApplication();

  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/prefix/sub", m_face, 0);
}

void
FileProducer::StopApplication()
{
  App::StopApplication();
}

} // namespace ns3
