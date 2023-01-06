#include "types.hpp"

std::string ListValue::inspect() {
    std::string out = "(";
    for(auto *value : m_list){
        out.append(value->inspect());
        out.append(" ");
    }
    out[out.length() - 1] = ')';
    return out;
}