#include "player_type.hxx"

#include <boost/config.hpp>

#include <algorithm>

namespace usagi::poker
{
  using namespace std;
  
  class player_b: public player_type
  {
      auto get_name() -> std::string override
      {
        return "Player-B/Heart-man";
      }
      
      auto pay_ante( const size_t my_chips, const size_t minimum, const size_t maximum ) -> size_t override
      {
        // いのちだいじに
        if ( my_chips < 100 )
          return 1;
        // みんながんばれ
        else if ( my_chips < 1000 )
          return ( minimum + maximum ) / 2;
        // ガンガンいこうぜ
        return maximum;
      }
      
      auto discard_cards( const cards_type drew_cards ) -> cards_type override
      {
        // ラブ・ハート・アルゴリズム
        cards_type discards;
        
        copy_if
        ( drew_cards.cbegin()
        , drew_cards.cend()
        , back_inserter( discards )
        , []( const auto& card ) { return card.get_suit() != suit_type::heart; }
        );
        
        return discards;
      }
  };
  
  extern "C" BOOST_SYMBOL_EXPORT player_b player;
  player_b player;
}
