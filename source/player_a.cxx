#include "player_type.hxx"

#include <boost/config.hpp>

namespace usagi::poker
{
  using namespace std;
  
  class player_a: public player_type
  {
      auto get_name() -> std::string override
      {
        return "Player-A/Nothing-man";
      }
      
      auto pay_ante( const size_t, const size_t minimum, const size_t ) -> size_t override
      {
        return minimum;
      }
      
      auto discard_cards( const cards_type ) -> cards_type override
      {
        return { };
      }
  };
  
  extern "C" BOOST_SYMBOL_EXPORT player_a player;
  player_a player;
}
