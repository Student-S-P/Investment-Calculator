/**********************************************************************/
/*! \file  InvestmentCalculator.h
 * \author Seth Peterson
 * \date   2020-09-07
 * \brief
 */
/**********************************************************************/

class InvestmentData
{
  private:
    struct YearlyData
    {
      double AnnualTotal;
      double AnnualGrowth;
      double AnnualInterestEarnings;
      double AnnualContributions;

      YearlyData();
      YearlyData(double Total, double Growth, double Interest, double Contribution);
    };

    YearlyData* Portfolio_;
    int CurrentIndex_ = 0;
    int PortfolioSize_ = 0;
    int StartYear_ = 0; 

    void Resize();
  public:
    InvestmentData();
    void Append(double Total, double Growth, double InterestEarnings, double Contributions);
    void Get(int StartIndex=0, int EndIndex=0);
};
