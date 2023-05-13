/**
 * Copyright (c) 2014-present, The osquery authors
 *
 * This source code is licensed as defined by the LICENSE file found in the
 * root directory of this source tree.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)
 */


#include <osquery/core/system.h>
#include <osquery/sdk/sdk.h>
#include <osquery/sql/dynamic_table_row.h>
#include "helpers.cpp"

using namespace osquery;

class PingTable : public TablePlugin {
private:
  TableColumns columns() const {
    return {
        std::make_tuple("host", TEXT_TYPE, ColumnOptions::DEFAULT),
        std::make_tuple("latency", TEXT_TYPE, ColumnOptions::DEFAULT),
    };
    }

  TableRows generate(QueryContext& request) {
    TableRows results;

    auto r = make_table_row();
    if (!request.hasConstraint("host")) {
      return results;
    }

    auto host = request.constraints["host"].getAll()[0].expr;
    if (!isValidHost(host)) {
      r["host"] = host;
      r["latency"] = "INVALID HOST";
      results.push_back(std::move(r));
      return results;
    }

    auto ping_query = "ping -c 4 " + host + " | tail -1| awk '{print $4}' | cut -d '/' -f 2";

    std::string latency{};
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    ping_query.append(" 2>&1"); 

    stream = popen(ping_query.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) latency.append(buffer);
        pclose(stream);
    }

    latency.erase(latency.length() - 1);
    r["host"] = host;
    r["latency"] = latency;
    results.push_back(std::move(r));
    return results;
  };
};

REGISTER_EXTERNAL(PingTable, "table", "ping");

int main(int argc, char* argv[]) {
  osquery::Initializer runner(argc, argv, ToolType::EXTENSION);

  auto status = startExtension("ping", "0.0.1");
  if (!status.ok()) {
    LOG(ERROR) << status.getMessage();
    runner.requestShutdown(status.getCode());
  }

  // Finally wait for a signal / interrupt to shutdown.
  runner.waitForShutdown();
  return runner.shutdown(0);
}
