// William Thurman        3/9/17
#include<string>
#include<iostream>
#include<vector>

using namespace std;

class ProgotronParser
{
  public:
    vector<string> m_tokens;
    const static string keywords[];
    
    ProgotronParser()
    {
      get_tokens();
    }
		
    void get_tokens();
    void skip_whitespace();
    
    bool is_keyword(const string& val);
		
    bool parse_int(); 
    bool parse_dec();
    bool parse_str();
    bool parse_id();
    
    bool parse_rel();    // Relation :=   < | > | = | #  
    bool parse_add_op(); // AddOperator :=   + | - | OR | &
    bool parse_mul_op(); // MulOperator :=   * | / | AND
		
    bool parse_exp();    // Expression := SimpleExpression [ Relation SimpleExpression ]
    bool parse_sim_exp();// SimpleExpression := Term { AddOperator Term }
    bool parse_term();   // Term := Factor { MulOperator Factor }
    bool parse_fact();   // Factor :=  integer | decimal | string | identifier | ( Expression ) | ~ Factor

    bool parse_assign(); // Assignment := identifier := Expression !
    bool parse_print();  // PrintStatement := PRINT ( Expression )!
    bool parse_ret();    // RetStatement := RET identifier !
    bool parse_if();     // IfStatement := IF ( Expression ) StatementSequence [ ELSE StatementSequence ] FI
    bool parse_loop();   // LoopStatement := LOOP ( Expression ) StatementSequence POOL

    bool parse_statement();     // Statement := Assignment | PrintStatement | RetStatement | IfStatement | LoopStatement
    bool parse_statement_seq(); // StatementSequence := Statement { Statement }

    bool parse_param_seq(); // ParamSequence :=  identifier  { , identifier }
    bool parse_func_dec();  // FunctionDeclaration := FUNC identifier ( [ ParamSequence ] ) BEGIN StatementSequence END.

    bool parse_func_seq();  // FunctionSequence := FunctionDeclaration { FunctionDeclaration }
};

int main()
{
  ProgotronParser parse;
  if(parse.parse_int())
    cout << "ID" << endl;
  cout << endl;
  return 0;
}

const string ProgotronParser::keywords[] = {":=", "+", "-" , "*", "OR", "AND",
                                            "~", "<", ">", "(", ")", "=", "#",
                                            "&", "!", "PRINT", "IF", "ELSE",
                                            "FI", "LOOP", "POOL", "RET", "BEGIN",
                                            "END", "/"};

bool ProgotronParser::is_keyword(const string& s)
{
  for(int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
  {
    if(s == keywords[i])
      return true;
  }
  return false;
}

bool ProgotronParser::parse_int()
{
  int i = 0;
  if(m_tokens[0][i] == '+' || m_tokens[0][i] == '-')
  {
    i++;
  }
  if(isdigit(m_tokens[0][i]))
  {
     
    while(isdigit(m_tokens[0][i]) && i < m_tokens[0].length())
      i++;

    if(i == m_tokens[0].length())
    {
      m_tokens.erase(m_tokens.begin());
      return true;
    }
  }
  return false;
}

bool ProgotronParser::parse_dec()
{
  int i = 0;
  if(m_tokens[0][i] == '+' || m_tokens[0][i] == '-')
  {
    i++;
  }
  if(isdigit(m_tokens[0][i]))
  {
     
    while(isdigit(m_tokens[0][i]) && i < m_tokens[0].length())
      i++;
    
    if(m_tokens[0][i] == '.')
    {
      i++;
      while(isdigit(m_tokens[0][i]) && i < m_tokens[0].length())
        i++;
      if(i == m_tokens[0].length())
      {
        m_tokens.erase(m_tokens.begin());
        return true;
      }
    }
  }
  return false;
  
}

bool ProgotronParser::parse_str()
{
  int i = 0;
  if(m_tokens[0][i] == '"')
  {
    i++;
    
    if(!isspace(m_tokens[0][i]))
    {
      while(m_tokens[0][i] != '"')
      {
        i++;
        if(isspace(m_tokens[0][i]))
          return false;
        
        
      }
      if(m_tokens[0][i] == '"')
        i++;
      
      if(i == m_tokens[0].length())
      {
        m_tokens.erase(m_tokens.begin());
        return true;
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_id()
{
  int i = 0;
  if(isalpha(m_tokens[0][i]))
  {
    i++;
    
    
    if(isalnum(m_tokens[0][i]))
    {
      while(isalnum(m_tokens[0][i]))
      {
        i++;
        
      }
      
      if(i == m_tokens[0].length())
      {
        if(!is_keyword(m_tokens[0]))
        {
          m_tokens.erase(m_tokens.begin());
          return true;
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_rel()
{
  int i = 0;
  if(m_tokens[0][i] == '<' || m_tokens[0][i] == '>' || m_tokens[0][i] == '=' || m_tokens[0][i] == '#')
  {
    i++;
    if(i == m_tokens[0].length())
    {
      m_tokens.erase(m_tokens.begin());
      return true;
    }
  }
  return false;
}

bool ProgotronParser::parse_add_op()
{
  int i = 0;
  if(m_tokens[0][i] == '+' || m_tokens[0][i] == '-' || m_tokens[0][i] == '&')
  {
    i++;
    if( i == m_tokens[0].length())
    {
      m_tokens.erase(m_tokens.begin());
      return true;
    }
  }
  else if(m_tokens[0] == 'OR')
  {
    m_tokens.erase(m_tokens.begin());
    return true;
  }
  return false;
}

bool ProgotronParser::parse_mul_op()
{
  int i = 0;
  if(m_tokens[0][i] == '*' || m_tokens[0][i] == '/')
  {
    i++;
    if(i == m_tokens[0].length())
      return true;
  }
  else if(m_tokens[0] == "AND")
  {
    m_tokens.erase(m_tokens.begin());
    return true;
  }
  return false;
}

void ProgotronParser::get_tokens()
{
  string token;
  while(cin >> token)
  {
    cout << token;
    m_tokens.push_back(token);
  }
}


// bool ProgotronParser::
