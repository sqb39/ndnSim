/*
 * ConsumerNode.h
 *
 *  Created on: Sep 26, 2019
 *      Author: saqib
 */

#ifndef SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_CONSUMERNODE_H_
#define SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_CONSUMERNODE_H_

#include "ns3/ndnSIM/apps/ndn-app.hpp"

namespace ns3 {

class ConsumerNode : public ndn::App {
public:
  // register NS-3 type "CustomApp"
  static TypeId
  GetTypeId();

  // (overridden from ndn::App) Processing upon start of the application
  virtual void
  StartApplication();

  // (overridden from ndn::App) Processing when application is stopped
  virtual void
  StopApplication();

  // (overridden from ndn::App) Callback that will be called when Interest arrives
  virtual void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

  // (overridden from ndn::App) Callback that will be called when Data arrives
  virtual void
  OnData(std::shared_ptr<const ndn::Data> contentObject);

private:
  void
  SendInterest();

};
}
#endif /* SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_CONSUMERNODE_H_ */
