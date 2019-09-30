/*
 * FileProducer.h
 *
 *  Created on: Sep 24, 2019
 *      Author: saqib
 */

#ifndef SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_FILEPRODUCER_H_
#define SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_FILEPRODUCER_H_

#include "ns3/ndnSIM/apps/ndn-app.hpp"

namespace ns3 {

class FileProducer : public ndn::App {
public:
  static TypeId
  GetTypeId();

  FileProducer();

  // Receive all Interests but do nothing in response
  void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

protected:
  // inherited from Application base class.
  virtual void
  StartApplication();

  virtual void
  StopApplication();
};
}
#endif /* SRC_NDNSIM_EXAMPLES_NDN_CUSTOM_APPS_FILEPRODUCER_H_ */
