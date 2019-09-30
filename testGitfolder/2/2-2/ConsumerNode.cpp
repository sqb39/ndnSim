/*
 * ConsumerNode.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: saqib
 */

#include "ConsumerNode.h"

#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"

#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

#include "ns3/random-variable-stream.h"

NS_LOG_COMPONENT_DEFINE("ConsumerNode");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED(ConsumerNode);

// register NS-3 type
TypeId
ConsumerNode::GetTypeId()
{
  static TypeId tid = TypeId("ConsumerNode").SetParent<ndn::App>().AddConstructor<ConsumerNode>();
  return tid;
}

// Processing upon start of the application
void
ConsumerNode::StartApplication()
{
  // initialize ndn::App
  ndn::App::StartApplication();

  // Add entry to FIB
  ndn::FibHelper::AddRoute(GetNode(), "/a/b/c/d", m_face, 1);

  // Schedule send of first interest
  Simulator::Schedule(Seconds(1.0), &ConsumerNode::SendInterest, this);
}

// Processing when application is stopped
void
ConsumerNode::StopApplication()
{
  // cleanup ndn::App
  ndn::App::StopApplication();
}

void
ConsumerNode::SendInterest()
{
  /////////////////////////////////////
  // Sending one Interest packet out //
  /////////////////////////////////////

  // Create and configure ndn::Interest
  auto interest = std::make_shared<ndn::Interest>("/a/b/c/d");
  Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
  interest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
  interest->setInterestLifetime(ndn::time::seconds(5));

  NS_LOG_DEBUG("Sending Interest packet for " << *interest);

  // Call trace (for logging purposes)
  m_transmittedInterests(interest, this, m_face);

  m_appLink->onReceiveInterest(*interest);
}

// Callback that will be called when Interest arrives
void
ConsumerNode::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest);

  NS_LOG_DEBUG("Received Interest packet for " << interest->getName());

  // Note that Interests send out by the app will not be sent back to the app !

//  auto data = std::make_shared<ndn::Data>(interest->getName());
//  data->setFreshnessPeriod(ndn::time::milliseconds(1000));
//  data->setContent(std::make_shared< ::ndn::Buffer>(1024));
//  ndn::StackHelper::getKeyChain().sign(*data);
//
//  NS_LOG_DEBUG("Sending Data packet for " << data->getName());
//
//  // Call trace (for logging purposes)
//  m_transmittedDatas(data, this, m_face);
//
//  m_appLink->onReceiveData(*data);
}

// Callback that will be called when Data arrives
void
ConsumerNode::OnData(std::shared_ptr<const ndn::Data> data)
{
  NS_LOG_DEBUG("Receiving Data packet for " << data->getName());

  std::cout << "DATA received for name " << data->getName() << std::endl;
}


} // namespace ns3

