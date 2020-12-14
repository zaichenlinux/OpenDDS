#pragma once

#include "Action.h"
#include "ace/Proactor.h"
#include "BenchTypeSupportImpl.h"

#include <random>

namespace Bench {

class WriteAction : public Action {
public:
  WriteAction(ACE_Proactor& proactor);

  bool init(const ActionConfig& config, ActionReport& report, Builder::ReaderMap& readers,
    Builder::WriterMap& writers, const Builder::ContentFilteredTopicMap& cft_map) override;

  void start() override;
  void stop() override;

  void do_write();

protected:
  std::mutex mutex_;
  ACE_Proactor& proactor_;
  bool started_, stopped_, manual_rescheduling_;
  DataDataWriter_var data_dw_;
  Data data_;
  ACE_Time_Value write_period_;
  ACE_Time_Value last_scheduled_time_;
  size_t max_count_;
  size_t new_key_count_;
  uint64_t new_key_probability_;
  DDS::InstanceHandle_t instance_;
  std::shared_ptr<ACE_Handler> handler_;
  std::mt19937_64 mt_;
  size_t filter_class_start_value_;
  size_t filter_class_stop_value_;
  size_t filter_class_increment_;
};

}
