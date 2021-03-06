#pragma once

#include <memory>

#include "envoy/api/api.h"
#include "envoy/common/pure.h"
#include "envoy/common/time.h"
#include "envoy/event/dispatcher.h"
#include "envoy/upstream/cluster_manager.h"

#include "nighthawk/client/benchmark_client.h"
#include "nighthawk/client/options.h"
#include "nighthawk/client/output_formatter.h"
#include "nighthawk/common/platform_util.h"
#include "nighthawk/common/request_source.h"
#include "nighthawk/common/sequencer.h"
#include "nighthawk/common/statistic.h"
#include "nighthawk/common/termination_predicate.h"
#include "nighthawk/common/uri.h"

namespace Nighthawk {
namespace Client {

class BenchmarkClientFactory {
public:
  virtual ~BenchmarkClientFactory() = default;
  virtual BenchmarkClientPtr create(Envoy::Api::Api& api, Envoy::Event::Dispatcher& dispatcher,
                                    Envoy::Stats::Scope& scope,
                                    Envoy::Upstream::ClusterManagerPtr& cluster_manager,
                                    Envoy::Tracing::HttpTracerSharedPtr& http_tracer,
                                    absl::string_view cluster_name,
                                    RequestSource& request_generator) const PURE;
};

class OutputFormatterFactory {
public:
  virtual ~OutputFormatterFactory() = default;
  virtual OutputFormatterPtr
  create(const nighthawk::client::OutputFormat_OutputFormatOptions) const PURE;
};

} // namespace Client
} // namespace Nighthawk
