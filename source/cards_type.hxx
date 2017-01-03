#pragma once

#include "card_type.hxx"

#include <vector>
//#include <unordered_set>

namespace usagi::experimental::oh2016
{
  using namespace std;
  
  using cards_type = vector< card_type >;
  //using cards_type = unordered_set< card_type, card_type::hasher >;
}
