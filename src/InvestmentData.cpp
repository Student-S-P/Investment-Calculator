/**********************************************************************/
/*! \file  InvestmentCalculator.cpp
 * \author Seth Peterson
 * \date   2020-09-07
 * \brief
 */
/**********************************************************************/
#include "InvestmentData.h"


/*! \brief
 * Default constructor.
 * \param 
 */
InvestmentData::YearlyData::YearlyData() :
  AnnualTotal(0), AnnualGrowth(0), AnnualInterestEarnings(0), AnnualContributions(0)
{
}
/*! \brief
 * Constructs the object and initializes its fields.
 * \param 
 */
InvestmentData::YearlyData::YearlyData(double Total, double Growth, double Interest, double Contribution) :
  AnnualTotal(Total), AnnualGrowth(Growth), AnnualInterestEarnings(Interest), AnnualContributions(Contribution)
{
}

void InvestmentData::Append(double Total, double Growth, double InterestEarnings, double Contributions)
{
  //Add more storage space if we're already full.
  if (CurrentIndex_ == PortfolioSize_)
  {
    Resize();
  }
  Portfolio_[CurrentIndex_++] = YearlyData(Total,Growth,InterestEarnings, Contributions);

}

void InvestmentData::Resize()
{
  if (PortfolioSize_ == 0)
  {
    //Create an array of size 8 once there's something to store.
    Portfolio_ = new YearlyData [8];
    PortfolioSize_ = 8;
  } else {
    //Double the size of the container as needed.
    YearlyData* replacement = new YearlyData[PortfolioSize_*2];
    for (int i=0; i<PortfolioSize_; ++i)
    {
      replacement[i].AnnualTotal = Portfolio_[i].AnnualTotal;
      replacement[i].AnnualGrowth = Portfolio_[i].AnnualGrowth;
      replacement[i].AnnualInterestEarnings = Portfolio_[i].AnnualInterestEarnings;
      replacement[i].AnnualContributions = Portfolio_[i].AnnualContributions;
    }
    //Get rid of duplicate data.
    delete Portfolio_;
    //Assign the data where it needs to go.
    Portfolio_ = replacement;
    PortfolioSize_ *= 2;
  }
}
