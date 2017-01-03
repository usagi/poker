#include "draw_poker.hxx"

#include <cmdline.h>
#include <boost/dll/import.hpp>

#include <string>

namespace usagi::poker
{
  using namespace std;
  
  auto parse_options
  ( const int count_of_arguments
  , const char* const* const arguments
  ) noexcept -> cmdline::parser
  {
    auto p = cmdline::parser();
    
    p.add< size_t >
    ( "play-count-limit"
    , 'c'
    , "limit of play count"
    , false
    , 1000
    );
    
    p.add< size_t >
    ( "player-initial-chips"
    , 'C'
    , "number of player's chips in initial time"
    , false
    , 100
    );
    
    p.add< std::string >
    ( "player"
    , 'p'
    , "player module name"
    , true
    );
    
    p.add< size_t >
    ( "ante-min"
    , 'a'
    , "minimum ante"
    , false
    , 1
    );
    
    p.add< size_t >
    ( "ante-max"
    , 'A'
    , "maximum ante"
    , false
    , 10
    );
    
    p.add
    ( "no-output-logging"
    , 'n'
    , "no output logging ( [system] and [game] )"
    );
    
    p.add
    ( "version"
    , 'v'
    , "version information"
    );
    
    p.parse_check ( count_of_arguments, const_cast< char** > ( arguments ) );
    
    return p;
  }
}

auto main
( const int count_of_arguments
, const char* const* const arguments
) -> int
{
  using namespace usagi::poker;
  
  const auto& parser = parse_options ( count_of_arguments, arguments );
  
  if ( parser.exist( "version" ) )
  {
    std::cout
      << "draw_poker\n"
      << "  version: 0.0.1" << endl
      ;
    return 0;
  }
  
  draw_poker_type draw_poker;
  
  draw_poker.set_play_count_limit( parser.get< size_t >( "play-count-limit" ) );
  draw_poker.set_player_initial_chips( parser.get< size_t >( "player-initial-chips") );
  draw_poker.set_ante_min( parser.get< size_t >( "ante-min" ) );
  draw_poker.set_ante_max( parser.get< size_t >( "ante-max" ) );
  draw_poker.set_logging( not parser.exist( "no-output-logging" ) );
  
  {
    auto player =
      boost::dll::import< player_type >
      ( boost::filesystem::path( parser.get< std::string >( "player" ) )
      , "player"
      , boost::dll::load_mode::append_decorations
      );
    
    draw_poker.set_player( draw_poker_type::shared_player_type( player.get(), [ player ] ( ... ) mutable { player.reset(); } ) );
  }
  
  draw_poker();
  
  return 0;
}
