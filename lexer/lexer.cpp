
#include "lexer.h"
#include <locale>
#include <boost/algorithm/string.hpp>
#include <utility>
#include "lexer_static_data.h"
using std::vector;
using std::string;
using std::map;
using std::pair;
using std::make_pair;
using std::istream;
using std::ostream;
using std::unique_ptr;

bool is_keyword(const string& word);
bool is_legal_in_identifier(char c);
const Token* const get_token_from_word(const string& word);
const Token* const get_next_token(char c);
string to_string(const Tokens type);

/*------------------------------------------------
  Token Methods
  ----------------------------------------------*/

// Constructs a token of the given type
Token::Token(Tokens type) : type_(type) {}

// Returns the type of the token
const Tokens Token::type() const{
  return type_;
}

// Sends a string representation of the token to the given output stream
ostream& operator<< (ostream& output, const Token& toke) {
  const string toke_to_string = toke.toString();
  return output << toke_to_string;
}

// Returns a string representation of the token
const string Token::toString() const{
  // keywords : simply look up the string in the keywords list
  if (type_ <= Tokens::PERCENT) {
    return boost::algorithm::to_upper_copy(kws[type_].first);
  }
  // Symbols: return a string representation of the token
  switch (type_) {
  case STAR:
    return "STAR";
  case QUOTE:
    return "QUOTE";
  case SEMICOLON:
    return "SEMICOLON";
  case EQUAL:
    return "EQUAL";
  case NEQUAL:
    return "NEQUAL";
  case GTHAN:
    return "GTHAN";
  case LTHAN:
    return "LTHAN";
  case GEQ:
    return "GEQ";
  case LEQ:
    return "LEQ";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case COMMA:
    return "COMMA";
  case UNDERSCORE:
    return "UNDERSCORE";
  case PERCENT_SIGN:
    return "PERCENT_SIGN";
  case PLUS:
    return "PLUS";
  default:
    return "Error: unrecognized type";
  }
}

/*------------------------------------------------
  Identifier Methods
  -----------------------------------------------*/

// Returns the name of the identifier
const string& Identifier::name() const{
  return name_;
}

// constructs a new identifier using the given name. Assumes that name does not
// refer to a keyword
Identifier::Identifier(const string& name) : name_(name), Token(Tokens::IDENTIFIER) {
  assert(!is_keyword(name));  
}

// Returns a string representation of the identifier in the form
// "Identifier(<name_>)"
const string Identifier::toString() const {
  return "Identifier(" + name_ +")";
}


/*-----------------------------------------------
  Error methods
  ---------------------------------------------*/

// Constructs a new error token with the given message
Error::Error(const string& error) : error_(error) , Token(Tokens::ERROR) {}

// returns the error message associated with the token
const string& Error::error() const{
  return error_;
}

// Returns a string representation of the error of the form
// "Error( <error_message>)"
const string Error::toString() const {
  return "Error("+ error_ +")";
}



/*-------------------------------------------------------------
  Utility functions
  -----------------------------------------------------------*/

  // Tokenizes the command into a vector of the above tokens.
void tokenize_command(const string& command,
		      vector<unique_ptr<const Token>>& result) {  
    for ( auto it = command.cbegin(); it < command.cend(); ++it) {
      // Skip over whitespace
      if (!std::isspace(static_cast<unsigned char> (*it))) {
	const Token* new_token;
	if (std::isalpha(*it)) {
	  // Parse the next keyword
	  auto curr = it;
	  while (is_legal_in_identifier(*curr)) {
	    ++curr;
	  }
	  string word (it, curr);
	  new_token = get_token_from_word(word);
	  it = curr - 1;
	} else {
	  switch (*it) {
	  case '<':
	    // Three special cases: either this is a not equal sign, a less than
	    // or equal sign, or a less than sign.
	    if (it + 1 != command.cend()) {
	      switch (*(it + 1)) {
	      case '>':
	      new_token = new Token(Tokens::NEQUAL);
	      ++it;
	      break;
	      case '=':
		new_token = new Token(Tokens::LEQ);
	      ++it;
	      break;
	      default:
		new_token = new Token(Tokens::LTHAN);
		break;
	    }
	    } else {
	      new_token = new Token(Tokens::LTHAN);
	    }
	    break;
	  case '>':
	    if (it+1 != command.cend() && (*(it + 1)) == '=') {
	      new_token = new Token(Tokens::GEQ);
	      ++it;
	    } else {
	      new_token = new Token(Tokens::GTHAN);
	    }
	    break;
	  default:
	    new_token = get_next_token(*it);
	  }
	}
	result.push_back(std::move(unique_ptr<const Token>(new_token)));
      }
    }
  }
  

  // Returns the next symbolic token given by the character
  // in the stream. Caller is responsible for deleting the token.
  // Does not handle the case of symbols beginning with < or >.
  // Returns an error token in the case of an unrecognizable symbol.
const Token* const get_next_token(char c) {
  switch (c) {
  case '*':
    return new Token(Tokens::STAR);
  case '\"':
    return new Token(Tokens::QUOTE);
  case ';':
    return new Token(Tokens::SEMICOLON);
  case '=':
    return new Token(Tokens::EQUAL);
  case '(':
    return new Token(Tokens::LPAREN);
  case ')':
    return new Token(Tokens::RPAREN);
  case '%':
    return new Token(Tokens::PERCENT_SIGN);
  case ',':
    return new Token(Tokens::COMMA);
  case '+':
    return new Token(Tokens::PLUS);
  case '_':
    return new Token(Tokens::UNDERSCORE);
  default:
    string error_message("Unrecognized Symbol: ");
    return new Error(error_message + c);
  }
}


// Returns true if the word given is a registered SQL keyword
bool is_keyword(const string& word) {
  string lowercase_word = boost::algorithm::to_lower_copy(word);
  return keywords.find(lowercase_word) != keywords.end();
}


// Returns true if the given character is legal in an SQL identifier
bool is_legal_in_identifier(char c) {
  return isalpha(c) || isdigit(c) || c == '_';
}

// Returns a dynamically allocated Token associated with the given
// string. Client is responsible for deleting token after use.
const Token* const get_token_from_word(const string& word) {
  string lowercase_word = boost::algorithm::to_lower_copy(word);
  auto it = keywords.find(lowercase_word);
  if (it == keywords.end()) {
    return new Identifier(word);
  }
  return new Token(it->second);      
}




