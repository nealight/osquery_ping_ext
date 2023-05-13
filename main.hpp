#include <osquery/core/system.h>
#include <osquery/sdk/sdk.h>
#include <osquery/sql/dynamic_table_row.h>

using namespace osquery;

class PingTable : public TablePlugin {
 private:
  TableColumns columns() const;
  TableRows generate(QueryContext& request);

};

