#pragma once

#include <lovely/model/model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

namespace lovely {

class custom_model : public model<stock, etf, bool, int> {
protected:
    virtual void initialize_internal() override
    {
        enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
        enroll<etf>({{"tse:vab", {}}});
        enroll<bool>({{"tse:td", true}});
        enroll<int>({{"tse:td", 42}});
    }
};
}  // namespace lovely