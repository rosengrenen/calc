#pragma once

#include <exception>
#include <string>

class CalculatorException : public std::exception
{
public:
  CalculatorException(const char* message) :
    message(message)
  { }

  CalculatorException(const std::string& message) :
    message(message)
  { }

  virtual ~CalculatorException() noexcept
  { }

  virtual const char* what() const noexcept
  {
    return message.c_str();
  }

protected:
  /** Error message.
  */
  std::string message;
};