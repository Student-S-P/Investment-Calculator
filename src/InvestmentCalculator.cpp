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
#include <stdexcept> //For exception handling when given bad input
#include <cassert> //for assert on destructor

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
    InitialCapital_(InitialCapital), InterestRate_(InterestRate), YearlyContribution_(YearlyContribution), History_(nullptr)
{
}

InvestmentCalculator::~InvestmentCalculator()
{
  if (History_ != nullptr)
  {
    delete History_;
    History_ = nullptr;
    assert(!History_);
  }
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

  //Calculate growth.
  while(current_year <= YearsToPredict)
  {
    double Total = CalculateNextTotal(Capital, InterestRate_, YearlyContribution_);
    double Growth = Total - Capital;
    double InterestGrowth = Growth - YearlyContribution_;

    //Add information to history.
    AddToHistory(Total, InterestGrowth, YearlyContribution_);

    Capital = Total;
    ++current_year;
  }

  return Capital;
}

/*! \brief
 * Adds one year's worth of history to the calculator's data object.
 * 
 */
void InvestmentCalculator::AddToHistory(double Capital, double Interest, double Contribution)
{
  if (History_ == nullptr)
  {
    History_ = new InvestmentData();
  }
  History_->Append(Capital, Interest, Contribution);
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
  printf("-----------------Cumulative------------------------------\n");
  PrintCumulativeLabelRow();
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

/* Prints contents from data object 
 * Can break if History_ is nullptr
 */
void InvestmentCalculator::PrintHistory()
{
  PrintContentsLabelRow();
  History_->PrintContents();
}

/* Gets the cumulative information from History. */
void InvestmentCalculator::PrintCumulativeHistory()
{
  PrintCumulativeLabelRow();
  History_->PrintCumulative();
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

/*! \brief
 *   This function prints the label row at the top of the predictions.
 */

/*! \brief
 *   This function prints the information at each iteration of the
 *   investment prediction.
 */
void PrintInvestmentInformation(int year, double Total, double InterestGrowth, double Contribution)
{
  printf("%5i: %5.2f || %5.2f || %5.2f || %5.2f\n",year,Total,InterestGrowth+Contribution,InterestGrowth,Contribution);
}


/* This function prints useful information in the console window */
void PrintHelp()
{
  printf("You can use this executable two ways:\n  1. Enter nothing and it will try to pull information from Data.txt\n  2. Enter in four arguments (Initial capital, interest, yearly contribution, years to predict)\n");
}

