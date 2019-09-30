/*
 * ComputeNode.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: saqib
 */

#include "ComputeNode.h"

#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "ns3/random-variable-stream.h"

#include "ns3/log.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"

#include "model/ndn-l3-protocol.hpp"
#include "helper/ndn-fib-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"


#include <memory>


NS_LOG_COMPONENT_DEFINE("ComputeNode");

namespace ns3 {

// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(ComputeNode);

TypeId
ComputeNode::GetTypeId()
{
  static TypeId tid = TypeId("ComputeNode").SetParent<ndn::App>().AddConstructor<ComputeNode>();

  return tid;
}

ComputeNode::ComputeNode()
{
}


void
ComputeNode::StartApplication()
{
  App::StartApplication();

  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/a/b/c/d", m_face, 1);
//  ndn::FibHelper::AddRoute(GetNode(), "/e/f/g", m_face, 0);

}

void
ComputeNode::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest);

  NS_LOG_DEBUG("Receiving  Interest packet for compute node " << interest->getName());



  auto softInterest = std::make_shared<ndn::Interest>("/e/f/g");
  Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
  softInterest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
  softInterest->setInterestLifetime(ndn::time::seconds(1));

//  	  ndn::StackHelper::getKeyChain().sign(*data);

  NS_LOG_DEBUG("Sending software interest packet for " << softInterest->getName());

  m_appLink->onReceiveInterest(*softInterest);



///////////////////////// works well ///////////////////////
//  	  auto data = std::make_shared<ndn::Data>(interest->getName());
//  	  data->setFreshnessPeriod(ndn::time::milliseconds(1000));
//  	  data->setContent(std::make_shared< ::ndn::Buffer>(1024));
//  	  ndn::StackHelper::getKeyChain().sign(*data);
//
//  	  NS_LOG_DEBUG("Sending Data packet for " << data->getName());
//
//  	  // Call trace (for logging purposes)
//  	  m_transmittedDatas(data, this, m_face);
//
//  	  m_appLink->onReceiveData(*data);
///////////////////////////////////////////////////////////////




//  std::vector<std::string> prefVector;
//
//  std::string pref = interest->getName().toUri();
//
//  boost::split(prefVector, pref, [](char c){return c == '/';});
//
//  if (prefVector(0) == "a"){
//
//	  auto softwareNodeInterest = std::make_shared<ndn::Interest>("/e/software");
//	  Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
//	  softwareNodeInterest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
//	  softwareNodeInterest->setInterestLifetime(ndn::time::seconds(2));
//
//	  NS_LOG_DEBUG("Sending Interest packet for " << *softwareNodeInterest);
//
//	  auto fileNodeInterest = std::make_shared<ndn::Interest>("/f/software");
//	  Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
//	  fileNodeInterest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
//	  fileNodeInterest->setInterestLifetime(ndn::time::seconds(2));
//
//	  NS_LOG_DEBUG("Sending Interest packet for " << *fileNodeInterest);
//
//	  m_appLink->onReceiveInterest(*softwareNodeInterest);
//
//	  m_appLink->onReceiveInterest(*fileNodeInterest);


//  }


}


void
ComputeNode::StopApplication()
{
  App::StopApplication();
}

} // namespace ns3
