/**********************************************************************/
/*! \file  Driver-main.cpp
 * \author Seth Peterson
 * \date   2020-09-08
 * \brief
 *     Driver file, creates interactions with command line.
 *     Allows for usage of the calculator.
 */
/**********************************************************************/
#include "InvestmentCalculator.h"
#include <string> //For stod
#include <cstdio> //For printf
#include <stdexcept> //For exception handling when given bad input
#include <jsoncpp/json/json.h> //Needed to parse Data.json
#include <fstream>  //Needed to read Data.json

void TestCalculator(double Capital, double Interest, double Contribution, double Years)
{
  InvestmentCalculator ic = InvestmentCalculator(Capital, Interest, Contribution);
  ic.PredictGrowth(Years);
}

void TestData()
{
  int StartingYear = 38;
  double StartMoney = 16000.00;
  double InterestGain = 1.07;
  double Addition = 5000.00;

  InvestmentData id = InvestmentData(StartingYear);
  id.Append(StartMoney,InterestGain,Addition);
  id.PrintContents();
}

void TestHistory()
{
  double InitialMoney = 16000.00;
  double Interest = 1.07;
  double Contribution = 5000.00;
  int Years = 38;

  InvestmentCalculator ic = InvestmentCalculator(InitialMoney, Interest, Contribution);
  ic.PredictGrowth(Years);
  ic.PrintHistory();
}

int main(int argc, char* argv[])
{
  /*
  TestData();
  return 1;
  */

  TestHistory();
  return 1;
  /**************BELOW IS DEFAULT FUNCTIONALITY************/

  double initialmoney = 0.00;
  double interest = 0.00;
  double contribution = 0.00;
  int years = 0;

  //Client gave inputs for each variable.
  if (argc == 5 )
  {
    try
    {
      InitialMoney = std::stod(argv[1]);
      Interest = std::stod(argv[2]);
      Contribution = std::stod(argv[3]);
      Years = std::stoi(argv[4]);
    }
    catch (std::invalid_argument const &e)
    {
      printf("Bad input: std::invalid_argument thrown");
    }
    catch (std::out_of_range const &e)
    {
      printf("Number overflow: std::out_of_range thrown");
    }
  }
  // Check if client gave data file, or if they're asking for help.
  else if (argc == 2)
  {
    std::string arg1(argv[1]);
    /* Check for help request */
    if ( arg1 == "help" )
    {
      PrintHelp();
    }
    /* Check for text file */
    else
    {
    }
    return 1;
  }
  //User gave only program name as an argument.
  // Check for Input.json
  else if (argc == 1)
  {
    Json::Value inputs;
    std::ifstream input_file("Input.json", std::ifstream::binary);
    input_file >> inputs;

    InitialMoney << input_file["Capital"];
    Interest << input_file["Interest"];
    Contribution << input_file["Contribution"];
    Years << input_file["Years"];

    InvestmentCalculator ic = InvestmentCalculator(InitialMoney, Interest, Contribution);
    ic.PredictGrowth(Years);
    return 1;
  } else { return 1; }
}

