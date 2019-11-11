#ifndef QTABLE_H
#define QTABLE_H

//#include "ns3/ipv4-address.h"
//#include "ns3/nstime.h"
//#include "ns3/log.h"
//#include "ns3/output-stream-wrapper.h"
//#include "ns3/thomas-configuration.h"
//#include "ns3/simulator.h"
//#include "ns3/make-functional-event.h"
//#include <algorithm>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <cstdlib>
#include "qdecision.h"


namespace ns3 {

class QTableEntry : public QDecisionEntry {
public:
  QTableEntry();
  QTableEntry(Ipv4Address, Time, float c_threshold, float lm_threshold, Ipv4Address myip);
  ~QTableEntry();

  void SetQValue(Time t, bool verbose = false);
  void SetSenderConverged(bool b);
  void Unconverge();
  bool LearnMore();
  bool LearnLess();
  void AddStrike();
  void DeductStrike();
//private:
//  Ipv4Address m_next_hop;
//  Time m_my_estim;
//  uint64_t m_real_observed_delay;
//  uint16_t m_real_observed_loss;
//  float m_coeff_tally;
//  bool m_converged;
//  bool m_sender_converged;
//  bool m_unavailable;
//  bool m_learn_more;
//  bool m_learn_less;
//  float m_conv_threshold;
//  float m_learn_more_threshold;
//  bool m_allow_change_to_learning;
//  bool m_blacklisted;
//  Ipv4Address m_my_ip;
//  int m_number_of_strikes;
};

class QTable : public QDecision {
public:
  QTable();
  QTable(std::vector<Ipv4Address>, Ipv4Address, float, float, float, std::vector<Ipv4Address>, std::string, bool, bool, float);
  ~QTable();

  // true if destination is already in our list of destinations
  bool CheckDestinationKnown(const Ipv4Address& i);

  bool AddDestination(Ipv4Address via, Ipv4Address dst, Time t);

  void Update(Ipv4Address, Ipv4Address, Time, Time, Time);
  //used exclusively in QoS QLearner to converge more easily ...
  uint64_t CalculateNewQValue(Ipv4Address, Ipv4Address, Time, Time, Time);

  QDecisionEntry* GetNextEstim(Ipv4Address);
  QDecisionEntry* GetNextEstim(Ipv4Address,Ipv4Address);
  QDecisionEntry* GetNextEstim(Ipv4Address,Ipv4Address,Ipv4Address);
  QDecisionEntry* GetNextEstimToLearn(Ipv4Address);
  QDecisionEntry* GetRandomEstim(Ipv4Address,bool=false);
  QDecisionEntry* GetEntryByRef(Ipv4Address,Ipv4Address);

  bool AllNeighboursBlacklisted(Ipv4Address);
  std::string PrettyPrint(std::string="");
//  void PrettyPrintToCout() { std::cout << PrettyPrint(); }
  void ToFile(std::string filename);
  void FinalFile();
  void ChangeQValuesFromZero(Ipv4Address dst, Ipv4Address aodv_next_hop) ;
  void MarkNeighbDown(Ipv4Address);
  void AddNeighbour(Ipv4Address);

  bool IsNeighbourAvailable(Ipv4Address);

  bool HasConverged(Ipv4Address dst, bool = false);

  void Unconverge();

  bool LearnLess(Ipv4Address);
  bool LearnMore(Ipv4Address);

  void SetQValueWrapper(Ipv4Address,Ipv4Address,Time);

  //For test...
//  std::vector<Ipv4Address> GetNeighbours() { return m_neighbours; }
//  std::vector<Ipv4Address> GetUnavails() { return m_unavail; }
//  std::vector<QDecisionEntry> GetEstims(Ipv4Address dst) { return m_qtable[dst]; }
private:
  void RemoveNeighbour(Ipv4Address);
  // std::map<Ipv4Address, std::vector<std::pair<Ipv4Address, Time> > > m_qtable;

  // HANS - all of these are defined in qdecision.h
  // std::map<Ipv4Address, std::vector<QDecisionEntry > > m_qtable;

//  Ipv4Address m_nodeip;
//  float m_learningrate;
//  float m_convergence_threshold;
//  float m_gamma;
//  float m_learn_more_threshold;
//  std::string m_output_file_name;
//  std::vector<Ipv4Address> m_neighbours;
//  std::vector<Ipv4Address> m_destinations;
//  std::vector<Ipv4Address> m_unavail;
//  Ptr<OutputStreamWrapper> m_out_stream;
//  bool m_in_test;
//  bool m_print_qtables;
};


} //namespace ns3

#endif /* QTABLE_H */
