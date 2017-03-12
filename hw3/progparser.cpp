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
  if(parse.parse_func_seq())
    cout << "CORRECT" << endl;
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
  else if(m_tokens[0] == "OR")
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
    {
      m_tokens.erase(m_tokens.begin());
      return true;
    }
  }
  else if(m_tokens[0] == "AND")
  {
    m_tokens.erase(m_tokens.begin());
    return true;
  }
  return false;
}

bool ProgotronParser::parse_fact()
{
  if(parse_int() || parse_dec() || parse_id() || parse_str())
  {
    return true;
  }
  else if(m_tokens[0] == "(")
  {
    m_tokens.erase(m_tokens.begin());
    if(parse_exp())
    {
      if(m_tokens[0] == ")")
      {
        m_tokens.erase(m_tokens.begin());
        return true;
      }
    }
    return false; 
  }
  else if(m_tokens[0] == "~")
  {
    m_tokens.erase(m_tokens.begin());
    if(parse_fact())
      return true;
  }
  return false;
}

bool ProgotronParser::parse_term()
{
  bool res = false;
  if(parse_fact())
  {
    res = true;
    while(m_tokens[0] == "*" || m_tokens[0] == "/" || m_tokens[0] == "AND")
    {
      parse_mul_op();
      if(parse_fact())
      {}
      else
      {
        cout << "Stopping because of " << m_tokens[0] << endl;
        res = false;
        break;
      }
    }
  }
  return res;
}

bool ProgotronParser::parse_sim_exp()
{
  bool res = false;
  if(parse_term())
  {
    res = true;
    while(m_tokens[0] == "+" || m_tokens[0] == "-" || m_tokens[0] == "&" || m_tokens[0] == "OR")
    {
      parse_add_op();
      if(parse_term())
      {}
      else
      {
        res = false;
        break;
      }
    }
  }
  return res;
}

bool ProgotronParser::parse_exp()
{
  bool res = false;
  if(parse_sim_exp())
  {
    res = true;
    if(parse_rel())
    {
      if(parse_sim_exp())
      {}
      else
        res = false;
    }
  }
  return res;
}

bool ProgotronParser::parse_assign()
{
  if(parse_id())
  {
    if(m_tokens[0] == ":=")
    {
      m_tokens.erase(m_tokens.begin());
      if(parse_exp())
      {
        if(m_tokens[0] == "!")
        {
          m_tokens.erase(m_tokens.begin());
          return true;
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_print()
{
  if(m_tokens[0] == "PRINT")
  {
    m_tokens.erase(m_tokens.begin());
    if(m_tokens[0] == "(")
    {
      m_tokens.erase(m_tokens.begin());
      if(parse_exp())
      {
        if(m_tokens[0] == ")")
        {
          m_tokens.erase(m_tokens.begin());
          if(m_tokens[0] == "!")
          {
            m_tokens.erase(m_tokens.begin());
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_ret()
{
  if(m_tokens[0] == "RET")
  {
    m_tokens.erase(m_tokens.begin());
    if(parse_id())
    {
      if(m_tokens[0] == "!")
      {
        m_tokens.erase(m_tokens.begin());
        return true;
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_if()
{
  if(m_tokens[0] == "IF")
  {
    m_tokens.erase(m_tokens.begin());
    if(m_tokens[0] == "(")
    {
      m_tokens.erase(m_tokens.begin());
      if(parse_exp())
      {
        if(m_tokens[0] == ")")
        {
          m_tokens.erase(m_tokens.begin());
          if(parse_statement_seq())
          {
            if(m_tokens[0] == "ELSE")
            {
              m_tokens.erase(m_tokens.begin());
              if(parse_statement_seq())
              {
                if(m_tokens[0] == "FI")
                {
                  m_tokens.erase(m_tokens.begin());
                  return true;
                }
              }
            }
            else if(m_tokens[0] == "FI")
            {
              m_tokens.erase(m_tokens.begin());
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_loop()
{
  if(m_tokens[0] == "LOOP")
  {
    if(m_tokens[0] == "(")
    {
      m_tokens.erase(m_tokens.begin());
      if(parse_exp())
      {
        if(m_tokens[0] == ")")
        {
          m_tokens.erase(m_tokens.begin());
          if(parse_statement_seq())
          {
            if(m_tokens[0] == "POOL")
            {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_statement()
{
  if(parse_assign() || parse_print() || parse_ret() || parse_if() || parse_loop())
  {
    return true;
  }
  return false;
}

bool ProgotronParser::parse_statement_seq()
{
  bool res = false;
  if(parse_statement())
  {
    res = true;
    while(parse_statement())
    {}
  }
  return res;
}

bool ProgotronParser::parse_param_seq()
{
  bool res = false;
  if(parse_id())
  {
    res = true;
    while(m_tokens[0] == ",")
    {
      m_tokens.erase(m_tokens.begin());
      if(parse_id())
      {}
      else
      {
        res = false;
        break;
      }
    }
  }
  return res;
}

bool ProgotronParser::parse_func_dec()
{
  if(m_tokens[0] == "FUNC")
  {
    m_tokens.erase(m_tokens.begin());
    if(parse_id())
    {
      if(m_tokens[0] == "(")
      {
        m_tokens.erase(m_tokens.begin());
        parse_param_seq();
        if(m_tokens[0] == ")")
        {
          m_tokens.erase(m_tokens.begin());
          if(m_tokens[0] == "BEGIN")
          {
            if(parse_statement_seq())
            {
              if(m_tokens[0] == "END.")
              {
                m_tokens.erase(m_tokens.begin());
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}

bool ProgotronParser::parse_func_seq()
{
  bool res = false;
  
  if(parse_func_dec())
  {
    res = true;
    while(parse_func_dec())
    { }
  }
  return res;
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
