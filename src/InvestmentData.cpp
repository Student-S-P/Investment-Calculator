/**********************************************************************/
/*! \file  InvestmentCalculator.cpp
 * \author Seth Peterson
 * \date   2020-09-07
 * \brief
 */
/**********************************************************************/
#include "InvestmentData.h"
#include <cstdio> //For printf
#include <cassert> //for assert on destructor

/*! \brief
 * Default constructor.
 * \param 
 */
InvestmentData::YearlyData::YearlyData() :
  AnnualTotal(0), AnnualInterestEarnings(0), AnnualContributions(0)
{
}
/*! \brief
 * Constructs the object and initializes its fields.
 * \param 
 */
InvestmentData::YearlyData::YearlyData(double Total, double Interest, double Contribution) :
  AnnualTotal(Total), AnnualInterestEarnings(Interest), AnnualContributions(Contribution)
{
}

//Default constructor
InvestmentData::InvestmentData() :
  Portfolio_(nullptr), CurrentIndex_(0), PortfolioSize_(0), StartYear_(0)
{
}

//Specific constructor - allows for a start year.
InvestmentData::InvestmentData(int StartYear) :
  Portfolio_(nullptr), CurrentIndex_(0), PortfolioSize_(0), StartYear_(StartYear)
{
}
//Destructor makes sure that the data in portfolio is released
InvestmentData::~InvestmentData()
{
  if (Portfolio_ != nullptr)
  {
    delete Portfolio_;
    Portfolio_ = nullptr;
    assert(!Portfolio_);
  }
}

void InvestmentData::Append(double Total, double InterestEarnings, double Contributions)
{
  //Add more storage space if we're already full.
  if (CurrentIndex_ == PortfolioSize_)
  {
    Resize();
  }
  Portfolio_[CurrentIndex_++] = YearlyData(Total,InterestEarnings,Contributions);

}

void InvestmentData::Resize()
{
  if (PortfolioSize_ == 0)
  {
    //Create an array of size 8 once there's something to store.
    Portfolio_ = new YearlyData [1];
    PortfolioSize_ = 1;
  } else {
    //Double the size of the container as needed.
    YearlyData* replacement = new YearlyData[PortfolioSize_*2];
    for (int i=0; i<PortfolioSize_; ++i)
    {
      replacement[i].AnnualTotal = Portfolio_[i].AnnualTotal;
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

/* Print all the arrays as a series of rows. NOTE: IT IGNORES EMPTY SPACES
 * AT THE END! */
void InvestmentData::PrintContents()
{
  for(int i=0; i<CurrentIndex_; ++i)
  {
    YearlyData abrv = Portfolio_[i];
    printf("%5i : %5.2f || %5.2f || %5.2f || %5.2f\n",StartYear_+i,abrv.AnnualTotal,abrv.AnnualInterestEarnings+abrv.AnnualContributions,abrv.AnnualInterestEarnings,abrv.AnnualContributions);
  }
}


