/**********************************************************************/
/*! \file  InvestmentCalculator
 * \author Seth Peterson
 * \date   2019-10-16
 * \brief
 *     This file contains a class implementation that produces a timeline
 *     showing the progression of an investment on a yearly basis.
 */
/**********************************************************************/
#include "InvestmentCalculator.h"
#include <cstdio> //For printf
#include <string> //For stod
#include <stdexcept> //For exception handling when given bad input

  /*! \brief
   * Constructs the object and initializes its fields.
   * \param InitialCapital
   * Amount of money invested in year 0 to be compounded in the result for year 1.
   * \param InterestRate
   * Growth rate of the capital from last year.
   * \param YearlyContribution
   * Flat amount added to the total invested at the end of a year. Not affected
   * by interest the year it is added.
   */
InvestmentCalculator::InvestmentCalculator(double InitialCapital, double InterestRate, double YearlyContribution) :
    InitialCapital_(InitialCapital), InterestRate_(InterestRate), YearlyContribution_(YearlyContribution)
{
}

/*! \brief
 * Simulates the growth of an investment without changing the internal variables.
 * \param YearsToPredict
 * How many lines to display in the spreadsheet.
 * \return
 * Size of the investment after the years have passed.
 */
double InvestmentCalculator::PredictGrowth(unsigned YearsToPredict)
{
  unsigned current_year = 1;
  double Capital = InitialCapital_;
  double CumulativeInterest = 0.0;
  double CumulativeContribution = 0.0;

  PrintInitialInvestment();
  PrintInvestmentLabelRow();
  while(current_year <= YearsToPredict)
  {
    double Total = CalculateNextTotal(Capital, InterestRate_, YearlyContribution_);
    double Growth = Total - Capital;
    double InterestGrowth = Growth - YearlyContribution_;

    CumulativeInterest += InterestGrowth;
    CumulativeContribution += YearlyContribution_;

    PrintInvestmentInformation(current_year, Total, InterestGrowth, YearlyContribution_);

    Capital = Total;
    ++current_year;
  }
  PrintInvestmentCumulativeRow(Capital, CumulativeInterest, CumulativeContribution);
  return Capital;
}

/*! \brief
 * Prints out instance data into the console.
 */
void InvestmentCalculator::PrintInitialInvestment()
{
  printf("Initial Capital: %5.2f\nInterest Rate: %3.5f\n",InitialCapital_,InterestRate_-1.0);
}

/*! \brief
 * Prints the total amounts put into the fund by the owner, as well as interest growth.
 * \param Capital
 * Initial contribution
 * \param InterestGrowth
 * Total earnings from interest growth.
 * \param Contribution
 * Sum of yearly contribution amounts.
 */
void InvestmentCalculator::PrintInvestmentCumulativeRow(double Capital, double InterestGrowth, double Contribution)
{
  printf("--------------------------------------------------------");
  PrintInvestmentLabelRow();
  printf("%5.2f || %5.2f || %5.2f || %5.2f\n",Capital,InterestGrowth+Contribution,InterestGrowth,Contribution);
}

/*! \brief
 * Sets capital to a new value.
 * \param NewCapital
 * Double passed in to replace stored variable.
 */
void InvestmentCalculator::SetInitialCapital(double NewCapital)
{
  if (NewCapital < 0)
  {
    throw std::invalid_argument("Capital must be a positive value.");
  }
  InitialCapital_ = NewCapital;
}
/*! \brief
 * Sets interest rate to a new value.
 * \param NewRate
 * Double passed in to replace stored variable.
 */
void InvestmentCalculator::SetInterestRate(double NewRate)
{
  if (NewRate < 0 || NewRate > 0.5)
  {
    throw std::invalid_argument("Interest rate must be within 0-0.5 range.");
  }
  InterestRate_ = NewRate;
}
/*! \brief
 * Sets yearly contribution to a new value.
 * \param NewContribution
 * Double passed in to replace stored variable.
 */
void InvestmentCalculator::SetYearlyContribution(double NewContribution)
{
  /* There is intentionally no checking here, as people may withdraw money yearly */
  YearlyContribution_ = NewContribution;
}
/*! \brief
 * Exposes the current value of capital.
 * \return
 * Copy of stored value.
 */
double InvestmentCalculator::GetInitialCapital()
{
  return InitialCapital_;
}

/*! \brief
 * Exposes the current value of interest rate.
 * \return
 * Copy of stored value.
 */
double InvestmentCalculator::GetInterestRate()
{
  return InterestRate_;
}
/*! \brief
 * Exposes the current value of yearly contribution.
 * \return
 * Copy of stored value.
 */
double InvestmentCalculator::GetYearlyContribution()
{
  return YearlyContribution_;
}

/*! \brief
 * Calculates the new total for invested capital (year 2).
 * \param InitialCapital
 * Investment stored in the account in previous year.
 * \param InterestRate
 * Amount to increase the initialcapital by.
 * \param YearlyContribution
 * Flat increase to the final resulting total.
 * \return
 * 
 */
double CalculateNextTotal(double InitialCapital, double InterestRate, double YearlyContribution)
{
  return InterestRate * InitialCapital + YearlyContribution;
}

void PrintInvestmentLabelRow()
{
  printf("Year |   Total  | Growth | Interest | Contribution\n");
}
void PrintInvestmentInformation(int year, double Total, double InterestGrowth, double Contribution)
{
  printf("%5i: %5.2f || %5.2f || %5.2f || %5.2f\n",year,Total,InterestGrowth+Contribution,InterestGrowth,Contribution);
}


int main(int argc, char* argv[])
{
  //If no arguments are given use the default here.
  double InitialMoney = 16000.00;
  double Interest = 1.07;
  double Contribution = 5000.00;
  int Years = 38;

  //Client gave command line arguments.
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
  //Client gave location to a data file
  else if (argc == 1)
  {
  }
  else { return 1; }

  InvestmentCalculator ic = InvestmentCalculator(InitialMoney, Interest, Contribution);
  ic.PredictGrowth(Years);
  return 1;
}
